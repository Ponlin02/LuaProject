#include "game.hpp"

game::game(lua_State* L)
{
    this->camera.position = { 0.0f, 2.0f, 6.0f };
    this->camera.target = { 0.0f, 1.0f, 0.0f };
    this->camera.up = { 0.0f, 1.0f, 0.0f };
    this->camera.fovy = 45.0f;
    this->camera.projection = CAMERA_PERSPECTIVE;

    maze.InitializeMaze(L, this->scene);

    //ECS scene
    Scene::lua_openscene(L, &this->scene);

    //player entity
    //int player = scene.CreateEntity();
    //this->scene.SetComponent(player, Player{ {0.0f, 2.0f, -25.0f} });
    //this->scene.SetComponent(player, CameraComponent{ &this->player.getCamera() });
    //this->scene.SetComponent(player, Collider{ 0.0f, 2.0f, -25.0f, {1.0f, 1.0f, 1.0f} });

    //maze entities
    int Tile0 = scene.CreateEntity();
    this->scene.SetComponent(Tile0, Floor{ 0.0f, -3.0f });
    this->scene.SetComponent(Tile0, Wall{ 0.0f, -3.0f });
    this->scene.SetComponent(Tile0, Collider{ 0.0f, this->wallBBsize.Y / 2, -3.0f, this->wallBBsize });

    int Tile1 = scene.CreateEntity();
    this->scene.SetComponent(Tile1, Floor{ 1.0f, -3.0f });
    this->scene.SetComponent(Tile1, Wall{ 1.0f, -3.0f });
    this->scene.SetComponent(Tile1, Collider{ 1.0f, this->wallBBsize.Y / 2, -3.0f, this->wallBBsize });

    int Tile2 = scene.CreateEntity();
    this->scene.SetComponent(Tile2, Floor{ 0.0f, -4.0f });

    int Tile3 = scene.CreateEntity();
    this->scene.SetComponent(Tile3, Floor{ 1.0f, -4.0f });

    //test with lua
    luaL_dofile(L, "scripts/default_scene.lua");

    //find the player entity and give it a raylib camera
    for (int i = 0; i < this->scene.GetEntityCount(); i++)
    {
        if (this->scene.IsEntity(i) && this->scene.HasComponents<Player>(i))
        {
            this->player.getCamera().target = { scene.GetComponent<Player>(i).Pos.X, 1, 100 };
            this->scene.SetComponent(i, CameraComponent{ &this->player.getCamera() });
            break; //only ONE player!!
        }
    }

    //systems
    scene.CreateSystem<FloorRenderSystem>();
    scene.CreateSystem<WallRenderSystem>();
    scene.CreateSystem<BBSystem>();
    scene.CreateSystem<PlayerRenderSystem>();
    scene.CreateSystem<PlayerControllerSystem>();
    scene.CreateSystem<PlayerCollisionSystem>();
}

GameState game::run(lua_State* L)
{
    ClearBackground(RAYWHITE);

    if (!IsKeyDown(KEY_B))
    {
        BeginMode3D(this->player.getCamera());
    }
    else
    {
        BeginMode3D(this->camera);
    }

    //update all systems
    this->scene.UpdateSystems(1);
    //this->maze.draw(this->player.getCamera(), this->scene);
    EndMode3D();

    if (IsKeyPressed(KEY_ESCAPE))
    {
        return GameState::PAUSED;
    }

    return GameState::PLAYING;
}
