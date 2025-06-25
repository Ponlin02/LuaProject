#pragma once
#include "raylib.h"
#include "../../Scene.hpp"

/*
* Component that cant be with the others
* This is because it uses raylib.
*/
struct CameraComponent 
{
	Camera* camera;

	CameraComponent(Camera* camera) : camera(camera) {}
	CameraComponent() = default;
};

class player
{
public:
	player();
	Camera& getCamera();

private:
	Vector3 position;
	Camera camera = { 0 };
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

//System that makes the player move
class PlayerControllerSystem : public System
{
	int hej = 0;

public:
	PlayerControllerSystem() = default;
	bool OnUpdate(entt::registry& registry, float delta)
	{
		auto view = registry.view<Player, CameraComponent, Collider>();
		view.each([&](Player& player, CameraComponent camCom, Collider& collider) {
			//Create a potential move for the player
			camCom.camera->position = { player.Pos.X, player.Pos.Y, player.Pos.Z };

			UpdateCamera(camCom.camera, CAMERA_FIRST_PERSON);
			player.Pos = { camCom.camera->position.x, camCom.camera->position.y, camCom.camera->position.z };
			collider.PosX = player.Pos.X;
			collider.PosY = player.Pos.Y;
			collider.PosZ = player.Pos.Z;
			SetMousePosition(GetScreenWidth() / 2, GetScreenHeight() / 2);
		});
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
		for (int i = 0; i < wallBBs.size(); i++)
		{
			DrawBoundingBox(wallBBs[i], BLUE);
		}
		DrawBoundingBox(playerCollider, PURPLE);

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
