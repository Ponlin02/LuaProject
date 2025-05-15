#include "Scene.hpp"

Scene::~Scene()
{
	for (auto system : m_systems) {
		system = nullptr;
	}
}

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
	for (auto it = m_systems.begin(); it != m_systems.end(); it++)
	{
		if ((*it)->OnUpdate(m_registry, delta)) {
			delete (*it);
			it = m_systems.erase(it);
		}
	}
}