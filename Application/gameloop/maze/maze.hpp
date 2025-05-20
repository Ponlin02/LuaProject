#pragma once
#include "../../Scene.hpp"

class maze
{
public:
	void InitializeMaze(lua_State*L, bool& isInitialized);
	void makeFloor(float posX, float posZ);
	void makeSlabWall(float posX, float posZ);
	void makeFullWall(float posX, float posZ);
	void makeTunnel(float posX, float posZ, bool north, bool south, bool east, bool west, float time);
	void draw();

private:
	float wallHeight = 4.0f;
	float tileSize = 5.0f;

	float wallTime = 1.f;

	Scene scene;
};

class FloorSystem : public System
{
	int hej = 0;

public:
	FloorSystem() = default;
	bool OnUpdate(entt::registry& registry, float delta)
	{
		maze Maze;
		auto view = registry.view<Floor>();
		view.each([&](Floor& floor) {
			Maze.makeFloor(floor.PosX, floor.PosZ);
			});
		return false;
	};
};

class WallSystem : public System
{
	int hej = 0;

public:
	WallSystem() = default;
	bool OnUpdate(entt::registry& registry, float delta)
	{
		maze Maze;
		auto view = registry.view<Wall>();
		view.each([&](Wall& wall) {
			Maze.makeFullWall(wall.PosX, wall.PosZ);
			});
		return false;
	};
};