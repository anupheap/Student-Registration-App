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

void availibilityDecrease(const char* selectedUnit);

RegistrationToggles registrations;
class Bars{
    private:
        Animations animBars;
        Color selectedColor;

        char displayText[200];
        char displayName[200];
        float currentYScale = 0.0f;
        float finalYScale = 99.0f;
        
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
                xpos,
                ypos,
                45 + MeasureTextEx(font.torus30, text, 30, 3).x,
                30
            };
            Color colorState;
            Color mmYesGREEEEEEN = {172, 247, 98, 255};
            bool isHovering = CheckCollisionPointRec(GetMousePosition(), collisionBoxForCheckBoxes);
            bool clicked = (isHovering && IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
            if(clicked){
                if (toggleStateRadio[toggleLabel]){
                    toggleStateRadio[toggleLabel] = !toggleStateRadio[toggleLabel];
                }else{
                    for (int i = 0; i < 4; i++){
                        toggleStateRadio[i] = (i == toggleLabel);
                    }
                }
            } else if (isHovering || toggleStateRadio[toggleLabel]){
                colorState = mmYesGREEEEEEN;
            } else{
                colorState = WHITE;
            }
            DrawRectangleLines(xpos, ypos, 30, 30, colorState);
            DrawTextEx(font.torus30, text, {xpos + 40, ypos}, 30, 3, colorState);
            if(toggleStateRadio[toggleLabel]){
                DrawRectangle(xpos+5, ypos+5, 20, 20, colorState);
            } 
            return toggleStateRadio[toggleLabel];
        }
};
class CheckBoxesForUnits{

