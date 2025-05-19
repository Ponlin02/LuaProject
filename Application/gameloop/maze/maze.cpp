#include "maze.hpp"

void maze::makeFloor(float posX, float posZ)
{
	//Floor test
	Vector3 floorPosition = { posX * this->tileSize, 0.0f, posZ * this->tileSize };
	Vector3 floorSize = { this->tileSize, 0.1f, this->tileSize };

	if (!IsKeyDown(KEY_X))
	{
		DrawCubeWiresV(floorPosition, floorSize, BLACK);
		DrawCubeV(floorPosition, floorSize, ORANGE);
	}
}

void maze::makeSlabWall(float posX, float posZ)
{
	//Wall test
	Vector3 wallPosition = { posX * this->tileSize + this->tileSize / 2, this->wallHeight / 2, posZ * this->tileSize };
	Vector3 wallSize = { 0.3f, this->wallHeight, this->tileSize };

	if (!IsKeyDown(KEY_Z))
	{
		DrawCubeWiresV(wallPosition, wallSize, BLACK);
		DrawCubeV(wallPosition, wallSize, LIME);
	}
}

void maze::makeFullWall(float posX, float posZ)
{
	//Wall test
	Vector3 wallPosition = { posX * this->tileSize, this->wallHeight / 2, posZ * this->tileSize };
	Vector3 wallSize = { this->tileSize, this->wallHeight, this->tileSize };

	if (!IsKeyDown(KEY_C))
	{
		DrawCubeWiresV(wallPosition, wallSize, BLACK);
		DrawCubeV(wallPosition, wallSize, BEIGE);
	}

	//Add in vector
	wall newWall;
	newWall.position = { posX, posZ };
	newWall.boundingBox = {
		Vector3{
			posX * this->tileSize - this->tileSize / 2,
			0,
			posZ * this->tileSize - this->tileSize / 2},

		Vector3{
			posX * this->tileSize + this->tileSize / 2,
			this->wallHeight,
			posZ * this->tileSize + this->tileSize / 2}
	};
	
	this->walls.push_back(newWall);
}

void maze::draw()
{
	DrawSphere(Vector3{ 0.0f, 0.0f, -15.0f }, 1.5f, RED);

	makeFloor(0.0f, 0.0f);
	makeFloor(0.0f, -1.0f);
	makeFloor(-1.0f, 0.0f);
	makeFloor(1.0f, 0.0f);

	makeFloor(1.0f, -1.0f);

	//makeSlabWall(0.0f, 0.0f);
	//makeSlabWall(-1.0f, 0.0f);

	//makeSlabWall(0.0f, -1.0f);
	makeFullWall(-1.0f, -1.0f);
	makeFullWall(1.0f, -1.0f);

	this->drawHitboxes();
}

std::vector<BoundingBox> maze::getRelevantBBs(Vector2 playerPos)
{
	std::vector<BoundingBox> returnVector;
	for (int i = 0; i < this->walls.size(); i++)
	{
		Vector2 tempVec = { playerPos.x - this->walls[i].position.x, playerPos.y - this->walls[i].position.y };
		float length = sqrt(pow(tempVec.x, 2) + pow(tempVec.y, 2));
		if (length < 10)
		{
			returnVector.push_back(this->walls[i].boundingBox);
		}
	}

	return returnVector;
}

void maze::drawHitboxes()
{
	for (int i = 0; i < this->walls.size(); i++)
	{
		DrawBoundingBox(this->walls[i].boundingBox, RED);
	}
}
