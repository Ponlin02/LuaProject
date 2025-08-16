#include "gameloop.hpp"
#include "raylib.h"

#include "mazegame/main_menu.hpp"
#include "mazegame/game.hpp"
#include "mazegame/paused.hpp"
#include "mazegame/win_text.h"
#include "mazegame/loss_text.h"
#include "mazegame/edit.h"

void Gameloop::run(lua_State* L)
{
    //Preparing stuff
    InitWindow(1280, 720, "Maze Game!");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    GameState currentState = MAIN_MENU;

    Main_menu main_menu;
    Paused paused;
    Win_text win_text;
    Loss_text loss_text;
    Game* game = nullptr;
    Edit edit(L);

    //The gameloop
    while (!WindowShouldClose() && currentState != GameState::QUIT)
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (currentState)
        {
        case MAIN_MENU:
            currentState = main_menu.draw();
            //reset the game from main menu
            if (currentState == GameState::PLAYING)
            {
                delete game;
                game = new Game(L);

            }
            break;

        case PLAYING:
            currentState = game->run(L);
            break;

        case PAUSED:
            currentState = paused.draw();
            break;

        case WIN:
            game->run(L);
            currentState = win_text.draw();
            if (currentState == GameState::PLAYING)
            {
                delete game;
                game = new Game(L);
            }
            break;
        case LOSS:
            currentState = loss_text.draw();
            if (currentState == GameState::PLAYING)
            {
                delete game;
                game = new Game(L);
            }
            break;
        case EDIT:
            currentState = edit.run(L);
            break;

        default:
            break;
        }

        EndDrawing();
    }
    delete game;
    CloseWindow();
}
