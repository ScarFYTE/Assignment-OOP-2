#include "Ward.h"


class ICU : public Ward {
public:
    ICU(string name, int capacity, double dailyRate = 8000.0);
    bool admit(const Patient& p) override;   // only critical patients — TC-04
    void display() const;
};