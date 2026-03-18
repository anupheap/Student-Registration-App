#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h" 
#include "student.h"
#include "buttonsAndTextFields.hpp"
#include "textsAndFonts.hpp"
#define REASINGS_IMPLEMENTATION
#include "reasings.h"
#include "variables.hpp"
#include "mainMenuElements.hpp"
#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace nlohmann;
using namespace std;
using vs = ValiditySafeguards;


int main(){
    extern ordered_json data;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
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
        //"Registration Button Textures"
        char registerButtonPath[] = "assets\\textures\\registration_button.png";
        char registerButtonHoverPath[] = "assets\\textures\\registration_button_hover.png";
        char registerButtonClickedPath[] = "assets\\textures\\registration_button_clicked.png";
        //View/Print Button Textures
        char viewOrPrintButtonPath[] = "assets\\textures\\viewOrPrint_button.png";
        char viewOrPrintButtonHoverPath[] = "assets\\textures\\viewOrPrint_button_hover.png";
        char viewOrPrintButtonClickedPath[] = "assets\\textures\\viewOrPrint_button_clicked.png";
        Image viewOrPrintButtonTexture = LoadImage(viewOrPrintButtonPath);
        char exitButtonPath[] = "assets\\textures\\exit_button.png";
        char exitButtonWhenHoverPath[] = "assets\\textures\\exit_button_hover.png";
        char exitButtonWhenClickedPath[] = "assets\\textures\\exit_button_clicked.png";
        Image exitButtonTexture = LoadImage(exitButtonPath);
        char mainMenuRegistrationPanelAPath[] = "assets\\textures\\parallelogram_maybe.png";
        char mainMenuRegistrationPanelBPath[] = "assets\\textures\\par2.png";
        char submitButtonButtonPath[] = "assets\\textures\\submitButton.png";
        char submitButtonWhenHoverPath[] = "assets\\textures\\submitButtonHover.png";
        char submitButtonWhenClickedPath[] = "assets\\textures\\submitButtonClicked.png";

    // App Icon
        char logoPath[] = "assets\\textures\\student_registration_logo.png";
        Image logo = LoadImage(logoPath);
        ImageResizeNN(&logo, 256, 256);

    // Initialize Classes, Buttons, Text input Boxes and Game Screen

        Student student;
        Screen currentScreen = SCREEN_LOGIN;
        textFonts font;

        //loads ascii art file
        string artPath = buildPath("assets\\art.txt");
        char* fileData = LoadFileText(artPath.c_str()); 
        texts text(font, fileData);

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
        
        Button registerButton(
            registerButtonPath,
            registerButtonHoverPath,
            registerButtonClickedPath);
        Button viewOrPrintButton(
            viewOrPrintButtonPath,
            viewOrPrintButtonHoverPath,
            viewOrPrintButtonClickedPath
        );

        Button exitButton(
            exitButtonPath,
            exitButtonWhenHoverPath,
            exitButtonWhenClickedPath
        );
        Button submitButton(
            submitButtonButtonPath,
            submitButtonWhenHoverPath,
            submitButtonWhenClickedPath
        );
    
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
    bool yearValidity = false;
    Color white = WHITE;
    Color gray = {211, 211, 211, 255};
    Color purple = {140, 102, 255, 255};
    Color backgroundColor = {49, 46, 56, 255};
    Color baseColor = {36, 34, 43, 255};
    Color baseTextColor = {150, 140, 171, 255};
    Color focusedTextColor = {204, 193, 230, 255};
    Color transparentBlack = {10, 10, 10, 100};
    Color greenColor = {172, 247, 98, 255};
    Color blueColor  = {102, 204, 255, 255};
    Color viewOrPrintBarColor = {102, 204, 255, 255};
    Color registrationBarColor = {172, 247, 98, 255};
    int semesterSelection = 0;
    int yearSelection = 0;
    float animTimer = 0.0f;
    float animEnd = 0.25f;
    Bars registrationBar(registrationBarColor);
    Bars viewOrPrintBar(viewOrPrintBarColor);
    Panels registrationPanelA(mainMenuRegistrationPanelAPath);
    Panels registrationPanelB(mainMenuRegistrationPanelBPath);
    CheckBoxesForGroupings grouping1;
    CheckBoxesForGroupings grouping2;
    CheckBoxesForGroupings grouping3;
    CheckBoxesForGroupings grouping4;
    CheckBoxesForUnits programming;
    CheckBoxesForUnits physics;
    CheckBoxesForUnits mathematics;
    CheckBoxesForUnits writingNResearchSkills;
    CheckBoxesForUnits selectAll;

    ordered_json viewData;
    bool viewDataLoaded = false;



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
        GuiSetStyle(DROPDOWNBOX, BASE_COLOR_NORMAL, ColorToInt(baseColor));
        GuiSetStyle(DROPDOWNBOX, BASE_COLOR_PRESSED, ColorToInt(backgroundColor));
        GuiSetStyle(DROPDOWNBOX, BASE_COLOR_FOCUSED, ColorToInt(baseColor));
        GuiSetStyle(DROPDOWNBOX, BORDER_WIDTH, 3);
        GuiSetStyle(DROPDOWNBOX, BORDER_COLOR_FOCUSED, ColorToInt(baseColor));
        GuiSetStyle(DROPDOWNBOX, BORDER_COLOR_NORMAL, ColorToInt(baseColor));
        GuiSetStyle(DROPDOWNBOX, BORDER_COLOR_PRESSED, ColorToInt(purple));
        GuiSetStyle(DROPDOWNBOX, BASE_COLOR_DISABLED, ColorToInt(baseColor));
        GuiSetStyle(DROPDOWNBOX, TEXT_COLOR_PRESSED, ColorToInt(WHITE));
        GuiSetStyle(DROPDOWNBOX, TEXT_COLOR_FOCUSED, ColorToInt(focusedTextColor));
        GuiSetStyle(DROPDOWNBOX, TEXT_COLOR_NORMAL, ColorToInt(baseTextColor));
        bool hoverAnyButton = false;
        bool anyGroupingSelected = false;


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
            if(next.Draw({(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 1.34f}, 0.3f, 0)) hoverAnyButton = true;
            if (hoverAnyButton){
                SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            } else {
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            }

            if (next.isPressed()){
                // Validate first name
                switch(nameInputValidation(firstNameBuffer)){
                    case(vs::IS_EMPTY):
                        strcpy(errorMessageForFirstName, "[ERROR]\tYour First Name is Empty!");
                        firstNameValidity = false;
                        break;
                    case(vs::HAS_PRECEDING_WHITESPACE):
                        strcpy(errorMessageForFirstName, "[ERROR]\tPlease Remove the Preceding Whitespace(s) from your First name!");
                        firstNameValidity = false;
                        break;
                    case(vs::HAS_PROCEDING_WHITESPACE):
                        strcpy(errorMessageForFirstName, "[ERROR]\tPlease remove the Proceding Whitespace(s) from your First Name!");
                        firstNameValidity = false;
                        break;
                    case(vs::HAS_WHITESPACE):
                        strcpy(errorMessageForFirstName, "[ERROR]\tPlease remove the additional whitespace(s) from your First Name!");
                        firstNameValidity = false;
                        break;
                    case(vs::HAS_NUMBERS):
                        strcpy(errorMessageForFirstName, "[ERROR]\tYour First Name has a Number(s)!");
                        firstNameValidity = false;
                        break;
                    case(vs::HAS_SYMBOLS):
                        strcpy(errorMessageForFirstName, "[ERROR]\tYour First Name has an Invalid Character(s)!");
                        firstNameValidity = false;
                        break;
                    default:
                        firstNameValidity = true;
                        strcpy(errorMessageForFirstName, "\0");
                }

                // Validate middle name
                switch(nameInputValidation(middleNameBuffer)){
                    case(vs::HAS_PRECEDING_WHITESPACE):
                        strcpy(errorMessageForMiddleName, "[ERROR]\tPlease Remove the Preceding Whitespace(s) from your Middle Name!");
                        middleNameValidity = false;
                        break;
                    case(vs::HAS_PROCEDING_WHITESPACE):
                        strcpy(errorMessageForMiddleName, "[ERROR]\tPlease remove the Proceding whitespace(s) from your Middle Name!");
                        middleNameValidity = false;
                        break;
                    case(vs::HAS_WHITESPACE):
                        strcpy(errorMessageForMiddleName, "[ERROR]\tPlease remove the additional whitespace(s)!");
                        middleNameValidity = false;
                        break;
                    case(vs::HAS_NUMBERS):
                        strcpy(errorMessageForMiddleName, "[ERROR]\tText has numbers!");
                        middleNameValidity = false;
                        break;
                    case(vs::HAS_SYMBOLS):
                        strcpy(errorMessageForMiddleName, "[ERROR]\tInvalid Character(s)!");
                        middleNameValidity = false;
                        break;
                    default:
                        middleNameValidity = true;
                        strcpy(errorMessageForMiddleName, "\0");
                }

                // Validate last name
                switch(nameInputValidation(lastNameBuffer)){
                    case(vs::IS_EMPTY):
                        strcpy(errorMessageForLastName, "[ERROR]\tYour Last Name is Empty!");
                        lastNameValidity = false;
                        break;
                    case(vs::HAS_PRECEDING_WHITESPACE):
                        strcpy(errorMessageForLastName, "[ERROR]\tPlease Remove the Preceding Whitespace(s) from your Last name!");
                        lastNameValidity = false;
                        break;
                    case(vs::HAS_PROCEDING_WHITESPACE):
                        strcpy(errorMessageForLastName, "[ERROR]\tPlease remove the Proceding Whitespace(s) from your Last Name!");
                        lastNameValidity = false;
                        break;
                    case(vs::HAS_WHITESPACE):
                        strcpy(errorMessageForLastName, "[ERROR]\tPlease remove the additional whitespace(s) from your Last Name!");
                        lastNameValidity = false;
                        break;
                    case(vs::HAS_NUMBERS):
                        strcpy(errorMessageForLastName, "[ERROR]\tYour Last Name has a Number(s)!");
                        lastNameValidity = false;
                        break;
                    case(vs::HAS_SYMBOLS):
                        strcpy(errorMessageForLastName, "[ERROR]\tYour Last Name has an Invalid Character(s)!");
                        lastNameValidity = false;
                        break;
                    default:
                        lastNameValidity = true;
                        strcpy(errorMessageForLastName, "\0");
                }

                // Validate ID
                switch(IDInputValidation(IDBuffer)){
                    case(vs::INVALID_ID_FORMAT):
                        strcpy(errorMessageForID, "[ERROR]\tYour ID should be in 7000XXXXX format!");
                        IDValidity = false;
                        break;
                    case(vs::IS_EMPTY):
                        strcpy(errorMessageForID, "[ERROR]\tYour ID is Empty!");
                        IDValidity = false;
                        break;
                    case(vs::INSUFFICIENT_CHARACTERS):
                        strcpy(errorMessageForID, "[ERROR]\tYour ID is not exactly 9 digits!");
                        IDValidity = false;
                        break;
                    case(vs::HAS_WHITESPACE):
                        strcpy(errorMessageForID, "[ERROR]\tYour ID should not have a Whitespace(s)!");
                        IDValidity = false;
                        break;
                    case(vs::HAS_ALPHA_AND_OR_SYMBOLS):
                        strcpy(errorMessageForID, "[ERROR]\tYour ID should only contain Digits!");
                        IDValidity = false;
                        break;
                    default:
                        IDValidity = true;
                        strcpy(errorMessageForID, "\0");
                }
                
                // If all validations pass
                if (firstNameValidity && IDValidity && middleNameValidity && lastNameValidity) 
                {
                    // Set student name and filename
                    if (strlen(middleNameBuffer) == 0) {
                        student.setName(firstNameBuffer, lastNameBuffer);
                        student.setFileName(firstNameBuffer, lastNameBuffer);
                    } else {
                        student.setName(firstNameBuffer, middleNameBuffer, lastNameBuffer);
                        student.setFileName(firstNameBuffer, middleNameBuffer, lastNameBuffer);
                    }
                    student.setID(IDBuffer);
                    student.setDisplayName();

                    // Build file path and check if student exists
                    std::string fullPath = buildPath(info.studentFileName);
                    std::ifstream existingFile(fullPath);

                    if (existingFile.is_open()) {
                        // File exists - try to load it
                        try {
                            existingFile >> data;
                            existingFile.close();

                            // Check if ID matches
                            if (data.contains("id") && data["id"] == IDBuffer) {
                                // Returning student - load their info and skip to main menu
                                TraceLog(LOG_INFO, "Returning student detected: %s", info.studentFileName);
                                
                                // Load semester and year from JSON
                                if (data.contains("semester") && data.contains("year")) {
                                    info.studentSemester = data["semester"].get<int>();
                                    info.studentYear = data["year"].get<int>();
                                }
                                
                                setStudentInfo();
                                currentScreen = MAIN_MENU;
                            } 
                            else {
                                // Name exists but ID is different
                                strcpy(errorMessageForID, "[ERROR] Name exists but ID mismatch!");
                                TraceLog(LOG_WARNING, "Name collision: %s with different ID", info.studentFileName);
                            }
                        } 
                        catch (const std::exception& e) {
                            TraceLog(LOG_ERROR, "Error reading existing file: %s", e.what());
                            existingFile.close();
                            currentScreen = SEMESTER_SCREEN;
                        }
                    } 
                    else {
                        // File doesn't exist - check if ID is used elsewhere
                        if (isIDDuplicate(IDBuffer)) {
                            strcpy(errorMessageForID, "[ERROR] ID already registered to another name!");
                            TraceLog(LOG_WARNING, "ID collision: %s already exists", IDBuffer);
                        } 
                        else {
                            // New student - proceed to semester screen
                            TraceLog(LOG_INFO, "New student: %s", info.studentFileName);
                            setStudentInfo();
                            currentScreen = SEMESTER_SCREEN;
                        }
                    }
                }
            }
        }


        if (currentScreen == SEMESTER_SCREEN)
        {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            int errorMessageForSemesterPosY = (GetScreenHeight() / 2 - 10) * 1.85f;
            int errorMessageForYearPosY = (GetScreenHeight() / 2 - 10) * 1.95f;

            yearValidity = false;

            DrawTextEx(font.torus50, text.semesterDetailsText, text.semesterDetailsTextPos, text.titleScale, text.spacing, white);
            DrawTextEx(font.torus30, text.semesterText, text.semesterTextPos, text.subtitleScale, text.spacing, white);
            DrawRectangleRec(yearInputBox, baseColor);
            if(confirm.Draw({(float)GetScreenWidth() / 2, (float)text.yearTextPos.y + 130}, 0.3f, 0)) hoverAnyButton = true;
            if (hoverAnyButton){
                SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            } else {
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            }
            if (GuiDropdownBox(semesterInputBox, "1;2;3", &semesterSelection, semesterToggle)) semesterToggle = !semesterToggle;
            DrawTextEx(font.torus30, text.yearText, text.yearTextPos, text.subtitleScale, text.spacing, white);
            if (GuiDropdownBox(yearInputBox, "2024;2025;2026;2027;2028;2029;2030", &yearSelection, yearToggle)) yearToggle = !yearToggle;
            
            if (confirm.isPressed() && !yearToggle)
            {
                student.setSemesterAndYear(semesterSelection + 1, yearSelection);
                setStudentInfo();
                primeJsonFile();
                viewDataLoaded = false; 
                currentScreen = MAIN_MENU;
            }
        }
 


        if (currentScreen == MAIN_MENU)
        {
            DrawTextEx(font.torus50, text.mainMenuText, {text.mainMenuTextPos.x, text.mainMenuTextPos.y}, text.titleScale, text.spacing, white);
            DrawTextEx(font.torus30, text.welcomeMainMenuText1, text.welcomeMainMenuText1Pos, text.subtitleScale, text.spacing, gray);
            DrawTextEx(font.torus30, text.welcomeMainMenuText2, text.welcomeMainMenuText2Pos, text.subtitleScale, text.spacing, gray);
            if(toggleState[0]){
                hoverAnyButton = false;
                currentScreen = DEVELOPER_INFO;
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            }
            if (toggleState[1] || toggleState[2]) DrawRectangle(0, 0, 1280, 720, transparentBlack);
            registrationPanelA.Draw(10.0f, 228.0f, BOTTOMLEFT, 1);
            registrationPanelB.Draw((float)(GetScreenWidth() - 621.0f), 228.0f, TOPRIGHT, 1);
            registrationBar.Draw(1);
            viewOrPrintBar.Draw(2); 
            
            if(toggleState[1]){
                DrawTextEx(font.torus30, text.registrationText, text.registrationTextPos, text.subtitleScale, text.spacing, backgroundColor);
                Vector2 getNameScale = MeasureTextEx(font.torus30, info.displayName, text.subtitleScale, text.spacing);
                Vector2 nameTextPos = {(GetScreenWidth()/2.0f - getNameScale.x/2.0f), (text.registrationTextPos.y + 30)};
                DrawTextEx(font.torus30, info.displayName, nameTextPos, text.subtitleScale, text.spacing, baseColor);
                
                bool isProgFull = (getAvailableSlots("Programming", data["year"]) <= 0);
                bool isPhyFull = (getAvailableSlots("Physics I", data["year"]) <= 0);
                bool isMathFull = (getAvailableSlots("Mathematics II", data["year"]) <= 0);
                bool isWritingFull = (getAvailableSlots("Writing and Researching skills", data["year"]) <= 0);


                bool progLocked = isUnitRegistered("Programming", data) || isProgFull;
                bool physLocked = isUnitRegistered("Physics I", data) || isPhyFull;
                bool mathLocked = isUnitRegistered("Mathematics II", data) || isMathFull;
                bool writLocked = isUnitRegistered("Writing And Researching Skills", data) || isWritingFull;

                bool selectAllLocked = (progLocked || physLocked || mathLocked || writLocked);

                grouping1.Draw((float)280.0f, (float)365.0f, "1E1", 0, registrations.toggleStateForGroupings, font);
                grouping2.Draw((float)277.0f, (float)425.0f, "1E2", 1, registrations.toggleStateForGroupings, font);
                grouping3.Draw((float)274.0f, (float)485.0f, "1E3", 2, registrations.toggleStateForGroupings, font);
                grouping4.Draw((float)271.0f, (float)545.0f, "1E4", 3, registrations.toggleStateForGroupings, font);

                programming.Draw(700.0f, 365.0f, "Programming", 0, registrations.toggleStateForUnits, font, progLocked);
                physics.Draw(697.0f, 410.0f, "Physics I", 1, registrations.toggleStateForUnits, font, physLocked);
                mathematics.Draw(694.0f, 455.0f, "Mathematics II", 2, registrations.toggleStateForUnits, font, mathLocked);
                writingNResearchSkills.Draw(691.0f, 500.0f, "Writing And Researching Skills", 3, registrations.toggleStateForUnits, font, writLocked);
                
                selectAll.Draw(688.0f, 545.0f, "Select All Units", 4, registrations.toggleStateForUnits, font, selectAllLocked);
                submitButton.Draw({GetScreenWidth()/2.0f, 660.0f}, 0.35f, 0);
                if(submitButton.isPressed()){
                    setRegistration(0);
                    setRegistration(1);
                    setRegistration(2);
                    setRegistration(3);
                    writeIntoJson();
                    viewDataLoaded = false; 
                    for(auto& units : registrations.toggleStateForUnits){
                        units = false;
                    }
                    for(auto& groupings : registrations.toggleStateForGroupings){
                        groupings = false;
                    }
                }
            }

            if(toggleState[2]){
                std::string fullPath = buildPath(info.studentFileName);
                {
                    std::ifstream f(fullPath);
                    if(f.is_open()) f >> viewData;
                }

                float startY = 210.0f;
                float col1   = 100.0f;
                float col2   = 650.0f;

                string trimStr = "Trimester: " + to_string(viewData.value("semester", 0)) + "F-" + to_string(viewData.value("year", 0));
                string nameStr = "Student Name: " + viewData.value("name", "—");
                string idStr   = "Student ID: "   + viewData.value("id",   "—");

                DrawTextEx(font.torus30, text.viewOrPrintText, text.viewOrPrintTextPos, text.subtitleScale, text.spacing, backgroundColor);
                Vector2 getNameScale = MeasureTextEx(font.torus30, info.displayName, text.subtitleScale, text.spacing);
                Vector2 nameTextPos = {(GetScreenWidth()/2.0f - getNameScale.x/2.0f), (text.viewOrPrintTextPos.y + 30)};
                DrawTextEx(font.torus30, info.displayName, nameTextPos, text.subtitleScale, text.spacing, baseColor);
                DrawTextEx(font.torus30, trimStr.c_str(), {col1, startY}, 30, 3, white); startY += 38;
                DrawTextEx(font.torus30, nameStr.c_str(), {col1, startY}, 30, 3, white); startY += 38;
                DrawTextEx(font.torus30, idStr.c_str(),   {col1, startY}, 30, 3, white); startY += 50;

                DrawTextEx(font.torus30, "Unit",     {col1, startY}, 30, 3, blueColor);
                DrawTextEx(font.torus30, "Grouping", {col2, startY}, 30, 3, blueColor);
                startY += 36;

                const char* groups[]      = {"Registrations for 1E1", "Registrations for 1E2", "Registrations for 1E3", "Registrations for 1E4"};
                const char* groupLabels[] = {"1E1", "1E2", "1E3", "1E4"};

                bool anyRegistrations = false;
                for(int g = 0; g < 4; g++){
                    if(!viewData.contains(groups[g]) || viewData[groups[g]].empty()) continue;
                    for(auto& unit : viewData[groups[g]]){
                        anyRegistrations = true;
                        DrawTextEx(font.torus30, unit.get<string>().c_str(), {col1, startY}, 30, 3, white);
                        DrawTextEx(font.torus30, groupLabels[g],             {col2, startY}, 30, 3, white);
                        startY += 34;
                    }
                }

                if(!anyRegistrations){
                    DrawTextEx(font.torus30, "No registrations yet.", {col1, startY}, 28, 3, baseTextColor);
                }
            }

            DrawRectangle(0, 0, GetScreenWidth(), 99, baseColor);
            if(exitButton.Draw({((float)GetScreenWidth() / 2) - 500, (float)GetScreenHeight() - 664.0f}, 0.35f, 0, 0)) hoverAnyButton = true;
            if (registerButton.Draw({((float)GetScreenWidth() / 2) + 300, (float)GetScreenHeight() - 664.0f}, 0.35f, 0, 1)) hoverAnyButton = true;
            if (viewOrPrintButton.Draw({((float)GetScreenWidth() / 2) + 480, (float)GetScreenHeight() - 664.0f}, 0.35f, 0, 2)) hoverAnyButton = true;
            if(hoverAnyButton){
                SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            } else {
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            }
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !hoverAnyButton && GetMousePosition().y <= 99.0f) {
                for (int i = 0; i < 3; i++) toggleState[i] = false;
                viewDataLoaded = false; 
            }
        }


        if (currentScreen == DEVELOPER_INFO){
            DrawTextEx(font.fira12, fileData, text.artPos, text.artScale, text.spacing, white);

            float startY = 350.0f;
            float col1   = 50.0f;
            float col2   = 450.0f;
            float col3   = 700.0f;

            DrawTextEx(font.torus20, "Group 1E1-A",  {col1, startY}, 20, 3, greenColor); startY += 42;

            DrawTextEx(font.torus20, "Ung Phearakleap",  {col1, startY}, 20, 3, white);
            DrawTextEx(font.torus20, "P20250001",         {col2, startY}, 20, 3, baseTextColor);
            DrawTextEx(font.torus20, "Core system, Login, registration, JSON",  {col3, startY}, 20, 3, baseTextColor);
            startY += 36;

            DrawTextEx(font.torus20, "Buntong Anupheap", {col1, startY}, 20, 3, white);
            DrawTextEx(font.torus20, "P20250055",         {col2, startY}, 20, 3, baseTextColor);
            DrawTextEx(font.torus20, "View/Print page, Developer Info screen",  {col3, startY}, 20, 3, baseTextColor);
            startY += 36;

            DrawTextEx(font.torus20, "Pheng Sopheak",    {col1, startY}, 20, 3, white);
            DrawTextEx(font.torus20, "P20250002",         {col2, startY}, 20, 3, baseTextColor);
            DrawTextEx(font.torus20, "Flowchart",                                {col3, startY}, 20, 3, baseTextColor);
            startY += 56;

            DrawTextEx(font.torus30, "Press any key or click to exit...", {col1, startY}, 28, 3, baseTextColor);

            if(IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                CloseWindow();
            }

        }
        EndDrawing();
    }
    
    return 0;
}