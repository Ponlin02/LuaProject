#pragma once
#include "gameState.hpp"
#include "raylib.h"
#include "../player/player.hpp"
#include "../maze/maze.hpp"

class game
{
public:
	game();
	bool playerWallCollide();
	GameState run();

private:
	Camera camera = { 0 };
	maze maze;
	player player;
};
