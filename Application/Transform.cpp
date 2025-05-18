#include "Transform.hpp"
//#include "lauxlib.h" // For luaL_check* and lua_pushnumber
#include <iostream>
#include <string>

// Utility: Get string from Lua value for debug
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

// Debug: Print Lua stack
void DumpStack(lua_State* L)
{
    int size = lua_gettop(L);
    std::cout << "--- STACK BEGIN ---" << std::endl;
    for (int i = size; i > 0; --i)
    {
        std::cout << i << "\t" << lua_typename(L, lua_type(L, i))
            << "\t" << GetValueString(L, i) << std::endl;
    }
    std::cout << "--- STACK END ---" << std::endl;
}

void DumpError(lua_State* L)
{
	if (lua_gettop(L) && lua_isstring(L, -1))
	{
		std::cout << "Lua error: " << lua_tostring(L, -1) << std::endl;
		lua_pop(L, 1);
	}
}


// Convert Lua table to Vector3
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

// Push Vector3 as Lua table
int lua_pushvector(lua_State* L, const Vector3& vector)
{
    lua_newtable(L);

    lua_pushnumber(L, static_cast<lua_Number>(vector.X));
    lua_setfield(L, -2, "x");

    lua_pushnumber(L, static_cast<lua_Number>(vector.Y));
    lua_setfield(L, -2, "y");

    lua_pushnumber(L, static_cast<lua_Number>(vector.Z));
    lua_setfield(L, -2, "z");

    return 1; // Returning 1 table on the stack
}

// Convert Lua table to Transform
Transform lua_totransform(lua_State* L, int index)
{
    Transform transform;

    lua_getfield(L, index, "position");
    transform.Position = lua_tovector(L, -1);
    lua_pop(L, 1);

    lua_getfield(L, index, "rotation");
    transform.Rotation = lua_tovector(L, -1);
    lua_pop(L, 1);

    lua_getfield(L, index, "scale");
    transform.Scale = lua_tovector(L, -1);
    lua_pop(L, 1);

    return transform;
}

// Push Transform as Lua table
int lua_pushtransform(lua_State* L, const Transform& transform)
{
    lua_newtable(L);

    lua_pushvector(L, transform.Position);
    lua_setfield(L, -2, "position");

    lua_pushvector(L, transform.Rotation);
    lua_setfield(L, -2, "rotation");

    lua_pushvector(L, transform.Scale);
    lua_setfield(L, -2, "scale");

    return 1; // Returning 1 table on the stack
}
