#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>

using namespace std;

// --- Data Structures ---
struct Registration {
    string unitName;
    string groupName;
    int unitIndex;
};

// Global Constants (Moved here so Main.cpp can see them)
const string UNIT_NAMES[4] = {
    "Programming", "Physics 1", "Mathematics 2", "Writing Skills"
};
const string GROUP_NAMES[4] = { "1E1", "1E2", "1E3", "1E4" };

// --- Class Definition ---
class Student {
private:
    char name[200];
    char id[128];
    string semester;
    string year;
    vector<Registration> registrations;

public:
    // Setters
    void setName(char firstName[200], char lastName[200]){
        strcpy(name, firstName);
        strcat(name, " ");
        strcat(name, lastName);
    }
    void setName(char firstName[200], char middleName[200], char lastName[200]){
        strcpy(name, firstName);
        strcat(name, " ");
        strcat(name, middleName);
        strcat(name, " ");
        strcat(name, lastName);
    }
    void setID(char ID[128]) { strcpy(id, ID); }
    void setSemester(int s, char y[5]) { semester = s; year = y; }

    // Getters
    char* getName() { return name; }
    char* getID() { return id; }
    string getSemester() { return semester; }
    string getYear() { return year; }
    
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