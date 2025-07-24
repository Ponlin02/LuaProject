#pragma once
#include "raylib.h"
#include "systemClass.hpp"
#include "components.hpp"
#include <format>

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
				//DrawCubeWiresV(floorPosition, floorSize, RED);
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

//System that renders the player
class PlayerRenderSystem : public System
{
	int hej = 0;

public:
	PlayerRenderSystem() = default;
	bool OnUpdate(entt::registry& registry, float delta)
	{
		auto view = registry.view<Player>();
		view.each([&](Player& player) {
			DrawSphere({ player.Pos.X, player.Pos.Y, player.Pos.Z }, 0.5, BLUE);
			});
		return false;
	};
};

//System that renders all of the colliders in the scene
class BBSystem : public System
{
	int hej = 0;

public:
	BBSystem() = default;
	bool OnUpdate(entt::registry& registry, float delta)
	{
		auto view = registry.view<Collider>();
		view.each([&](Collider& collider) {
			BoundingBox BB = {
				Vector3{
					collider.PosX - collider.size.X / 2,
					collider.PosY - collider.size.Y / 2,
					collider.PosZ - collider.size.Z / 2},

				Vector3{
					collider.PosX + collider.size.X / 2,
					collider.PosY + collider.size.Y / 2,
					collider.PosZ + collider.size.Z / 2}
			};

			DrawBoundingBox(BB, RED);
			});
		return false;
	};
};

//System that makes a button clickable
class Button1ClickSystem : public System
{
	int hej = 0;

public:
	Button1ClickSystem() = default;
	bool OnUpdate(entt::registry& registry, float delta)
	{
		Camera camera;
		auto view = registry.view<CameraComponent>();
		view.each([&](CameraComponent& camCom) {
			camera = *camCom.camera;
			});

		auto view2 = registry.view<Button1, Collider, Button1click>();
		view2.each([&](Button1& button, Collider& collider, Button1click& click) {
			//calculate length to buttons to only do collison checks on close buttons
			Vector2 distanceVec = { button.PosX - camera.position.x, button.PosZ - camera.position.z };
			float length = sqrt(pow(distanceVec.x, 2) + pow(distanceVec.y, 2));

			if (length < 6)
			{
				BoundingBox BB = {
				Vector3{
					collider.PosX - collider.size.X / 2,
					collider.PosY - collider.size.Y / 2,
					collider.PosZ - collider.size.Z / 2},

				Vector3{
					collider.PosX + collider.size.X / 2,
					collider.PosY + collider.size.Y / 2,
					collider.PosZ + collider.size.Z / 2}
				};

				Ray ray = GetMouseRay(GetMousePosition(), camera);
				RayCollision collision = GetRayCollisionBox(ray, BB);
				bool clicked = collision.hit && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

				if (clicked)
				{
					std::cout << "Button clicked!" << std::endl;
					click.clicked = true;
				}
			}
			});
		return false;
	};
};

//System that removes the door when enough buttons have been pressed
class Door1OpenSystem : public System
{
	int hej = 0;

public:
	Door1OpenSystem() = default;
	bool OnUpdate(entt::registry& registry, float delta)
	{
		float totalButtons = 0;
		float buttonsClicked = 0;
		auto view = registry.view<Button1click>();
		view.each([&](Button1click& click) {
			totalButtons += 1;
			if (click.clicked)
			{
				buttonsClicked += 1;
			}
			});

		if (buttonsClicked == totalButtons)
		{
			auto doorView = registry.view<Door1>();
			for (auto doorEntity : doorView)
			{
				registry.destroy(doorEntity);
			}
		}
		return false;
	};
};