    public:
        CheckBoxesForUnits() = default;
        bool Draw(float xpos, float ypos, const char* text, int toggleLabel, bool* toggleStateRadio, textFonts &font){
            Rectangle collisionBoxForCheckBoxes = {
                xpos,
                ypos,
                45 + MeasureTextEx(font.torus30, text, 30, 3).x,
                30
            };
            Color colorState;
            Color mmYesGREEEEEEN = {172, 247, 98, 255};
            bool isHovering = CheckCollisionPointRec(GetMousePosition(), collisionBoxForCheckBoxes);
            bool clicked = (isHovering && IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
            if(clicked){
                toggleStateRadio[toggleLabel] = !toggleStateRadio[toggleLabel];
                if(toggleStateRadio[4]){
                    for (int i = 0; i < 5; i++) toggleStateRadio[i] = (i == toggleLabel);
                }
            } else if (isHovering || toggleStateRadio[toggleLabel]){
                colorState = mmYesGREEEEEEN;
            } else{
                colorState = WHITE;
            }
            DrawRectangleLines(xpos, ypos, 30, 30, colorState);
            DrawTextEx(font.torus30, text, {xpos + 40, ypos}, 30, 3, colorState);
            if(toggleStateRadio[toggleLabel]){
                DrawRectangle(xpos+5, ypos+5, 20, 20, colorState);
            } 
            return toggleStateRadio[toggleLabel];
        }
};

inline Bars::Bars(Color color){
    selectedColor = color;
}
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
inline Bars::~Bars(){
    animBars.animTimer = 0.0f;
    currentYScale = 0.0f;
}

inline Panels::Panels(char* panelTexturePath)
{
    Image mainMenuRegistrationPanel = LoadImage(panelTexturePath);
    ImageResize(&mainMenuRegistrationPanel, (mainMenuRegistrationPanel.width/2) - 70, (mainMenuRegistrationPanel.height/2) - 70);
    registrationPanel = LoadTextureFromImage(mainMenuRegistrationPanel);
    GenTextureMipmaps(&registrationPanel);
    SetTextureFilter(registrationPanel, TEXTURE_FILTER_TRILINEAR);
    UnloadImage(mainMenuRegistrationPanel);
}
inline Panels::~Panels(){
    UnloadTexture(registrationPanel);
}
inline void Panels::Draw(float xpos, float ypos, originDirection selectedDirection, int toggleNumber){
    float deltaTime = GetFrameTime();
    animPanels.animDuration = 0.2f;
    switch(selectedDirection){
        case (BOTTOMLEFT):{
            originPos = {0, (float)GetScreenHeight()};
            break;
        }
        case (TOPRIGHT):{
            originPos = {(float)(GetScreenWidth() - registrationPanel.width), (float)(0-registrationPanel.height)};
            break;
        }
    }

    if(toggleState[toggleNumber]) animPanels.animTimer += deltaTime;
    else animPanels.animTimer -= deltaTime;
    if(animPanels.animTimer > animPanels.animDuration) animPanels.animTimer = animPanels.animDuration;
    else if(animPanels.animTimer < 0.0f) animPanels.animTimer = 0.0f;

    float deltaX = xpos - originPos.x;
    float deltaY = ypos - originPos.y;

    float offsetX = EaseExpoOut(animPanels.animTimer, 0, deltaX, animPanels.animDuration);
    float offsetY = EaseExpoOut(animPanels.animTimer, 0, deltaY, animPanels.animDuration);

    Vector2 currentPos = { originPos.x + offsetX, originPos.y + offsetY };

    DrawTextureEx(registrationPanel, currentPos, 0, 1, WHITE);
}

void setRegistration(int groupingNumber){
    extern ordered_json data;
    const char* registrationData[] = {"Registrations for 1E1", "Registrations for 1E2", "Registrations for 1E3", "Registrations for 1E4"};
    const char* units[] = {"Programming", "Physics I", "Mathematics", "Writing And Researching Skills"};
    bool containsDuplicates = false;
    if(registrations.toggleStateForGroupings[groupingNumber]){
        for (int i = 0; i < 5; i++){
            if(registrations.toggleStateForUnits[4]){
                for(auto& unitSelection : units){
                    for (auto& [key, value] : data.items()){
                        for(auto& arr : value){
                            if(arr == unitSelection){
                                TraceLog(LOG_WARNING, "\"%s\" Already exists in group \"%s\"", unitSelection, key.c_str());
                                containsDuplicates = true;
                            }
                        }
                    }
                    if(!containsDuplicates){
                        data[registrationData[groupingNumber]].push_back(unitSelection);
                        //availibilityDecrease(unitSelection);
                        TraceLog(LOG_INFO, "\"%s\" Added to group \"%s\"", unitSelection, registrationData[groupingNumber]);
                    }
                    else return;
                }
                break;
            }
            if(registrations.toggleStateForUnits[i]){
                for (auto& [key, value] : data.items()){
                    if(key == registrationData[groupingNumber]){
                        for(auto& arr : value){
                            if(arr == units[i]) {
                                TraceLog(LOG_WARNING, "\"%s\" Already exists in group \"%s\"", units[i], key.c_str());
                                containsDuplicates = true;
                            }
                        }
                        continue;
                    }
                    for(auto& arr : value){
                        if(arr == units[i]){
                            TraceLog(LOG_WARNING, "\"%s\" Already exists in group \"%s\"", units[i], key.c_str());
                            containsDuplicates = true;
                        }
                    }
                }
                if(!containsDuplicates){
                    data[registrationData[groupingNumber]].push_back(units[i]);
                    //availibilityDecrease(units[i]);
                    TraceLog(LOG_INFO, "\"%s\" Added to group \"%s\"", units[i], registrationData[groupingNumber]);
                }
                else return;
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
    extern StudentInfo info;
    ofstream outDocs(info.studentFileName);
    if(outDocs.is_open()){
        outDocs << data.dump(8);
        outDocs.close();
    }
}
void primeJsonFile(){
    extern ordered_json data;
    extern StudentInfo info;
    ifstream inDocs(info.studentFileName);
    if(!inDocs.is_open()){
        ofstream outDocs(info.studentFileName);
        outDocs << data.dump(8);
        outDocs.close();
    } else{
        inDocs >> data;
    }
    inDocs.close();
}
/*
inline void availibilityDecrease(const char* selectedUnit){
    extern ordered_json data;
    ordered_json availableSlots;
    const char* years[7] = {"year2024.json", "year2025.json", "year2026.json", "year2027.json", "year2028.json", "year2029.json", "year2030.json"};
    char filePath[500] = "records/availableSlots/";
    switch(info.studentYear){
        case (2024):{
            strcat(filePath, years[0]);
            break;
        }
        case (2025):{
            strcat(filePath, years[1]);
            break;
        }
        case (2026):{
            strcat(filePath, years[2]);
            break;
        }
        case (2027):{
            strcat(filePath, years[3]);
            break;
        }
        case (2028):{
            strcat(filePath, years[4]);
            break;
        }
        case(2029):{
            strcat(filePath, years[5]);
            break;            
        }
        case (2030):{
            strcat(filePath, years[6]);
            break;            
        }
    };
    ifstream availableSlotsIn(filePath);
    availableSlotsIn >> availableSlots;
    availableSlotsIn.close();
    if (availableSlots.contains(selectedUnit) && availableSlots[selectedUnit].is_number()) {
        availableSlots[selectedUnit] = data[selectedUnit].get<int>() - 1;
    }
    ofstream availableSlotsOut(filePath);
    availableSlotsOut << availableSlots.dump(4);
    availableSlotsOut.close();
}
*/
#endif