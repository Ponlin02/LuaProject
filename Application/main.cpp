#include "entt.hpp"
#include "lua.hpp"
#include "graphics/rayLibTest.hpp"

#include <iostream>
#include <thread>
#include <string>
#include "Scene.hpp"
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

#include "gameloop/gameloop.hpp"

#include "graphics/rayLibTest.hpp"

void ConsoleThreadFunction(lua_State* L)
{
	std::string input;
	while (GetConsoleWindow())
	{
		std::cout << "> ";
		std::getline(std::cin, input);

		if (luaL_dostring(L, input.c_str()) != LUA_OK)
		{
			DumpError(L);
		}
	}
}

class BehaviourSystem : public System
{
	lua_State* L;
public: 
	BehaviourSystem(lua_State* L) : L(L){}

	bool OnUpdate(entt::registry& registry, float delta) final
	{
		auto view = registry.view<BehaviourComponent>();

		view.each([&](BehaviourComponent& script) {
			lua_rawgeti(L, LUA_REGISTRYINDEX, script.LuaRef);
			lua_getfield(L, -1, "OnUpdate");
			lua_pushvalue(L, -2);
			lua_pushnumber(L, delta);

			if (lua_pcall(L, 2, 0, 0) != LUA_OK) {
				DumpError(L);
			}

			lua_pop(L, 1);
			});

		return false;
	}
};

int main()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	std::thread consoleThread(ConsoleThreadFunction, L);

	Gameloop mazegame;
	mazegame.run(L);

	consoleThread.detach();

	
	return 0;
}