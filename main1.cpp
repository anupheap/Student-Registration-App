#include "include\raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "student.h"
#include "elements.hpp"

// Screens
typedef enum
{
    SCREEN_LOGIN
} GameScreen;

// Main Program
int main()
{

    // Draw the Main Window
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI);
    InitWindow(800, 600, "Student Registration System");
    SetWindowMinSize(800, 600);
    SetTargetFPS(60);
    // Variables
        // Sekuya
        char sekuyaPath[] = "assets\\fonts\\Sekuya-Regular.ttf";
        Font sekuya30 = LoadFontEx(sekuyaPath, 30, 0, 0);
        TextureFilter
        // Orbitron
        char orbitronPath[] = "assets\\fonts\\Orbitron-SemiBold.ttf";
        Font orbitron15 = LoadFontEx(orbitronPath, 15, 0, 0);

    Student student;
    GameScreen currentScreen = SCREEN_LOGIN;
    

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        float textScale = 30.0f * ((float)GetScreenHeight()/400.0f);
        //====LOGIN-SCREEN====
        if (currentScreen == SCREEN_LOGIN)
        {
            Vector2 titleTextScale = MeasureTextEx(sekuya30, "STUDENT LOGIN", textScale, 3.0f);
            float posX = (GetScreenWidth() / 2) - (titleTextScale.x / 2);
            float posY = (GetScreenHeight() / 4) - (titleTextScale.y / 2);
            DrawTextEx(sekuya30, "STUDENT LOGIN", {posX, posY}, textScale, 3.0f, BLACK);
            Vector2 nameTextScale = MeasureTextEx(orbitron15, "Name:", 15.0f, 3.0f);
            DrawTextEx(orbitron15, "Name:", {(GetScreenWidth() / 5) - (nameTextScale.x / 2), (GetScreenHeight() / 3) - (nameTextScale.y / 2)}, 15.0f, 3.0f, DARKGRAY);
            Vector2 IDTextScale = MeasureTextEx(orbitron15, "ID:", 15.0f, 3.0f);
            DrawTextEx(orbitron15, "ID:", {(GetScreenWidth() / 5) - (nameTextScale.x / 2), (GetScreenHeight() / 2.5f) - (nameTextScale.y / 2)}, 15.0f, 3.0f, DARKGRAY);
        }
        EndDrawing();
    }
}
