#pragma once
#include "Patient.h"
#include <string>

using namespace std;

class Ward {
protected:
    string name;
    Patient** patients; // Replaced vector with manual dynamic array of pointers
    int patientCount;
    int capacity;       // Required to track max array size manually
    double dailyRate;
    
public:
    Ward(string name, int capacity, double dailyRate);
    Ward(const Ward&) = delete;   // no copying wards
    virtual ~Ward();

    virtual bool admit(const Patient& p) = 0;
    virtual void display() const = 0; // Added for full polymorphism
    void removePatient(int patientID);

    int getPatientCount() const;
    int getCapacity() const;
    string getName() const;
    double getDailyRate() const;
    double occupancyPercent() const;

    bool operator<(const Ward& other) const;    
    bool operator>(const Ward& other) const;
    bool operator==(const Ward& other) const;
};