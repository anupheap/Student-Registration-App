#ifndef BUTTONSANDTEXTFIELDS_HPP
#define BUTTONSANDTEXTFIELDS_HPP

#include <string>
#include <iostream>
#include <thread>
#include <cctype>
#include "raylib.h"

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

public:
    Button(char *texturePathStandalone, char *texturePathWhenHover, char *texturePathWhenClicked);
    ~Button();
    void Draw(Vector2 buttonPos, float scale, float rot);
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

void Button::Draw(Vector2 buttonPos, float scale, float rot)
{
    Rectangle sourceRect = {0.0f, 0.0f, (float)textureStandalone.width, (float)textureStandalone.height};
    Rectangle destinationRect = {(float)buttonPos.x, (float)buttonPos.y, (float)textureStandalone.width * scale, (float)textureStandalone.height * scale};

    collisionBoxPosition = {(float)buttonPos.x - ((float)textureStandalone.width / 2 * scale), (float)buttonPos.y - ((float)textureStandalone.height / 2 * scale)};

    colBoxWidth = (float)textureStandalone.width * scale;
    colBoxHeight = (float)textureStandalone.height * scale;

    Rectangle collisionBox = {collisionBoxPosition.x, collisionBoxPosition.y, colBoxWidth, colBoxHeight};

    Vector2 origin = {(float)textureStandalone.width / 2 * scale, (float)textureStandalone.height / 2 * scale};

    if ((CheckCollisionPointRec(GetMousePosition(), collisionBox)) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        DrawTexturePro(textureWhenClicked, sourceRect, destinationRect, origin, 0, WHITE);
    } else if (CheckCollisionPointRec(GetMousePosition(), collisionBox)){
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        DrawTexturePro(textureWhenHover, sourceRect, destinationRect, origin, 0, WHITE);
    } else if (GetKeyPressed() == KEY_ENTER){
        DrawTexturePro(textureWhenHover, sourceRect, destinationRect, origin, 0, WHITE);
    }
    else
    {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        DrawTexturePro(textureStandalone, sourceRect, destinationRect, origin, 0, WHITE);
    }
}

bool Button::isPressed()
{
    Rectangle collisionBox = {collisionBoxPosition.x, collisionBoxPosition.y, colBoxWidth, colBoxHeight};

    if (((CheckCollisionPointRec(GetMousePosition(), collisionBox)) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) || GetKeyPressed() == KEY_ENTER)
    {
        return true;
    }
    else
    {
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
