#pragma once
#include "raylib.h"

class player
{
public:
	player();

	void update();
	void draw();
	
	BoundingBox getBoundingBox();
	Vector3 getPosition();
	void setPosition(Vector3& position);

private:
	Vector3 position;
	Vector3 size = {1.0f, 1.0f, 1.0f};
};