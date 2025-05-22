#pragma once
#include "raylib.h"
#include "rcamera.h"
#include "raymath.h"
#include <vector>
#include "../../Scene.hpp"

struct wall
{
	Vector2 position;
	BoundingBox boundingBox;
};


class Maze
{
public:
	void InitializeMaze(lua_State*L, bool& isInitialized);
	bool makeFloor(float posX, float posZ, SelfVector3 cameraPos);
	bool makeButton(float posX, float posZ, SelfVector3 cameraPos);

	void makeSlabWall(float posX, float posZ);
	void makeFullWall(float posX, float posZ);
	void makeTunnel(float posX, float posZ, bool north, bool south, bool east, bool west, float time);
	void draw(Camera camera);
	void GetMazeCamera(Camera& cameraOther);

	std::vector<BoundingBox> getRelevantBBs(Vector2 playerPos);

private:
	float wallHeight = 4.0f;
	float tileSize = 5.0f;

	std::vector<wall> walls;

private:
	void drawHitboxes();
	float wallTime = 1.f;
	bool isClicked = false;

	Scene scene;
	Camera camera;
};

class FloorSystem : public System
{
	lua_State* L;

public:
	FloorSystem(lua_State* L) : L(L) {}
	FloorSystem() = default;
	bool OnUpdate(entt::registry& registry, float delta, SelfVector3 cameraPos)
	{
		// Skicka med en bool i makeFloor och kolla om den är true eller inte
		// Sen tror jag att jag kan hämta entityfan

		//bool isClicked = false;
		entt::entity clickedEntity = entt::null;
		Maze maze;
		auto view = registry.view<Floor>();
		view.each([&](entt::entity entity, Floor& floor) {

			bool tileClicked = maze.makeFloor(floor.PosX, floor.PosZ, cameraPos);
			if  (clickedEntity == entt::null && tileClicked){
				clickedEntity = entity;
				std::cout << "EntityID: " << (uint32_t)clickedEntity << "Floor is clicked with position " << floor.PosX << " and " << floor.PosZ << std::endl;

				auto scriptView = registry.view<BehaviourComponent>();
				scriptView.each([&](BehaviourComponent& script) {

					lua_rawgeti(L, LUA_REGISTRYINDEX, script.LuaRef);

					lua_getfield(L, -1, "time");
					
					int temp = lua_tonumber(L, -1);
					std::cout << temp << std::endl;
					lua_pop(L, 1);

					lua_getfield(L, -1, "OnActivate");
					lua_pushvalue(L, -2);
					lua_pushnumber(L, 1);

					/*if (lua_pcall(L, 2, 0, 0) != LUA_OK) {
						DumpError(L);
					}*/
					lua_pop(L, 1);
					});

			}

			});

		//if (clickedEntity != entt::null && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		//	std::cout << "Floor clicked! EntityID: " << (uint32_t)clickedEntity << std::endl;
		//}

		return false;
	};

	/*bool OnActivate(entt::registry& registry)
	{

	}*/
};

class BehaviourSystem : public System
{
	lua_State* L;
public:
	BehaviourSystem(lua_State* L) : L(L) {}
	bool OnUpdate(entt::registry& registry, float delta, SelfVector3 cameraPos)
	{
		entt::entity clickedEntity = entt::null;
		Maze maze;
		auto view = registry.view<Button>();


		view.each([&](Button& button) {
			
			auto scriptView = registry.view<BehaviourComponent>();
			scriptView.each([&](BehaviourComponent& script) {
				// Draw the button.
				// If return is true then run activate else draw the tunnel
				lua_rawgeti(L, LUA_REGISTRYINDEX, script.LuaRef);

				lua_getfield(L, -1, "OnUpdate");
				lua_pushvalue(L, -2);
				lua_pushnumber(L, 1);
				
				if (lua_pcall(L, 2, 0, 0) != LUA_OK) {
					DumpError(L);
				}
				//lua_pop(L, 1);

				if (maze.makeButton(button.PosX, button.PosZ, cameraPos)) {
					lua_getfield(L, -1, "OnActivate");
					lua_pushvalue(L, -2);
					lua_pushnumber(L, 1);

					if (lua_pcall(L, 2, 0, 0) != LUA_OK) {
						DumpError(L);
					}
					lua_pop(L, 1);

				}

				lua_getfield(L, -1, "time");
				int time = lua_tonumber(L, -1);

				lua_pop(L, 1);

				maze.makeTunnel(1.0, 1.0f, false, false, true, true, time);
				
				


				});
			
		});

		return false;
	}
	bool OnActivate(entt::registry& registry)
	{

	}

};
class WallSystem : public System
{
	int hej = 0;

public:
	WallSystem() = default;
	bool OnUpdate(entt::registry& registry, float delta, SelfVector3 cameraPos)
	{
		Maze maze;
		auto view = registry.view<Wall>();
		view.each([&](Wall& wall) {
			maze.makeFullWall(wall.PosX, wall.PosZ);

			});
		return false;
	};
};