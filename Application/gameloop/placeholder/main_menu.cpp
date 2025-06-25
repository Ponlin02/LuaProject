#include "main_menu.hpp"

GameState Main_menu::draw()
{
    ClearBackground(SKYBLUE);
    DrawText("Maze Game!", 200, 100, 60, BLACK);
    DrawText("Press [Enter] to start premade game", 200, 200, 30, BLACK);
    DrawText("Press [E] to edit your own maze", 200, 300, 30, BLACK);
    DrawText("Press ['Some button'] to play your own maze", 200, 400, 30, BLACK);
    DrawText("Press [ESCAPE] to QUIT", 200, 500, 30, BLACK);

    if (IsKeyPressed(KEY_ENTER))
    {
        return GameState::PLAYING;
    }
    if (IsKeyPressed(KEY_E))
    {
        return GameState::EDIT;
    }
    if (IsKeyPressed(KEY_ESCAPE))
    {
        return GameState::QUIT;
    }
    return GameState::MAIN_MENU;
}