//System that makes the player not collide with walls
class PlayerCollisionSystem : public System
{
	int hej = 0;
	SelfVector3 lastValidPos = { 0.0f, 0.0f, 0.0f };

public:
	PlayerCollisionSystem() = default;
	bool OnUpdate(entt::registry& registry, float delta)
	{
		BoundingBox playerCollider;
		Vector2 playerPos;
		std::vector<BoundingBox> wallBBs;

		//get player BB
		auto view = registry.view<Player, Collider>();
		view.each([&](Player& player, Collider& collider) {
			playerPos = { player.Pos.X, player.Pos.Z };
			playerCollider = {
				Vector3{
					collider.PosX - collider.size.X / 2,
					collider.PosY - collider.size.Y / 2,
					collider.PosZ - collider.size.Z / 2},

				Vector3{
					collider.PosX + collider.size.X / 2,
					collider.PosY + collider.size.Y / 2,
					collider.PosZ + collider.size.Z / 2}
			};
			});

		//get relevant walls BBs
		auto view2 = registry.view<Wall, Collider>();
		view2.each([&](Wall& wall, Collider& collider) {
			//calculate length to walls to only do collison checks on close walls
			Vector2 wallWorldPos = { wall.PosX, wall.PosZ };
			Vector2 distanceVec = { playerPos.x - wallWorldPos.x, playerPos.y - wallWorldPos.y };
			float length = sqrt(pow(distanceVec.x, 2) + pow(distanceVec.y, 2));

			if (length < 6)
			{
				BoundingBox wallBB = {
				Vector3{
					collider.PosX - collider.size.X / 2,
					collider.PosY - collider.size.Y / 2,
					collider.PosZ - collider.size.Z / 2},

				Vector3{
					collider.PosX + collider.size.X / 2,
					collider.PosY + collider.size.Y / 2,
					collider.PosZ + collider.size.Z / 2}
				};
				wallBBs.push_back(wallBB);
			}
			});

		//get relevant door BBs
		auto view3 = registry.view<Door1, Collider>();
		view3.each([&](Door1& door, Collider& collider) {
			//calculate length to doors to only do collison checks on close doors
			Vector2 doorWorldPos = { door.PosX, door.PosZ };
			Vector2 distanceVec = { playerPos.x - doorWorldPos.x, playerPos.y - doorWorldPos.y };
			float length = sqrt(pow(distanceVec.x, 2) + pow(distanceVec.y, 2));

			if (length < 6)
			{
				BoundingBox doorBB = {
				Vector3{
					collider.PosX - collider.size.X / 2,
					collider.PosY - collider.size.Y / 2,
					collider.PosZ - collider.size.Z / 2},

				Vector3{
					collider.PosX + collider.size.X / 2,
					collider.PosY + collider.size.Y / 2,
					collider.PosZ + collider.size.Z / 2}
				};
				wallBBs.push_back(doorBB);
			}
			});

		//do collision check
		view.each([&](Player& player, Collider& collider) {
			for (int i = 0; i < wallBBs.size(); i++)
			{
				if (CheckCollisionBoxes(wallBBs[i], playerCollider))
				{
					player.Pos = this->lastValidPos;
				}
			}
			this->lastValidPos = player.Pos;
			});

		//drawing the valid boxes for testing!
		/*for (int i = 0; i < wallBBs.size(); i++)
		{
			DrawBoundingBox(wallBBs[i], BLUE);
		}
		DrawBoundingBox(playerCollider, PURPLE);*/

		return false;
	};
};

//System that makes the player win when touching goal
class GoalCollisionSystem : public System
{
	int hej = 0;

public:
	GoalCollisionSystem() = default;
	bool OnUpdate(entt::registry& registry, float delta)
	{
		BoundingBox playerCollider;
		std::vector<BoundingBox> goalBB; //should only be one but just in case

		//get player BB
		auto view = registry.view<Player, Collider>();
		view.each([&](Player& player, Collider& collider) {
			playerCollider = {
				Vector3{
					collider.PosX - collider.size.X / 2,
					collider.PosY - collider.size.Y / 2,
					collider.PosZ - collider.size.Z / 2},

				Vector3{
					collider.PosX + collider.size.X / 2,
					collider.PosY + collider.size.Y / 2,
					collider.PosZ + collider.size.Z / 2}
			};
			});

		//get the goal / goals
		auto view2 = registry.view<Goal, Collider>();
		view2.each([&](Goal& goal, Collider& collider) {
			BoundingBox BB = {
				Vector3{
					collider.PosX - collider.size.X / 2,
					collider.PosY - collider.size.Y / 2,
					collider.PosZ - collider.size.Z / 2},

				Vector3{
					collider.PosX + collider.size.X / 2,
					collider.PosY + collider.size.Y / 2,
					collider.PosZ + collider.size.Z / 2}
			};
			goalBB.push_back(BB);
			});

		//do collision check
		auto view3 = registry.view<WinTrigger>();
		view3.each([&](WinTrigger& trigger) {
			for (int i = 0; i < goalBB.size(); i++)
			{
				if (CheckCollisionBoxes(goalBB[i], playerCollider))
				{
					*trigger.winFlag = true;
				}
			}
			});

		return false;
	};
};

