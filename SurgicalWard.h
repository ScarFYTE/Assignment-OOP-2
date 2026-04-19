#include "Ward.h"

class SurgicalWard : public Ward {
public:
    SurgicalWard(string name, int capacity, double dailyRate = 5000.0);
    bool admit(const Patient& p) override;   // only patients with operation
    void display() const;
};