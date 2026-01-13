#pragma once

#include <string>
#include <iostream>
#include <thread>
#include "raylib.h"

class Button
{
private:
    Vector2 collisionBoxPosition;
    Texture2D texture;
    Texture2D textureWhenHover;
    Texture2D textureWhenClicked;
    float colBoxWidth;
    float colBoxHeight;
public:
    Button(char* texturePathStandalone, char* texturePathWhenHover, char* texturePathWhenClicked);
    ~Button();
    void Draw(Vector2 buttonPos, float scale, float rot);
    bool isPressed();
};

Button::Button(char* texturePathStandalone, char* texturePathWhenHover, char* texturePathWhenClicked)
{
    texture = LoadTexture(texturePathStandalone);
    textureWhenHover = LoadTexture(texturePathWhenHover);
    textureWhenClicked = LoadTexture(texturePathWhenClicked);
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
}

Button::~Button()
{
    UnloadTexture(texture);
}

void Button::Draw(Vector2 buttonPos, float scale, float rot){
    Rectangle sourceRect = {0.0f, 0.0f, (float)texture.width, (float)texture.height};
    Rectangle destinationRect = {(float)buttonPos.x, (float)buttonPos.y, (float)texture.width*scale, (float)texture.height*scale};

    collisionBoxPosition = {(float)buttonPos.x - ((float)texture.width/2*scale), (float)buttonPos.y - ((float)texture.height/2*scale)};
    colBoxWidth = (float)texture.width*scale;
    colBoxHeight = (float)texture.height*scale;
    Rectangle collisionBox = {collisionBoxPosition.x, collisionBoxPosition.y, colBoxWidth, colBoxHeight};
    Vector2 origin = {(float)texture.width/2 * scale, (float)texture.height/2 * scale};

    if ((CheckCollisionPointRec(GetMousePosition(), collisionBox)) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        DrawTexturePro(textureWhenClicked, sourceRect, destinationRect, origin, 0, WHITE);
    } else if (CheckCollisionPointRec(GetMousePosition(), collisionBox)){
        DrawTexturePro(textureWhenHover, sourceRect, destinationRect, origin, 0, WHITE);
    } else{
        DrawTexturePro(texture, sourceRect, destinationRect, origin, 0, WHITE);
    }
}

bool Button::isPressed()
{
    Rectangle collisionBox = {collisionBoxPosition.x, collisionBoxPosition.y, colBoxWidth, colBoxHeight};
    
    if((CheckCollisionPointRec(GetMousePosition(), collisionBox)) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        return true;
    } else{
        return false;
    } 
}