class EditFloorRenderSystem : public System
{
	int hej = 0;
	float tileSize = MazeConstants::TILE_SIZE;

	//Mesh testing
	Mesh floorMesh = GenMeshPlane(tileSize, tileSize, 1, 1);
	Model floorModel = LoadModelFromMesh(floorMesh);
	Texture2D floorTexture = LoadTexture("assets/floor.jpg");

	Mesh ceilingMesh = GenMeshPlane(tileSize, tileSize, 1, 1);
	Model ceilingModel = LoadModelFromMesh(ceilingMesh);
	Texture2D ceilingTexture = LoadTexture("assets/cat.png");

	lua_State* L;

public:
	EditFloorRenderSystem(lua_State* L) : L(L)
	{
		floorModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = floorTexture;
		ceilingModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = ceilingTexture;
	}
	~EditFloorRenderSystem()
	{
		UnloadTexture(floorTexture);
		UnloadModel(floorModel);
		UnloadTexture(ceilingTexture);
		UnloadModel(ceilingModel);
	}
	bool OnUpdate(entt::registry& registry, float delta)
	{
		auto camView = registry.view<CameraComponent>();
		std::string objects[5] = {"wall", "floor", "door", "button", "goal"};

		camView.each([&](CameraComponent camCom) {

			entt::entity clickedEntity = entt::null;
			auto view = registry.view<Floor>();
			view.each([&](entt::entity entity, Floor& floor) {
				Vector3 floorPosition = { floor.PosX, 0.0f, floor.PosZ };
				Vector3 floorSize = { this->tileSize, 0.1f, this->tileSize };

				Vector3 ceilingPosition = { floor.PosX, MazeConstants::WALL_HEIGHT, floor.PosZ };
				//float distance = sqrt(pow(playerPos.x - floor.PosX, 2) + pow(playerPos.y - floor.PosZ, 2));


				Vector2 screenPos = GetWorldToScreen(floorPosition, *camCom.camera);

				BoundingBox box = {
					{ floorPosition.x - this->tileSize / 2, floorPosition.y - 0.05f, floorPosition.z - tileSize / 2 },
					{ floorPosition.x + tileSize / 2, floorPosition.y + 0.05f, floorPosition.z + tileSize / 2 }
					};

				Vector2 mousePos = GetMousePosition();

				Ray ray = GetScreenToWorldRay(mousePos, *camCom.camera);
				RayCollision collision = GetRayCollisionBox(ray, box);

				bool isHovered = collision.hit;
				bool isClicked = isHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

				if (isHovered)
					floorModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = ceilingTexture;
					
						
				else
					floorModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = floorTexture;
				std::string block = "setWall";

				if (IsKeyDown(KEY_ONE)) {
					block = "setGoal";
				}

				if (isClicked)
				{
					clickedEntity = entity;
					std::string luaCommand = "scene.SetComponent(" + std::to_string(static_cast<uint32_t>(clickedEntity)) + ", 'wall', " + 
						std::to_string(floor.PosX/5) + ", " + std::to_string(floor.PosZ/5) + ")";
					//luaL_dostring(L, luaCommand.c_str());
					//luaL_dostring(L, "scene.SetComponent(1, 'floor', -1, 1");
					//std::cout << "EntityID: " << (uint32_t)clickedEntity << "Floor is clicked with position " << floor.PosX << " and " << floor.PosZ << std::endl;

				

					lua_getglobal(L, block.c_str());
					lua_pushinteger(L, (uint32_t)clickedEntity);
					lua_pushinteger(L, floor.PosX / MazeConstants::TILE_SIZE);
					lua_pushinteger(L, floor.PosZ / MazeConstants::TILE_SIZE);

					if (lua_pcall(L, 3, 0, 0) != LUA_OK) {
						std::cerr << "Lua error: " << lua_tostring(L, -1) << std::endl;
						lua_pop(L, 1); // ta bort felmeddelandet
					}

				}
				camCom.camera->position;

				if (!IsKeyDown(KEY_X))
				{
					DrawCubeWiresV(floorPosition, floorSize, RED);
					//DrawCubeV(floorPosition, floorSize, ORANGE);
					DrawModel(floorModel, floorPosition, 1.0f, GRAY);
					// Out commented now for easier understanding of editing tool
					//DrawModelEx(ceilingModel, ceilingPosition, { 1, 0, 0 }, 180, { 1, 1, 1 }, GRAY);
				}
				});
			});
		return false;
	};
};
