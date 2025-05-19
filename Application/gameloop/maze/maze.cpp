#include "maze.hpp"
#include "raylib.h"

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

void maze::draw()
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

	scene.UpdateSystems(1);
	int count = scene.GetEntityCount();
	
	//std::cout << "Antal floor entities: " << count << std::endl;

}
