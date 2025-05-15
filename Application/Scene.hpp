#include "entt.hpp"
#include <iostream>
#include <stdlib.h>

#include <Windows.h>

struct Health
{
	float Value;
	Health(float value) : Value(value) {}
};

struct Poison
{
	float TickDamage;
	Poison(float tickDamage) : TickDamage(tickDamage) {}
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

public: 
	Scene() = default;
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
