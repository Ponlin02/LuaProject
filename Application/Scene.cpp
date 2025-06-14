#include "Scene.hpp"
#include "gameloop/placeholder/constants.h"

Scene::Scene(lua_State* L) : m_luaState(L)
{

}

Scene::~Scene()
{
	for (auto system : m_systems) {
		system = nullptr;
	}
}

// ECS function for c++ interface

int Scene::GetEntityCount()
{
	int count = 0;
	
	auto view = m_registry.view<entt::entity>();
	view.each([&](entt::entity) {
		count++;
		});

	return count;
}

int Scene::CreateEntity() 
{
	return (int)m_registry.create();

}

bool Scene::IsEntity(int entity)
{
	return m_registry.valid((entt::entity)entity);
}

void Scene::RemoveEntity(int entity)
{
	m_registry.destroy((entt::entity)entity);
}

void Scene::UpdateSystems(float delta)
{
	for (auto it = m_systems.begin(); it != m_systems.end();)
	{
		if ((*it)->OnUpdate(m_registry, delta)) {
			delete (*it);
			it = m_systems.erase(it);
		}
		else
		{
			++it;
		}
	}
}

// Wrappers for the ECS functions for use in lua

Scene* Scene::lua_GetSceneUpValue(lua_State* L)
{
	Scene* scene = nullptr;
	if (lua_isuserdata(L, lua_upvalueindex(1)))
	{
		scene = (Scene*)lua_touserdata(L, lua_upvalueindex(1));
	}
	return scene;
}

int Scene::lua_GetEntityCount(lua_State* L)
{
	Scene* scene = lua_GetSceneUpValue(L);
	int count = scene->GetEntityCount();
	lua_pushinteger(L, count);
	return 1;
}

int Scene::lua_CreateEntity(lua_State* L)
{
	Scene* scene = lua_GetSceneUpValue(L);
	int entity = scene->CreateEntity();
	lua_pushinteger(L, entity);
	return 1;
}

int Scene::lua_IsEntity(lua_State* L)
{
	Scene* scene = lua_GetSceneUpValue(L);
	int entity = lua_tointeger(L, 1);
	bool alive = scene->IsEntity(entity);
	lua_pushboolean(L, alive);
	return 1;
}

int Scene::lua_RemoveEntity(lua_State* L)
{
	Scene* scene = lua_GetSceneUpValue(L);
	int entity = lua_tointeger(L, 1);
	scene->RemoveEntity(entity);
	return 0;
}

int Scene::lua_HasComponent(lua_State* L) 
{
	Scene* scene = lua_GetSceneUpValue(L);
	int entity = lua_tointeger(L, 1);
	std::string type = lua_tostring(L, 2);

	bool hasComponent = false;

	if (type == "health") {
		hasComponent = scene->HasComponents<Health>(entity);
	}
	else if (type == "poison") {
		hasComponent = scene->HasComponents<Poison>(entity);
	}
	else if (type == "transform") {
		hasComponent = scene->HasComponents<SelfTransform>(entity);
	}
	else if (type == "floor") {
		hasComponent = scene->HasComponents<Floor>(entity);
	}
	else if (type == "wall") {
		hasComponent = scene->HasComponents<Wall>(entity);
	}
	else if (type == "collider") {
		hasComponent = scene->HasComponents<Collider>(entity);
	}
	else if (type == "player") {
		hasComponent = scene->HasComponents<Player>(entity);
	}

	lua_pushboolean(L, hasComponent);
	return 1;

}

int Scene::lua_GetComponent(lua_State* L)
{

	Scene* scene = lua_GetSceneUpValue(L);

	if (!lua_isinteger(L, 1) || !lua_isstring(L, 2))
	{
		lua_pushnil(L);
		return 1;
	}

	int entity = lua_tointeger(L, 1);
	std::string type = lua_tostring(L, 2);

	if (!scene->IsEntity(entity))
	{
		lua_pushnil(L);
		return 1;
	}

	if (type == "health" && scene->HasComponents<Health>(entity))
	{
		Health& health = scene->GetComponent<Health>(entity);
		lua_pushnumber(L, health.Value);
		return 1;
	}
	else if (type == "poison" && scene->HasComponents<Poison>(entity))
	{
		Poison& poison = scene->GetComponent<Poison>(entity);
		lua_pushnumber(L, poison.TickDamage);
		return 1;
	}
	else if (type == "transform" && scene->HasComponents<SelfTransform>(entity))
	{
		SelfTransform& transform = scene->GetComponent<SelfTransform>(entity);
		lua_pushtransform(L, transform);
		return 1;
	}
	else if (type == "floor" && scene->HasComponents<Floor>(entity))
	{
		Floor& floor = scene->GetComponent<Floor>(entity);
		lua_pushnumber(L, floor.PosX);
		lua_pushnumber(L, floor.PosZ);
		return 2;
	}
	else if (type == "wall" && scene->HasComponents<Floor>(entity))
	{
		Wall& wall = scene->GetComponent<Wall>(entity);
		lua_pushnumber(L, wall.PosX);
		lua_pushnumber(L, wall.PosZ);
		return 2;
	}
	else if (type == "collider" && scene->HasComponents<Collider>(entity))
	{
		Collider& collider = scene->GetComponent<Collider>(entity);
		lua_pushnumber(L, collider.PosX);
		lua_pushnumber(L, collider.PosY);
		lua_pushnumber(L, collider.PosZ);
		lua_pushvector(L, collider.size);
		return 4;
	}
	else if (type == "player" && scene->HasComponents<Player>(entity))
	{
		Player& player = scene->GetComponent<Player>(entity);
		lua_pushnumber(L, player.Pos.X);
		lua_pushnumber(L, player.Pos.Y);
		lua_pushnumber(L, player.Pos.Z);
		return 3;
	}

}

