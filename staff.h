#ifndef STAFF_H
#define STAFF_H

#include <iostream>
#include <string>
using namespace std;

class Staff {
public:
    string name;
    string role;
    string schedule;
    bool isAvailable;

    Staff(string name, string role, string schedule, bool isAvailable);
    void updateSchedule(const string& newSchedule);
    void toggleAvailability();
    void display();
};

// Function Declarations
void manageDoctorSchedule();
void managePathologistSchedule();
void manageNurseSchedule();
void manageMedicalRecords();
void manageLeaveRequests();
void manageEmergencyContacts();
void managePatientCareNotes();
void viewDoctorAppointments(); // New function
void staffMenu();

#endif
