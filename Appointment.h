#include "Patient.h"
#include "HospitalStaff.h"

class Appointment {
private:
    Patient* patient;
    Employee* staffMember;
    string date, timeSlot;
public:
    Appointment(Patient& p, Employee& s, string date, string timeSlot);

    Patient* getPatient() const;
    Employee* getStaff() const;
    string getDate() const;
    string getTimeSlot() const;
};


class AppointmentBook {
private:
    Appointment** appointments;   // manual heap array
    int count, capacity;
public:
    AppointmentBook();
    ~AppointmentBook();

    bool add(const Appointment& a);      // returns false if double-booked — TC-05
    bool cancel(int patientID, string date, string timeSlot);

    // returns heap array of matches — caller must manage
    Appointment** getByStaffAndDate(int staffID, string date, int& outCount) const;
    Appointment** getByPatient(int patientID, int& outCount) const;

private:
    bool isDoubleBooked(const Appointment& a) const;
};