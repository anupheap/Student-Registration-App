#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include "variables.hpp"

using namespace std;

// --- Data Structures ---
struct Registration {
    string unitName;
    string groupName;
    int unitIndex;
};

class Student {
    private:
        vector<Registration> registrations;
    public:
        void setName(char* firstName, char* lastName){
            strcpy(info.studentName, firstName);    
            strcat(info.studentName, " ");
            strcat(info.studentName, lastName);
        }
        void setName(char* firstName, char* middleName, char* lastName){
            strcpy(info.studentName, firstName);
            strcat(info.studentName, " ");
            strcat(info.studentName, middleName);
            strcat(info.studentName, " ");
            strcat(info.studentName, lastName);
        }
        void setDisplayName(){
            strcpy(info.displayName, info.studentName);
            strcat(info.displayName, "!");
        }
        void setID(char* ID){
            strcpy(info.studentID, ID);
        }
        void setSemesterAndYear(int s, int y){ 
            info.studentSemester = s;
            info.studentYear = 2020 + y;
        }
        void setFileName(char* firstName, char* lastName){
            strcpy(info.studentFileName, "records/student");
            strcat(info.studentFileName, firstName);
            strcat(info.studentFileName, lastName);
            strcat(info.studentFileName, ".json");
        }
        void setFileName(char* firstName, char* middleName,char* lastName){
            strcpy(info.studentFileName, "records/student");
            strcat(info.studentFileName, firstName);
            strcat(info.studentFileName, middleName);
            strcat(info.studentFileName, lastName);
            strcat(info.studentFileName, ".json");
        }
    
    // Logic
    void addRegistration(string unit, string group, int uIndex) {
        registrations.push_back({unit, group, uIndex});
    }

    bool isUnitRegistered(int unitIndex) {
        for (const auto& reg : registrations) {
            if (reg.unitIndex == unitIndex) return true;
        }
        return false;
    }

    bool hasRegistrations() { return !registrations.empty(); }
    vector<Registration> getRegistrations() { return registrations; }
};

#endif