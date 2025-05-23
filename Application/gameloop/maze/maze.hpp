#pragma once
#include "raylib.h"
#include <vector>
#include "../../Scene.hpp"

struct oldwall
{
	Vector2 position;
	BoundingBox boundingBox;
};


class maze
{
public:
	void InitializeMaze(lua_State*L, Scene& scene);
	void makeFloor(float posX, float posZ);
	void makeSlabWall(float posX, float posZ);
	void makeFullWall(float posX, float posZ);
	void makeTunnel(float posX, float posZ, bool north, bool south, bool east, bool west, float time, bool isClicked);
	void makeButton(float posX, float posZ, Camera camera, bool& isClicked);
	void draw(Camera camera, Scene& scene);

	std::vector<BoundingBox> getRelevantBBs(Vector2 playerPos);

private:
	float wallHeight = 4.0f;
	float tileSize = 5.0f;

	std::vector<oldwall> walls;

private:
	void drawHitboxes();
	float wallTime = 1.f;
};

class FloorSystem : public System
{
	int hej = 0;
	float tileSize = 5.0f;

public:
	FloorSystem() = default;
	bool OnUpdate(entt::registry& registry, float delta)
	{
		auto view = registry.view<Floor>();
		view.each([&](Floor& floor) {
			Vector3 floorPosition = { floor.PosX * this->tileSize, 0.0f, floor.PosZ * this->tileSize };
			Vector3 floorSize = { this->tileSize, 0.1f, this->tileSize };

			if (!IsKeyDown(KEY_X))
			{
				DrawCubeWiresV(floorPosition, floorSize, BLACK);
				DrawCubeV(floorPosition, floorSize, ORANGE);
			}
		});
		return false;
	};
};

class WallSystem : public System
{
	int hej = 0;
	float wallHeight = 4.0f;
	float tileSize = 5.0f;

public:
	WallSystem() = default;
	bool OnUpdate(entt::registry& registry, float delta)
	{
		auto view = registry.view<Wall>();
		view.each([&](Wall& wall) {
			Vector3 wallPosition = { wall.PosX * this->tileSize, this->wallHeight / 2, wall.PosZ * this->tileSize };
			Vector3 wallSize = { this->tileSize, this->wallHeight, this->tileSize };

			if (!IsKeyDown(KEY_C))
			{
				DrawCubeWiresV(wallPosition, wallSize, BLACK);
				DrawCubeV(wallPosition, wallSize, BEIGE);
			}
		});
		return false;
	};
};