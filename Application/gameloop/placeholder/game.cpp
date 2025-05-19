#include "game.hpp"

game::game()
{
    this->camera.position = { 0.0f, 2.0f, 6.0f };
    this->camera.target = { 0.0f, 1.0f, 0.0f };
    this->camera.up = { 0.0f, 1.0f, 0.0f };
    this->camera.fovy = 45.0f;
    this->camera.projection = CAMERA_PERSPECTIVE;
}

bool game::playerWallCollide()
{
    Vector2 playerPos = { this->player.getPosition().x, this->player.getPosition().z };
    std::vector<BoundingBox> relevantBBs = this->maze.getRelevantBBs(playerPos);

    BoundingBox playerBB = this->player.getBoundingBox();
    for (int i = 0; i < relevantBBs.size(); i++)
    {
        if (CheckCollisionBoxes(relevantBBs[i], playerBB)) return true;
    }

    return false;
}

GameState game::run()
{
    //Update values
    Vector3 oldPlayerPosition = this->player.getPosition();
    this->player.update();

    if (this->playerWallCollide())
    {
        this->player.setPosition(oldPlayerPosition);
    }

    ClearBackground(RAYWHITE);
    BeginMode3D(this->camera);
    //UpdateCamera(&this->camera, CAMERA_FIRST_PERSON);
    //SetMousePosition(GetScreenWidth() / 2, GetScreenHeight() / 2);

    DrawBoundingBox(this->player.getBoundingBox(), RED);

    this->maze.draw();
    this->player.draw();
    EndMode3D();

    if (IsKeyPressed(KEY_ESCAPE))
    {
        return GameState::PAUSED;
    }

    return GameState::PLAYING;
}
