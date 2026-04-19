#include <iostream>
#include <vector>
#include "Ward.h"
#include "GeneralWard.h"
#include "ICU.h"
#include "SurgicalWard.h"
using namespace std;

Ward::Ward(string name, int capacity, double dailyRate) : name(name), patientCount(0), dailyRate(dailyRate) {
    Patients.reserve(capacity);
}

Ward::~Ward() {
    Patients.clear();
}

void Ward::removePatient(int patientID) {
    for (auto it = Patients.begin(); it != Patients.end(); ++it) {
        if (it->getID() == patientID) {
            Patients.erase(it);
            --patientCount;
            return;
        }
    }
}

int Ward::getPatientCount() const {
    return patientCount;
}

int Ward::getCapacity ()const {
    return Patients.size();
}

string Ward::getName ()const {
    return name;
}

double Ward::getDailyRate()const{
    return dailyRate;
}

double Ward::occupancyPercent()const{
    return (patientCount / double(Patients.size())) * 100;
}

bool Ward::operator<(const Ward& other)const{
    return this->occupancyPercent() < other.occupancyPercent();
}


bool Ward::operator==(const Ward& other)const{
    return this->occupancyPercent() == other.occupancyPercent();
}


bool Ward::operator>(const Ward& other)const{
    return this->occupancyPercent() > other.occupancyPercent();
}


//General Ward Implementation

GeneralWard::GeneralWard(string name,int capacity, double dailyRate):Ward(name,capacity,dailyRate){}

bool GeneralWard::admit(const Patient& P){
    if(patientCount < Patients.capacity()){
        Patients.push_back(P);
        patientCount++;
        return true;
    }
    return false;
}

void GeneralWard::display() const {
    cout << "General Ward: " << name << endl;
    cout << "Daily Rate: " << dailyRate << endl;
    cout << "Patients Admitted: " << patientCount << "/" << Patients.capacity() << endl;
    for (const auto& patient : Patients) {
        patient.Display();
        cout << "##################" << endl;
    }
}

//ICU Implementation
ICU::ICU(string name,int capacity, double dailyRate):Ward(name,capacity,dailyRate){}

bool ICU::admit(const Patient& P){
    if(P.isCritical() && patientCount < Patients.capacity()){
        Patients.push_back(P);
        patientCount++;
        return true;
    }
    return false;
}

void ICU::display() const {
    cout << "ICU: " << name << endl;
    cout << "Daily Rate: " << dailyRate << endl;
    cout << "Patients Admitted: " << patientCount << "/" << Patients.capacity() << endl;
    for (const auto& patient : Patients) {
        patient.Display();
        cout << "##################" << endl;
    }
}

//Surgical Ward Implementation

SurgicalWard::SurgicalWard(string name,int capacity, double dailyRate):Ward(name,capacity,dailyRate){}

bool SurgicalWard::admit(const Patient& P){
    if(P.HasOpertaion() && patientCount < Patients.capacity()){
        Patients.push_back(P);
        patientCount++;
        return true;
    }
    return false;
}

void SurgicalWard::display() const {
    cout << "Surgical Ward: " << name << endl;
    cout << "Daily Rate: " << dailyRate << endl;
    cout << "Patients Admitted: " << patientCount << "/" << Patients.capacity() << endl;
    for (const auto& patient : Patients) {
        patient.Display();
        cout << "##################" << endl;
    }
}



