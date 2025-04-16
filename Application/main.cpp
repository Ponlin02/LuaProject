#include <iostream>
#include <thread>
#include <string>
#include <Windows.h>

#include "lua.hpp"
#include "graphics/rayLibTest.hpp"
#include "gameloop/gameloop.hpp"

void DumpError(lua_State* L)
{
	if (lua_gettop(L) && lua_isstring(L, -1))
	{
		std::cout << "Lua error: " << lua_tostring(L, -1) << std::endl;
		lua_pop(L, 1);
	}
}

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

	//rayLib raylib;
	//raylib.run();

	//gameloop mazegame;
	//mazegame.run();

	//Some lua chunks
	std::cout << "[C++] Hello C++!" << std::endl;
	luaL_dostring(L, "print('[Lua] Hello Lua!')");
	//luaL_dostring(L, "dofile('fizzbuzz.lua')");
	lua_pushnumber(L, 3.14159f);
	lua_setglobal(L, "Pi");
	lua_pushnumber(L, 1.41421f);
	lua_setglobal(L, "SqrtOfTwo");
	lua_pushnumber(L, 1.61803f);
	lua_setglobal(L, "Phi");
	lua_pushnumber(L, 2.71828f);
	lua_setglobal(L, "Euler");
	lua_pushnumber(L, 0.56714f);
	lua_setglobal(L, "Omega");
	lua_pushnumber(L, 0.83462f);
	lua_setglobal(L, "Gauss");
	luaL_dofile(L, "ex2.lua");

	bool running = true;
	while (running)
	{
		//Update game
		//Render game
		
		
		//luaL_dostring(L, "dofile('loop.lua')");
	}
	
	return 0;
}