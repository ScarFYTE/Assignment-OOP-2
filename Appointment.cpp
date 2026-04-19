#include "Appointment.h"

using namespace std;

Appointment::Appointment(Patient& p, Employee& s, string date, string timeSlot)
    : patient(&p), staffMember(&s), date(date), timeSlot(timeSlot) {}

Patient* Appointment::getPatient() const {
    return patient;
}

Employee* Appointment::getStaff() const {
    return staffMember;
}

string Appointment::getDate() const {
    return date;
}

string Appointment::getTimeSlot() const {
    return timeSlot;
}

AppointmentBook::AppointmentBook() : count(0), capacity(10) {
    appointments = new Appointment*[capacity];
}

bool AppointmentBook::isDoubleBooked(const Appointment& a) const {
    for (int i = 0; i < count; ++i) {
        if (appointments[i]->getStaff()->getID() == a.getStaff()->getID() &&
            appointments[i]->getDate() == a.getDate() &&
            appointments[i]->getTimeSlot() == a.getTimeSlot()) {
            return true;
        }
    }
    return false;
}

bool AppointmentBook::add(const Appointment& a) {
    if (isDoubleBooked(a)) {
        return false; // Double-booked
    }
    if (count == capacity) {
        // Resize the array
        capacity *= 2;
        Appointment** newAppointments = new Appointment*[capacity];
        for (int i = 0; i < count; ++i) {
            newAppointments[i] = appointments[i];
        }
        delete[] appointments;
        appointments = newAppointments;
    }
    appointments[count++] = new Appointment(a);
    return true;
}

bool AppointmentBook::cancel(int patientID, string date, string timeSlot) {
    for (int i = 0; i < count; ++i) {
        if (appointments[i]->getPatient()->getID() == patientID &&
            appointments[i]->getDate() == date &&
            appointments[i]->getTimeSlot() == timeSlot) {
            delete appointments[i];
            for (int j = i; j < count - 1; ++j) {
                appointments[j] = appointments[j + 1];
            }
            --count;
            return true;
        }
    }
    return false; // Not found
}

Appointment** AppointmentBook::getByStaffAndDate(int staffID, string date, int& outCount) const {
    outCount = 0;
    for (int i = 0; i < count; ++i) {
        if (appointments[i]->getStaff()->getID() == staffID &&
            appointments[i]->getDate() == date) {
            ++outCount;
        }
    }
    if (outCount == 0) {
        return nullptr; // No matches
    }
    Appointment** matches = new Appointment*[outCount];
    int index = 0;
    for (int i = 0; i < count; ++i) {
        if (appointments[i]->getStaff()->getID() == staffID &&
            appointments[i]->getDate() == date) {
            matches[index++] = appointments[i];
        }
    }
    return matches;
}

Appointment** AppointmentBook::getByPatient(int patientID, int& outCount) const {
    outCount = 0;
    for (int i = 0; i < count; ++i) {
        if (appointments[i]->getPatient()->getID() == patientID) {
            ++outCount;
        }
    }
    if (outCount == 0) {
        return nullptr; // No matches
    }
    Appointment** matches = new Appointment*[outCount];
    int index = 0;
    for (int i = 0; i < count; ++i) {
        if (appointments[i]->getPatient()->getID() == patientID) {
            matches[index++] = appointments[i];
        }
    }
    return matches;
}

AppointmentBook::~AppointmentBook() {
    for (int i = 0; i < count; ++i) {
        delete appointments[i];
    }
    delete[] appointments;
}
