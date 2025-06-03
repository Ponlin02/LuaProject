#pragma once
#include "gameState.hpp"
#include "raylib.h"
#include "../player/player.hpp"
#include "../maze/maze.hpp"
#include "../../Scene.hpp"

class game
{
public:
	game(lua_State* L);
	bool playerWallCollide();
	GameState run(lua_State* L);

private:
	Camera camera = { 0 };
	maze maze;
	player player;
	Scene scene;

	SelfVector3 wallBBsize = { 5.0f, 4.0f, 5.0f };
};

//System that renders all of the bounding boxes in the scene
class WallBBSystem : public System
{
	int hej = 0;

public:
	WallBBSystem() = default;
	bool OnUpdate(entt::registry& registry, float delta)
	{
		auto view = registry.view<Collider, Wall>();
		view.each([&](Collider& collider, Wall& wall) {
			BoundingBox BB = {
				Vector3{
					collider.PosX * collider.size.X - collider.size.X / 2,
					0,
					collider.PosZ * collider.size.Z - collider.size.Z / 2},

				Vector3{
					collider.PosX * collider.size.X + collider.size.X / 2,
					collider.size.Y,
					collider.PosZ * collider.size.Z + collider.size.Z / 2}
			};

			DrawBoundingBox(BB, RED);
		});
		return false;
	};
};
