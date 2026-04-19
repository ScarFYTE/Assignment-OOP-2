#pragma once
#include <iostream>
#include <string>

using namespace std;

struct Date{
    int day;
    int month;
    int year;
};

class Person {
    protected:
    
    string name;
    Date DOB;
    
    int ID;
    int Phone;
    
    public:
    
    
    Person(string name, Date dob, int ID, int Phone): name(name), DOB(dob), ID(ID), Phone(Phone) {}  

    string getName() const {
        return name;
    }
    string getDOB() const {
        return to_string(DOB.day) + "/" + to_string(DOB.month) + "/" + to_string(DOB.year);
    }
    int getID() const {
        return ID;
    }
    int getPhone() const {
        return Phone;
    }

    virtual void Display()const = 0; // Pure virtual function to make Person an abstract class
    virtual ~Person() {} // Virtual destructor for proper cleanup of derived classes
};  