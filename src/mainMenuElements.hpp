#ifndef MAINMENUELEMENTS_HPP
#define MAINMENUELEMENTS_HPP

#include "raylib.h"
#include "textsAndFonts.hpp"
#include "string.h"
#include "variables.hpp"
#include "reasings.h"
#include "buttonsAndTextFields.hpp"
#include "nlohmann/json.hpp"
#include <fstream>
#include <filesystem>
#include "student.h"

inline std::string getBaseDir(){
    return std::string(GetApplicationDirectory());
}

inline std::string buildPath(const char* relative){
    return getBaseDir() + relative;
}

inline void recalculateSlots(int year){
    const char* units[] = {"Programming", "Physics I", "Mathematics II", "Writing And Researching Skills"};
    const int MAX_SLOTS = 15;

    ordered_json availableSlots;
    for(auto& u : units) availableSlots[u] = MAX_SLOTS;

    std::string studentsDir = buildPath("records/students/");
    std::filesystem::create_directories(studentsDir);

    for(const auto& entry : std::filesystem::directory_iterator(studentsDir)){
        if(entry.path().extension() != ".json") continue;

        std::ifstream f(entry.path());
        if(!f.is_open()) continue;

        ordered_json studentData;
        try{ 
            f >> studentData;
        }catch(...){
            continue;
        }

        if(!studentData.contains("year") || studentData["year"] != year) continue;

        const char* groups[] = {"Registrations for 1E1", "Registrations for 1E2", "Registrations for 1E3", "Registrations for 1E4"};
        for(auto& group : groups){
            if(!studentData.contains(group)) continue;
            for(auto& registeredUnit : studentData[group]){
                std::string unitStr = registeredUnit.get<std::string>();
                if(availableSlots.contains(unitStr)){
                    int current = availableSlots[unitStr].get<int>();
                    if(current > 0) availableSlots[unitStr] = current - 1;
                }
            }
        }
    }

    char yearFileName[64];
    sprintf(yearFileName, "year%d.json", year);
    std::string slotDir  = buildPath("records/availableSlots/");
    std::string slotPath = slotDir + yearFileName;
    std::filesystem::create_directories(slotDir);

    {
        std::ofstream out(slotPath);
        if(out.is_open()){
            out << availableSlots.dump(4);
            TraceLog(LOG_INFO, "Slots recalculated and saved: %s", slotPath.c_str());
        } else {
            TraceLog(LOG_ERROR, "FAILED TO WRITE SLOT FILE: %s", slotPath.c_str());
        }
    }
}


RegistrationToggles registrations;

class Bars{
    private:
        Animations animBars;
        Color selectedColor;
        char displayText[200];
        char displayName[200];
        float currentYScale = 0.0f;
        float finalYScale   = 99.0f;
    public:
        Bars(Color color);
        ~Bars();
        void Draw(int toggleNumber);
};

class Panels{
    private:
        Animations animPanels;
        Texture2D registrationPanel;
        Vector2 originPosOffset;
        Vector2 originPos;
    public:
        Panels(char* panelTexturePath);
        ~Panels();
        void Draw(float xpos, float ypos, originDirection selectedDirection, int toggleNumber);
};

