#pragma once
#include "gameState.hpp"
#include "raylib.h"
#include "../player/player.hpp"
#include "../maze/maze.hpp"

class game
{
public:
	game();
	bool playerWallCollide();
	GameState run(lua_State* L);

private:
	Camera camera = { 0 };
	//Scene scene;
	Maze maze;
	player player;
	bool isInitialized = false;
};

//class FloorSystem : public System
//{
//	int hej = 0;
//
//public:
//	FloorSystem() = default;
//	bool OnUpdate(entt::registry& registry, float delta)
//	{
//		// Skicka med en bool i makeFloor och kolla om den är true eller inte
//		// Sen tror jag att jag kan hämta entityfan
//
//		//bool isClicked = false;
//		entt::entity clickedEntity = entt::null;
//		Maze maze;
//		auto view = registry.view<Floor>();
//		view.each([&](entt::entity entity, Floor& floor) {
//
//			bool tileClicked = maze.makeFloor(floor.PosX, floor.PosZ);
//			if (clickedEntity == entt::null && tileClicked) {
//				clickedEntity = entity;
//				std::cout << "EntityID: " << (uint32_t)clickedEntity << "Floor is clicked with position " << floor.PosX << " and " << floor.PosZ << std::endl;
//			}
//
//			});
//
//		//if (clickedEntity != entt::null && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
//		//	std::cout << "Floor clicked! EntityID: " << (uint32_t)clickedEntity << std::endl;
//		//}
//
//		return false;
//	};
//};
