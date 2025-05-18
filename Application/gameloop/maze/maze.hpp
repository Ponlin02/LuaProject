#pragma once

class maze
{
public:
	void makeFloor(float posX, float posZ);
	void makeSlabWall(float posX, float posZ);
	void makeFullWall(float posX, float posZ);
	void draw();

private:
	float wallHeight = 4.0f;
	float tileSize = 5.0f;
};