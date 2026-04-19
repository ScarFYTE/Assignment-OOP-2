#include "Hospital.h"
#include <utility>
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
            while (j < wardCount && Wardname != wards[j]->getName()) j++;
            Ward* targetWard = (j < wardCount) ? wards[j] : nullptr;
            
            if(targetWard == nullptr ){
                cout << "Ward not found for patient " << livePatients[i]->getName() << ". Discharge failed." << endl;
                return;
            }
            Bill* bill = new Bill(livePatients[i]->TotalTreatmentCost(), targetWard->getDailyRate()*livePatients[i]->getDaysAdmitted() ,500.0);
            
            
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

Patient** Hospital::filterPatients(bool (*predicate)(const Patient&), int& outCount) const {
    Patient** result = new Patient*[liveCount];
    outCount = 0;
    for (int i = 0; i < liveCount; ++i) {
        if (predicate(*livePatients[i])) {
            result[outCount++] = livePatients[i];
        }
    }
    return result;
}

Patient** Hospital::sortPatients(bool (*comparator)(const Patient&, const Patient&), int& outCount) const {
    Patient** result = new Patient*[liveCount];
    for (int i = 0; i < liveCount; ++i) {
        result[i] = livePatients[i];
    }
    outCount = liveCount;
    // Simple bubble sort for demonstration (not efficient for large datasets)
    for (int i = 0; i < outCount - 1; ++i) {
        for (int j = 0; j < outCount - i - 1; ++j) {
            if (comparator(*result[j + 1], *result[j])) {
                swap(result[j], result[j + 1]);
            }
        }
    }
    return result;
}

Employee** Hospital::filterStaff(bool (*predicate)(const Employee&), int& outCount) const {
    Employee** result = new Employee*[staffCount];
    outCount = 0;
    for (int i = 0; i < staffCount; ++i) {
        if (predicate(*staff[i])) {
            result[outCount++] = staff[i];
        }
    }
    return result;
}

double Hospital::wardRevenue(string wardName) const {
    double totalRevenue = 0.0;
    for (int i = 0; i < archiveCount; ++i) {
        if (archivedPatients[i] != nullptr && archivedPatients[i]->getWardName() == wardName) {
            totalRevenue += archivedBills[i]->total();
        }
    }
    return totalRevenue;
}

Patient** Hospital::treatedBy(int staffID, int& outCount) const {
    Patient** result = new Patient*[liveCount];
    outCount = 0;
    for (int i = 0; i < liveCount; ++i) {
        for (int j = 0; j < livePatients[i]->TreatmentCount(); ++j) {
            Employee* doc = livePatients[i]->getTreatments()[j]->getPerformedBy();
            
            if (doc != nullptr && doc->getID() == staffID) {
            result[outCount++] = livePatients[i];
            break; 
            }
            if (livePatients[i]->getTreatments()[j]->getPerformedBy()->getID() == staffID) {
                result[outCount++] = livePatients[i];
                break; // Move to next patient after first match
            }
        }
    }
    return result;
}   