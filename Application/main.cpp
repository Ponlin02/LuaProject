#include <iostream>
#include <thread>
#include <string>
#include <Windows.h>

#include "lua.hpp"
#include "graphics/rayLibTest.hpp"
#include "gameloop/gameloop.hpp"

struct Vector3
{
	float X, Y, Z;
	Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f) :
		X(x), Y(y), Z(z) {}
};

Vector3 lua_tovector(lua_State* L, int index)
{
	//check if it is a table
	if (!lua_istable(L, index))
	{
		throw "lua_tovector: table expected.";
	}

	Vector3 vector;

	lua_getfield(L, index, "x"); //Push x to stack
	vector.X = lua_tonumber(L, -1);
	lua_pop(L, 1); //pop x

	lua_getfield(L, index, "y"); //Push y to stack
	vector.Y = lua_tonumber(L, -1);
	lua_pop(L, 1); //pop y

	lua_getfield(L, index, "z"); //Push z to stack
	vector.Z = lua_tonumber(L, -1);
	lua_pop(L, 1); //pop z

	return vector;
}

/*
Lua arguments in table:
	1 | table		| -1
1: a table representing the vector
Return values : none
*/
int PrintVector(lua_State* L)
{
	Vector3 vector = lua_tovector(L, 1);

	std::cout << "[C++] Vector("
		<< vector.X << ", "
		<< vector.Y << ", "
		<< vector.Z << ")"
		<< std::endl;

	//no return values
	return 0;
}

void lua_pushvector(lua_State* L, const Vector3& vector)
{
	lua_newtable(L);

	lua_pushnumber(L, vector.X);
	lua_setfield(L, -2, "x");

	lua_pushnumber(L, vector.Y);
	lua_setfield(L, -2, "y");

	lua_pushnumber(L, vector.Z);
	lua_setfield(L, -2, "z");
}

/*
Lua arguments in table :
	2 | number		| -1
	1 | number		| -2
1: floor of the randomized values
2: roof of the randomize values

Return values :
	A table representing the
	randomized vector .
*/
int RandomVector(lua_State* L)
{
	//Sanity check
	if (!lua_isnumber(L, 1) || !lua_isnumber(L, 2))
	{
		return 0;
	}

	int min = lua_tonumber(L, 1);
	int max = lua_tonumber(L, 2);
	int diff = max - min;
	lua_pop(L, 2);

	Vector3 vector(rand() % diff + min, rand() % diff + min, rand() % diff + min);

	lua_pushvector(L, vector);
	return 1;
}

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
	/*luaL_dofile(L, "populate.lua");

	//table
	lua_getglobal(L, "dino");

	//species
	lua_getfield(L, -1, "species");
	std::cout << "Species: " << lua_tostring(L, -1) << std::endl;
	lua_pop(L, 1);

	//name
	lua_getfield(L, -1, "name");
	std::cout << "Name: " << lua_tostring(L, -1) << std::endl;
	lua_pop(L, 1);

	//has wings?
	lua_getfield(L, -1, "wings");
	std::cout << "Has wings?: " << lua_toboolean(L, -1) << std::endl;
	lua_pop(L, 1);

	//noise function
	lua_getfield(L, -1, "getnoise");

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

	//release table
	lua_pop(L, -1);

	std::cout << "Size: " << lua_gettop(L) << std::endl;*/



	//ex 5
	luaL_dofile(L, "vector.lua");
	lua_pop(L, 1);
	std::cout << "Size: " << lua_gettop(L) << std::endl;

	//print vector function to lua
	lua_pushcfunction(L, PrintVector);
	lua_setglobal(L, "PrintVector");
	std::cout << "Size: " << lua_gettop(L) << std::endl;

	//random vector function to lua
	lua_pushcfunction(L, RandomVector);
	lua_setglobal(L, "RandomVector");
	std::cout << "Size: " << lua_gettop(L) << std::endl;

	//function that uses my new functinos and prints 2 random vectors :D
	luaL_dofile(L, "vector-demo.lua");



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