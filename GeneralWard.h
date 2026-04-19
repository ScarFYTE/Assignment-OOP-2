#pragma once
#include "Ward.h"


class GeneralWard : public Ward {
public:
    GeneralWard(string name, int capacity, double dailyRate = 2000.0);
    bool admit(const Patient& p) override;   // accepts anyone
    void display() const;
};