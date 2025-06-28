#pragma once
#include "raylib.h"
#include <vector>
#include "../../Scene.hpp"
#include "../placeholder/constants.h"

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

//System that renders all of the floors in the scene
class FloorRenderSystem : public System
{
	int hej = 0;
	float tileSize = MazeConstants::TILE_SIZE;

	//Mesh testing
	Mesh floorMesh = GenMeshPlane(tileSize, tileSize, 1, 1);
	Model floorModel = LoadModelFromMesh(floorMesh);
	Texture2D floorTexture = LoadTexture("assets/floor.jpg");

	Mesh ceilingMesh = GenMeshPlane(tileSize, tileSize, 1, 1);
	Model ceilingModel = LoadModelFromMesh(ceilingMesh);
	Texture2D ceilingTexture = LoadTexture("assets/ceiling.jpg");

public:
	FloorRenderSystem()
	{
		floorModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = floorTexture;
		ceilingModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = ceilingTexture;
	}
	~FloorRenderSystem()
	{
		UnloadTexture(floorTexture);
		UnloadModel(floorModel);
		UnloadTexture(ceilingTexture);
		UnloadModel(ceilingModel);
	}
	bool OnUpdate(entt::registry& registry, float delta)
	{
		/*Vector2 playerPos;
		auto viewP = registry.view<Player>();
		viewP.each([&](Player& player) {
			playerPos = { player.Pos.X, player.Pos.Z };
		});*/

		auto view = registry.view<Floor>();
		view.each([&](Floor& floor) {
			Vector3 floorPosition = { floor.PosX, 0.0f, floor.PosZ };
			Vector3 floorSize = { this->tileSize, 0.1f, this->tileSize };

			Vector3 ceilingPosition = { floor.PosX, MazeConstants::WALL_HEIGHT, floor.PosZ };
			//float distance = sqrt(pow(playerPos.x - floor.PosX, 2) + pow(playerPos.y - floor.PosZ, 2));

			if (!IsKeyDown(KEY_X))
			{
				//DrawCubeWiresV(floorPosition, floorSize, BLACK);
				//DrawCubeV(floorPosition, floorSize, ORANGE);
				DrawModel(floorModel, floorPosition, 1.0f, GRAY);
				DrawModelEx(ceilingModel, ceilingPosition, { 1, 0, 0 }, 180, { 1, 1, 1 }, GRAY);
			}
		});
		return false;
	};
};

//System that renders all of the walls in the scene
class WallRenderSystem : public System
{
	int hej = 0;
	float wallHeight = MazeConstants::WALL_HEIGHT;
	float tileSize = MazeConstants::TILE_SIZE;

	//Mesh testing
	Mesh wallMesh = GenMeshCube(tileSize, wallHeight, tileSize);
	Model wallModel = LoadModelFromMesh(wallMesh);
	Texture2D wallTexture = LoadTexture("assets/brick.jpg");

public:
	WallRenderSystem()
	{
		wallModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = wallTexture;
	}
	~WallRenderSystem()
	{
		UnloadTexture(wallTexture);
		UnloadModel(wallModel);
	}
	bool OnUpdate(entt::registry& registry, float delta)
	{
		auto view = registry.view<Wall>();
		view.each([&](Wall& wall) {
			Vector3 wallPosition = { wall.PosX, this->wallHeight / 2, wall.PosZ };
			Vector3 wallSize = { this->tileSize, this->wallHeight, this->tileSize };

			if (!IsKeyDown(KEY_C))
			{
				//DrawCubeWiresV(wallPosition, wallSize, BLACK);
				//DrawCubeV(wallPosition, wallSize, BEIGE);
				DrawModel(wallModel, wallPosition, 1.0f, WHITE);
			}
		});
		return false;
	};
};

//System that renders all of the door1 in the scene
class Door1RenderSystem : public System
{
	int hej = 0;
	float wallHeight = MazeConstants::WALL_HEIGHT;
	float tileSize = MazeConstants::TILE_SIZE;

	//Mesh testing
	Mesh doorMesh = GenMeshCube(tileSize, wallHeight, tileSize);
	Model doorModel = LoadModelFromMesh(doorMesh);
	Texture2D doorTexture = LoadTexture("assets/door.jpg");

public:
	Door1RenderSystem()
	{
		doorModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = doorTexture;
	}
	~Door1RenderSystem()
	{
		UnloadTexture(doorTexture);
		UnloadModel(doorModel);
	}
	bool OnUpdate(entt::registry& registry, float delta)
	{
		auto view = registry.view<Door1>();
		view.each([&](Door1& door) {
			Vector3 doorPosition = { door.PosX, this->wallHeight / 2, door.PosZ };
			Vector3 doorSize = { this->tileSize, this->wallHeight, this->tileSize };

			if (!IsKeyDown(KEY_C))
			{
				//DrawCubeWiresV(doorPosition, doorSize, BLACK);
				//DrawCubeV(doorPosition, doorSize, BROWN);
				DrawModel(doorModel, doorPosition, 1.0f, WHITE);
			}
		});
		return false;
	};
};

//System that renders all of the pressure plates in the scene
class Button1RenderSystem : public System
{
	int hej = 0;
	float buttonHeight = MazeConstants::BUTTON1_HEIGHT;
	float buttonSize = MazeConstants::BUTTON1_SIZE;

public:
	Button1RenderSystem() = default;
	bool OnUpdate(entt::registry& registry, float delta)
	{
		auto view = registry.view<Button1, Button1click>();
		view.each([&](Button1& button, Button1click click) {
			Vector3 buttonPosition = { button.PosX, this->buttonHeight / 2, button.PosZ };
			Vector3 buttonSize = { this->buttonSize, this->buttonHeight, this->buttonSize };

			if (!IsKeyDown(KEY_C))
			{
				DrawCubeWiresV(buttonPosition, buttonSize, BLACK);
				if (click.clicked)
				{
					DrawCubeV(buttonPosition, buttonSize, LIME);
				}
				else
				{
					DrawCubeV(buttonPosition, buttonSize, DARKBLUE);
				}
			}
		});
		return false;
	};
};

//System that renders the goal
class GoalRenderSystem : public System
{
	int hej = 0;

public:
	GoalRenderSystem() = default;
	bool OnUpdate(entt::registry& registry, float delta)
	{
		auto view = registry.view<Goal>();
		view.each([&](Goal& goal) {
			DrawSphere({ goal.PosX, MazeConstants::GOAL_FLOAT_HEIGHT, goal.PosZ }, 0.5, GOLD);
			});
		return false;
	};
};
