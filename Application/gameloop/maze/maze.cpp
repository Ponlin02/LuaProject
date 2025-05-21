#include "maze.hpp"


void maze::InitializeMaze(lua_State* L, bool& isInitialized)
{
	// Använder denna för att sätta in startvärden
	// Kommer att lägga in en Serializer här senare
	// Det är funktionen som kommer att läsa all data 
	// från en fil

	Scene::lua_openscene(L, &scene);

	int entity = scene.CreateEntity();
	int entity2 = scene.CreateEntity();
	int entity3 = scene.CreateEntity();

	Floor floor1(0.f,1.f);
	Floor floor2(0.f,-1.f);
	Floor floor3(0.f,0.f);


	scene.SetComponent(entity, floor1);
	scene.SetComponent(entity2, floor2);
	//scene.SetComponent(entity3, floor3);
	
	scene.CreateSystem<FloorSystem>();
	scene.CreateSystem<WallSystem>();
	
	isInitialized = true;

}


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
}

void maze::makeTunnel(float posX, float posZ, bool north, bool south, bool east, bool west, float time, bool isClicked)
{
	float halfSize = this->tileSize / 2.0f;

	float wallThickness = this->tileSize * 0.1f; // thin wall edges
	if(isClicked)
		float wallThickness = this->tileSize * 0.1f * time;
	if (wallThickness >= halfSize)
		wallThickness = halfSize;
	float wallHeight = this->wallHeight;

	// Center position of the tile
	Vector3 basePos = { posX * this->tileSize, wallHeight / 2.0f, posZ * this->tileSize };

	// North wall (top side of tile)
	if (north) {
		Vector3 wallSize = { this->tileSize, wallHeight, wallThickness };
		Vector3 wallPos = { basePos.x, basePos.y, basePos.z - halfSize + wallThickness / 2.0f };
		DrawCubeV(wallPos, wallSize, BEIGE);
		DrawCubeWiresV(wallPos, wallSize, BLACK);
	}

	// South wall (bottom side of tile)
	if (south) {
		Vector3 wallSize = { this->tileSize, wallHeight, wallThickness };
		Vector3 wallPos = { basePos.x, basePos.y, basePos.z + halfSize - wallThickness / 2.0f };
		DrawCubeV(wallPos, wallSize, BEIGE);
		DrawCubeWiresV(wallPos, wallSize, BLACK);
	}

	// East wall (right side of tile)
	if (east) {
		Vector3 wallSize = { wallThickness, wallHeight, this->tileSize };
		Vector3 wallPos = { basePos.x + halfSize - wallThickness / 2.0f, basePos.y, basePos.z };
		DrawCubeV(wallPos, wallSize, BEIGE);
		DrawCubeWiresV(wallPos, wallSize, BLACK);
	}

	// West wall (left side of tile)
	if (west) {
		Vector3 wallSize = { wallThickness, wallHeight, this->tileSize };
		Vector3 wallPos = { basePos.x - halfSize + wallThickness / 2.0f, basePos.y, basePos.z };
		DrawCubeV(wallPos, wallSize, BEIGE);
		DrawCubeWiresV(wallPos, wallSize, BLACK);
	}
}

void maze::makeButton(float posX, float posZ, Camera camera, bool& isClicked)
{
	Vector3 wallPosition = { posX * this->tileSize + this->tileSize / 2, this->wallHeight / 2, posZ * this->tileSize };
	Vector3 wallSize = { 0.2f, 0.2f, 0.2f };

	

	Vector2 screenPos = GetWorldToScreen(wallPosition, camera);
		
	 //This code is for hovering over our objects that could be useful for the map editor!

		BoundingBox box = {
		{ wallPosition.x - wallSize.x / 2, wallPosition.y - wallSize.y / 2, wallPosition.z - wallSize.z / 2 },
		{ wallPosition.x + wallSize.x / 2, wallPosition.y + wallSize.y / 2, wallPosition.z + wallSize.z / 2 }
		};

		Ray ray = GetMouseRay(GetMousePosition(), camera);


		RayCollision collision = GetRayCollisionBox(ray, box);
		bool isHovered = collision.hit;
		isClicked = isHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

	Color btnColor = isHovered ? SKYBLUE : BEIGE;

	if (isClicked)
		std::cout << "Button clicked!" << std::endl;

	if (!IsKeyDown(KEY_C))
	{
		DrawCubeWiresV(wallPosition, wallSize, BLACK);
		DrawCubeV(wallPosition, wallSize, btnColor);
	}
}

void maze::draw(Camera camera)
{
	//DrawSphere(Vector3{ 0.0f, 0.0f, -15.0f }, 1.5f, RED);
	
	// Utkommenterat för att se om jag kan göra dessa till komponenter istället
	// Och sätta de i initialize istället!
	//makeFloor(0.0f, 0.0f);
	//makeFloor(0.0f, -1.0f);
	//makeFloor(-1.0f, 0.0f);
	//makeFloor(1.0f, 0.0f);

	//makeFloor(1.0f, -1.0f);

	//makeSlabWall(0.0f, 0.0f);
	//makeSlabWall(-1.0f, 0.0f);

	//makeSlabWall(0.0f, -1.0f);
	//makeFullWall(-1.0f, -1.0f);
	bool isHovered = false;
	makeButton(0.f, 0.f, camera, isHovered);
	makeTunnel(0.f, -1.f, false, false, true, true, wallTime, isHovered);

	wallTime += 0.01;

	scene.UpdateSystems(1);
	int count = scene.GetEntityCount();

}
