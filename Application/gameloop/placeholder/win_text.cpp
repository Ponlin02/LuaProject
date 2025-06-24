#include "win_text.h"

GameState Win_text::draw()
{
    DrawText("YOU WIN!", 200, 100, 140, GREEN);
    DrawText("Press [Enter] to play again", 200, 300, 30, BLACK);
    DrawText("Press [ESCAPE] to go to main menu", 200, 400, 30, BLACK);

    if (IsKeyPressed(KEY_ENTER))
    {
        return GameState::PLAYING;
    }
    if (IsKeyPressed(KEY_ESCAPE))
    {
        return GameState::MAIN_MENU;
    }
    return GameState::WIN;
}
