#include "entt.hpp"
#include <iostream>
class Scene
{

entt::registry m_registry;

public: 
	Scene() = default;
	~Scene() = default;

	int GetEntityCount();

	int CreateEntity();
	bool IsEntity(int entity);
	void RemoveEntity(int entity);
};