#include "Patient.h"
#include <chrono>
#include "Ward.h"
#include "GeneralWard.h"
#include "ICU.h"
#include "SurgicalWard.h"
#include <iostream>
#include <vector>
#include "Treatment.h"
#include "Bill.h" 
#include "Person.h"

using namespace std;   

int main(){
    // Create some patients
    Patient p1("John Doe", Date(1, 1, 1980), 12345, 5551234567, "Flu", Date(1, 10, 2024), false, false);
    Patient p2("Jane Smith", Date(5, 5, 1975), 67890, 5559876543, "Pneumonia", Date(2, 10, 2024), true, false);
    Patient p3("Alice Johnson", Date(10, 10, 1990), 54321, 5551112222, "Appendicitis", Date(3, 10, 2024), false, true);

    // Create some treatments
    Treatment t1("Flu Medication", 100.0, "Dr. Brown");
    Treatment t2("Antibiotics", 200.0, "Dr. Green");
    Treatment t3("Surgery", 5000.0, "Dr. White");

    // Add treatments to patients
    p1.addTreatment(t1);
    p2.addTreatment(t2);
    p3.addTreatment(t3);

    // Create wards
    GeneralWard gw("General Ward A", 10, 300.0);
    ICU icu("ICU B", 5, 1000.0);
    SurgicalWard sw("Surgical Ward C", 8, 500.0);

    // Admit patients to wards
    gw.admit(p1); // Should succeed
    icu.admit(p2); // Should succeed (critical)
    sw.admit(p3); // Should succeed (operation)

    // Display ward information
    gw.display();
    icu.display();
    sw.display();

    return 0;
}



