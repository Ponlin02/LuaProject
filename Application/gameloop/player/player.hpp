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

	void update();
	void draw();
	
	BoundingBox getBoundingBox();
	Vector3 getPosition();
	void setPosition(Vector3& position);
	Camera& getCamera();

private:
	Vector3 position;
	Vector3 size = {1.0f, 1.0f, 1.0f};
	Camera camera = { 0 };
};