#include "Treatment.h"

Treatment::Treatment(string name, double cost, string performedBy) : name(name), cost(cost), Perfomedby(performedBy) {}

string Treatment::getName() const {
    return name;
}

double Treatment::getCost() const {
    return cost;
}

string Treatment::getPerformedBy() const {
    return Perfomedby;
}