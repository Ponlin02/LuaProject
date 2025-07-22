#include "edit.h"

Edit::Edit(lua_State* L)
{
	//ECS scene
	Scene::lua_openscene(L, &this->scene);

	luaL_dofile(L, "scripts/edit_default_scene.lua");

	for (int i = 0; i < this->scene.GetEntityCount(); i++)
	{
		if (this->scene.IsEntity(i) && this->scene.HasComponents<Player>(i))
		{
			this->player.getCamera().target = { scene.GetComponent<Player>(i).Pos.X, 1, 100 };
			this->scene.SetComponent(i, CameraComponent{ &this->player.getCamera() });
			break; //only ONE player!!
		}
	}



	scene.CreateSystem<EditFloorRenderSystem>(L);
	scene.CreateSystem<WallRenderSystem>();
	//scene.CreateSystem<PlayerRenderSystem>();
	scene.CreateSystem<PlayerEditControllSystem>();
	//scene.CreateSystem<PlayerCollisionSystem>();
}

GameState Edit::run(lua_State* L)
{
	ClearBackground(RAYWHITE);

	BeginMode3D(this->player.getCamera());

	this->scene.UpdateSystems(1);

	EndMode3D();

	if (IsKeyPressed(KEY_ESCAPE))
	{
		return GameState::MAIN_MENU;
	}

	return GameState::EDIT;
}
