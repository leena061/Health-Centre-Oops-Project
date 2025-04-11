#include "student_faculty.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <limits>
#include <iomanip>
using namespace std;

void viewDoctorSchedule() {
    cout << "\n--- Doctor Schedule ---\n";
    cout << left << setw(15) << "Doctor" << setw(20) << "Days" << setw(15) << "Time" << "\n";
    cout << string(50, '-') << "\n";
    cout << left << setw(15) << "Dr. A" << setw(20) << "Mon/Wed/Fri" << setw(15) << "10am - 1pm" << "\n";
    cout << left << setw(15) << "Dr. B" << setw(20) << "Tue/Thu/Sat" << setw(15) << "2pm - 5pm" << "\n";
}

void bookAppointment(const string& username) {
    string date, time, doctor;
    cout << "\n--- Book Appointment ---\n";
    cout << "Enter Date (DD-MM-YYYY): ";
    getline(cin, date);
    cout << "Enter Time (e.g. 10:30 AM): ";
    getline(cin, time);
    cout << "Enter Doctor Name: ";
    getline(cin, doctor);

    ofstream out("appointments.txt", ios::app);
    out << username << "," << date << "," << time << "," << doctor << "\n";
    out.close();
    cout << "Appointment booked!\n";
}

void viewAppointments(const string& username) {
    cout << "\n--- Your Appointments ---\n";
    ifstream in("appointments.txt");
    string line;
    bool found = false;
    int index = 1;

    cout << left << setw(5) << "No." << setw(15) << "Date" << setw(15) << "Time" << setw(15) << "Doctor" << endl;
    cout << string(50, '-') << endl;

    while (getline(in, line)) {
        stringstream ss(line);
        string user, date, time, doctor;
        getline(ss, user, ',');
        getline(ss, date, ',');
        getline(ss, time, ',');
        getline(ss, doctor);

        if (user == username) {
            cout << left << setw(5) << index++ << setw(15) << date << setw(15) << time << setw(15) << doctor << endl;
            found = true;
        }
    }
    if (!found) cout << "No appointments found.\n";
    in.close();
}

void checkMedicalRecords(const string& username) {
    cout << "\n--- Medical Records ---\n";
    ifstream in(username + "_records.txt");
    if (!in) {
        cout << "No records found.\n";
        return;
    }
    string line;
    while (getline(in, line)) {
        cout << line << "\n";
    }
    in.close();
}

void showEmergencyContacts() {
    cout << "\n--- Emergency Contacts ---\n";
    cout << left << setw(20) << "Contact" << setw(15) << "Phone Number" << "\n";
    cout << string(40, '-') << "\n";
    cout << left << setw(20) << "Dr. A" << "1234567890" << "\n";
    cout << left << setw(20) << "Ambulance" << "108" << "\n";
}

void noteMenu(const string& username) {
    while (true) {
        cout << "\n====== Notes Menu ======\n";
        cout << "1. Add Note\n";
        cout << "2. View Notes\n";
        cout << "3. Delete Note\n";
        cout << "4. Back\n";
        cout << "========================\n";
        cout << "Enter choice: ";
        int ch;
        cin >> ch;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (ch == 1) {
            string note;
            cout << "Enter note: ";
            getline(cin, note);
            ofstream out(username + "_notes.txt", ios::app);
            out << note << "\n";
            out.close();
            cout << "Note saved.\n";
        } else if (ch == 2) {
            ifstream in(username + "_notes.txt");
            if (!in) {
                cout << "No notes found.\n";
                continue;
            }
            string line;
            int idx = 1;
            cout << "\n--- Your Notes ---\n";
            while (getline(in, line)) {
                cout << idx++ << ". " << line << "\n";
            }
            in.close();
        } else if (ch == 3) {
            vector<string> notes;
            ifstream in(username + "_notes.txt");
            if (!in) {
                cout << "No notes found.\n";
                continue;
            }
            string line;
            while (getline(in, line)) {
                notes.push_back(line);
            }
            in.close();

            if (notes.empty()) {
                cout << "No notes to delete.\n";
                continue;
            }

            for (size_t i = 0; i < notes.size(); ++i) {
                cout << i + 1 << ". " << notes[i] << "\n";
            }
            cout << "Enter note number to delete: ";
            int num;
            cin >> num;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (num > 0 && num <= static_cast<int>(notes.size())) {
                notes.erase(notes.begin() + num - 1);
                ofstream out(username + "_notes.txt");
                for (const auto& n : notes) {
                    out << n << "\n";
                }
                out.close();
                cout << "Note deleted.\n";
            } else {
                cout << "Invalid note number.\n";
            }
        } else if (ch == 4) {
            return;
        } else {
            cout << "Invalid choice.\n";
        }
    }
}

void appointmentMenu(const string& username) {
    while (true) {
        cout << "\n====== Appointment Menu ======\n";
        cout << "1. Book Appointment\n";
        cout << "2. View Appointments\n";
        cout << "3. Cancel (Coming Soon)\n";
        cout << "4. Back\n";
        cout << "================================\n";
        cout << "Enter choice: ";
        int ch;
        cin >> ch;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (ch) {
            case 1: bookAppointment(username); break;
            case 2: viewAppointments(username); break;
            case 3: cout << "Cancel feature coming soon...\n"; break;
            case 4: return;
            default: cout << "Invalid choice.\n"; break;
        }
    }
}

void studentFacultyMenu(const string& username) {
    while (true) {
        cout << "\n========= Health Centre Menu =========\n";
        cout << left << setw(3) << "1." << "View Doctor Schedule" << "\n";
        cout << left << setw(3) << "2." << "Appointments" << "\n";
        cout << left << setw(3) << "3." << "Check Medical Records" << "\n";
        cout << left << setw(3) << "4." << "Emergency Contacts" << "\n";
        cout << left << setw(3) << "5." << "Notes" << "\n";
        cout << left << setw(3) << "6." << "Back to Main Menu" << "\n";
        cout << "=======================================\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: viewDoctorSchedule(); break;
            case 2: appointmentMenu(username); break;
            case 3: checkMedicalRecords(username); break;
            case 4: showEmergencyContacts(); break;
            case 5: noteMenu(username); break;
            case 6: return;
            default: cout << "Invalid choice!\n";
        }
    }
}
