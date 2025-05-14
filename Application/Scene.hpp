#include "entt.hpp"

class Scene
{

entt::registry m_registry;

public: 
	Scene();
	~Scene();

	int GetEntityCount();

	int CreateEntity();
	bool IsEntity(int entity);
	void RemoveEntity(int entity);
};