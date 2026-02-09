#ifndef MAINMENUELEMENTS_HPP
#define MAINMENUELEMENTS_HPP

#include "raylib.h"
#include "textsAndFonts.hpp"
#include "string.h"
#include "variables.hpp"
#include "reasings.h"
#include "buttonsAndTextFields.hpp"

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

    Vector2 drawPos = { originPos.x + offsetX, originPos.y + offsetY };

    DrawTextureEx(registrationPanel, drawPos, 0, 1, WHITE);
}
#endif