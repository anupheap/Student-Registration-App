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
#endif