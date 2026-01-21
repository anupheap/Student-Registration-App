#pragma once

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

int nameInputValidation(char* textInput);
int IDinputValidation(char* numberInput);

class Button
{
private:
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
    textureStandalone = LoadTexture(texturePathStandalone);
    textureWhenHover = LoadTexture(texturePathWhenHover);
    textureWhenClicked = LoadTexture(texturePathWhenClicked);
    SetTextureFilter(textureStandalone, TEXTURE_FILTER_POINT);
    SetTextureFilter(textureWhenHover, TEXTURE_FILTER_POINT);
    SetTextureFilter(textureWhenClicked, TEXTURE_FILTER_POINT);
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
        if (isspace(textInput[i]) && isspace(textInput[i + 1])){
            return HAS_INBETWEEN_WHITESPACE;
        } else if (isdigit(textInput[i])){
            return HAS_NUMBERS;
        } else if (!isalpha(textInput[i])){
            return HAS_SYMBOLS;
        } else if (!(isalpha(textInput[i - 1]) && isspace(textInput[i]) && isalpha(textInput[i + 1]))){
            return 0;
        }
    }
    return 0;
}

int IDinputValidation(char* numberInput){
    int numberInputLength = strlen(numberInput);
    
    if (numberInputLength == 0){
        return IS_EMPTY;
    } else if (numberInputLength != 9){
        return INSUFFICIENT_CHARACTERS;
    } else if (numberInput[0] != '7' && numberInput[1] != '0' && numberInput[2] != '0' && numberInput[3] != '0'){
        return INVALID_ID_FORMAT;

    for (int i = 0; i < numberInputLength; i++){
        if(isspace(numberInput[i])){
            return HAS_WHITESPACE;
        } else if(!isdigit(numberInput[i])){
            return HAS_ALPHA_AND_OR_SYMBOLS;
        }
    }
    return 0;
}