class CheckBoxesForGroupings{
    public:
        CheckBoxesForGroupings() = default;
        bool Draw(float xpos, float ypos, const char* text, int toggleLabel, bool* toggleStateRadio, textFonts &font){
            Rectangle collisionBoxForCheckBoxes = {
                xpos, ypos,
                45 + MeasureTextEx(font.torus30, text, 30, 3).x, 30
            };
            Color colorState;
            Color mmYesGREEEEEEN = {172, 247, 98, 255};
            bool isHovering = CheckCollisionPointRec(GetMousePosition(), collisionBoxForCheckBoxes);
            bool clicked = (isHovering && IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
            if(clicked){
                if(toggleStateRadio[toggleLabel]){
                    toggleStateRadio[toggleLabel] = !toggleStateRadio[toggleLabel];
                } else {
                    for(int i = 0; i < 4; i++) toggleStateRadio[i] = (i == toggleLabel);
                }
            } else if(isHovering || toggleStateRadio[toggleLabel]){
                colorState = mmYesGREEEEEEN;
            } else {
                colorState = WHITE;
            }
            DrawRectangleLines(xpos, ypos, 30, 30, colorState);
            DrawTextEx(font.torus30, text, {xpos + 40, ypos}, 30, 3, colorState);
            if(toggleStateRadio[toggleLabel]) DrawRectangle(xpos + 5, ypos + 5, 20, 20, colorState);
            return toggleStateRadio[toggleLabel];
        }
};

class CheckBoxesForUnits{
    public:
        CheckBoxesForUnits() = default;
        bool Draw(float xpos, float ypos, const char* text, int toggleLabel, bool* toggleStateRadio, textFonts &font){
            Rectangle collisionBoxForCheckBoxes = {
                xpos, ypos,
                45 + MeasureTextEx(font.torus30, text, 30, 3).x, 30
            };
            Color colorState;
            Color mmYesGREEEEEEN = {172, 247, 98, 255};
            bool isHovering = CheckCollisionPointRec(GetMousePosition(), collisionBoxForCheckBoxes);
            bool clicked = (isHovering && IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
            if(clicked){
                toggleStateRadio[toggleLabel] = !toggleStateRadio[toggleLabel];
                if(toggleStateRadio[4]){
                    for(int i = 0; i < 5; i++) toggleStateRadio[i] = (i == toggleLabel);
                }
            } else if(isHovering || toggleStateRadio[toggleLabel]){
                colorState = mmYesGREEEEEEN;
            } else {
                colorState = WHITE;
            }
            DrawRectangleLines(xpos, ypos, 30, 30, colorState);
            DrawTextEx(font.torus30, text, {xpos + 40, ypos}, 30, 3, colorState);
            if(toggleStateRadio[toggleLabel]) DrawRectangle(xpos+5, ypos+5, 20, 20, colorState);
            return toggleStateRadio[toggleLabel];
        }
};

inline Bars::Bars(Color color){ selectedColor = color; }
inline void Bars::Draw(int toggleNumber){
    float deltaTime = GetFrameTime();
    animBars.animDuration = 0.15f;
    if(toggleState[toggleNumber]) animBars.animTimer += deltaTime;
    else animBars.animTimer -= deltaTime;
    if(animBars.animTimer > animBars.animDuration) animBars.animTimer = animBars.animDuration;
    else if(animBars.animTimer < 0) animBars.animTimer = 0;
    currentYScale = EaseBackOut(animBars.animTimer, 0.0f, finalYScale, animBars.animDuration);
    DrawRectangle(0, 99, GetScreenWidth(), currentYScale, selectedColor);
}
inline Bars::~Bars(){ animBars.animTimer = 0.0f; currentYScale = 0.0f; }

inline Panels::Panels(char* panelTexturePath){
    Image mainMenuRegistrationPanel = LoadImage(panelTexturePath);
    ImageResize(&mainMenuRegistrationPanel,
        (mainMenuRegistrationPanel.width/2)  - 70,
        (mainMenuRegistrationPanel.height/2) - 70);
    registrationPanel = LoadTextureFromImage(mainMenuRegistrationPanel);
    GenTextureMipmaps(&registrationPanel);
    SetTextureFilter(registrationPanel, TEXTURE_FILTER_TRILINEAR);
    UnloadImage(mainMenuRegistrationPanel);
}
inline Panels::~Panels(){ UnloadTexture(registrationPanel); }
inline void Panels::Draw(float xpos, float ypos, originDirection selectedDirection, int toggleNumber){
    float deltaTime = GetFrameTime();
    animPanels.animDuration = 0.2f;
    switch(selectedDirection){
        case (BOTTOMLEFT):{
            originPos = {0, (float)GetScreenHeight()};
            break;
        }
        case (TOPRIGHT):{
            originPos = {(float)(GetScreenWidth() - registrationPanel.width), (float)(0 - registrationPanel.height)};
            break;
        }
        default:{
            break;
        }
    }
    if(toggleState[toggleNumber]) animPanels.animTimer += deltaTime;
    else animPanels.animTimer -= deltaTime;
    if(animPanels.animTimer > animPanels.animDuration) animPanels.animTimer = animPanels.animDuration;
    else if(animPanels.animTimer < 0.0f) animPanels.animTimer = 0.0f;

    float deltaX  = xpos - originPos.x;
    float deltaY  = ypos - originPos.y;
    float offsetX = EaseExpoOut(animPanels.animTimer, 0, deltaX, animPanels.animDuration);
    float offsetY = EaseExpoOut(animPanels.animTimer, 0, deltaY, animPanels.animDuration);
    DrawTextureEx(registrationPanel, {originPos.x + offsetX, originPos.y + offsetY}, 0, 1, WHITE);
}

void setRegistration(int groupingNumber){
    extern ordered_json data;
    const char* registrationData[] = {"Registrations for 1E1", "Registrations for 1E2", "Registrations for 1E3", "Registrations for 1E4"};
    const char* units[] = {"Programming", "Physics I", "Mathematics II", "Writing And Researching Skills"};

    if(!registrations.toggleStateForGroupings[groupingNumber]) return;

    for(int i = 0; i < 5; i++){
        if(registrations.toggleStateForUnits[4]){
            for(auto& unitSelection : units){
                bool duplicate = false;
                for(auto& [key, value] : data.items()){
                    for(auto& arr : value){
                        if(arr == unitSelection){
                            TraceLog(LOG_WARNING, "\"%s\" already in \"%s\"", unitSelection, key.c_str());
                            duplicate = true;
                        }
                    }
                }
                if(!duplicate){
                    data[registrationData[groupingNumber]].push_back(unitSelection);
                    TraceLog(LOG_INFO, "\"%s\" added to \"%s\"", unitSelection, registrationData[groupingNumber]);
                }
            }
            break;
        }

        if(!registrations.toggleStateForUnits[i]) continue;

        bool duplicate = false;
        for(auto& [key, value] : data.items()){
            for(auto& arr : value){
                if(arr == units[i]){
                    TraceLog(LOG_WARNING, "\"%s\" already in \"%s\"", units[i], key.c_str());
                    duplicate = true;
                }
            }
        }
        if(!duplicate){
            data[registrationData[groupingNumber]].push_back(units[i]);
            TraceLog(LOG_INFO, "\"%s\" added to \"%s\"", units[i], registrationData[groupingNumber]);
        }
    }
}

void setStudentInfo(){
    extern ordered_json data;
    data["name"] = info.studentName;
    data["id"] = info.studentID;
    data["semester"] = info.studentSemester;
    data["year"] = info.studentYear;
}

void writeIntoJson(){
    extern ordered_json data;

    std::string studentsDir = buildPath("records/students/");
    std::filesystem::create_directories(studentsDir);

    std::string fullPath = buildPath(info.studentFileName);

    {
        std::ofstream outDocs(fullPath);
        if(outDocs.is_open()){
            outDocs << data.dump(8);
            TraceLog(LOG_INFO, "Student file written: %s", fullPath.c_str());
        } else {
            TraceLog(LOG_ERROR, "FAILED TO WRITE STUDENT FILE: %s", fullPath.c_str());
            return;
        }
    }

    recalculateSlots(data["year"]);
}

void primeJsonFile(){
    extern ordered_json data;

    std::string studentsDir = buildPath("records/students/");
    std::filesystem::create_directories(studentsDir);

    std::string fullPath = buildPath(info.studentFileName);

    std::ifstream inDocs(fullPath);
    if(!inDocs.is_open()){
        std::ofstream outDocs(fullPath);
        if(outDocs.is_open()){
            outDocs << data.dump(8);
            TraceLog(LOG_INFO, "New student file created: %s", fullPath.c_str());
        } else {
            TraceLog(LOG_ERROR, "FAILED TO CREATE STUDENT FILE: %s", fullPath.c_str());
        }
    } else {
        inDocs >> data;
        TraceLog(LOG_INFO, "Existing student file loaded: %s", fullPath.c_str());
    }
}

#endif