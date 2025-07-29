#include "SaveFunctions.hpp"
#include "raylib.h"
#include <vector>
#include <iostream>
#include <filesystem>


void SaveFileName(std::string &fileName) {
    bool running = true;
    while (!WindowShouldClose() && running) {
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
                fileName = "gameloop/mazegame/Maps/" + fileName + ".txt";
            }

            fileSaved = true;
        }

        if (IsKeyPressed(KEY_ESCAPE)) {
            running = false;
        }

        // Rita UI
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Cancel [ESC]:", 50, 50, 20, DARKGRAY);
        DrawText("Ange ett filnamn att spara (Enter = spara):", 50, 100, 20, DARKGRAY);
        DrawRectangle(50, 140, 500, 40, LIGHTGRAY);
        DrawText(fileName.c_str(), 60, 150, 20, BLACK);

        if (fileSaved) {
            DrawText((" Sparade till: " + fileName).c_str(), 50, 200, 20, DARKGREEN);
        }

        EndDrawing();
    }

}

void LoadMap(lua_State* L)
{
    std::cout << "Current working dir: " << std::filesystem::current_path() << std::endl;
    std::vector<std::string> maps = GetMapFiles("gameloop/mazegame/Maps/");
    int selected = -1;

    while (!WindowShouldClose() && selected < 0) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Välj en karta att ladda:", 50, 40, 20, DARKGRAY);

        for (size_t i = 0; i < maps.size(); ++i) {
            Color color = (i == selected) ? LIGHTGRAY : GRAY;
            Rectangle btn = { 50, 80 + (int)i * 40, 300, 30 };
            if (CheckCollisionPointRec(GetMousePosition(), btn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                selected = static_cast<int>(i);
            }
            DrawRectangleRec(btn, color);
            DrawText(maps[i].c_str(), 60, 85 + (int)i * 40, 20, BLACK);
        }

        EndDrawing();

        if (selected >= 0) {
            std::string chosenMap = "gameloop/mazegame/Maps/" + maps[selected];

            
            lua_pushstring(L, chosenMap.c_str());
            lua_setglobal(L, "MAP_TO_LOAD");

        }

    }
}

std::vector<std::string> GetMapFiles(const std::string& folder) {
    std::vector<std::string> mapFiles;
    for (const auto& entry : std::filesystem::directory_iterator(folder)) {
        if (entry.path().extension() == ".txt") {
            mapFiles.push_back(entry.path().filename().string());
        }
    }
    return mapFiles;
}