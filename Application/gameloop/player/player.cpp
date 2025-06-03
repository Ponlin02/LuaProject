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

void player::update()
{
	this->camera.position = this->position;

	UpdateCamera(&this->camera, CAMERA_FIRST_PERSON);
	this->position = this->camera.position;
	SetMousePosition(GetScreenWidth() / 2, GetScreenHeight() / 2);

	/*if (IsKeyDown(KEY_W)) this->position.y += 10.0f * GetFrameTime();
	if (IsKeyDown(KEY_S)) this->position.y -= 10.0f * GetFrameTime();
	if (IsKeyDown(KEY_A)) this->position.x -= 10.0f * GetFrameTime();
	if (IsKeyDown(KEY_D)) this->position.x += 10.0f * GetFrameTime();

	if (IsKeyDown(KEY_UP)) this->position.z -= 10.0f * GetFrameTime();
	if (IsKeyDown(KEY_DOWN)) this->position.z += 10.0f * GetFrameTime();*/
}

void player::draw()
{
	DrawSphere(this->position, 0.5, BLUE);
}

BoundingBox player::getBoundingBox()
{
	BoundingBox box = {
		Vector3{
			this->position.x - this->size.x / 2,
			this->position.y - this->size.y / 2,
			this->position.z - this->size.z / 2},

		Vector3{
			this->position.x + this->size.x / 2,
			this->position.y + this->size.y / 2,
			this->position.z + this->size.z / 2}
	};
	return box;
}

Vector3 player::getPosition()
{
	return this->position;
}

void player::setPosition(Vector3& position)
{
	this->position = position;
}

Camera& player::getCamera()
{
	return this->camera;
}
