#include "main_menu.hpp"

GameState main_menu::draw()
{
    ClearBackground(SKYBLUE);
    DrawText("Maze Game!", 200, 100, 60, BLACK);
    DrawText("Press [Enter] to start the game", 200, 200, 30, BLACK);
    DrawText("Press [ESCAPE] to QUIT", 200, 300, 30, BLACK);

    if (IsKeyPressed(KEY_ENTER))
    {
        return GameState::PLAYING;
    }
    if (IsKeyPressed(KEY_ESCAPE))
    {
        return GameState::QUIT;
    }
    return GameState::MAIN_MENU;
}
