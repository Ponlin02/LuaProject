#include "game.hpp"

game::game()
{
    this->camera.position = { 0.0f, 2.0f, 6.0f };
    this->camera.target = { 0.0f, 1.0f, 0.0f };
    this->camera.up = { 0.0f, 1.0f, 0.0f };
    this->camera.fovy = 45.0f;
    this->camera.projection = CAMERA_PERSPECTIVE;
}

GameState game::run(lua_State* L)
{
    //Update values
    this->player.update();

    ClearBackground(RAYWHITE);

    if (!isInitialized) {
        maze.InitializeMaze(L, isInitialized);
    }

    BeginMode3D(this->camera);
    this->maze.draw(this->camera);
    this->player.draw();
    EndMode3D();

    if (IsKeyPressed(KEY_ESCAPE))
    {
        return GameState::PAUSED;
    }

    return GameState::PLAYING;
}
