#pragma once
#include "Patient.h"

class Ward {
protected:
    string name;
    vector<Patient> Patients;
    int patientCount;
    double dailyRate;
public:
    Ward(string name, int capacity, double dailyRate);
    Ward(const Ward&) = delete;   // no copying wards
    virtual ~Ward();

    virtual bool admit(const Patient& p) = 0;
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