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