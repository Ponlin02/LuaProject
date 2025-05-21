#pragma once
#include "raylib.h"
#include <vector>
#include "../../Scene.hpp"

struct wall
{
	Vector2 position;
	BoundingBox boundingBox;
};


class maze
{
public:
	void InitializeMaze(lua_State*L, bool& isInitialized);
	void makeFloor(float posX, float posZ);
	void makeSlabWall(float posX, float posZ);
	void makeFullWall(float posX, float posZ);
	void makeTunnel(float posX, float posZ, bool north, bool south, bool east, bool west, float time, bool isClicked);
	void makeButton(float posX, float posZ, Camera camera, bool& isClicked);
	void draw(Camera camera);

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
};

class FloorSystem : public System
{
	int hej = 0;

public:
	FloorSystem() = default;
	bool OnUpdate(entt::registry& registry, float delta)
	{
		maze Maze;
		auto view = registry.view<Floor>();
		view.each([&](Floor& floor) {
			Maze.makeFloor(floor.PosX, floor.PosZ);
			});
		return false;
	};
};

class BehaviourSystem : public System
{
	lua_State* L;
public:
	BehaviourSystem(lua_State* L) : L(L) {}
	bool OnActivate(entt::registry& registry)
	{
		auto view = registry.view<Button>();
		view.each([&](Button& button) {
			if (button.activated) {
				auto scriptView = registry.view<BehaviourComponent>();
				scriptView.each([&](BehaviourComponent& script) {

					lua_rawgeti(L, LUA_REGISTRYINDEX, script.LuaRef);
					lua_getfield(L, -1, "OnActivate");

					if (lua_pcall(L, 1, 0, 0) != LUA_OK) {
						DumpError(L);
					}
					lua_pop(L, 1);
					});
			}
			});
	}
	bool OnUpdate(entt::registry& registry, float delta) final
	{
		auto view = registry.view<BehaviourComponent>();

		view.each([&](BehaviourComponent& script) {
			lua_rawgeti(L, LUA_REGISTRYINDEX, script.LuaRef);
			lua_getfield(L, -1, "OnUpdate");
			lua_pushvalue(L, -2);
			lua_pushnumber(L, delta);

			if (lua_pcall(L, 2, 0, 0) != LUA_OK) {
				DumpError(L);
			}

			lua_pop(L, 1);
			});

		return false;
	}
};
class WallSystem : public System
{
	int hej = 0;

public:
	WallSystem() = default;
	bool OnUpdate(entt::registry& registry, float delta)
	{
		maze Maze;
		auto view = registry.view<Wall>();
		view.each([&](Wall& wall) {
			Maze.makeFullWall(wall.PosX, wall.PosZ);

			});
		return false;
	};
};