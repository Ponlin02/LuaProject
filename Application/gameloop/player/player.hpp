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

	Vector3 getPosition(); //might not need?
	void setPosition(Vector3& position); //might not need?
	Camera& getCamera();

private:
	Vector3 position;
	Camera camera = { 0 };
};

//System that renders the player move
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
			Vector2 wallWorldPos = { wall.PosX * collider.size.X, wall.PosZ * collider.size.Z };
			Vector2 distanceVec = { playerPos.x - wallWorldPos.x, playerPos.y - wallWorldPos.y };
			float length = sqrt(pow(distanceVec.x, 2) + pow(distanceVec.y, 2));

			if (length < 10)
			{
				BoundingBox wallBB = {
				Vector3{
					collider.PosX * collider.size.X - collider.size.X / 2,
					collider.PosY - collider.size.Y / 2,
					collider.PosZ * collider.size.Z - collider.size.Z / 2},

				Vector3{
					collider.PosX * collider.size.X + collider.size.X / 2,
					collider.PosY + collider.size.Y / 2,
					collider.PosZ * collider.size.Z + collider.size.Z / 2}
				};
				wallBBs.push_back(wallBB);
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
