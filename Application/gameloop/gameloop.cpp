#include "gameloop.hpp"
#include "raylib.h"

#include "placeholder/main_menu.hpp"
#include "placeholder/game.hpp"
#include "placeholder/paused.hpp"

void gameloop::run(lua_State* L)
{
    //Preparing stuff
    InitWindow(1280, 720, "Maze Game!");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    GameState currentState = MAIN_MENU;

    main_menu main_menu;
    game game(L);
    paused paused;

    //The gameloop
    while (!WindowShouldClose() && currentState != GameState::QUIT)
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (currentState)
        {
        case MAIN_MENU:
            currentState = main_menu.draw();
            break;

        case PLAYING:
            currentState = game.run(L);
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

    CloseWindow();
}
