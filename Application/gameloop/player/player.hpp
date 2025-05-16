#pragma once
#include "raylib.h"

class player
{
public:
	player();

	void update();
	void draw();

private:
	Vector3 position;
};