#pragma once
#include "gameState.hpp"
#include "raylib.h"
#include "../player/player.hpp"
#include "../maze/maze.hpp"

class game
{
public:
	game();
	GameState run(lua_State* L);

private:
	Camera camera = { 0 };
	maze maze;
	player player;
	bool isInitialized = false;
};
