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
