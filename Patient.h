#include "Person.h"
#include <vector>
#include "Treatment.h"
#include "Bill.h"
using namespace std;



class Patient : public Person{
    string Diagnosis;
    Date AdmissionDate;
    string Ward;
    vector<Treatment> Treatments;
    bool Critical;
    bool Operation;

public:

    Patient(string name, Date dob, int id, string phone, string diagnosis, string admissionDate, bool critical = false, bool Operation = false);
    
    //Deep Copy
    Patient(const Patient &P);

    Patient(Patient &&move) noexcept;

    Patient& operator=(const Patient& p);

    Patient &operator=(Patient &&p) noexcept;

    ~Patient(){}

    void    addTreatment        (Treatment &T);
    int     TreatmentCount      ();
    double  TotalTreatmentCost  ();
    Bill    GenerateBill        (double DailyRate ,int days);
    void    Display             ()const override;
    bool    isCritical          ();
    bool    HasOpertaion        ();
    string  getWardName         ();
    void    SetWardName         ();
};