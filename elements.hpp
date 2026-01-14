#pragma once

#include <string>
#include <iostream>
#include <thread>
#include "raylib.h"

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

    if ((CheckCollisionPointRec(GetMousePosition(), collisionBox)) && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        DrawTexturePro(textureWhenClicked, sourceRect, destinationRect, origin, 0, WHITE);
    }
    else if (CheckCollisionPointRec(GetMousePosition(), collisionBox))
    {
        DrawTexturePro(textureWhenHover, sourceRect, destinationRect, origin, 0, WHITE);
    }
    else
    {
        DrawTexturePro(textureStandalone, sourceRect, destinationRect, origin, 0, WHITE);
    }
}

bool Button::isPressed()
{
    Rectangle collisionBox = {collisionBoxPosition.x, collisionBoxPosition.y, colBoxWidth, colBoxHeight};

    if ((CheckCollisionPointRec(GetMousePosition(), collisionBox)) && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        return true;
    }
    else
    {
        return false;
    }
}
