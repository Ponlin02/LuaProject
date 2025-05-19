#pragma once
#include "raylib.h"
#include <vector>

struct wall
{
	Vector2 position;
	BoundingBox boundingBox;
};

class maze
{
public:
	void makeFloor(float posX, float posZ);
	void makeSlabWall(float posX, float posZ);
	void makeFullWall(float posX, float posZ);
	void draw();

	std::vector<BoundingBox> getRelevantBBs(Vector2 playerPos);

private:
	float wallHeight = 4.0f;
	float tileSize = 5.0f;

	std::vector<wall> walls;

private:
	void drawHitboxes();
};