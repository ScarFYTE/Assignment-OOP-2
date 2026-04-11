#include "Patient.h"

class Ward {
protected:
    string name;
    vector<Patient> Patients;
    int patientCount;
    double dailyRate;
public:
    Ward(string name, int capacity, double dailyRate);
    Ward(const Ward&) = delete;   // no copying wards
    virtual ~Ward();

    virtual bool admit(const Patient& p) = 0;
    void removePatient(int patientID);

    int getPatientCount() const;
    int getCapacity() const;
    string getName() const;
    double getDailyRate() const;
    double occupancyPercent() const;

    bool operator<(const Ward& other) const;    
    bool operator>(const Ward& other) const;
    bool operator==(const Ward& other) const;
};

class GeneralWard : public Ward {
public:
    GeneralWard(string name, int capacity, double dailyRate = 2000.0);
    bool admit(const Patient& p) override;   // accepts anyone
    void display() const;
};

class ICU : public Ward {
public:
    ICU(string name, int capacity, double dailyRate = 8000.0);
    bool admit(const Patient& p) override;   // only critical patients — TC-04
    void display() const;
};

class SurgicalWard : public Ward {
public:
    SurgicalWard(string name, int capacity, double dailyRate = 5000.0);
    bool admit(const Patient& p) override;   // only patients with operation
    void display() const;
};

class SurgicalWard : public Ward {
public:
    SurgicalWard(string name, int capacity, double dailyRate = 5000.0);
    bool admit(const Patient& p) override;   // only patients with operation
    void display() const;
};