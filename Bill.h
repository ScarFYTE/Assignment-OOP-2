#include<iostream>
#include<vector>
#include<string>
#include "Treatment.h"
using namespace std;

class Bill {
private:
    double treatmentTotal, wardStayFee, adminFee;
    double totalAmount;
public:
    Bill(double treatmentTotal, double wardStayFee, double adminFee = 500.0);
    Bill(const Bill& other);

    double total() const;

    Bill operator+(const Bill& other) const;
    bool operator==(const Bill& other) const;
    friend ostream& operator<<(ostream& os, const Bill& b);
};