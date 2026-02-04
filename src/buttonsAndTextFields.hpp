#ifndef BUTTONSANDTEXTFIELDS_HPP
#define BUTTONSANDTEXTFIELDS_HPP

#include <string>
#include <iostream>
#include <thread>
#include <cctype>
#include "raylib.h"
#include "reasings.h"

const int IS_EMPTY = 101;
const int HAS_NUMBERS = 102;
const int HAS_PROCEDING_WHITESPACE = 103;
const int HAS_PRECEDING_WHITESPACE = 104;
const int HAS_INBETWEEN_WHITESPACE = 105;
const int HAS_SYMBOLS = 106;
const int HAS_ALPHA_AND_OR_SYMBOLS = 107;
const int INSUFFICIENT_CHARACTERS = 108;
const int INVALID_ID_FORMAT = 109;
const int HAS_WHITESPACE = 110;
const int INVALID_CHOICE_FOR_SEMESTER = 111;


int nameInputValidation(char* textInput);
int IDInputValidation(char* numberInput);
int semesterInputValidation(char* semesterInput);
int yearInputValidation(char* yearInput);
bool toggleState[3] = {false, false, false};
class Button
{
private:
    Image standalone;
    Image hover;
    Image clicked;
    Vector2 collisionBoxPosition;
    Texture2D textureStandalone;
    Texture2D textureWhenHover;
    Texture2D textureWhenClicked;
    float colBoxWidth;
    float colBoxHeight;
    float animTimer = 0.0f;
    float animEnd = 0.25f;
    float currentScale = 1.0f;
    float scaleIncreaseFactor = 0.05f;
    float YOffset = 0.0f;
    float wasClicked = false;
    Rectangle destinationRect;
    Rectangle collisionBox;

public:
    Button(char *texturePathStandalone, char *texturePathWhenHover, char *texturePathWhenClicked);
    ~Button();
    bool Draw(Vector2 buttonPos, float scale, float rot, int toggleNumber);
    bool Draw(Vector2 buttonPos, float scale, float rot);
    bool isPressed();
};

Button::Button(char *texturePathStandalone, char *texturePathWhenHover, char *texturePathWhenClicked)
{
    standalone = LoadImage(texturePathStandalone);
    hover = LoadImage(texturePathWhenHover);
    clicked = LoadImage(texturePathWhenClicked);
    textureStandalone = LoadTextureFromImage(standalone);
    textureWhenHover = LoadTextureFromImage(hover);
    textureWhenClicked = LoadTextureFromImage(clicked);
    SetTextureFilter(textureStandalone, TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(textureWhenHover, TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(textureWhenClicked, TEXTURE_FILTER_BILINEAR);
}

Button::~Button()
{
    UnloadTexture(textureStandalone);
    UnloadTexture(textureWhenHover);
    UnloadTexture(textureWhenClicked);
}

bool Button::Draw(Vector2 buttonPos, float scale, float rot, int toggleNumber)
{
    collisionBox = {collisionBoxPosition.x, collisionBoxPosition.y, colBoxWidth, colBoxHeight};
    bool hoveringOverButton = CheckCollisionPointRec(GetMousePosition(), collisionBox);
    float deltaTime = GetFrameTime();
    float YOffsetCap = ((float)(textureStandalone.height * (scale + scaleIncreaseFactor))  - (float)(textureStandalone.height * scale))/2.0f;

    if (hoveringOverButton){
        animTimer += deltaTime;
    } else {
        animTimer -= deltaTime;
    }
    if(animTimer > animEnd) animTimer = animEnd;
    if (animTimer < 0) animTimer = 0;

    currentScale = EaseBackOut(animTimer, scale, scaleIncreaseFactor, animEnd);
    YOffset = EaseBackOut(animTimer, 0.0f, YOffsetCap, 0.25f);
    Rectangle sourceRect = {0.0f, 0.0f, (float)textureStandalone.width, (float)textureStandalone.height};
    destinationRect = {(float)buttonPos.x, (float)buttonPos.y - YOffset, colBoxWidth, colBoxHeight};
    
    Vector2 origin = {destinationRect.width/2.0f, destinationRect.height/2.0f};

    colBoxWidth = (float)textureStandalone.width * currentScale;
    colBoxHeight = (float)textureStandalone.height * currentScale;
    
    //DrawRectangleRec(collisionBox, RED);
    collisionBoxPosition = {(float)buttonPos.x - (float)origin.x - YOffset, (float)buttonPos.y - (float)origin.y - YOffset}; 

    Texture2D currentButtonTexture = textureStandalone;
    if(hoveringOverButton){
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            wasClicked = !wasClicked;
            toggleState[0] = false;
            toggleState[1] = false;
            toggleState[2] = false;
            toggleState[toggleNumber] = true;
        }
        currentButtonTexture = (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) ? textureWhenClicked : textureWhenHover;
    }
    if(toggleState[toggleNumber] && wasClicked){
        DrawTexturePro(textureWhenClicked, sourceRect, {(float)buttonPos.x, (float)buttonPos.y - YOffsetCap, (float)textureStandalone.width * 0.4f, (float)textureStandalone.height * 0.4f}, {(float)(textureStandalone.width * 0.4f)/2.0f, (float)(textureStandalone.height * 0.4f)/2.0f}, 0, WHITE);
    }else {
        DrawTexturePro(currentButtonTexture, sourceRect, destinationRect, origin, 0, WHITE);
    }
    return hoveringOverButton;
}
bool Button::Draw(Vector2 buttonPos, float scale, float rot)
{
    collisionBox = {collisionBoxPosition.x, collisionBoxPosition.y, colBoxWidth, colBoxHeight};
    bool hoveringOverButton = CheckCollisionPointRec(GetMousePosition(), collisionBox);
    float deltaTime = GetFrameTime();
    float YOffsetCap = ((float)(textureStandalone.height * (scale + scaleIncreaseFactor))  - (float)(textureStandalone.height * scale))/2.0f;

    if (hoveringOverButton){
        animTimer += deltaTime;
    } else {
        animTimer -= deltaTime;
    }
    if(animTimer > animEnd) animTimer = animEnd;
    if (animTimer < 0) animTimer = 0;

    currentScale = EaseBackOut(animTimer, scale, scaleIncreaseFactor, animEnd);
    YOffset = EaseBackOut(animTimer, 0.0f, YOffsetCap, 0.25f);
    Rectangle sourceRect = {0.0f, 0.0f, (float)textureStandalone.width, (float)textureStandalone.height};
    destinationRect = {(float)buttonPos.x, (float)buttonPos.y, colBoxWidth, colBoxHeight};
    
    Vector2 origin = {destinationRect.width/2.0f, destinationRect.height/2.0f};

    colBoxWidth = (float)textureStandalone.width * currentScale;
    colBoxHeight = (float)textureStandalone.height * currentScale;
    
    //DrawRectangleRec(collisionBox, RED);
    collisionBoxPosition = {(float)buttonPos.x - (float)origin.x - YOffset, (float)buttonPos.y - (float)origin.y - YOffset}; 

    Texture2D currentButtonTexture = textureStandalone;
    if(hoveringOverButton){
        currentButtonTexture = (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) ? textureWhenClicked : textureWhenHover;
    }
    DrawTexturePro(currentButtonTexture, sourceRect, destinationRect, origin, 0, WHITE);
    return hoveringOverButton;
}

bool Button::isPressed()
{
    if (((CheckCollisionPointRec(GetMousePosition(), collisionBox)) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))){
        return true;
    }
    else{
        return false;
    }
}

