#include "rayLibTest.hpp"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include "raylib.h"

void rayLib::run()
{
    InitWindow(800, 450, "raylib separated!");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Running separately from Lua!", 180, 200, 20, DARKGRAY);
        EndDrawing();
    }
    CloseWindow();
}
