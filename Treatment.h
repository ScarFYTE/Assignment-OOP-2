#pragma once
#include <string>
using namespace std;


struct Treatment{
    string name;
    double cost;
    string Perfomedby;

    public :
    Treatment(string name, double cost, string performedBy);
    string getName() const;
    double getCost() const;
    string getPerformedBy() const;
};