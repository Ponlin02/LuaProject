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

// Editing tool
// Make it possible to move side ways looking down in a 2D view
// New class or a definition to change when in editing tool?

class PlayerEditControllSystem : public System
{
	int hej = 0;

public:
	PlayerEditControllSystem() = default;
	bool OnUpdate(entt::registry& registry, float delta)
	{

		// UpdateCamera is a function of 3D perspective
		// This code is manual and act in 2D which is the requested format

		auto view = registry.view<Player, CameraComponent, Collider>();
		view.each([&](Player& player, CameraComponent camCom, Collider& collider) {

			// Movement
			float speed = 1.0f * delta;

			if (IsKeyDown(KEY_W)) player.Pos.Z -= speed;
			if (IsKeyDown(KEY_S)) player.Pos.Z += speed;
			if (IsKeyDown(KEY_A)) player.Pos.X -= speed;
			if (IsKeyDown(KEY_D)) player.Pos.X += speed;

			// Kamera setup
			camCom.camera->projection = CAMERA_ORTHOGRAPHIC;
			camCom.camera->position = { player.Pos.X, 1.0f, player.Pos.Z };
			camCom.camera->target = { player.Pos.X, 0.0f, player.Pos.Z };
			camCom.camera->up = { 0.0f, 0.0f, -1.0f };

			// Uppdatera collider (om du behöver kollision även i edit-mode)
			collider.PosX = player.Pos.X;
			collider.PosY = player.Pos.Y;
			collider.PosZ = player.Pos.Z;
			});
		return false;
	};
	
};
