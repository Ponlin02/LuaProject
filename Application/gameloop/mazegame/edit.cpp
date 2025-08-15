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

	luaL_dofile(L, "scripts/utilityFunctions.lua");

	scene.CreateSystem<EditFloorRenderSystem>(L);
	scene.CreateSystem<WallRenderSystem>();
	scene.CreateSystem<GoalRenderSystem>();
	scene.CreateSystem<PlayerEditControllSystem>();
	scene.CreateSystem<Door1RenderSystem>();
	scene.CreateSystem<Button1RenderSystem>();
	scene.CreateSystem<CoroutineSystem>(L);
}

GameState Edit::run(lua_State* L)
{

	Scene::lua_openscene(L, &this->scene);

	ClearBackground(RAYWHITE);

	BeginMode3D(this->player.getCamera());

	this->scene.UpdateSystems(1);

	EndMode3D();

	//Highlight chosen item
	if (IsKeyPressed(KEY_ONE))
		color = 1;
	else if (IsKeyPressed(KEY_TWO))
		color = 2;
	else if (IsKeyPressed(KEY_THREE))
		color = 3;
	else if (IsKeyPressed(KEY_FOUR))
		color = 4;
	else if (IsKeyPressed(KEY_FIVE))
		color = 5;
	else if (IsKeyPressed(KEY_SIX))
		color = 6;
	/*else if (IsKeyPressed(KEY_P)) {
		return GameState::MAIN_MENU;
	}*/
	
	DrawText("PlayerSpawn on tile {1, 1}", 900, 40, 30, BLACK);
	DrawText("Objects!", 1000, 100, 60, BLACK);
	DrawText("1. Wall", 1060, 200, 30, color == 1 ? SKYBLUE : BLACK);
	DrawText("2. Button", 1060, 260, 30, color == 2 ? SKYBLUE : BLACK);
	DrawText("3. Door |", 1060, 320, 30, color == 3 ? SKYBLUE : BLACK);
	DrawText("4. Door <->", 1060, 380, 30, color == 4 ? SKYBLUE : BLACK);
	DrawText("5. Goal", 1060, 440, 30, color == 5 ? SKYBLUE : BLACK);
	DrawText("7. Add Row", 1060, 560, 30, BLACK);
	DrawText("8. Add Collumn", 1060, 620, 30, BLACK);
	DrawText("P. Save file!", 1060, 680, 30, BLACK);

	if (IsKeyPressed(KEY_ESCAPE))
	{
		return GameState::MAIN_MENU;
	}

	return GameState::EDIT;
}
