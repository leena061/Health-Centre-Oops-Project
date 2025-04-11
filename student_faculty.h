#ifndef STUDENT_FACULTY_H
#define STUDENT_FACULTY_H

#include <string>
using namespace std;

void studentFacultyMenu(const string& username);
void viewDoctorSchedule();
void bookAppointment(const string& username);
void viewAppointments(const string& username);
void checkMedicalRecords(const string& username);
void showEmergencyContacts();
void addOrViewNotes(const string& username);

#endif
