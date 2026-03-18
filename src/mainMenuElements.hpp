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
inline bool isIDDuplicate(const char* inputID) {
    std::string studentsDir = buildPath("records/students/");
    std::error_code ec;

    // directory_iterator with 'ec' prevents a crash if the folder is missing
    auto it = std::filesystem::directory_iterator(studentsDir, ec);
    if (ec) return false; 

    for (const auto& entry : it) {
        if (entry.path().extension() == ".json") {
            std::ifstream f(entry.path());
            if (f.is_open()) {
                nlohmann::ordered_json existingData;
                try {
                    f >> existingData; // Parse the file
                    
                    // Check if the "id" field matches the one being entered
                    if (existingData.contains("id") && existingData["id"] == inputID) {
                        return true; // Match found!
                    }
                } catch (...) { 
                    // If a file is corrupted, skip it instead of crashing
                    continue; 
                }
            }
        }
    }
    return false;
}
inline bool isUnitRegistered(const char* unitName, nlohmann::ordered_json& data) {
    if (data.empty()) return false;
    try {
        for (auto& [key, value] : data.items()) {
            if (value.is_array()) { 
                for (auto& item : value) {
                    // Check if it's a string AND matches
                    if (item.is_string() && item.get<std::string>() == unitName) return true;
                }
            }
        }
    } catch (...) { return false; }
    return false;
}

inline void recalculateSlots(int year){
    const char* units[] = {"Programming", "Physics I", "Mathematics II", "Writing And Researching Skills"};
    const int MAX_SLOTS = 15;

    ordered_json availableSlots;
    for(auto& u : units) availableSlots[u] = MAX_SLOTS;

    std::string studentsDir = buildPath("records/students/");
    std::error_code ec; // SILENT ERROR CHECK
    
    // Check if directory exists before iterating
    if (!std::filesystem::exists(studentsDir, ec)) {
        std::filesystem::create_directories(studentsDir, ec);
    }

    auto it = std::filesystem::directory_iterator(studentsDir, ec);
    if (ec) return; // Exit quietly if folder is still missing

    for(const auto& entry : it){
        if(entry.path().extension() != ".json") continue;

        std::ifstream f(entry.path());
        if(!f.is_open()) continue;

        ordered_json studentData;
        try{ 
            f >> studentData;
        }catch(...){ continue; }

        if(!studentData.contains("year") || studentData["year"] != year) continue;

        const char* groups[] = {"Registrations for 1E1", "Registrations for 1E2", "Registrations for 1E3", "Registrations for 1E4"};
        for(auto& group : groups){
            if(!studentData.contains(group) || !studentData[group].is_array()) continue;
            
            for(auto& registeredUnit : studentData[group]){
                // SAFETY: Check if the unit is actually a string before converting
                if (registeredUnit.is_string()) {
                    std::string unitStr = registeredUnit.get<std::string>();
                    if(availableSlots.contains(unitStr)){
                        int current = availableSlots[unitStr].get<int>();
                        if(current > 0) availableSlots[unitStr] = current - 1;
                    }
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
inline int getAvailableSlots(const char* unitName, int year) {
    const int MAX_SLOTS = 15;
    int takenSlots = 0;
    std::error_code ec;
    
    std::string studentsDir = buildPath("records/students/");
    auto it = std::filesystem::directory_iterator(studentsDir, ec);
    if (ec) return MAX_SLOTS;

    for (const auto& entry : it) {
        if (entry.path().extension() != ".json") continue;

        std::ifstream f(entry.path());
        if (!f.is_open()) continue;

        nlohmann::ordered_json studentData;
        
        try {
            f >> studentData;

            if (studentData.contains("year") && studentData["year"] == year) {
                const char* groups[] = {"Registrations for 1E1", "Registrations for 1E2", "Registrations for 1E3", "Registrations for 1E4"};
                
                for (auto& group : groups) {
                    if (studentData.contains(group) && studentData[group].is_array()) {
                        for (auto& regUnit : studentData[group]) {
                            if (regUnit == unitName) {
                                takenSlots++;
                                break;
                            }
                        }
                    }
                }
            }
        } 
        catch (...) {
            TraceLog(LOG_WARNING, "Corrupted file ignored during slot count: %s", entry.path().string().c_str());
            continue; 
        }
    }

    return MAX_SLOTS - takenSlots;
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

        bool Draw(float xpos, float ypos, const char* text, int toggleLabel, bool* toggleStateRadio, textFonts &font, bool isLocked){
            Rectangle collisionBoxForCheckBoxes = {
                xpos, ypos,
                45 + MeasureTextEx(font.torus30, text, 30, 3).x, 30
            };
            
            Color colorState;
            Color mmYesGREEEEEEN = {172, 247, 98, 255};
            Color lockedGray = {100, 100, 100, 255};

            bool isHovering = CheckCollisionPointRec(GetMousePosition(), collisionBoxForCheckBoxes);
            
            if (isLocked) {
                colorState = lockedGray;
            } else {
                bool clicked = (isHovering && IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
                if(clicked){
                    // SELECT ALL CONDITION
                    if (toggleLabel == 4) {
                        bool anyIndividual = false;
                        for(int i = 0; i < 4; i++) if(toggleStateRadio[i]) anyIndividual = true;
                        if(!anyIndividual) toggleStateRadio[4] = !toggleStateRadio[4];
                    } else {
                        toggleStateRadio[toggleLabel] = !toggleStateRadio[toggleLabel];
                        if(toggleStateRadio[toggleLabel]) toggleStateRadio[4] = false;
                    }
                } 
                
                if(isHovering || toggleStateRadio[toggleLabel]) colorState = mmYesGREEEEEEN;
                else colorState = WHITE;
            }

            DrawRectangleLines(xpos, ypos, 30, 30, colorState);
            DrawTextEx(font.torus30, text, {xpos + 40, ypos}, 30, 3, colorState);

            if(toggleStateRadio[toggleLabel] || isLocked) DrawRectangle(xpos + 5, ypos + 5, 20, 20, colorState);
            
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

void setRegistration(int groupingNumber) {
    extern ordered_json data;
    const char* registrationData[] = {"Registrations for 1E1", "Registrations for 1E2", "Registrations for 1E3", "Registrations for 1E4"};
    const char* units[] = {"Programming", "Physics I", "Mathematics II", "Writing And Researching Skills"};

    if (groupingNumber < 0 || groupingNumber > 3) return;
    if (!registrations.toggleStateForGroupings[groupingNumber]) return;

    if (registrations.toggleStateForUnits[4]) {
        for (int i = 0; i < 4; i++) {
            if (!isUnitRegistered(units[i], data)) {
                data[registrationData[groupingNumber]].push_back(units[i]);
            }
        }
    } 
    else {
        for (int i = 0; i < 4; i++) {
            if (registrations.toggleStateForUnits[i]) {
                if (!isUnitRegistered(units[i], data)) {
                    data[registrationData[groupingNumber]].push_back(units[i]);
                }
            }
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