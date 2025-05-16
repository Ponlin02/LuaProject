#pragma once

#include "lua.hpp"
#include <string>

struct Vector3
{
    float X, Y, Z;
    Vector3(float x = 0.f, float y = 0.f, float z = 0.f)
        : X(x), Y(y), Z(z) {
    }
};

struct Transform
{
    Vector3 Position;
    Vector3 Rotation;
    Vector3 Scale;
    Transform(Vector3 position = Vector3(),
        Vector3 rotation = Vector3(),
        Vector3 scale = Vector3())
        : Position(position), Rotation(rotation), Scale(scale) {
    }
};

std::string GetValueString(lua_State* L, int index);
void DumpStack(lua_State* L);
void DumpError(lua_State* L);


// Lua conversion functions
Vector3 lua_tovector(lua_State* L, int index);
int lua_pushvector(lua_State* L, const Vector3& vector);
int lua_pushtransform(lua_State* L, const Transform& transform);
Transform lua_totransform(lua_State* L, int index);
