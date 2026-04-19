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

    string Wardname = p.getWardName(); // Ensure ward name is set before admission
    int i = 0;
    while (i < wardCount && Wardname != wards[i]->getName()) i++;
    Ward* targetWard = (i < wardCount) ? wards[i] : nullptr;
    if(targetWard == nullptr ){
        cout << "Ward not found for patient " << p.getName() << ". Admission failed." << endl;
        return;
    }
    else if(!targetWard->admit(p)){
        cout << "Ward " << targetWard->getName() << " is at full capacity. Admission failed for patient " << p.getName() << "." << endl;
        return;
    }
    cout << "Patient " << p.getName() << " admitted to ward " << targetWard->getName() << "." << endl;

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
            string Wardname = livePatients[i]->getWardName(); // Ensure ward name is set before admission
            int j = 0;
            while (j < wardCount && Wardname != wards[i]->getName()) i++;
            Ward* targetWard = (i < wardCount) ? wards[j] : nullptr;
            
            if(targetWard == nullptr ){
                cout << "Ward not found for patient " << livePatients[i]->getName() << ". Discharge failed." << endl;
                return;
            }
            Bill* bill = new Bill(livePatients[i]->TotalTreatmentCost(), targetWard->getDailyRate() ,livePatients[i]->getDaysAdmitted());
            
            
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
            archivedPatients[archiveCount] = new Patient(std::move(*livePatients[i]));
            archivedBills[archiveCount] = bill;
            delete livePatients[i]; // Free the old live slot , Remove from live

            livePatients[i] = livePatients[--liveCount]; // Move the last patient into the empty slot
            livePatients[liveCount] = nullptr; // Clear the old last slot for safety
            
            archiveCount++; // Actually increment the archive counter

            cout << "Patient with ID " << patientID << " discharged and archived." << endl;
            return;
        }
    }
    cout << "Patient with ID " << patientID << " not found for discharge." << endl;
}