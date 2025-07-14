#pragma once
#include "raylib.h"
#include <vector>
#include "../../Scene.hpp"
#include "../mazegame/constants.h"

class maze
{
public:
	void InitializeMaze(lua_State*L, Scene& scene);
	void makeTunnel(float posX, float posZ, bool north, bool south, bool east, bool west, float time, bool isClicked);
	void makeButton(float posX, float posZ, Camera camera, bool& isClicked);
	void draw(Camera camera, Scene& scene);

private:
	float wallHeight = MazeConstants::WALL_HEIGHT;
	float tileSize = MazeConstants::TILE_SIZE;

private:
	float wallTime = 1.f;
};
