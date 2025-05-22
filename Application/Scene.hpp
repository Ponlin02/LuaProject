#pragma once
#include "entt.hpp"
#include "Transform.hpp"
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include "lua.hpp"

//#include <Windows.h>

struct Health
{
	float Value;
	Health(float value) : Value(value) {}

	Health() = default;
};

struct Button
{
	float size;
};

struct Poison
{
	float TickDamage;
	Poison(float tickDamage) : TickDamage(tickDamage) {}
};

struct BehaviourComponent 
{
	char ScriptPath[64];
	int LuaRef;

	BehaviourComponent(const char* path, int luaRef) : LuaRef(luaRef)
	{
		memset(ScriptPath, '\0', 64);
		strcpy_s(ScriptPath, path);
	}

	BehaviourComponent() = default;
};

struct Floor 
{
	float PosX;
	float PosZ;
	Floor(float posx, float posz) : PosX(posx), PosZ(posz){}
	Floor() = default;
};

struct Wall
{
	float PosX;
	float PosZ;
	Wall(float posx, float posz) : PosX(posx), PosZ(posz) {}
	Wall() = default;
};

struct Player
{
	float PosX;
	float PosZ;
	Player(float posx, float posz) : PosX(posx), PosZ(posz) {}
	Player() = default;
};


class System
{
public:
	virtual bool OnUpdate(entt::registry& registry, float delta) = 0;
};



class Scene
{

	entt::registry m_registry;
	std::vector<System*> m_systems;
	lua_State* m_luaState;

public: 
	Scene() = default;
	Scene(lua_State* L);
	~Scene();

	int GetEntityCount();

	int CreateEntity();
	bool IsEntity(int entity);
	void RemoveEntity(int entity);

	template <typename...Args>
	bool HasComponents(int entity);

	template <typename T>
	T& GetComponent(int entity);

	template <typename T>
	void SetComponent(int entity, const T&);

	template <typename T, typename...Args>
	void SetComponent(int entity, Args...args);

	template <typename T>
	void RemoveComponent(int entity);

	template <typename T, typename ...Args>
	void CreateSystem(Args ... args);

	void UpdateSystems(float delta);

	static void lua_openscene(lua_State* L, Scene* scene);


private: 
	// Lua funktioner så att lua kan skapa en scen
	// Or "make a scene" :D
	static Scene* lua_GetSceneUpValue(lua_State* L);

	static int lua_GetEntityCount(lua_State* L);
	static int lua_CreateEntity(lua_State* L);
	static int lua_IsEntity(lua_State* L);
	static int lua_RemoveEntity(lua_State* L);

	static int lua_HasComponent(lua_State* L);
	static int lua_GetComponent(lua_State* L);
	static int lua_SetComponent(lua_State* L);
	static int lua_RemoveComponent(lua_State* L);
	
	static int RefAndPushBehaviour(lua_State* L, int entity, const char* path);
};


class PoisonSystem : public System
{
	int m_lifetime;
public: 
	PoisonSystem(int lifetime) : m_lifetime(lifetime) {}
	bool OnUpdate(entt::registry& registry, float delta) final
	{
		auto view = registry.view<Health, Poison>();
		view.each([](Health& health, const Poison& poison) {
			health.Value -= poison.TickDamage;
			});

		return (--m_lifetime) <= 0;
	}
};

class CleanupSystem : public System
{
public:
	bool OnUpdate(entt::registry& registry, float delta) final 
	{
		auto view = registry.view<Health>();
		view.each([&](entt::entity entity, const Health& health) {
			if (health.Value <= 0.f) {
				registry.destroy(entity);
			}
			});
		return false;
	}
};

class InfoSystem : public System
{
	int m_updateCounter = 0;
public: 
	InfoSystem() = default;
	bool OnUpdate(entt::registry& registry, float delta) final
	{
		int count = 0;

		auto view = registry.view<entt::entity>();
		view.each([&](entt::entity) {
			count++;
			});
		auto healthView = registry.view<Health>();
		auto poisonView = registry.view<Poison>();
		printf("\n-- Update %i -- \n", ++m_updateCounter);
		printf(" Living entities: \t%i\n",healthView.size());
		printf("\n-- Poisoned entities: \t%i\n ", poisonView.size());
		return false;
	}
};

//class FloorSystem : public System
//{
//	int hej = 0;
//
//public:
//	FloorSystem() = default;
//	bool OnUpdate(entt::registry& registry, float delta);
//	/*{
//		auto view = registry.view<Floor>();
//		view.each([&](entt::entity) {
//			makeFloor();
//			})
//	}*/
//	
//};



template <typename ... Args>
bool Scene::HasComponents(int entity)
{
	return m_registry.all_of<Args...>(
		(entt::entity)entity);
}

template<typename T>
T& Scene::GetComponent(int entity)
{
	return m_registry.get<T>(
		(entt::entity)entity);
}

template<typename T>
void Scene::SetComponent(int entity, const T& component)
{
	m_registry.emplace_or_replace<T>(
		(entt::entity)entity, component);

}

template<typename T, typename ...Args>
void Scene::SetComponent(int entity, Args...args)
{
	m_registry.emplace_or_replace<T>(
		(entt::entity)entity, args...);
}

template<typename T>
void Scene::RemoveComponent(int entity)
{
	m_registry.remove<T>((entt::entity)entity);
}

template<typename T, typename ... Args>
void Scene::CreateSystem(Args ... args)
{
	m_systems.emplace_back(new T(args...));
}
