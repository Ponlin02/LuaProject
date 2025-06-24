#include "gameloop.hpp"
#include "raylib.h"

#include "placeholder/main_menu.hpp"
#include "placeholder/game.hpp"
#include "placeholder/paused.hpp"

void Gameloop::run(lua_State* L)
{
    //Preparing stuff
    InitWindow(1280, 720, "Maze Game!");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    GameState currentState = MAIN_MENU;

    Main_menu main_menu;
    Paused paused;
    Game* game = nullptr;

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
            //game.run(L);
            break;

        case PAUSED:
            currentState = paused.draw();
            break;

        case WIN:
            break;

        default:
            break;
        }

        EndDrawing();
    }

    delete game;
    CloseWindow();
}
