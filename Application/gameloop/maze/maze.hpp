#pragma once
#include "raylib.h"
#include <vector>
#include "../../Scene.hpp"
#include "../placeholder/constants.h"

class maze
{
public:
	void InitializeMaze(lua_State*L, Scene& scene);
	void makeFloor(float posX, float posZ); //Aim to remove this
	void makeSlabWall(float posX, float posZ);
	void makeFullWall(float posX, float posZ); //Aim to remove this
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

public:
	FloorRenderSystem() = default;
	bool OnUpdate(entt::registry& registry, float delta)
	{
		auto view = registry.view<Floor>();
		view.each([&](Floor& floor) {
			Vector3 floorPosition = { floor.PosX, 0.0f, floor.PosZ };
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

//System that renders all of the walls in the scene
class WallRenderSystem : public System
{
	int hej = 0;
	float wallHeight = MazeConstants::WALL_HEIGHT;
	float tileSize = MazeConstants::TILE_SIZE;

public:
	WallRenderSystem() = default;
	bool OnUpdate(entt::registry& registry, float delta)
	{
		auto view = registry.view<Wall>();
		view.each([&](Wall& wall) {
			Vector3 wallPosition = { wall.PosX, this->wallHeight / 2, wall.PosZ };
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

//System that renders all of the door1 in the scene
class Door1RenderSystem : public System
{
	int hej = 0;
	float wallHeight = MazeConstants::WALL_HEIGHT;
	float tileSize = MazeConstants::TILE_SIZE;

public:
	Door1RenderSystem() = default;
	bool OnUpdate(entt::registry& registry, float delta)
	{
		auto view = registry.view<Door1>();
		view.each([&](Door1& door) {
			Vector3 doorPosition = { door.PosX, this->wallHeight / 2, door.PosZ };
			Vector3 doorSize = { this->tileSize, this->wallHeight, this->tileSize };

			if (!IsKeyDown(KEY_C))
			{
				DrawCubeWiresV(doorPosition, doorSize, BLACK);
				DrawCubeV(doorPosition, doorSize, BROWN);
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
