#include "player.hpp"

player::player()
{
	this->position = { 0.0f, 2.0f, -25.0f };

	this->camera.position = this->position;
	this->camera.target = { 0.0f, 1.0f, 0.0f };
	this->camera.up = { 0.0f, 1.0f, 0.0f };
	this->camera.fovy = 45.0f;
	this->camera.projection = CAMERA_PERSPECTIVE;
}

Camera& player::getCamera()
{
	return this->camera;
}
