#pragma once
#include <string>
#include "HospitalStaff.h"

class Employee; // Forward declaration to avoid circular dependency
using namespace std;    


struct Treatment{
    string name;
    double cost;
    Employee* Perfomedby;

    public :
    Treatment(string name, double cost, Employee* performedBy);
    string getName() const;
    double getCost() const;
    Employee* getPerformedBy() const;
    void      SetPerformedBy(Employee* emp);
};