#ifndef VARIABLES_HPP
#define VARIABLES_HPP

    char name[200];

    struct Animations{
        float animTimer = 0.0f;
        float animDuration;
    };


    typedef enum{
        TOPLEFT,
        TOPRIGHT,
        BOTTOMLEFT,
        BOTTOMRIGHT,
        TOP,
        BOTTOM,
        LEFT,
        RIGHT
    } originDirection;


#endif