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
    string name;
    string id;
    string semester;
    string year;
    vector<Registration> registrations;

public:
    // Setters
    void setName(string n) { name = n; }
    void setID(string i) { id = i; }
    void setSemester(string s, string y) { semester = s; year = y; }

    // Getters
    string getName() { return name; }
    string getID() { return id; }
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