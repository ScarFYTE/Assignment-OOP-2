#pragma once

#include "Person.h"
#include <vector>
#include "Treatment.h"
#include "Bill.h"
using namespace std;



class Patient : public Person{
    string Diagnosis;
    Date AdmissionDate;
    string Ward;
    Treatment** Treatments;
    int treatmentCount;
    int treatmentCapacity;
    bool Critical;
    bool Operation;

public:

    Patient(string name, Date dob, int id, long long int phone, string diagnosis, Date admissionDate, bool critical = false, bool Operation = false);
    
    //Deep Copy
    Patient(const Patient &P);

    Patient(Patient &&move) noexcept;

    Patient& operator=(const Patient& p);

    Patient& operator=(Patient &&p) noexcept;

    ~Patient();

    void    addTreatment        (Treatment &T);
    int     TreatmentCount      ();
    double  TotalTreatmentCost  ();
    Bill    GenerateBill        (double DailyRate ,int days);
    void    Display             ()const override;
    bool    isCritical          ()const;
    bool    HasOpertaion        ()const;
    string  getWardName         ();
    void    SetWardName         ();
    string  getDiagnosis        ()const;
};