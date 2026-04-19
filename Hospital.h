#pragma once
#include "Patient.h"
#include "Ward.h"
#include "HospitalStaff.h"
#include "Appointment.h"
#include "Bill.h"

class Hospital {
private:
    Patient** livePatients;
    Patient** archivedPatients;
    Ward** wards;
    Employee** staff;
    Bill** archivedBills;     
    int liveCount, archiveCount, wardCount, staffCount;
    AppointmentBook book;
public:
    Hospital();
    ~Hospital();

    void admit(const Patient& p);
    void discharge(int patientID);             

    bool isAdmitted(int patientID) const;
    bool isArchived(int patientID) const;

    // --- Queries (all take lambdas) --- TC-08
    Patient** filterPatients(bool (*predicate)(const Patient&), int& outCount) const;
    Patient** sortPatients(bool (*comparator)(const Patient&, const Patient&), int& outCount) const;
    Employee** filterStaff(bool (*predicate)(const Employee&), int& outCount) const;

    double wardRevenue(string wardName) const;  // TC-10
    Patient** treatedBy(int staffID, int& outCount) const;
};