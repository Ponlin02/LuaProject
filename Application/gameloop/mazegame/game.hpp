#pragma once
#include "gameState.hpp"
#include "raylib.h"
#include "../player/player.hpp"
#include "../maze/maze.hpp"
#include "../../Scene.hpp"
#include "ECS/systems.hpp"

class Game
{
public:
	Game(lua_State* L);
	~Game() = default;
	GameState run(lua_State* L);

private:
	maze maze;
	player player;
	Scene scene;
	bool hasWon = false;

	SelfVector3 wallBBsize = { MazeConstants::TILE_SIZE, MazeConstants::WALL_HEIGHT, MazeConstants::TILE_SIZE };
};
