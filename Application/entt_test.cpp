#include <iostream>
#include "entt/entt.hpp"

//Våra komponenter
struct Position
{
	float x, y;
};

struct Velocity
{
	float dx, dy;
};

int myEnttTest()
{
	entt::registry registry;

	//Skapa en entitet
	auto entity = registry.create();
	registry.emplace<Position>(entity, 10.0f, 20.0f);
	registry.emplace<Velocity>(entity, 1.0f, 5.0f);

	//Simulera ett system: uppdatera position med velocity
	auto view = registry.view<Position, Velocity>();
	view.each([](auto entity, Position& pos, Velocity& vel)
	{
		pos.x += vel.dx;
		pos.y += vel.dy;

		std::cout << "Ny position: (" << pos.x << ", " << pos.y << ")\n";
	});

	return 0;
}