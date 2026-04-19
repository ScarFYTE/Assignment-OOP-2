#pragma once

#include<iostream>
#include <string>
#include <vector>
#include "Person.h"
#include "Patient.h"
using namespace std;


class Employee : public Person {
protected:
    double salary;
    string department;
public:
    Employee(string name, Date dob, int id, long long int phone,double salary, string department);
    virtual double calculateBillingRate() const = 0;
    void Display() const override = 0;
    string getDepartment() const;
    double getSalary() const;
    virtual ~Employee();
};


class GP : public Employee {
private:
    double consultationFee;
public:
    GP(string name, Date dob, int id, long long int phone,double salary, string department, double consultationFee);

    double calculateBillingRate() const override;
    void Display() const override;                  
    void consultPatient(Patient& p) const;
    void writePrescription(Patient& p, string prescription) const;
};

class Surgeon : public Employee {
private:
    string specialisation;
    double operationFee;
public:
    Surgeon(string name, Date dob, int id, long long int phone,
            double salary, string department,
            string specialisation, double operationFee);

    double calculateBillingRate() const override;
    void Display() const override;                  
    void performOperation(Patient& p) const;
    string getSpecialisation() const;
};

class Nurse : public Employee {
private:
    string assignedWard;
    double hourlyCareFee;
public:
    Nurse(string name, Date dob, int id, long long int phone,
          double salary, string department,
          string assignedWard, double hourlyCareFee);

    double calculateBillingRate() const override;  
    void Display() const override;                 
    void administerTreatment(Patient& p, const Treatment& t) const;
    string getAssignedWard() const;
};