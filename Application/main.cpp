#include <iostream>
#include <thread>
#include <string>
#include <Windows.h>

#include "lua.hpp"
#include "graphics/rayLibTest.hpp"

void DumpError(lua_State* L)
{
	if (lua_gettop(L) && lua_isstring(L, -1))
	{
		std::cout << "Lua error: " << lua_tostring(L, -1) << std::endl;
		lua_pop(L, 1);
	}
}

std::string GetValueString(lua_State* L, int i)
{
	switch (lua_type(L, i))
	{
	case LUA_TNIL: return "nil";
	case LUA_TBOOLEAN: return lua_toboolean(L, i) ? "true" : "false";
	case LUA_TNUMBER: return std::to_string(lua_tonumber(L, i));
	case LUA_TSTRING: return lua_tostring(L, i);
	default: return "";
	}
}

void DumpStack(lua_State* L)
{
	int size = lua_gettop(L);

	std::cout << "--- STACK BEGIN ---" << std::endl;
	for (int i = size; i > 0; i--)
	{
		std::cout << i
			<< "\t"
			<< lua_typename(L, lua_type(L, i))
			<< "\t\t" << GetValueString(L, i)
			<< std::endl;
	}
	std::cout << "--- STACK END ---" << std::endl;
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

struct Vector3
{
	float X, Y, Z;
	Vector3(float x = 0.f, float y = 0.f, float z = 0.f) :
		X(x), Y(y), Z(z) { }
};

Vector3 lua_tovector(lua_State* L, int index)
{
	Vector3 vector;
	lua_getfield(L, index, "x");
	vector.X = lua_tonumber(L, -1);
	lua_pop(L, 1);
	
	lua_getfield(L, index, "y");
	vector.Y = lua_tonumber(L, -1);
	lua_pop(L, 1);
	lua_getfield(L, index, "z");
	vector.Z = lua_tonumber(L, -1);
	lua_pop(L, 1);
	
	return vector;
}

static int PrintVector(lua_State* L)
{
	Vector3 hej = lua_tovector(L, -1);

	std::cout << "[c++] Vector("
		<< hej.X << ", "
		<< hej.Y << ", "
		<< hej.Z << ")"
		<< std::endl;

	return -1;
}

int main()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	luaL_dostring(L, "print('hello from lua')");

	

	lua_newtable(L);

	lua_pushstring(L, "x");
	lua_pushnumber(L, 1);
	lua_settable(L, -3);

	lua_pushstring(L, "y");
	lua_pushnumber(L, 2);
	lua_settable(L, -3);
	DumpStack(L);

	lua_pushstring(L, "z");
	lua_pushnumber(L, 3);
	lua_settable(L, -3);
	DumpStack(L);

	//PrintVector(L);
	lua_pushcfunction(L, PrintVector);
	lua_setglobal(L, "PrintVector");
	luaL_dofile(L, "vector-demo.lua");


	std::thread consoleThread(ConsoleThreadFunction, L);



	rayLib raylib;
	raylib.run();

	bool running = true;
	while (!running)
	{
		//Update game
		//Render game
	}
	
	return 0;
}