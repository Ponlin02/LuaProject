#pragma once
#include "gameState.hpp"
#include "raylib.h"
#include "../player/player.hpp"
#include "../maze/maze.hpp"
#include "../../Scene.hpp"

class game
{
public:
	game(lua_State* L);
	bool playerWallCollide();
	GameState run(lua_State* L);

private:
	Camera camera = { 0 };
	maze maze;
	player player;
	Scene scene;

	SelfVector3 wallBBsize = { 5.0f, 4.0f, 5.0f };
};
