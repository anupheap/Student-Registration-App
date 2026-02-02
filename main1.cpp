#include "include\raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "student.h"
#include "buttonsAndTextFields.hpp"
#include "textsAndFonts.hpp"

// Screens
typedef enum
{
    SCREEN_LOGIN,
    SEMESTER_SCREEN,
    MAIN_MENU,
    REGISTRATION_SCREEN
} Screen;

// Main Program
int main()
{
    // Draw the Main Window
    InitWindow(1280, 720, "Student Registration System");
    SetTargetFPS(60);

    // Initialize Textures
    //"NEXT" Button Textures
    char nextButtonPath[] = "assets\\textures\\next_button.png";
    char nextButtonHoverPath[] = "assets\\textures\\next_button_hover.png";
    char nextButtonClickedPath[] = "assets\\textures\\button_clicked.png";

    //"CONFIRM" Button Textures
    char confirmButtonPath[] = "assets\\textures\\confirm_button.png";
    char confirmButtonHoverPath[] = "assets\\textures\\confirm_button_hover.png";
    char confirmButtonClickedPath[] = "assets\\textures\\button_pressed.png";
    // App Icon
    char logoPath[] = "assets\\textures\\student_registration_logo.png";
    Image logo = LoadImage(logoPath);
    ImageResizeNN(&logo, 256, 256);

    // Initialize Classes, Buttons, Text input Boxes and Game Screen
    Student student;
    Screen currentScreen = SCREEN_LOGIN;
    textFonts font;
    texts text(font);

    //"NEXT" Button
    Button next(
        nextButtonPath,
        nextButtonHoverPath,
        nextButtonClickedPath);
    //"CONFIRM" button
    Button confirm(
        confirmButtonPath,
        confirmButtonHoverPath,
        confirmButtonClickedPath);

    SetWindowIcon(logo);

    Rectangle firstNameInputBox = {
        GetScreenWidth() / 2.8f,
        GetScreenHeight() / 3.37f - (text.getFirstNameTextScale.y / 2),
        370,
        30};

    Rectangle middleNameInputBox = {
        GetScreenWidth() / 2.8f,
        GetScreenHeight() / 2.47f - (text.getMiddleNameTextScale.y / 2),
        370,
        30};
    Rectangle lastNameInputBox = {
        GetScreenWidth() / 2.8f,
        GetScreenHeight() / 1.95f - (text.getLastNameTextScale.y / 2),
        370,
        30};
    Rectangle IDInputBox = {
        GetScreenWidth() / 2.8f,
        GetScreenHeight() / 1.59f - (text.getIDTextScale.y / 2),
        370,
        30};
    Rectangle semesterInputBox = {
        GetScreenWidth() / 2.8f,
        text.semesterTextPos.y,
        370,
        30};
    Rectangle yearInputBox = {
        GetScreenWidth() / 2.8f,
        text.yearTextPos.y,
        370,
        30};
    char imgPath[] = "output\\assets\\images\\sample.png";
    Image sample = LoadImage(imgPath);
    ImageResizeNN(&sample, 1280, 720);
    Texture2D back = LoadTextureFromImage(sample);
    UnloadImage(sample);

    // Initialize TextBox Buffers
    char errorMessageForFirstName[200] = "\0";
    char errorMessageForMiddleName[200] = "\0";
    char errorMessageForLastName[200] = "\0";
    char errorMessageForID[200] = "\0";
    char errorMessageForSemester[200] = "\0";
    char errorMessageForYear[200] = "\0";
    char firstNameBuffer[128] = "\0";
    char middleNameBuffer[128] = "\0";
    char lastNameBuffer[128] = "\0";
    char IDBuffer[128] = "\0";
    char semesterBuffer[128] = "\0";
    char yearBuffer[128] = "\0";
    bool firstNameToggle = false;
    bool middleNameToggle = false;
    bool lastNameToggle = false;
    bool IDBoxToggle = false;
    bool semesterToggle = false;
    bool yearToggle = false;

    // Initialize Validifiers
    bool firstNameValidity = false;
    bool middleNameValidity = false;
    bool lastNameValidity = false;
    bool IDValidity = false;
    bool semesterValidity = false;
    bool yearValidity = false;
    Color white = WHITE;
    Color purple = {140, 102, 255, 255};
    Color backgroundColor = {49, 46, 56, 255};
    Color baseColor = {36, 34, 43, 255};
    Color baseTextColor = {150, 140, 171, 255};
    Color focusedTextColor = {204, 193, 230, 255};
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(backgroundColor);

        GuiSetFont(font.textboxTorus30);
        GuiSetStyle(DEFAULT, TEXT_SIZE, 30);
        GuiSetStyle(TEXTBOX, BORDER_WIDTH, 3);
        GuiSetStyle(TEXTBOX, BORDER_COLOR_NORMAL, ColorToInt(baseColor));
        GuiSetStyle(TEXTBOX, BASE_COLOR_PRESSED, ColorToInt(backgroundColor));
        GuiSetStyle(TEXTBOX, BORDER_COLOR_PRESSED, ColorToInt(purple));
        GuiSetStyle(TEXTBOX, BORDER_COLOR_FOCUSED, ColorToInt(baseColor));
        GuiSetStyle(TEXTBOX, TEXT_COLOR_PRESSED, ColorToInt(WHITE));
        GuiSetStyle(TEXTBOX, TEXT_COLOR_FOCUSED, ColorToInt(focusedTextColor));
        GuiSetStyle(TEXTBOX, TEXT_COLOR_NORMAL, ColorToInt(baseTextColor));

        //====LOGIN-SCREEN====
        if (currentScreen == SCREEN_LOGIN)
        {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            int errorMessageForFirstNamePosY = (GetScreenHeight() / 2 - 10) * 1.65f;
            int errorMessageForMiddleNamePosY = (GetScreenHeight() / 2 - 10) * 1.75f;
            int errorMessageForLastNamePosY = (GetScreenHeight() / 2 - 10) * 1.85f;
            int errorMessageForIDPosY = (GetScreenHeight() / 2 - 10) * 1.95f;

            firstNameValidity = false;
            middleNameValidity = false;
            lastNameValidity = false;
            IDValidity = false;

            DrawTextEx(font.torus50, text.studentLoginText, {text.studentLoginTextPos.x, text.studentLoginTextPos.y}, text.titleScale, text.spacing, white);
            DrawTextEx(font.torus30, text.firstNameText, {text.firstNameTextPos.x, text.firstNameTextPos.y}, text.subtitleScale, text.spacing, white);
            DrawTextEx(font.torus30, text.middleNameText, {text.middleNameTextPos.x, text.middleNameTextPos.y}, text.subtitleScale, text.spacing, white);
            DrawTextEx(font.torus30, text.lastNameText, {text.lastNameTextPos.x, text.lastNameTextPos.y}, text.subtitleScale, text.spacing, white);
            DrawRectangleRec(firstNameInputBox, baseColor);
            DrawRectangleRec(middleNameInputBox, baseColor);
            DrawRectangleRec(lastNameInputBox, baseColor);
            DrawRectangleRec(IDInputBox, baseColor);
            if (GuiTextBox(firstNameInputBox, firstNameBuffer, 128, firstNameToggle))
            {
                firstNameToggle = !firstNameToggle;
            };
            if (GuiTextBox(middleNameInputBox, middleNameBuffer, 128, middleNameToggle))
            {
                middleNameToggle = !middleNameToggle;
            };
            if (GuiTextBox(lastNameInputBox, lastNameBuffer, 128, lastNameToggle))
            {
                lastNameToggle = !lastNameToggle;
            };
            DrawTextEx(font.torus30, text.IDText, {text.IDTextPos.x, text.IDTextPos.y}, text.subtitleScale, text.spacing, white);
            if (GuiTextBox(IDInputBox, IDBuffer, 10, IDBoxToggle))
            {
                IDBoxToggle = !IDBoxToggle;
            };
            next.Draw({(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 1.34f}, 0.3f, 0);

            if (next.isPressed())
            {
                switch (nameInputValidation(firstNameBuffer))
                {
                case (IS_EMPTY):
                {
                    strcpy(errorMessageForFirstName, "[ERROR]\tYour First Name is Empty!");
                    firstNameValidity = false;
                    break;
                }
                case (HAS_PRECEDING_WHITESPACE):
                {
                    strcpy(errorMessageForFirstName, "[ERROR]\tPlease Remove the Preceding Whitespace(s) from your First name!");
                    firstNameValidity = false;
                    break;
                }
                case (HAS_PROCEDING_WHITESPACE):
                {
                    strcpy(errorMessageForFirstName, "[ERROR]\tPlease remove the Proceding Whitespace(s) from your First Name!");
                    firstNameValidity = false;
                    break;
                }
                case (HAS_WHITESPACE):
                {
                    strcpy(errorMessageForFirstName, "[ERROR]\tPlease remove the additional whitespace(s) from your First Name!");
                    firstNameValidity = false;
                    break;
                }
                case (HAS_NUMBERS):
                {
                    strcpy(errorMessageForFirstName, "[ERROR]\tYour First Name has a Number(s)!");
                    firstNameValidity = false;
                    break;
                }
                case (HAS_SYMBOLS):
                {
                    strcpy(errorMessageForFirstName, "[ERROR]\tYour First Name has an Invalid Character(s)!");
                    firstNameValidity = false;
                    break;
                }
                default:
                {
                    firstNameValidity = true;
                    strcpy(errorMessageForFirstName, "\0");
                }
                }
                switch (nameInputValidation(middleNameBuffer))
                {
                case (HAS_PRECEDING_WHITESPACE):
                {
                    strcpy(errorMessageForMiddleName, "[ERROR]\tPlease Remove the Preceding Whitespace(s) from your Middle Name!");
                    middleNameValidity = false;
                    break;
                }
                case (HAS_PROCEDING_WHITESPACE):
                {
                    strcpy(errorMessageForMiddleName, "[ERROR]\tPlease remove the Proceding whitespace(s) from your Middle Name!");
                    middleNameValidity = false;
                    break;
                }
                case (HAS_WHITESPACE):
                {
                    strcpy(errorMessageForMiddleName, "[ERROR]\tPlease remove the additional whitespace(s)!");
                    middleNameValidity = false;
                    break;
                }
                case (HAS_NUMBERS):
                {
                    strcpy(errorMessageForMiddleName, "[ERROR]\tText has numbers!");
                    middleNameValidity = false;
                    break;
                }
                case (HAS_SYMBOLS):
                {
                    strcpy(errorMessageForMiddleName, "[ERROR]\tInvalid Character(s)!");
                    middleNameValidity = false;
                    break;
                }
                default:
                {
                    middleNameValidity = true;
                    strcpy(errorMessageForMiddleName, "\0");
                }
                }
                switch (nameInputValidation(lastNameBuffer))
                {
                case (IS_EMPTY):
                {
                    strcpy(errorMessageForLastName, "[ERROR]\tYour Last Name is Empty!");
                    lastNameValidity = false;
                    break;
                }
                case (HAS_PRECEDING_WHITESPACE):
                {
                    strcpy(errorMessageForLastName, "[ERROR]\tPlease Remove the Preceding Whitespace(s) from your Last name!");
                    lastNameValidity = false;
                    break;
                }
                case (HAS_PROCEDING_WHITESPACE):
                {
                    strcpy(errorMessageForLastName, "[ERROR]\tPlease remove the Proceding Whitespace(s) from your Last Name!");
                    lastNameValidity = false;
                    break;
                }
                case (HAS_WHITESPACE):
                {
                    strcpy(errorMessageForLastName, "[ERROR]\tPlease remove the additional whitespace(s) from your Last Name!");
                    lastNameValidity = false;
                    break;
                }
                case (HAS_NUMBERS):
                {
                    strcpy(errorMessageForLastName, "[ERROR]\tYour Last Name has a Number(s)!");
                    lastNameValidity = false;
                    break;
                }
                case (HAS_SYMBOLS):
                {
                    strcpy(errorMessageForLastName, "[ERROR]\tYour Last Name has an Invalid Character(s)!");
                    lastNameValidity = false;
                    break;
                }
                default:
                {
                    lastNameValidity = true;
                    strcpy(errorMessageForLastName, "\0");
                }
                }
                switch (IDInputValidation(IDBuffer))
                {
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

            if (firstNameValidity && IDValidity && middleNameValidity && lastNameValidity)
            {
                currentScreen = SEMESTER_SCREEN;
            }
            else
            {
                DrawText(errorMessageForFirstName, 10, errorMessageForFirstNamePosY, 20, RED);
                DrawText(errorMessageForMiddleName, 10, errorMessageForMiddleNamePosY, 20, RED);
                DrawText(errorMessageForLastName, 10, errorMessageForLastNamePosY, 20, RED);
                DrawText(errorMessageForID, 10, errorMessageForIDPosY, 20, RED);
            }
        }
        if (currentScreen == SEMESTER_SCREEN)
        {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            int errorMessageForSemesterPosY = (GetScreenHeight() / 2 - 10) * 1.85f;
            int errorMessageForYearPosY = (GetScreenHeight() / 2 - 10) * 1.95f;

            semesterValidity = false;
            yearValidity = false;

            DrawTextEx(font.torus50, text.semesterDetailsText, text.semesterDetailsTextPos, text.titleScale, text.spacing, white);

            DrawTextEx(font.torus30, text.semesterText, text.semesterTextPos, text.subtitleScale, text.spacing, white);
            DrawRectangleRec(semesterInputBox, baseColor);
            DrawRectangleRec(yearInputBox, baseColor);
            if (GuiTextBox(semesterInputBox, semesterBuffer, 2, semesterToggle)) semesterToggle = !semesterToggle;
            DrawTextEx(font.torus30, text.yearText, text.yearTextPos, text.subtitleScale, text.spacing, white);
            if (GuiTextBox(yearInputBox, yearBuffer, 5, yearToggle)) yearToggle = !yearToggle;
            confirm.Draw({(float)GetScreenWidth() / 2, (float)text.yearTextPos.y + 100}, 0.3f, 0);
            if (confirm.isPressed())
            {
                switch(semesterInputValidation(semesterBuffer)){
                    case (IS_EMPTY):{
                        semesterValidity = false;
                        strcpy(errorMessageForSemester, "[ERROR]\tSemester is Empty!");
                        break;
                    }
                    case (HAS_WHITESPACE):{
                        semesterValidity = false;
                        strcpy(errorMessageForSemester, "[ERROR]\tSemester is Empty!");
                    }
                    case (INVALID_CHOICE_FOR_SEMESTER):{
                        semesterValidity = false;
                        strcpy(errorMessageForSemester, "[ERROR]\tSemester should only be between 1-3!");
                        break;
                    }
                    case (HAS_ALPHA_AND_OR_SYMBOLS):{
                        semesterValidity = false;
                        strcpy(errorMessageForSemester, "[ERROR]\tSemester should only have an Integer(s)!");
                        break;
                    }
                    default:{
                        semesterValidity = true;
                        strcpy(errorMessageForSemester, "\0");
                    }
                }
                switch(yearInputValidation(yearBuffer)){
                    case (IS_EMPTY):{
                        yearValidity = false;
                        strcpy(errorMessageForYear, "[ERROR]\tYear is Empty!");
                        break;
                    }
                    case (HAS_WHITESPACE):{
                        yearValidity = false;
                        strcpy(errorMessageForYear, "[ERROR]\tRemove the Whitespace(s)!");
                        break;
                    }
                    case (HAS_ALPHA_AND_OR_SYMBOLS):{
                        yearValidity = false;
                        strcpy(errorMessageForYear, "[ERROR]\tYear should only have Integers!");
                        break;
                    }
                    default:{
                        yearValidity = true;
                        strcpy(errorMessageForYear, "\0");
                    }
                }
            }
            if(semesterValidity && yearValidity){
                currentScreen = MAIN_MENU;
            }else{
                DrawText(errorMessageForSemester, 10, errorMessageForSemesterPosY, 20, RED);
                DrawText(errorMessageForYear, 10, errorMessageForYearPosY, 20, RED);
            }
        }

        // NEEDS WORK HERE  **NEEDS TEXTURES** 
        if (currentScreen == MAIN_MENU)
        {

            // Button Calls
            // REGISTER BUTTON PATHS !! NEEDS TEXTURES !! CURRENTLY USING PLACEHOLDER TEXTURES !!
            char registerButtonPath[] = "assets\\textures\\confirm_button.png";
            char registerButtonHoverPath[] = "assets\\textures\\confirm_button_hover.png";
            char registerButtonClickedPath[] = "assets\\textures\\button_pressed.png";
            // Register Button
            Button registerButton(
                registerButtonPath,
                registerButtonHoverPath,
                registerButtonClickedPath);
            
            // VIEWRECORD BUTTON PATHS !! NEEDS TEXTURES !! CURRENTLY USING PLACEHOLDER TEXTURES !!
            char viewRecordButtonPath[] = "assets\\textures\\confirm_button.png";
            char viewRecordButtonHoverPath[] = "assets\\textures\\confirm_button_hover.png";
            char viewRecordButtonClickedPath[] = "assets\\textures\\button_pressed.png";
            // ViewRecord Button
            Button viewRecordButton(
                viewRecordButtonPath,
                viewRecordButtonHoverPath,
                viewRecordButtonClickedPath);

            // EXIT BUTTON PATHS !! NEEDS TEXTURES !! CURRENTLY USING PLACEHOLDER TEXTURES !!
            char exitButtonPath[] = "assets\\textures\\confirm_button.png";
            char exitButtonHoverPath[] = "assets\\textures\\confirm_button_hover.png";
            char exitButtonClickedPath[] = "assets\\textures\\button_pressed.png";
            // Exit Button
            Button exitButton(
                exitButtonPath,
                exitButtonHoverPath,
                exitButtonClickedPath);

            DrawTextEx(font.torus50, text.mainMenuText, {text.mainMenuTextPos.x, text.mainMenuTextPos.y}, text.titleScale, text.spacing, white);

            //Draw Buttons
            registerButton.Draw({(float)GetScreenWidth() / 2, (float)text.yearTextPos.y}, 0.3f, 0);
            viewRecordButton.Draw({(float)GetScreenWidth() / 2, (float)text.yearTextPos.y + 100}, 0.3f, 0);
            exitButton.Draw({(float)GetScreenWidth() / 2, (float)text.yearTextPos.y + 200}, 0.3f, 0);
        }
        EndDrawing();
    }
    return 0;
}
