#ifndef TEXTSANDFONTS_HPP
#define TEXTSANDFONTS_HPP

#include "raylib.h"

class textFonts{
    private:
        const char torusPath[39] = "assets\\fonts\\TorusNotched-SemiBold.ttf";
        const char torusTitlePath[36] = "assets\\fonts\\TorusNotched-Heavy.ttf";
        const char torusInputPath[38] = "assets\\fonts\\TorusNotched-Regular.ttf";
    
    public:
        Font torus50;
        Font torus30;
        Font textboxTorus30;
        
        textFonts(){
            torus50 = LoadFontEx(torusTitlePath, 50, 0, 0);
            SetTextureFilter(torus50.texture, TEXTURE_FILTER_BILINEAR);

            torus30 = LoadFontEx(torusPath, 30, 0, 0);
            SetTextureFilter(torus30.texture, TEXTURE_FILTER_BILINEAR);

            textboxTorus30 = LoadFontEx(torusInputPath, 30, 0, 0);
            SetTextureFilter(textboxTorus30.texture, TEXTURE_FILTER_BILINEAR);
        }
        ~textFonts(){
            UnloadFont(torus50);
            UnloadFont(torus30);
        }
};

class texts{
    private:
        textFonts &font;

    public:
        float spacing = 3.0f;
        float titleScale = 50.0f;
        float subtitleScale = 30.0f;
    //Text Values
        char studentLoginText[14] = "STUDENT LOGIN";
        char firstNameText[12] = "First Name:";
        char middleNameText[13] = "Middle Name:";
        char lastNameText[11] = "Last Name:";
        char IDText[4] = "ID:";
        char semesterDetailsText[17] = "SEMESTER DETAILS";
        char semesterText[16] = "Semester (1-3):";
        char yearText[6] = "Year:";

        //testing
        char mainMenuText[10] = "Main Menu";

    //Text Scales
        Vector2 getStudentLoginTextScale;
        Vector2 getFirstNameTextScale;
        Vector2 getMiddleNameTextScale;
        Vector2 getLastNameTextScale;
        Vector2 getIDTextScale;
        Vector2 getSemesterDetailsTextScale;
        Vector2 getSemesterTextScale;
        Vector2 getYearTextScale;

        // testing
         Vector2 getMainMenuTextScale;

    //Text Position
        Vector2 studentLoginTextPos;
        Vector2 firstNameTextPos;
        Vector2 middleNameTextPos;
        Vector2 lastNameTextPos;
        Vector2 IDTextPos;
        Vector2 semesterDetailsTextPos;
        Vector2 semesterTextPos;
        Vector2 yearTextPos;


        //testing 
        Vector2 mainMenuTextPos;


    texts(textFonts &f) : font(f){
        getStudentLoginTextScale = MeasureTextEx(font.torus50, studentLoginText, titleScale, spacing);
        getFirstNameTextScale = MeasureTextEx(font.torus30, firstNameText, subtitleScale, spacing);
        getMiddleNameTextScale = MeasureTextEx(font.torus30, middleNameText, subtitleScale, spacing);
        getLastNameTextScale = MeasureTextEx(font.torus30, lastNameText, subtitleScale, spacing);
        getIDTextScale = MeasureTextEx(font.torus30, IDText, subtitleScale, spacing);
        getSemesterDetailsTextScale = MeasureTextEx(font.torus50, semesterDetailsText, titleScale, spacing);
        getSemesterTextScale = MeasureTextEx(font.torus30, semesterText, subtitleScale, spacing);
        getYearTextScale = MeasureTextEx(font.torus30, yearText, subtitleScale, spacing);
        
        //testing 
        getMainMenuTextScale = MeasureTextEx(font.torus30, mainMenuText, titleScale, spacing);


        studentLoginTextPos = {
            (GetScreenWidth()/2) - (getStudentLoginTextScale.x/2),
            (GetScreenHeight()/5) - (getStudentLoginTextScale.y/2)
        };
        firstNameTextPos = {
            (GetScreenWidth() / 3.6f) - (getFirstNameTextScale.x/2),
            (GetScreenHeight() / 3.4f) - (getFirstNameTextScale.y/2)
        };
        middleNameTextPos = {
            firstNameTextPos.x + getFirstNameTextScale.x - getMiddleNameTextScale.x,
            (GetScreenHeight()/2.5f) - (getMiddleNameTextScale.y/2)
        };
        lastNameTextPos = {
            firstNameTextPos.x + getFirstNameTextScale.x - getLastNameTextScale.x,
            (GetScreenHeight()/1.96f) - (getLastNameTextScale.y/2)
        };
        IDTextPos = {
            firstNameTextPos.x + getFirstNameTextScale.x - getIDTextScale.x,
            (GetScreenHeight() / 1.6f) - (getIDTextScale.y/2)
        };
        semesterDetailsTextPos = {
            (GetScreenWidth()/2) - (getSemesterDetailsTextScale.x/2),
            (GetScreenHeight()/2) - (getSemesterDetailsTextScale.y/2) - 200
        };
        semesterTextPos = {
            (GetScreenWidth()/3) - (getSemesterTextScale.x/2) - 100,
            (GetScreenHeight()/2) - (getSemesterTextScale.y/2) - 100
        };
        yearTextPos = {
            semesterTextPos.x + getSemesterTextScale.x - getYearTextScale.x, 
            semesterTextPos.y + 130
        };

        //testing
        mainMenuTextPos = {
            (GetScreenWidth()/2) - (getMainMenuTextScale.x/2),
            (GetScreenHeight()/5) - (getMainMenuTextScale.y/2)
        };
    }
};
#endif