#include "loss_text.h"

GameState Loss_text::draw()
{
    ClearBackground(RED);
    DrawText("YOU LOST!", 200, 100, 140, BLACK);
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
    return GameState::LOSS;
}
