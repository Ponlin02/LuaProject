#include "edit.h"

Edit::Edit(lua_State* L)
{
	//ECS scene
	Scene::lua_openscene(L, &this->scene);
}

GameState Edit::run(lua_State* L)
{
	ClearBackground(RAYWHITE);

	if (IsKeyPressed(KEY_ESCAPE))
	{
		return GameState::MAIN_MENU;
	}

	return GameState::EDIT;
}
