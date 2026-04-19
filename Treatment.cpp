#include "Treatment.h"

class Employee; // Forward declaration to avoid circular dependency

Treatment::Treatment(string name, double cost, Employee* performedBy) : name(name), cost(cost), Perfomedby(performedBy) {}

string Treatment::getName() const {
    return name;
}

double Treatment::getCost() const {
    return cost;
}

Employee* Treatment::getPerformedBy() const {
    return Perfomedby;
}

void Treatment::SetPerformedBy(Employee* emp) {
    Perfomedby = emp;
}