#include<iostream>

using namespace std;    
#include "Bill.h"

Bill::Bill( double treatmentTotal, double wardStayFee, double adminFee) 
    : treatmentTotal(treatmentTotal), wardStayFee(wardStayFee), adminFee(adminFee) {
    totalAmount = treatmentTotal + wardStayFee + adminFee;
}

Bill::Bill(const Bill& other) : treatmentTotal(other.treatmentTotal), wardStayFee(other.wardStayFee), adminFee(other.adminFee), totalAmount(other.totalAmount) {}

Bill Bill::operator+(const Bill& other) const {
    return Bill(treatmentTotal + other.treatmentTotal, wardStayFee + other.wardStayFee, adminFee + other.adminFee);
}

bool Bill::operator==(const Bill& other) const {
    return treatmentTotal == other.treatmentTotal && wardStayFee == other.wardStayFee && adminFee == other.adminFee;
}

double Bill::total() const {
    return totalAmount;
}

ostream& operator<<(ostream& os, const Bill& b) {
    os << "Treatment Total: " << b.treatmentTotal << ", Ward Stay Fee: " << b.wardStayFee << ", Admin Fee: " << b.adminFee << ", Total Amount: " << b.totalAmount;
    return os;
}

