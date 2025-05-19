#pragma once
//#include "raylib.h"
#include "lua.hpp"
#include <string>

struct SelfVector3
{
    float X, Y, Z;
    SelfVector3(float x = 0.f, float y = 0.f, float z = 0.f)
        : X(x), Y(y), Z(z) {
    }
};

 // Raylib har både Vector3 och transform men dess transform använder quaternioins vilket 
 // jag inte orkar med därför gör jag min egna transform
struct SelfTransform
{
    SelfVector3 Position;
    SelfVector3 Rotation;
    SelfVector3 Scale;
    SelfTransform(SelfVector3 position = SelfVector3(),
        SelfVector3 rotation = SelfVector3(),
        SelfVector3 scale = SelfVector3())
        : Position(position), Rotation(rotation), Scale(scale) {
    }
};

std::string GetValueString(lua_State* L, int index);
void DumpStack(lua_State* L);
void DumpError(lua_State* L);


// Lua conversion functions
SelfVector3 lua_tovector(lua_State* L, int index);
int lua_pushvector(lua_State* L, const SelfVector3& vector);
int lua_pushtransform(lua_State* L, const SelfTransform& transform);
SelfTransform lua_totransform(lua_State* L, int index);