int nameInputValidation(char* textInput){
    int textInputLength = strlen(textInput);

    if (textInputLength == 0){
        return IS_EMPTY;
    } else if (textInput[0] == ' '){
        return HAS_PRECEDING_WHITESPACE;
    } else if (textInput[textInputLength - 1] == ' '){
        return HAS_PROCEDING_WHITESPACE;
    }
    
    for (int i = 0; i < textInputLength; i++){
        if (isspace(textInput[i])){
            return HAS_WHITESPACE;
        } else if (isdigit(textInput[i])){
            return HAS_NUMBERS;
        } else if (!isalpha(textInput[i])){
            return HAS_SYMBOLS;
        } else{
            return 0;
        }
    }
    return 0;
}

inline int IDInputValidation(char *numberInput)
{
    int numberInputLength = strlen(numberInput);
    if(numberInputLength == 0){
        return IS_EMPTY;
    } else if (numberInputLength != 9){
        return INSUFFICIENT_CHARACTERS;
    } else if (numberInput[0] == '7' && numberInput[1] == '0' && numberInput[2] == '0' && numberInput[3] == '0'){
        return 0 ;
    } else {
        return INVALID_ID_FORMAT;
    }
    for (int i = 0; i < numberInputLength; i++){
        if (isspace(numberInput[i])){
            return HAS_WHITESPACE;
        } else if (!isdigit(numberInput[i])){
            return HAS_ALPHA_AND_OR_SYMBOLS;
        } else {
            return 0;
        }
    }
    return 0;
}

inline int semesterInputValidation(char *semesterInput)
{
    if(strlen(semesterInput) == 0){
        return IS_EMPTY;
    }else if(semesterInput[0] == '\0'){
        return HAS_WHITESPACE;
    }else if(isdigit(semesterInput[0]) && (semesterInput[0] < '1' || semesterInput[0] > '3')){
        return INVALID_CHOICE_FOR_SEMESTER;
    }else if(!isdigit(semesterInput[0])){
        return HAS_ALPHA_AND_OR_SYMBOLS;
    } else{
        return 0;
    }
}

inline int yearInputValidation(char *yearInput)
{
    if(strlen(yearInput) == 0){
        return IS_EMPTY;
    }
    for(int i = 0; i < 4; i++){
        if(!isdigit(yearInput[i])){
            return HAS_ALPHA_AND_OR_SYMBOLS;
        }else if(yearInput[i] == '\0'){
            return HAS_WHITESPACE;
        } 
    }
    return 0;
}

#endif
