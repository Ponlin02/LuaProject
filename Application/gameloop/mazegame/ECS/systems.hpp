#pragma once
#include "raylib.h"
#include "systemClass.hpp"
#include "components.hpp"
#include <fstream>
#include "../SaveFunctions.hpp"

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
		
		auto view = registry.view<Floor>();
		view.each([&](Floor& floor) {
			Vector3 floorPosition = { floor.PosX, 0.0f, floor.PosZ };
			Vector3 floorSize = { this->tileSize, 0.1f, this->tileSize };

			Vector3 ceilingPosition = { floor.PosX, MazeConstants::WALL_HEIGHT, floor.PosZ };
			
				DrawModel(floorModel, floorPosition, 1.0f, GRAY);
				DrawModelEx(ceilingModel, ceilingPosition, { 1, 0, 0 }, 180, { 1, 1, 1 }, GRAY);
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
			
			DrawModel(wallModel, wallPosition, 1.0f, WHITE);

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
		auto view = registry.view<Door1, Door1State>();
		view.each([&](entt::entity entity, Door1& door, Door1State& state) {
			
			float halfSize = tileSize / 2;
			float wallThickness = tileSize * state.openAmount;
			Vector3 centerPos = { door.PosX , wallHeight / 2, door.PosZ };

			if(door.north)
			{
				Vector3 doorSize = { tileSize * state.openAmount, wallHeight , tileSize  };

				Vector3 wallPos = { centerPos.x - tileSize + (wallThickness - halfSize / 2 + (1.5f * halfSize * (1 - state.openAmount))), centerPos.y,  centerPos.z  };
				DrawModelEx(doorModel, wallPos, { 1, 0,0 }, 0, { 0.5f + (state.openAmount - 1) / 2,1, 1 }, WHITE);

				wallPos = { centerPos.x + tileSize - (wallThickness - halfSize / 2 + (1.5f * halfSize * (1 - state.openAmount))), centerPos.y, centerPos.z  };
				DrawModelEx(doorModel, wallPos, { 1, 0,0 }, 0, { 0.5f + (state.openAmount - 1) / 2,1, 1}, WHITE);

				
			}
			else
			{
				Vector3 doorSize = { tileSize, wallHeight , tileSize * state.openAmount };

				Vector3 wallPos = { centerPos.x, centerPos.y,  centerPos.z - tileSize + (wallThickness - halfSize / 2 + (1.5f * halfSize * (1 - state.openAmount))) };
				DrawModelEx(doorModel, wallPos, { 1, 0,0 }, 0, { 1,1, 0.5f + (state.openAmount - 1) / 2 }, WHITE);

				wallPos = { centerPos.x, centerPos.y, centerPos.z + tileSize  - (wallThickness - halfSize/2 + (1.5f * halfSize * (1 - state.openAmount)))};
				DrawModelEx(doorModel, wallPos, { 1, 0,0 }, 0, { 1,1, 0.5f + (state.openAmount - 1)/ 2}, WHITE);

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

			if (!IsKeyDown(KEY_X))
			{
				DrawCubeWiresV(buttonPosition, buttonSize, BLACK);
				if (click.color)
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
	bool ChangeColor = false;
	lua_State* L;
public:
	Door1OpenSystem(lua_State* L) : L(L) {};
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
			auto buttonView = registry.view<Door1, Door1State>();
			for (auto entity : buttonView)
			{
				
				lua_getglobal(L, "openDoorCoroutine");
				lua_pushinteger(L, (uint32_t)entity);

				if (lua_pcall(L, 1, 1, 0) != LUA_OK)
				{
					std::cerr << "Lua error: " << lua_tostring(L, -1) << std::endl;
					lua_pop(L, 1);
				}
				else
				{
					if (!lua_isthread(L, -1))
					{
						std::cerr << "Fel: Lua returnerade inte en coroutine!" << std::endl;
						lua_pop(L, 1);
					}
					else
					{
						lua_State* thread = lua_tothread(L, -1);
						int coroutineRef = luaL_ref(L, LUA_REGISTRYINDEX);
						registry.emplace_or_replace<CoroutineComponent>(entity, CoroutineComponent{ coroutineRef });
					}
				}
				view.each([&](Button1click& click) {
					click.clicked = false;
					});

			}
	
		}
		auto doorView = registry.view<Door1State>();
		doorView.each([&](Door1State& door) {
			view.each([&](Button1click& click) {
				if (door.isClosing || click.clicked)
				{
					click.color = true;

				}
				else
					click.color = false;
				});
			});
		return false;
	};
};

//System that makes the player not collide with walls
class PlayerCollisionSystem : public System
{
	float timeSinceLastAdded = 0;
	SelfVector3 lastValidPos = { 0.0f, 0.0f, 0.0f };

public:
	PlayerCollisionSystem() = default;
	bool OnUpdate(entt::registry& registry, float delta)
	{
		BoundingBox playerCollider;
		Vector2 playerPos;
		std::vector<BoundingBox> wallBBs;
		std::vector<BoundingBox> doorBBs;

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
					collider.PosX - collider.size.X / 2 ,
					collider.PosY - collider.size.Y / 2,
					collider.PosZ - collider.size.Z / 2 },

				Vector3{
					collider.PosX + collider.size.X / 2,
					collider.PosY + collider.size.Y / 2,
					collider.PosZ + collider.size.Z / 2}
				};
				wallBBs.push_back(wallBB);
			}
			});

		//get relevant door BBs
		auto view3 = registry.view<Door1, Collider, Door1State>();
		view3.each([&](Door1& door, Collider& collider, Door1State& state) {
			//calculate length to doors to only do collison checks on closed doors
			Vector2 doorWorldPos = { door.PosX, door.PosZ };
			Vector2 distanceVec = { playerPos.x - doorWorldPos.x, playerPos.y - doorWorldPos.y };
			float length = sqrt(pow(distanceVec.x, 2) + pow(distanceVec.y, 2));

			if (length < 6)
			{
				BoundingBox doorBB1; 
				if (door.north)
				{
					doorBB1 = {
					Vector3{
						collider.PosX - collider.size.X / 2,
						collider.PosY - collider.size.Y / 2,
						collider.PosZ - collider.size.Z / 2},
					Vector3{
						collider.PosX - collider.size.X / 2 * (1 - state.openAmount),
						collider.PosY + collider.size.Y / 2,
						collider.PosZ + collider.size.Z / 2 }
					};
				}
				else
				{

					doorBB1 = {
						Vector3{
							collider.PosX - collider.size.X / 2,
							collider.PosY - collider.size.Y / 2,
							collider.PosZ - collider.size.Z / 2},
						Vector3{
							collider.PosX + collider.size.X / 2,
							collider.PosY + collider.size.Y / 2,
							collider.PosZ - collider.size.Z / 2 * (1 - state.openAmount)}
						};
				}

				BoundingBox doorBB2; 
				if (door.north) 
				{
					doorBB2 = {
						Vector3{
							collider.PosX + collider.size.X / 2 * (1 - state.openAmount),
							collider.PosY - collider.size.Y / 2,
							collider.PosZ - collider.size.Z / 2},
						Vector3{
							collider.PosX + collider.size.X / 2,
							collider.PosY + collider.size.Y / 2,
							collider.PosZ + collider.size.Z / 2}
					};
				}
				else
				{
					doorBB2 = {
						Vector3{
							collider.PosX - collider.size.X / 2 ,
							collider.PosY - collider.size.Y / 2,
							collider.PosZ + collider.size.Z / 2 * (1 - state.openAmount)},
						Vector3{
							collider.PosX + collider.size.X / 2,
							collider.PosY + collider.size.Y / 2,
							collider.PosZ + collider.size.Z / 2}
											};

				}
				doorBBs.push_back(doorBB1);
				doorBBs.push_back(doorBB2);			}
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
			for (int i = 0; i < doorBBs.size(); i++)
			{
				if (CheckCollisionBoxes(doorBBs[i], playerCollider))
				{

					player.Pos = this->lastValidPos;
					timeSinceLastAdded += delta;
					if (timeSinceLastAdded > 90.0f) {

						auto lossView = registry.view<LossTrigger>();
						lossView.each([&](LossTrigger& trigger) {
							*trigger.lossFlag = true;

							});
						timeSinceLastAdded = 0.0f;
					}
				}
			}

			this->lastValidPos = player.Pos;
			});

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

	std::string block = "setWall";
	float timeSinceLastAdd = 0.0f;

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
		timeSinceLastAdd += delta;
		auto camView = registry.view<CameraComponent>();
		camView.each([&](CameraComponent camCom) {

			entt::entity clickedEntity = entt::null;
			auto view = registry.view<Floor>();
			view.each([&](entt::entity entity, Floor& floor) {
				Vector3 floorPosition = { floor.PosX, 0.0f, floor.PosZ };
				Vector3 floorSize = { this->tileSize, 0.1f, this->tileSize };

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

				// Change color of the floor if hovered
				if (isHovered)
					floorModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].color = BLUE;
					
				else
					floorModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].color = WHITE;

				
				// Change which block the player wants to use
				if (IsKeyDown(KEY_ONE)) {
					block = "setWall";
				}
				else if (IsKeyDown(KEY_TWO)) {
					block = "setButton1";
				}
				else if (IsKeyDown(KEY_THREE)) {
					block = "setDoorNorth";
				}
				else if (IsKeyDown(KEY_FOUR)) {
					block = "setDoorWest";
				}
				else if (IsKeyDown(KEY_FIVE)) {
					block = "setGoal";
				}
				else if (IsKeyDown(KEY_SIX)) {
					block = "setPlayer";
				}

				// Add row or collumn
				else if (IsKeyPressed(KEY_SEVEN) && timeSinceLastAdd > 1.0f) {
					timeSinceLastAdd = 0.0f;

					float maxPosX = 0.0f;
					float maxPosZ = 0.0f;
					auto posView = registry.view<Floor>();
					posView.each([&](entt::entity entity, Floor& floor) {
						if (floor.PosX > maxPosX) maxPosX = floor.PosX;
						if (floor.PosZ > maxPosZ) maxPosZ = floor.PosZ;
						});

					lua_getglobal(L, "createAddRowCoroutine");
					lua_pushinteger(L, maxPosX / MazeConstants::TILE_SIZE);
					lua_pushinteger(L, maxPosZ / MazeConstants::TILE_SIZE);

					if (lua_pcall(L, 2, 2, 0) != LUA_OK) {
						std::cerr << "Lua error: kan ej skapa korutin" << lua_tostring(L, -1) << std::endl;
						lua_pop(L, 1);
					}
					else {

						if (!lua_isthread(L, -2)) {
							std::cerr << "Första return är inte en coroutine!" << std::endl;
							lua_pop(L, 2);
							return;
						}
						if (!lua_isinteger(L, -1)) {
							std::cerr << "Andra return är inte ett entity ID!" << std::endl;
							lua_pop(L, 2);
							return;
						}

						entt::entity entity = (entt::entity)lua_tointeger(L, -1);
						lua_pop(L, 1);

						lua_State* thread = lua_tothread(L, -1);
						int coroutineRef = luaL_ref(L, LUA_REGISTRYINDEX);

						registry.emplace_or_replace<CoroutineComponent>(entity, CoroutineComponent{ coroutineRef });

					}
				}
				else if (IsKeyPressed(KEY_EIGHT) && timeSinceLastAdd > 1.0f  ) {
					timeSinceLastAdd = 0.0f;

					float maxPosX = 0.0f;
					float maxPosZ = 0.0f;
					auto posView = registry.view<Floor>();
					posView.each([&](entt::entity entity, Floor& floor) {
						if (floor.PosX > maxPosX) maxPosX = floor.PosX;
						if (floor.PosZ > maxPosZ) maxPosZ = floor.PosZ;
						});

					lua_getglobal(L, "createAddCollumnCoroutine");
					lua_pushinteger(L, maxPosX / MazeConstants::TILE_SIZE);
					lua_pushinteger(L, maxPosZ / MazeConstants::TILE_SIZE);

					if (lua_pcall(L, 2, 2, 0) != LUA_OK) {
						std::cerr << "Lua error: kan ej skapa korutin" << lua_tostring(L, -1) << std::endl;
						lua_pop(L, 1);
					}
					else {

						if (!lua_isthread(L, -2)) {
							std::cerr << "Första return är inte en coroutine!" << std::endl;
							lua_pop(L, 2);
							return;
						}
						if (!lua_isinteger(L, -1)) {
							std::cerr << "Andra return är inte ett entity ID!" << std::endl;
							lua_pop(L, 2);
							return;
						}
						
						entt::entity entity = (entt::entity)lua_tointeger(L, -1);
						lua_pop(L, 1);

						lua_State* thread = lua_tothread(L, -1); 
						int coroutineRef = luaL_ref(L, LUA_REGISTRYINDEX); 

						registry.emplace_or_replace<CoroutineComponent>(entity, CoroutineComponent{ coroutineRef });

					}
				}
				
				// If Left Mouse is clicked, add the current component onto chosen entity 
				if (isClicked)
				{
					clickedEntity = entity;
					
					lua_getglobal(L, block.c_str());
					lua_pushinteger(L, (uint32_t)clickedEntity);
					lua_pushinteger(L, floor.PosX / MazeConstants::TILE_SIZE);
					lua_pushinteger(L, floor.PosZ / MazeConstants::TILE_SIZE);

					if (lua_pcall(L, 3, 0, 0) != LUA_OK) {
						std::cerr << "Lua error: " << lua_tostring(L, -1) << std::endl;
						lua_pop(L, 1);
					}

				}
				

				if (!IsKeyDown(KEY_X))
				{
					DrawCubeWiresV(floorPosition, floorSize, RED);
					DrawModel(floorModel, floorPosition, 1.0f, GRAY);
				}
				});

				if (IsKeyPressed(KEY_P) && timeSinceLastAdd > 2.0f)
				{
					timeSinceLastAdd = 0.0f;
					EndMode3D();
					std::string filename = "";
					SaveFileName(filename);
					BeginMode3D(*camCom.camera);
					int size = 0;
					std::ofstream file(filename);
					if (!file.is_open()) {
						std::cerr << "Failed to open save file: " << filename << "\n";
						return;
					}
					int players = 0;
					auto view = registry.view<entt::entity>();
					view.each([&](entt::entity entity) {
						size++;
						uint32_t id = static_cast<uint32_t>(entity);

						if (registry.all_of<Floor>(entity))
						{
							auto& floor = registry.get<Floor>(entity);
							file << "entity: " << std::to_string(id) << " 'floor' posX: " << floor.PosX / MazeConstants::TILE_SIZE << " posZ: " << floor.PosZ / MazeConstants::TILE_SIZE << std::endl;
						}
						else if (registry.all_of<Wall>(entity))
						{
							auto& wall = registry.get<Wall>(entity);
							file << "entity: " << std::to_string(id) << " 'wall' posX: " << wall.PosX / MazeConstants::TILE_SIZE << " posZ: " << wall.PosZ / MazeConstants::TILE_SIZE << std::endl;
						}
						else if (registry.all_of<Button1>(entity))
						{
							auto& button = registry.get<Button1>(entity);
							file << "entity: " << std::to_string(id) << " 'button' posX: " << button.PosX / MazeConstants::TILE_SIZE << " posZ: " << button.PosZ / MazeConstants::TILE_SIZE << std::endl;
						}
						else if (registry.all_of<Door1>(entity))
						{
							auto& door = registry.get<Door1>(entity);
							file << "entity: " << std::to_string(id) << " 'door' posX: " << door.PosX / MazeConstants::TILE_SIZE << " posZ: " 
								<< door.PosZ / MazeConstants::TILE_SIZE << " north: " << (door.north == true ? "true" : "false") << std::endl;
						}
						else if (registry.all_of<Goal>(entity))
						{
							auto& goal = registry.get<Goal>(entity);
							file << "entity: " << std::to_string(id) << " 'goal' posX: " << goal.PosX / MazeConstants::TILE_SIZE << " posZ: " << goal.PosZ / MazeConstants::TILE_SIZE << std::endl;
						}
						else if (registry.all_of<Player>(entity))
						{
							auto& player = registry.get<Player>(entity);
							if (static_cast<uint32_t>(entity) != 25) {
								file << "entity: " << std::to_string(size) << " 'player' posX: " << player.Pos.X << " posZ: " << player.Pos.Z << std::endl;
									players++;


							}
						}
					});
					
					if(players == 0)
						file << "entity: " << std::to_string(size - 1) << " 'player' posX: " << 1 << " posZ: " << 1 << std::endl;


					file.close();

					std::cout << "File Saved! " << std::endl;
				}
			});
		return false;
	};
};