int Scene::lua_SetComponent(lua_State* L)
{
	Scene* scene = lua_GetSceneUpValue(L);

	int entity = lua_tointeger(L, 1);
	std::string type = lua_tostring(L, 2);

	if (type == "health")
	{
		float value = lua_tonumber(L, 3);
		scene->SetComponent<Health>(entity, value);
	}
	else if (type == "poison")
	{
		float tickDamage = lua_tonumber(L, 3);
		scene->SetComponent<Poison>(entity, tickDamage);
	}
	else if (type == "transform")
	{
		SelfTransform transform = lua_totransform(L, 3);
		scene->SetComponent<SelfTransform>(entity);
	}
	else if (type == "floor")
	{
		float posx = lua_tonumber(L, 3);
		float posz = lua_tonumber(L, 4);
		scene->SetComponent<Floor>(entity, posx, posz);
	}
	else if (type == "wall")
	{
		float posx = lua_tonumber(L, 3);
		float posz = lua_tonumber(L, 4);
		scene->SetComponent<Wall>(entity, posx, posz);
		scene->SetComponent<Collider>(entity, posx, MazeConstants::WALL_HEIGHT / 2, posz, 
			MazeConstants::TILE_SIZE, MazeConstants::WALL_HEIGHT, MazeConstants::TILE_SIZE);
	}
	else if (type == "collider")
	{
		float posx = lua_tonumber(L, 3);
		float posy = lua_tonumber(L, 4);
		float posz = lua_tonumber(L, 5);
		float sizex = lua_tonumber(L, 6);
		float sizey = lua_tonumber(L, 7);
		float sizez = lua_tonumber(L, 8);
		scene->SetComponent<Collider>(entity, posx, posy, posz, sizex, sizey, sizez);
	}
	else if (type == "player")
	{
		float posx = lua_tonumber(L, 3);
		float posy = lua_tonumber(L, 4);
		float posz = lua_tonumber(L, 5);
		scene->SetComponent<Player>(entity, posx, posy, posz);
		scene->SetComponent<Collider>(entity, posx, posy, posz, 1.0f, 1.0f, 1.0f);
	}
	else if (type == "behaviour")
	{
		if (scene->HasComponents<BehaviourComponent>(entity))
		{
			scene->RemoveComponent<BehaviourComponent>(entity);
		}

		const char* path = lua_tostring(L, 3);
		
		lua_pushvalue(L, -1);
		int ref = RefAndPushBehaviour(L, entity, path);

		lua_pushinteger(L, entity);
		lua_setfield(L, -2, "ID");

		lua_pushstring(L, path);
		lua_setfield(L, -2, "path");

		lua_getfield(L, -1, "OnCreate");
		lua_pushvalue(L, -2);
		lua_pcall(L, 1, 0, 0);

		scene->SetComponent<BehaviourComponent>(entity, path, ref);
		return 1;

	}

	return 0;

}

int Scene::lua_RemoveComponent(lua_State* L)
{
	Scene* scene = lua_GetSceneUpValue(L);
	int entity = lua_tointeger(L, 1);
	std::string type = lua_tostring(L, 2);

	if (type == "health")
		scene->RemoveComponent<Health>(entity);
	else if (type == "poison")
		scene->RemoveComponent<Poison>(entity);
	else if (type == "transform")
		scene->RemoveComponent<SelfTransform>(entity);
	else if (type == "floor")
		scene->RemoveComponent<Floor>(entity);
	else if (type == "wall")
	{
		scene->RemoveComponent<Wall>(entity);
		if (scene->HasComponents<Collider>(entity))
		{
			scene->RemoveComponent<Collider>(entity);
		}
	}
	else if (type == "collider")
		scene->RemoveComponent<Collider>(entity);
	else if (type == "player")
	{
		scene->RemoveComponent<Player>(entity);
		if (scene->HasComponents<Collider>(entity))
		{
			scene->RemoveComponent<Collider>(entity);
		}
	}
	return 0;
}

void Scene::lua_openscene(lua_State* L, Scene* scene)
{
	lua_newtable(L);
	luaL_Reg sceneMethods[] =
	{
		{"GetEntityCount", lua_GetEntityCount },
		{"CreateEntity", lua_CreateEntity},
		{"IsEntity", lua_IsEntity},
		{"RemoveEntity", lua_RemoveEntity},
		{"HasComponent", lua_HasComponent},
		{"GetComponent", lua_GetComponent},
		{"SetComponent", lua_SetComponent},
		{"RemoveComponent", lua_RemoveComponent},
		{ NULL, NULL}
	};
	lua_pushlightuserdata(L, scene);
	luaL_setfuncs(L, sceneMethods, 1);
	lua_setglobal(L, "scene");
}

int Scene::RefAndPushBehaviour(lua_State* L, int entity, const char* path)
{
	luaL_dofile(L, path);

	lua_pushvalue(L, -1);
	int luaTableRef = luaL_ref(L, LUA_REGISTRYINDEX);

	lua_pushinteger(L, entity);
	lua_setfield(L, -2, "ID");

	lua_pushstring(L, path);
	lua_setfield(L, -2, "path");

	lua_getfield(L, -1, "OnCreate");
	lua_pushvalue(L, -2);
	lua_pcall(L, 1, 0, 0);

	return luaTableRef;
}