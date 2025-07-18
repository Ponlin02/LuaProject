#pragma once
#include "game.hpp"

class Edit
{
public:
	Edit(lua_State* L);
	~Edit() = default;
	GameState run(lua_State* L);

private:
	Scene scene;
	player player;
};
