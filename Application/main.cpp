#include "entt.hpp"
#include "lua.hpp"
#include "graphics/rayLibTest.hpp"

#include <iostream>
#include <thread>
#include <string>
#include "Scene.hpp"
//#include "windowsThreading.cpp"
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

	luaL_dostring(L, "print('hello from lua')");

	std::thread consoleThread(ConsoleThreadFunction, L);

	//rayLib raylib;
	//raylib.run();

	Scene scene;
	//Scene::lua_openscene(L, &scene);
	
	scene.CreateSystem<PoisonSystem>(15);
	scene.CreateSystem<CleanupSystem>();
	scene.CreateSystem<InfoSystem>();
	scene.CreateSystem<BehaviourSystem>(L);
	luaL_dofile(L, "sceneDemo.lua");
	
	const char* script = "monster.lua";

	int entity = scene.CreateEntity();
	
	luaL_dofile(L, "test.lua");
	
	for (int i = 0; i < 20; i++)
	{
		scene.UpdateSystems(1);
	}

	//rayLib raylib;
	//raylib.run();

	gameloop mazegame;
	mazegame.run(L);

	bool running = true;
	while (!running)
	{
		//Update game
		//Render game
	}

	consoleThread.detach();
	
	return 0;
}