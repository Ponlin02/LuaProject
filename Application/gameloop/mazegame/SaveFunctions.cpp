#include "SaveFunctions.hpp"
#include "raylib.h"
void SaveFileName(std::string &fileName) {
    while (!WindowShouldClose()) {
        // Hantera tangentinput
        bool fileSaved = false;
        int key = GetCharPressed();
        while (key > 0) {
            if ((key >= 32) && (key <= 125)) {
                fileName += static_cast<char>(key);
            }
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE) && !fileName.empty()) {
            fileName.pop_back();
        }

        if (IsKeyPressed(KEY_ENTER) && !fileName.empty()) {
            
            if (fileName.find(".txt") == std::string::npos) {
                fileName = "maze/mazeloop" + fileName + ".txt";
            }

            fileSaved = true;
        }

        // Rita UI
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Ange ett filnamn att spara (Enter = spara):", 50, 100, 20, DARKGRAY);
        DrawRectangle(50, 140, 500, 40, LIGHTGRAY);
        DrawText(fileName.c_str(), 60, 150, 20, BLACK);

        if (fileSaved) {
            DrawText((" Sparade till: " + fileName).c_str(), 50, 200, 20, DARKGREEN);
        }

        EndDrawing();
    }

}