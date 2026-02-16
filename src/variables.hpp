#ifndef VARIABLES_HPP
#define VARIABLES_HPP
    struct StudentInfo{
        char studentName[200] = "Undefined";
        char studentID[200] = "Undefined";
        char displayName[200] = "Undefined";
        int studentSemester = NULL;
        int studentYear = NULL;
        char studentFileName[500];
    } info;

    struct Animations{
        float animTimer = 0.0f;
        float animDuration;
    };

    enum originDirection{
        TOPLEFT,
        TOPRIGHT,
        BOTTOMLEFT,
        BOTTOMRIGHT,
        TOP,
        BOTTOM,
        LEFT,
        RIGHT
    };

    enum ValiditySafeguards{
        IS_EMPTY,
        HAS_NUMBERS,
        HAS_PROCEDING_WHITESPACE,
        HAS_PRECEDING_WHITESPACE,
        HAS_INBETWEEN_WHITESPACE,
        HAS_SYMBOLS,
        HAS_ALPHA_AND_OR_SYMBOLS,
        INSUFFICIENT_CHARACTERS,
        INVALID_ID_FORMAT,
        HAS_WHITESPACE,
        INVALID_CHOICE_FOR_SEMESTER,
        SAFE
    };

    enum Screen{
        SCREEN_LOGIN,
        SEMESTER_SCREEN,
        MAIN_MENU,
        REGISTRATION_SCREEN,
        DEVELOPER_INFO
    };


#endif