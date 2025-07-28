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

	luaL_dofile(L, "comTest.lua");

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
	/*else if (IsKeyPressed(KEY_SEVEN)) {

		float maxPosX = 0.0f;
		float maxPosZ = 0.0f;
		auto posView = scene.GetRegistry().view<Floor>();
		posView.each([&](entt::entity entity, Floor& floor) {
			if (floor.PosX > maxPosX) maxPosX = floor.PosX;
			if (floor.PosZ > maxPosZ) maxPosZ = floor.PosZ;
			});

		lua_getglobal(L, "createAddCollumnCoroutine");
		lua_pushinteger(L, maxPosX / MazeConstants::TILE_SIZE);
		lua_pushinteger(L, maxPosZ / MazeConstants::TILE_SIZE);

		if (lua_pcall(L, 2, 1, 0) != LUA_OK) {
			std::cerr << "Lua error: kan ej skapa korutin" << lua_tostring(L, -1) << std::endl;
			lua_pop(L, 1);
		}
		
		
		
		
		int coroutineRef = luaL_ref(L, LUA_REGISTRYINDEX);
		int entity = scene.CreateEntity();
		scene.SetComponent(entity, CoroutineComponent{ coroutineRef });
	}*/
	DrawText("Objects!", 1000, 100, 60, BLACK);
	DrawText("1. Wall", 1100, 200, 30, color == 1 ? SKYBLUE : BLACK);
	DrawText("2. Button", 1100, 260, 30, color == 2 ? SKYBLUE : BLACK);
	DrawText("3. Door", 1100, 320, 30, color == 3 ? SKYBLUE : BLACK);
	DrawText("4. Goal", 1100, 380, 30, color == 4 ? SKYBLUE : BLACK);
	DrawText("5. Add Row", 1100, 440, 30, BLACK);
	DrawText("6. Add Collumn", 1100, 500, 30, BLACK);

	

	if (IsKeyPressed(KEY_ESCAPE))
	{
		return GameState::MAIN_MENU;
	}

	return GameState::EDIT;
}
