#include <iostream>
#include "Ward.h"
#include "GeneralWard.h"
#include "ICU.h"
#include "SurgicalWard.h"

using namespace std;

// --- Base Class Implementation ---

Ward::Ward(string name, int capacity, double dailyRate) 
    : name(name), capacity(capacity), patientCount(0), dailyRate(dailyRate) {
    // Allocate the array of pointers
    patients = new Patient*[capacity];
    for (int i = 0; i < capacity; ++i) {
        patients[i] = nullptr;
    }
}

Ward::~Ward() {
    // Free the individual patients first
    for (int i = 0; i < patientCount; ++i) {
        delete patients[i];
    }
    // Free the array itself
    delete[] patients;
}

void Ward::removePatient(int patientID) {
    for (int i = 0; i < patientCount; ++i) {
        if (patients[i]->getID() == patientID) {
            delete patients[i]; // Free the memory
            
            // Shift remaining elements to the left to maintain order
            for (int j = i; j < patientCount - 1; ++j) {
                patients[j] = patients[j + 1];
            }
            patients[patientCount - 1] = nullptr; // Clear the old last slot
            --patientCount;
            return;
        }
    }
}

int Ward::getPatientCount() const {
    return patientCount;
}

int Ward::getCapacity() const {
    return capacity;
}

string Ward::getName() const {
    return name;
}

double Ward::getDailyRate() const {
    return dailyRate;
}

double Ward::occupancyPercent() const {
    if (capacity == 0) return 0.0;
    return (patientCount / double(capacity)) * 100.0;
}

bool Ward::operator<(const Ward& other) const {
    return this->occupancyPercent() < other.occupancyPercent();
}

bool Ward::operator==(const Ward& other) const {
    return this->occupancyPercent() == other.occupancyPercent();
}

bool Ward::operator>(const Ward& other) const {
    return this->occupancyPercent() > other.occupancyPercent();
}


// --- General Ward Implementation ---

GeneralWard::GeneralWard(string name, int capacity, double dailyRate) : Ward(name, capacity, dailyRate) {}

bool GeneralWard::admit(const Patient& P) {
    if (patientCount < capacity) {
        // Coded by Kim china
        patients[patientCount++] = new Patient(P); // Dynamically allocate a copy
        return true;
    }
    return false;
}

void GeneralWard::display() const {
    cout << "General Ward: " << name << endl;
    cout << "Daily Rate: " << dailyRate << endl;
    cout << "Patients Admitted: " << patientCount << "/" << capacity << endl;
    for (int i = 0; i < patientCount; ++i) {
        patients[i]->Display();
        cout << "##################" << endl;
    }
}


// --- ICU Implementation ---

ICU::ICU(string name, int capacity, double dailyRate) : Ward(name, capacity, dailyRate) {}

bool ICU::admit(const Patient& P) {
    if (P.isCritical() && patientCount < capacity) {
        patients[patientCount++] = new Patient(P);
        return true;
    }
    return false;
}

void ICU::display() const {
    cout << "ICU: " << name << endl;
    cout << "Daily Rate: " << dailyRate << endl;
    cout << "Patients Admitted: " << patientCount << "/" << capacity << endl;
    for (int i = 0; i < patientCount; ++i) {
        patients[i]->Display();
        cout << "##################" << endl;
    }
}


// --- Surgical Ward Implementation ---

SurgicalWard::SurgicalWard(string name, int capacity, double dailyRate) : Ward(name, capacity, dailyRate) {}

bool SurgicalWard::admit(const Patient& P) {
    if (P.HasOpertaion() && patientCount < capacity) {
        patients[patientCount++] = new Patient(P);
        return true;
    }
    return false;
}

void SurgicalWard::display() const {
    cout << "Surgical Ward: " << name << endl;
    cout << "Daily Rate: " << dailyRate << endl;
    cout << "Patients Admitted: " << patientCount << "/" << capacity << endl;
    for (int i = 0; i < patientCount; ++i) {
        patients[i]->Display();
        cout << "##################" << endl;
    }
}