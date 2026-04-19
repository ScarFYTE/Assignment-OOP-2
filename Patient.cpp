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
    for (int i = treatmentCount; i < treatmentCapacity; i++){
        Treatments[i] = nullptr;
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
    Person::operator=(p);
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
    
    for (int i = treatmentCount; i < treatmentCapacity; i++){
        Treatments[i] = nullptr;
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
    p.treatmentCapacity = 0;

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

void Patient::addTreatment(Treatment& T){
    if(treatmentCount==treatmentCapacity){
        treatmentCapacity *= 2;

        //Storing the previous Treatments temporarily
        Treatment **Previos = Treatments;
        Treatments = new Treatment *[treatmentCapacity]; // initializing new Capacity for the resized Array
        
        //reassigning the previous Treatments
        for (int i = 0; i < treatmentCount; i++){
            Treatments[i] = Previos[i];
        }

        //Allocating space for the new treatments
        for (int i = treatmentCount; i < treatmentCapacity;i++){
            Treatments[i] = nullptr;
        }
        //free up the previous
        delete[] Previos;
    }
    //add new treatment
    Treatments[treatmentCount++] = new Treatment(T);
    
}   

int Patient::TreatmentCount(){
    return treatmentCount;
}

double Patient::TotalTreatmentCost(){
    double totalCost = 0.0;
    for (int i = 0; i < treatmentCount; i++){
        totalCost += Treatments[i]->getCost();
    }
    return totalCost;
}

Bill Patient::GenerateBill(double DailyRate, int days){
    double WardStayFee = DailyRate * days;
    double treatmentTotal = TotalTreatmentCost();
    return Bill(treatmentTotal, WardStayFee);
}

void Patient::Display() const {
    cout << "Patient Name: " << name << endl;
    cout << "DOB: " << getDOB() << endl;
    cout << "ID: " << ID << endl;
    cout << "Phone: " << Phone << endl;
    cout << "Diagnosis: " << Diagnosis << endl;
    cout << "Admission Date: " << getDOB() << endl;
    cout << "Ward: " << Ward << endl;
    cout << "Critical Condition: " << (Critical ? "Yes" : "No") << endl;
    cout << "Underwent Operation: " << (Operation ? "Yes" : "No") << endl;
    cout << "Treatments:" << endl;
    for (int i = 0; i < treatmentCount; i++){
        cout << "- " << Treatments[i]->getName() << ": $" << Treatments[i]->getCost() 
             << ", Performed by: " << Treatments[i]->getPerformedBy() << endl;
    }
}

bool Patient::isCritical() const {
    return Critical;
}

bool Patient::HasOpertaion() const {
    return Operation;
}

string Patient::getWardName() {
    return Ward;
}

void Patient::SetWardName() {
    cout << "Enter new ward name: ";
    cin >> Ward;
}

string Patient::getDiagnosis() const {
    return Diagnosis;
}