class CoroutineSystem : public System {
	lua_State* L;
public:
	CoroutineSystem(lua_State* L) : L(L) {}

	bool OnUpdate(entt::registry& registry, float delta) override {
		auto view = registry.view<CoroutineComponent>();

		std::vector<entt::entity> finishedCoroutines;

		for (auto entity : view) {
			
			auto& coro = view.get<CoroutineComponent>(entity);
			lua_rawgeti(L, LUA_REGISTRYINDEX, coro.coroutineRef);
			if (!lua_isthread(L, -1)) {
				std::cerr << "VARNING: coroutineRef " << coro.coroutineRef << " är inte en Lua-thread!" << std::endl;
				lua_pop(L, 1);
				continue;
			}

			lua_State* co = lua_tothread(L, -1);
			lua_pop(L, 1);

			int nresults = 0;
			int status = lua_resume(co, nullptr, 0, &nresults);

			if (status == LUA_OK) {
				// Coroutine klar, ta bort komponent och unref
				luaL_unref(L, LUA_REGISTRYINDEX, coro.coroutineRef);
				registry.remove<CoroutineComponent>(entity);
			}
			else if (status != LUA_YIELD) {
				std::cerr << "Lua coroutine error: " << lua_tostring(L, -1) << std::endl;
				lua_pop(co, 1);
				luaL_unref(L, LUA_REGISTRYINDEX, coro.coroutineRef);
				registry.remove<CoroutineComponent>(entity);
			}

		}

		return false;
	}
};
