#include "game.hpp"

Game::Game(lua_State* L)
{
    //ECS scene
    Scene::lua_openscene(L, &this->scene);

    //test with lua
    luaL_dofile(L, "scripts/default_scene.lua");

    //find the player entity and give it a raylib camera
    for (int i = 0; i < this->scene.GetEntityCount(); i++)
    {
        if (this->scene.IsEntity(i) && this->scene.HasComponents<Player>(i))
        {
            this->player.getCamera().target = { scene.GetComponent<Player>(i).Pos.X, 1, 100 };
            this->scene.SetComponent(i, CameraComponent{ &this->player.getCamera() });
            this->scene.SetComponent(i, WinTrigger{ &this->hasWon });
            break; //only ONE player!!
        }
    }

    //systems
    scene.CreateSystem<FloorRenderSystem>();
    scene.CreateSystem<WallRenderSystem>();
    scene.CreateSystem<Door1RenderSystem>();
    scene.CreateSystem<Button1RenderSystem>();
    scene.CreateSystem<GoalRenderSystem>();
    scene.CreateSystem<GoalCollisionSystem>();
    scene.CreateSystem<Button1ClickSystem>();
    scene.CreateSystem<Door1OpenSystem>();
    scene.CreateSystem<BBSystem>();
    scene.CreateSystem<PlayerRenderSystem>();
    scene.CreateSystem<PlayerControllerSystem>();
    scene.CreateSystem<PlayerCollisionSystem>();
}

GameState Game::run(lua_State* L)
{
    ClearBackground(RAYWHITE);

    BeginMode3D(this->player.getCamera());

    //update all systems
    this->scene.UpdateSystems(1);

    EndMode3D();

    if (IsKeyPressed(KEY_ESCAPE))
    {
        return GameState::PAUSED;
    }

    if (this->hasWon)
    {
        return GameState::WIN;
    }

    return GameState::PLAYING;
}
