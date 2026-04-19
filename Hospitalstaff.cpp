#include "HospitalStaff.h"
#include "Patient.h"
#include "Treatment.h"  



Employee::Employee(string name, Date dob, int id, long long int phone, double salary, string department) : Person(name, dob, id, phone),salary(salary),department(department){}

string Employee::getDepartment()const{
    return department;
}

double Employee::getSalary()const{
    return salary;
}

GP::GP(string name, Date dob, int id, long long int phone, double salary, string department, double consultationFee) : Employee(name, dob, id, phone, salary, department), consultationFee(consultationFee){}

double GP::calculateBillingRate()const {
    return consultationFee;
}

void GP::Display()const {
    cout << "GP Name: " << name << endl;
    cout << "DOB: " << getDOB() << endl;
    cout << "ID: " << ID << endl;
    cout << "Phone: " << Phone << endl;
    cout << "Salary: $" << salary << endl;
    cout << "Department: " << department << endl;
    cout << "Consultation Fee: $" << consultationFee << endl;

}

void GP::consultPatient(Patient& p)const {
    cout << name << " is consulting patient " << p.getName() << endl;
    cout << "Diagnosis: " << p.getDiagnosis() << endl;
    cout << "Billing Rate: $" << calculateBillingRate() << endl;
    Treatment consultation("Consultation", calculateBillingRate(), const_cast<GP*>(this)); // Create a treatment for the consultation
    p.addTreatment(consultation); // Add the consultation treatment to the patient's record
}

void GP::writePrescription(Patient& p, string prescription)const {
    cout << name << " is writing a prescription for patient " << p.getName() << endl;
    cout << "Prescription: " << prescription << endl;
}   

Surgeon::Surgeon(string name, Date dob, int id, long long int phone, double salary, string department, string specialisation, double operationFee) : Employee(name, dob, id, phone, salary, department), specialisation(specialisation), operationFee(operationFee){}

double Surgeon::calculateBillingRate()const {
    return operationFee;
}

void Surgeon::Display()const {
    cout << "Surgeon Name: " << name << endl;
    cout << "DOB: " << getDOB() << endl;
    cout << "ID: " << ID << endl;
    cout << "Phone: " << Phone << endl;
    cout << "Salary: $" << salary << endl;
    cout << "Department: " << department << endl;
    cout << "Specialisation: " << specialisation << endl;
    cout << "Operation Fee: $" << operationFee << endl;

}

void Surgeon::performOperation(Patient& p)const {
    cout << name << " is performing an operation on patient " << p.getName() << endl;
    cout << "Diagnosis: " << p.getDiagnosis() << endl;
    cout << "Billing Rate: $" << calculateBillingRate() << endl;

    Treatment operation("Operation", calculateBillingRate(), const_cast<Surgeon*>(this)); // Create a treatment for the operation
    p.addTreatment(operation); // Add the operation treatment to the patient's record
}

string Surgeon::getSpecialisation()const {
    return specialisation;
}

Nurse::Nurse(string name, Date dob, int id, long long int phone, double salary, string department, string assignedWard, double hourlyCareFee) : Employee(name, dob, id, phone, salary, department), assignedWard(assignedWard), hourlyCareFee(hourlyCareFee){}

double Nurse::calculateBillingRate()const {
    return hourlyCareFee;
}

void Nurse::Display()const {
    cout << "Nurse Name: " << name << endl;
    cout << "DOB: " << getDOB() << endl;
    cout << "ID: " << ID << endl;
    cout << "Phone: " << Phone << endl;
    cout << "Salary: $" << salary << endl;
    cout << "Department: " << department << endl;
    cout << "Assigned Ward: " << assignedWard << endl;
    cout << "Hourly Care Fee: $" << hourlyCareFee << endl;

}

void Nurse::administerTreatment(Patient& p, Treatment& t)const {
    cout << name << " is administering treatment to patient " << p.getName() << endl;
    cout << "Treatment: " << t.getName() << endl;
    cout << "Billing Rate: $" << calculateBillingRate() << endl;
    t.SetPerformedBy(const_cast<Nurse*>(this)); // Set the performing nurse for the treatment
    p.addTreatment(t);
    
}

string Nurse::getAssignedWard()const {
    return assignedWard;
}

Employee::~Employee() {
    // No dynamic memory to clean up in Employee
}