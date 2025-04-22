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
	//luaL_dofile(L, "ex2.lua");



	//ex 3
	//std::cout << "Before: " << lua_gettop(L) << std::endl;
	//luaL_dofile(L, "fail.lua");
	//std::cout << "After: " << lua_gettop(L) << std::endl;

	/*lua_pushboolean(L, false);
	lua_pushnil(L);
	lua_pushstring(L, "Hello!");
	lua_pushnumber(L, 3.14f);
	lua_pushvalue(L, -2);*/



	//ex 4
	luaL_dofile(L, "populate.lua");

	//species
	lua_getglobal(L, "dino_species");
	std::cout << lua_tostring(L, 1) << std::endl;
	lua_pop(L, 1);

	//name
	lua_getglobal(L, "dino_name");
	std::cout << lua_tostring(L, 1) << std::endl;
	lua_pop(L, 1);

	//has wings?
	lua_getglobal(L, "dino_wings");
	std::cout << lua_toboolean(L, 1) << std::endl;
	lua_pop(L, 1);

	//noise function
	lua_getglobal(L, "dino_getnoise");

	if (lua_isfunction(L, -1))
	{
		lua_pushnumber(L, 7);
		if (lua_pcall(L, 1, 1, 0) != LUA_OK)
		{
			std::cerr << "Fel vid anrop: " << lua_tostring(L, -1) << std::endl;
		}
		else
		{
			std::cout << "Resultatet blev: " << lua_tostring(L, -1) << std::endl;
		}
		lua_pop(L, 1);
	}
	else 
	{
		std::cout << "'dino_getnoise' is not a function!" << std::endl;
		lua_pop(L, 1);
	}

	std::cout << "Size: " << lua_gettop(L) << std::endl;



	//std::thread consoleThread(ConsoleThreadFunction, L);

	bool running = true;
	while (running)
	{
		//Update game
		//Render game
		
		
		//luaL_dostring(L, "dofile('loop.lua')");
	}
	
	return 0;
}