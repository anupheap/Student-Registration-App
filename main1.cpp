#include "include\raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "student.h"
#include "elements.hpp"

// Screens
typedef enum
{
    SCREEN_LOGIN,
    SEMESTER_SCREEN
} GameScreen;

// Main Program
int main()
{
    // Draw the Main Window
    InitWindow(1280, 720, "Student Registration System");
    SetTargetFPS(60);

    // Initialize Fonts
        // Sekuya
        char sekuyaPath[] = "assets\\fonts\\Sekuya-Regular.ttf";
        Font sekuya40 = LoadFontEx(sekuyaPath, 50, 0, 0);
        SetTextureFilter(sekuya40.texture, TEXTURE_FILTER_BILINEAR);
        // Orbitron
        char orbitronPath[] = "assets\\fonts\\Orbitron-SemiBold.ttf";
        Font orbitron30 = LoadFontEx(orbitronPath, 30, 0, 0);

    // Initialize Textures
        //"NEXT" Button Textures
        char nextButtonPath[] = "assets\\textures\\next_button.png";
        char nextButtonHoverPath[] = "assets\\textures\\next_hover.png";
        char nextButtonClickedPath[] = "assets\\textures\\next_pressed.png";

        //"CONFIRM" Button Textures
        char confirmButtonPath[] = "assets\\textures\\confirm_button.png";
        char confirmButtonHoverPath[] = "assets\\textures\\confirm_hover.png";
        char confirmButtonClickedPath[] = "assets\\textures\\confirm_pressed.png";
        //App Icon
        char logoPath[] = "assets\\textures\\student_registration_logo.png";
        Image logo = LoadImage(logoPath);
        ImageResizeNN(&logo, 256, 256);

    //Initialize Classes, Buttons, Text input Boxes and Game Screen
    Student student;
    GameScreen currentScreen = SCREEN_LOGIN;
    
        //"NEXT" Button
        Button next(
            nextButtonPath,
            nextButtonHoverPath,
            nextButtonClickedPath
        );
        //"CONFIRM" button
        Button confirm(
            confirmButtonPath,
            confirmButtonHoverPath,
            confirmButtonClickedPath
        );

    SetWindowIcon(logo);
    //Text, Position, and Scale Variables so that we don't gouge our eyes out when reading the code cuz whAT THE FUCK
    float spacing = 3.0f;
    float titleScale = 50.0f;
    float subtitleScale = 30.0f;
        //"STUDENT LOGIN" text position
        char studentLoginText[] = "STUDENT LOGIN";
        Vector2 getStudentLoginTextScale = MeasureTextEx(sekuya40, studentLoginText, titleScale, spacing);
        Vector2 studentLoginTextPos = {
            (GetScreenWidth()/2) - (getStudentLoginTextScale.x/2),
            (GetScreenHeight()/3.8f) - (getStudentLoginTextScale.y/2)
        };

        //"Name:" text position
        char nameText[] = "Name:";
        Vector2 getNameTextScale = MeasureTextEx(orbitron30, nameText, subtitleScale, spacing);
        Vector2 nameTextPos = {
            (GetScreenWidth() / 3.3f) - (getNameTextScale.x/2),
            (GetScreenHeight() / 2.6f) - (getNameTextScale.y/2)
        };
        //"ID:" text position
        char IDText[] = "ID:";
        Vector2 getIDTextScale = MeasureTextEx(orbitron30, IDText, subtitleScale, spacing);
        Vector2 IDTextPos = {
            (GetScreenWidth() / 2.88f) - (getNameTextScale.x/2),
            (GetScreenHeight() / 1.9f) - (getNameTextScale.y/2)
        };
        Rectangle nameInputBox = {
            GetScreenWidth()/2.8f,
            GetScreenHeight()/2.585f - (getNameTextScale.y/2),
            370,
            30
        };
        Rectangle IDInputBox = {
            GetScreenWidth()/2.8f,
            GetScreenHeight()/1.885f - (getIDTextScale.y/2),
            370,
            30
        };
        
    //Initialize TextBox Buffers
    char errorMessageForName[200] = "\0";
    char errorMessageForID[200] = "\0";
    char nameBuffer[128] = "\0";
    char IDBuffer[128] = "";
    bool nameToggle = false;
    bool IDBoxToggle = false;

    //Initialize Validifiers
    bool nameValidity = false;
    bool IDValidity = false;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        GuiSetStyle(DEFAULT, TEXT_SIZE, 30);
        //====LOGIN-SCREEN====
        if (currentScreen == SCREEN_LOGIN)
        {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            int errorMessageForNameLength = MeasureText(errorMessageForName, 30);
            int errorMessageForNamePosY = (GetScreenHeight()/2 - 15)*1.75f;
            int errorMessageForIDLength = MeasureText(errorMessageForID, 30);
            int errorMessageForIDPosY = (GetScreenHeight()/2 - 15) * 1.95f;
            
            DrawTextEx(sekuya40, studentLoginText,{studentLoginTextPos.x, studentLoginTextPos.y}, titleScale, spacing, BLACK);
            DrawTextEx(orbitron30, nameText, {nameTextPos.x, nameTextPos.y}, subtitleScale, spacing, DARKGRAY);
            if(GuiTextBox(nameInputBox, nameBuffer, 128, nameToggle)){
                nameToggle = !nameToggle;
            };
            DrawTextEx(orbitron30, IDText, {IDTextPos.x, IDTextPos.y}, subtitleScale, spacing, DARKGRAY);
            if(GuiTextBox(IDInputBox, IDBuffer, 100, IDBoxToggle)){
                IDBoxToggle = !IDBoxToggle;
            };
            string ID = string(IDBuffer);
            next.Draw({(float)GetScreenWidth()/2, (float)GetScreenHeight()/1.6f}, 2, 0);
        
            if(next.isPressed()){
                switch (nameInputValidation(nameBuffer)){
                    case (IS_EMPTY):
                        strcpy(errorMessageForName, "[ERROR]\tYour name is Empty!");
                        nameValidity = false;
                        break;
                    case (HAS_PRECEDING_WHITESPACE):
                        strcpy(errorMessageForName, "[ERROR]\tPlease Remove the Preceding Whitespace(s)!");
                        nameValidity = false;
                        break;
                    case (HAS_PROCEDING_WHITESPACE):
                        strcpy(errorMessageForName, "[ERROR]\tPlease remove the Proceding whitespace(s)!");
                        nameValidity = false;
                        break;
                    case (HAS_INBETWEEN_WHITESPACE):
                        strcpy(errorMessageForName, "[ERROR]\tPlease remove the additional whitespace(s)!");
                        nameValidity = false;
                        break;
                    case (HAS_NUMBERS):
                        strcpy(errorMessageForName, "[ERROR]\tText has numbers!");
                        nameValidity = false;
                        break;
                    case (HAS_SYMBOLS):
                        strcpy(errorMessageForName, "[ERROR]\tInvalid Character(s)!");
                        nameValidity = false;
                        break;
                    default:
                        nameValidity = true;
                        strcpy(errorMessageForName, "\0");
                }
                
                switch (IDinputValidation(IDBuffer)){
                    case INVALID_ID_FORMAT:
                        strcpy(errorMessageForID, "[ERROR]\tYour ID should be in 7000XXXXX format!");
                        IDValidity = false;
                        break;
                    case IS_EMPTY:
                        strcpy(errorMessageForID, "[ERROR]\tYour ID is Empty!");
                        IDValidity = false;
                        break;
                    case INSUFFICIENT_CHARACTERS:
                        strcpy(errorMessageForID, "[ERROR]\tYour ID is not exactly 9 digits!");
                        IDValidity = false;
                        break;
                    case HAS_WHITESPACE:
                        strcpy(errorMessageForID, "[ERROR]\tYour ID should not have a Whitespace(s)!");
                        IDValidity = false;
                        break;
                    case HAS_ALPHA_AND_OR_SYMBOLS:
                        strcpy(errorMessageForID, "[ERROR]\tYour ID should only contain Digits!");
                        IDValidity = false;
                        break;
                    default:
                        IDValidity = true;
                        strcpy(errorMessageForID, "\0");
                }
            }
            if (nameValidity && IDValidity){
                currentScreen = SEMESTER_SCREEN; 
            } else {
                DrawText(errorMessageForName, 10, errorMessageForNamePosY, 30, RED);
                DrawText(errorMessageForID, 10, errorMessageForIDPosY, 30, RED);
            }
        }
        if (currentScreen == SEMESTER_SCREEN){
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            DrawText("AAAAAAAAARRRRRRRRMMMMMMM BOOOOOOOOOOOOOOOOOOOOOOY!!!!!!!", 0, GetScreenHeight()/2, 30, GREEN);
        }
        EndDrawing();
    }
}
