#include "maze.hpp"
#include "raylib.h"

void maze::draw()
{
	DrawSphere(Vector3{ 0.0f, 0.0f, -15.0f }, 1.5f, RED);

	//Floor test
	Vector3 floorPosition = { 0.0f, 0.0f, 0.0f };
	Vector3 floorSize = { 5.0f, 0.1f, 5.0f };

	if (IsKeyDown(KEY_X))
	{
		DrawCubeWiresV(floorPosition, floorSize, BLACK);
		DrawCubeV(floorPosition, floorSize, ORANGE);
	}
	
	//Wall test
	float height = 4.0f;
	Vector3 wallPosition = { floorPosition.x + floorSize.x/2, height / 2, 0.0f};
	Vector3 wallSize = { 0.4f, height, floorSize.z };

	DrawCubeWiresV(wallPosition, wallSize, BLACK);
	DrawCubeV(wallPosition, wallSize, LIME);
}
