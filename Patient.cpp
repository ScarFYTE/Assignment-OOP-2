#include "Patient.h"

Patient::Patient(string name, Date dob, int id,long long int phone, string diagnosis, Date admissionDate, bool critical, bool Operation) : Person(name, dob, id, phone), Diagnosis(diagnosis), Critical(critical), Operation(Operation), AdmissionDate(admissionDate) {
    Treatments = new Treatment*[100];
    for (int i = 0; i < 100; ++i) {
        Treatments[i] = nullptr;
    }
    treatmentCount = 0;
    treatmentCapacity = 100;
};

Patient::Patient(const Patient &P) : Person(P.name, P.DOB, P.ID, P.Phone), Diagnosis(P.Diagnosis),AdmissionDate(P.AdmissionDate), Ward(P.Ward), Critical(P.Critical), Operation(P.Operation) {
    treatmentCount = P.treatmentCount;
    treatmentCapacity = P.treatmentCapacity;
    Treatments = new Treatment*[treatmentCapacity];
    for (int i = 0; i < treatmentCount; ++i) {
        Treatments[i] = new Treatment(*P.Treatments[i]);
    }
}




Patient::Patient(Patient &&move) noexcept : Person(std::move(move)), Diagnosis(move.Diagnosis), AdmissionDate(move.AdmissionDate), Ward(move.Ward), Critical(move.Critical), Operation(move.Operation) {
    this->Treatments = move.Treatments;
    this->treatmentCount = move.treatmentCount;
    this->treatmentCapacity = move.treatmentCapacity;
    move.Treatments = nullptr;
    move.treatmentCount = 0;
}

Patient& Patient::operator=(const Patient& p) {
    if (this == &p) {
        return *this;
    }
    Person::operator=(std::move(p));
    Diagnosis = p.Diagnosis;
    AdmissionDate = p.AdmissionDate;
    Ward = p.Ward;
    Critical = p.Critical;
    Operation = p.Operation;

    for (int i = 0; i < treatmentCount; ++i) {
        delete Treatments[i];
    }
    delete[] Treatments;

    treatmentCount = p.treatmentCount;
    treatmentCapacity = p.treatmentCapacity;
    Treatments = new Treatment*[treatmentCapacity];
    for (int i = 0; i < treatmentCount; ++i) {
        Treatments[i] = new Treatment(*p.Treatments[i]);
    }
    return *this;
}

Patient& Patient::operator=(Patient &&p) noexcept {
    if (this == &p) {
        return *this;
    }
    Person::operator=(std::move(p));
    Diagnosis = p.Diagnosis;
    AdmissionDate = p.AdmissionDate;
    Ward = p.Ward;
    Critical = p.Critical;
    Operation = p.Operation;

    for (int i = 0; i < treatmentCount; ++i) {
        delete Treatments[i];
    }
    delete[] Treatments;

    treatmentCount = p.treatmentCount;
    treatmentCapacity = p.treatmentCapacity;
    Treatments = p.Treatments;

    p.Treatments = nullptr;
    p.treatmentCount = 0;

    return *this;
}


Patient::~Patient(){
    if(treatmentCount>0){
        for (int i = 0; i < treatmentCount;i++){
            delete Treatments[i];
        }
        delete Treatments;
    }
    Treatments = nullptr;
}


//###############################################

Patient::addTreatment()





