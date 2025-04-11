#include "gameloop.hpp"
#include "raylib.h"

#include "../maze/maze.hpp" 
#include "../player/player.hpp"

void gameloop::run()
{
    //Preparing stuff
    InitWindow(800, 450, "Maze Game!");
    SetTargetFPS(60);

    Camera camera = { 0 };
    camera.position = { 0.0f, 2.0f, 6.0f };
    camera.target = { 0.0f, 1.0f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    maze maze;
    player player;

    //The gameloop
    while (!WindowShouldClose())
    {
        //Update values
        player.update();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);
        maze.draw();
        player.draw();
        EndMode3D();

        EndDrawing();
    }

    CloseWindow();
}
