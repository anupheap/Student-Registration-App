#include "raylib.h" // Pointing to your folder
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"         // Your downloaded header
#include "Student.h"        // Your class
#include <string>
#include "elements.hpp"

// Enum to manage which screen we are on
typedef enum { 
    SCREEN_LOGIN, 
    SCREEN_SEMESTER, 
    SCREEN_MENU, 
    SCREEN_REGISTER, 
    SCREEN_RECORD 
} GameScreen;

int main() {
    // 1. Setup Window
    InitWindow(800, 600, "Student Grouping System");
    SetTargetFPS(60);

    // 2. Data Variables
    Student student;
    GameScreen currentScreen = SCREEN_LOGIN;
    
    // 3. UI State Variables (Buffers for text boxes)
    char nameBuffer[128] = "";
    char idBuffer[128] = "";
    bool editName = false;
    bool editID = false;
    
    char semBuffer[10] = "";
    char yearBuffer[10] = "";
    bool editSem = false;
    bool editYear = false;

    // Error Message State
    char errorMessage[128] = "";

    // 4. Main Loop
    while (!WindowShouldClose()) {
        
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // --- SCREEN 1: LOGIN (START UP MODULE) ---
        if (currentScreen == SCREEN_LOGIN) {
            Button confirm((char*)"textures/confirm_button.png", (char*)"textures/confirm_hover.png", (char*)"textures/confirm_pressed.png");
            confirm.Draw({400, 300}, 2, 0);
            DrawText("STUDENT LOGIN", 320, 100, 20, DARKGRAY);

            DrawText("Name:", 200, 185, 20, BLACK);
            if (GuiTextBox((Rectangle){ 280, 180, 250, 30 }, nameBuffer, 128, editName)) editName = !editName;

            DrawText("ID:", 200, 235, 20, BLACK);
            if (GuiTextBox((Rectangle){ 280, 230, 250, 30 }, idBuffer, 128, editID)) editID = !editID;

            // Validation Logic (Button)
            if (confirm.isPressed()) {
                string sName = string(nameBuffer);
                string sID = string(idBuffer);

                if (sName.empty() && confirm.isPressed()) {
                    strcpy(errorMessage, "Error: Name cannot be empty!");
                } else if (sID.length() != 9 && confirm.isPressed()) {
                    strcpy(errorMessage, "Error: ID must be 9 digits!");
                } else if (sID.substr(0, 4) != "7000" && confirm.isPressed()) {
                    strcpy(errorMessage, "Error: ID must start with 7000!");
                } else {
                    student.setName(sName);
                    student.setID(sID);
                    errorMessage[0] = '\0';
                    currentScreen = SCREEN_SEMESTER;
                }
            }
            // Draw Error if exists
            DrawText(errorMessage, 250, 350, 15, RED);
        }

        // --- SCREEN 2: SEMESTER INPUT ---
        else if (currentScreen == SCREEN_SEMESTER) {
            DrawText("SEMESTER DETAILS", 300, 100, 20, DARKGRAY);
            
            DrawText("Semester (1-3):", 150, 185, 20, BLACK);
            if (GuiTextBox((Rectangle){ 320, 180, 100, 30 }, semBuffer, 10, editSem)) editSem = !editSem;

            DrawText("Year (e.g 2024):", 150, 235, 20, BLACK);
            if (GuiTextBox((Rectangle){ 320, 230, 100, 30 }, yearBuffer, 10, editYear)) editYear = !editYear;

            if (GuiButton((Rectangle){ 350, 300, 100, 30 }, "CONFIRM")) {
                // Simplified validation
                string sSem = string(semBuffer);
                string sYear = string(yearBuffer);
                
                if (sSem != "1" && sSem != "2" && sSem != "3") {
                    strcpy(errorMessage, "Error: Semester must be 1, 2 or 3");
                } else {
                    student.setSemester(sSem + "F", sYear);
                    errorMessage[0] = '\0';
                    currentScreen = SCREEN_MENU;
                }
            }
            DrawText(errorMessage, 250, 350, 15, RED);
        }

        // --- SCREEN 3: MAIN MENU ---
        else if (currentScreen == SCREEN_MENU) {
            DrawText(TextFormat("Welcome, %s", student.getName().c_str()), 20, 20, 20, DARKGRAY);
            DrawText("MAIN MENU", 350, 150, 30, BLACK);

            if (GuiButton((Rectangle){ 300, 220, 200, 40 }, "1. Register Grouping")) {
                currentScreen = SCREEN_REGISTER;
            }
            if (GuiButton((Rectangle){ 300, 280, 200, 40 }, "2. View Record")) {
                currentScreen = SCREEN_RECORD;
            }
            if (GuiButton((Rectangle){ 300, 340, 200, 40 }, "0. Exit")) {
                CloseWindow();
                return 0; // Break loop
            }
        }
        
        // --- SCREEN 4: REGISTRATION (Placeholder) ---
        else if (currentScreen == SCREEN_REGISTER) {
            DrawText("REGISTRATION MODULE", 300, 50, 20, DARKGRAY);
            DrawText("Select a Group (Click to simulate):", 100, 100, 20, BLACK);
            
            // Example of Group Selection
            for(int i=0; i<4; i++) {
                if (GuiButton((Rectangle){ 100.0f, 150.0f + (i*50), 100.0f, 40.0f }, GROUP_NAMES[i].c_str())) {
                    // Logic to select group
                }
            }

            if (GuiButton((Rectangle){ 50, 550, 100, 30 }, "BACK")) currentScreen = SCREEN_MENU;
        }

        // --- SCREEN 5: RECORD (Placeholder) ---
        else if (currentScreen == SCREEN_RECORD) {
            DrawText("STUDENT RECORD", 320, 50, 20, DARKGRAY);
            DrawText(TextFormat("Name: %s", student.getName().c_str()), 100, 100, 20, BLACK);
            DrawText(TextFormat("ID: %s", student.getID().c_str()), 100, 130, 20, BLACK);
            
            if (GuiButton((Rectangle){ 50, 550, 100, 30 }, "BACK")) currentScreen = SCREEN_MENU;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}