#include "paused.hpp"

GameState paused::draw()
{
    ClearBackground(DARKBLUE);
    DrawText("Paused!", 200, 100, 60, BLACK);
    DrawText("Press [Enter] to keep playing", 200, 200, 30, BLACK);
    DrawText("Press [ESCAPE] to go to main menu", 200, 300, 30, BLACK);

    if (IsKeyPressed(KEY_ENTER))
    {
        return GameState::PLAYING;
    }
    if (IsKeyPressed(KEY_ESCAPE))
    {
        return GameState::MAIN_MENU;
    }
    return GameState::PAUSED;
}
