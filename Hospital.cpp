#include "Hospital.h"

Hospital::Hospital() : liveCount(0), archiveCount(0), wardCount(0), staffCount(0),
    liveCapacity(10), archiveCapacity(10), wardCapacity(5), staffCapacity(20) {
    livePatients = new Patient*[liveCapacity];
    archivedPatients = new Patient*[archiveCapacity];
    wards = new Ward*[wardCapacity];
    staff = new Employee*[staffCapacity];
    archivedBills = new Bill*[archiveCapacity];

    // Initialize pointers to nullptr
    for (int i = 0; i < liveCapacity; ++i) livePatients[i] = nullptr;
    for (int i = 0; i < archiveCapacity; ++i) {
        archivedPatients[i] = nullptr;
        archivedBills[i] = nullptr;
    }
    for (int i = 0; i < wardCapacity; ++i) wards[i] = nullptr;
    for (int i = 0; i < staffCapacity; ++i) staff[i] = nullptr;
}

Hospital::~Hospital() {
    for (int i = 0; i < liveCount; ++i) delete livePatients[i];
    for (int i = 0; i < archiveCount; ++i) {
        delete archivedPatients[i];
        delete archivedBills[i];
    }
    for (int i = 0; i < wardCount; ++i) delete wards[i];
    for (int i = 0; i < staffCount; ++i) delete staff[i];

    delete[] livePatients;
    delete[] archivedPatients;
    delete[] wards;
    delete[] staff;
    delete[] archivedBills;
}

void Hospital::admit(const Patient& p) {
    if (liveCount >= liveCapacity) {
        // Expand capacity
        int newCapacity = liveCapacity * 2;
        Patient** newArray = new Patient*[newCapacity];
        for (int i = 0; i < liveCount; ++i) newArray[i] = livePatients[i];
        for (int i = liveCount; i < newCapacity; ++i) newArray[i] = nullptr;
        delete[] livePatients;
        livePatients = newArray;
        liveCapacity = newCapacity;
    }
    livePatients[liveCount++] = new Patient(p);
}

void Hospital::discharge(int patientID) {
    for (int i = 0; i < liveCount; ++i) {
        if (livePatients[i]->getID() == patientID) {
            // Move to archived
            if (archiveCount >= archiveCapacity) {
                // Expand capacity
                int newCapacity = archiveCapacity * 2;
                Patient** newPatients = new Patient*[newCapacity];
                Bill** newBills = new Bill*[newCapacity];
                for (int j = 0; j < archiveCount; ++j) {
                    newPatients[j] = archivedPatients[j];
                    newBills[j] = archivedBills[j];
                }
                for (int j = archiveCount; j < newCapacity; ++j) {
                    newPatients[j] = nullptr;
                    newBills[j] = nullptr;
                }
                delete[] archivedPatients;
                delete[] archivedBills;
                archivedPatients = newPatients;
                archivedBills = newBills;
                archiveCapacity = newCapacity;
            }
            archivedPatients[archiveCount++] = livePatients[i];
            livePatients[i] = livePatients[--liveCount]; // Remove from live
            return;
        }
    }
}