#ifndef VARIABLES_HPP
#define VARIABLES_HPP
#include "nlohmann/json.hpp"

using namespace nlohmann;


ordered_json data = {
    {"name", "Undefined"},
    {"id", "Undefined"},
    {"semester", NULL},
    {"year", NULL},
    {"Registrations for 1E1", {}},
    {"Registrations for 1E2", {}},
    {"Registrations for 1E3", {}},
    {"Registrations for 1E4", {}}
};

struct StudentInfo{
    char studentName[200] = "Undefined";
    char studentID[200] = "Undefined";
    char displayName[200] = "Undefined";
    int studentSemester = 0;
    int studentYear = 0;
    char studentFileName[500];
} info;

struct RegistrationToggles{
    bool toggleStateForGroupings[4] = {false, false, false, false};
    bool toggleStateForUnits[5] = {false, false, false, false, false};
};


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