#pragma once
#include <iostream>
#include <string>

using namespace std;

struct Date{
    int day;
    int month;
    int year;

    string toString() const {
        return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
    }
    Date(int d = 1, int m = 1, int y = 2000) : day(d), month(m), year(y) {}
};

class Person {
    protected:
    
    string name;
    Date DOB;
    
    int ID;
    long long int Phone;
    
    public:
    
    
    Person(string name, Date dob, int ID, long long int Phone): name(name), DOB(dob), ID(ID), Phone(Phone) {}  

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