#include "Scene.hpp"

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