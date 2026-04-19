Software Design Document: Hospital Management System
1. Introduction
The Hospital Management System is a terminal-based C++ application designed to manage hospital operations, including patient admissions, staff assignments, ward capacity, medical treatments, and billing. The system is built using strict Object-Oriented Programming (OOP) principles, featuring deep inheritance hierarchies, polymorphic dispatch, and fully manual dynamic memory management.

2. System Architecture & OOP Principles
The system architecture relies on abstraction and aggregation to model real-world hospital entities.

Encapsulation: All class attributes are protected/private, accessed strictly via getter and setter methods to ensure data integrity.

Inheritance: Deep class hierarchies are used to model specialized entities (e.g., Person -> Employee -> Surgeon).

Polymorphism: Abstract base classes (Ward, Employee) define pure virtual and virtual functions. Method resolution (such as Ward::admit() and Employee::Display()) occurs dynamically at runtime.

Aggregation: Objects reference other objects via raw pointers (e.g., Treatment holds an Employee* to represent the administering staff member without owning the staff object's memory).

3. Class Hierarchy & Relationships
3.1. The Person Hierarchy
Person (Abstract Base): Defines common human attributes (name, ID, DOB, contactInfo).

Patient: Adds medical specifics (diagnosis, wardName, AdmissionDate). Manages a dynamic array of Treatment* objects.

Employee (Abstract Base): Adds professional attributes (salary, department).

GP: General Practitioner, includes consultation fees.

Nurse: Includes nursing grade/shift details.

Surgeon: Includes specialty and surgical fee multipliers.

3.2. The Ward Hierarchy
Ward (Abstract Base): Manages a dynamic array of Patient* pointers. Tracks capacity and dailyRate. Contains pure virtual function virtual bool admit(const Patient& p) = 0;.

GeneralWard: Standard admission rules.

ICU: Overrides admit() to strictly accept patients flagged as "Critical."

SurgicalWard: Overrides admit() to strictly accept patients flagged for surgery.

3.3. Management & Utility Classes
Hospital (The System Hub): The top-level manager. Maintains dynamically resizing arrays for live patients, archived (discharged) patients, active staff, wards, and finalized bills.

AppointmentBook: Manages scheduling. Ensures data integrity by rejecting double-booked appointments based on StaffID, Date, and TimeSlot.

Treatment: Represents a specific medical action. Holds a cost, date, and an Employee* pointer to track the specific staff member who performed it.

Bill: Calculates total costs combining the Ward's dailyRate (times days admitted) and the aggregate cost of all Treatment objects assigned to the patient.

4. Memory Management Strategy
The system strictly prohibits standard library containers (like std::vector) in favor of raw pointer manipulation to demonstrate manual memory proficiency.

Rule of Five (Patient Class): The Patient class implements a custom Destructor, Copy Constructor, Copy Assignment Operator, Move Constructor, and Move Assignment Operator to safely handle deep copying of dynamic Treatment arrays and transfer ownership during hospital discharge.

Dynamic Array Resizing: Arrays (like livePatients in Hospital) track both count and capacity. Upon reaching capacity, a new array double the size is allocated, existing pointers are migrated, and the old array is deleted.

Array Compaction:

O(1) Swap-and-Pop: Used in Hospital::discharge. The last element in the array is swapped into the gap left by the deleted element, ensuring no nullptr fragmentation.

O(N) Left-Shift: Used in Ward and AppointmentBook to maintain chronological/sorted order when an element is removed.

Deep Deletion: Destructors explicitly iterate through object arrays to call delete on individual pointers before calling delete[] on the array container, preventing heap leaks.

5. Advanced C++ Features Implemented
Lambda Expressions (Function Pointers): The Hospital class utilizes higher-order functions (e.g., filterPatients, sortPatients) that accept boolean predicates. This allows dynamic, custom querying of hospital records without writing redundant loop structures.

Operator Overloading: Custom operators (<, >, ==) are implemented in classes like Ward to compare objects directly based on complex derived metrics (e.g., comparing Wards by occupancyPercent()).

Move Semantics: std::move() is utilized during patient discharge to transfer heap data efficiently from the livePatients roster to the archivedPatients roster without expensive deep copying.

Forward Declarations: Used extensively to resolve circular dependencies (e.g., between Treatment, Patient, and HospitalStaff), ensuring clean and isolated compilation units.
