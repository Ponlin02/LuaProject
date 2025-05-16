#include "player.hpp"

player::player()
{
	this->position = { 0.0f, 0.0f, -10.0f };
}

void player::update()
{
	if (IsKeyDown(KEY_W)) this->position.y += 10.0f * GetFrameTime();
	if (IsKeyDown(KEY_S)) this->position.y -= 10.0f * GetFrameTime();
	if (IsKeyDown(KEY_A)) this->position.x -= 10.0f * GetFrameTime();
	if (IsKeyDown(KEY_D)) this->position.x += 10.0f * GetFrameTime();

	if (IsKeyDown(KEY_UP)) this->position.z -= 10.0f * GetFrameTime();
	if (IsKeyDown(KEY_DOWN)) this->position.z += 10.0f * GetFrameTime();
}

void player::draw()
{
	DrawSphere(this->position, 0.5, BLUE);
}
