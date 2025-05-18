#include "rayLibTest.hpp"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include "raylib.h"

void rayLib::run()
{
    InitWindow(800, 450, "raylib separated!");
    SetTargetFPS(60);

    Camera camera = { 0 };
    camera.position = { 0.0f, 2.0f, 6.0f };
    camera.target = { 0.0f, 1.0f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_ORBITAL); // lets you rotate the camera around!

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        DrawSphere(Vector3{ 0.0f, 1.0f, 0.0f }, 1.0f, RED); // Draw a sphere!
        DrawCube(Vector3{ 2, 1, 0 }, 1, 1, 1, BLUE);

        DrawGrid(10, 1.0f); // helper ground grid

        EndMode3D();

        DrawText("3D Sphere in raylib!", 10, 10, 20, DARKGRAY);

        //DrawCircle(400, 225, 10.0f, GREEN);

        //DrawText("Running separately from Lua!", 180, 200, 20, DARKGRAY);
        EndDrawing();
    }
    CloseWindow();
}
