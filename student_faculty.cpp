#include <iostream>
#include <fstream>
#include "student_faculty.h"
#include <vector>
#include <sstream>
#include <iomanip>
#include <limits>  // Include this header for numeric_limits
#include "appointment_data.h"
using namespace std;

// Function to book an appointment with a selected doctor
void bookAppointment(const string& username) {
    string date, time, doctor, specialty;
    
    cout << "\n--- Book Appointment ---\n";
    cout << "Select Specialty:\n";
    cout << "1. General Medicine\n";
    cout << "2. Gynecologist\n";
    cout << "3. Dermatologist\n";
    cout << "4. Lab Pathologist\n";
    cout << "Enter choice (1-4): ";
    int choice;
    cin >> choice;
    cin.ignore();  // To clear the newline character left by `cin`
    
    switch (choice) {
        case 1: specialty = "General Medicine"; doctor = "Dr. A"; break;
        case 2: specialty = "Gynecologist"; doctor = "Dr. B"; break;
        case 3: specialty = "Dermatologist"; doctor = "Dr. C"; break;
        case 4: specialty = "Lab Pathologist"; doctor = "Dr. D"; break;
        default: 
            cout << "Invalid choice. Please try again.\n";
            return;
    }
    
    // Get date input and validate
    cout << "Enter Date (DD-MM-YYYY): ";
    getline(cin, date);
    if (date.empty()) {
        cout << "Invalid input. Date cannot be empty.\n";
        return;
    }
    
    // Get time input and validate
    cout << "Enter Time (e.g. 10:30 AM): ";
    getline(cin, time);
    if (time.empty()) {
        cout << "Invalid input. Time cannot be empty.\n";
        return;
    }

    // Write appointment details to a file
    ofstream out("appointments.txt", ios::app);
    if (!out) {
        cout << "Error opening file to save appointment.\n";
        return;
    }

    out << username << "," << date << "," << time << "," << doctor << "," << specialty << "\n";
    out.close();
    cout << "Appointment booked with " << doctor << " in " << specialty << "!\n";
}


void viewAppointments(const string& username) {
    cout << "\n--- View Appointments Booked ---\n";
    ifstream file("appointments.txt");
    if (!file) {
        cout << "Error opening appointments file.\n";
        return;
    }

    string line;
    cout << left << setw(15) << "Username"
         << setw(20) << "Date"
         << setw(15) << "Time"
         << setw(25) << "Doctor" << endl;
    cout << string(75, '-') << endl;

    while (getline(file, line)) {
        stringstream ss(line);
        string id, patientId, doctorId, date, time;
        getline(ss, id, ',');
        getline(ss, patientId, ',');
        getline(ss, doctorId, ',');
        getline(ss, date, ',');
        getline(ss, time, ',');

        cout << left << setw(15) << patientId
             << setw(20) << date
             << setw(15) << time
             << setw(25) << doctorId << endl;
    }

    file.close();
}

void viewMedicalReports(const string& username) {
    cout << "\n--- View Medical Reports ---\n";
    ifstream file("medical_reports.txt");
    if (!file) {
        cout << "Error opening medical reports file.\n";
        return;
    }

    string line;
    cout << left << setw(15) << "Patient ID"
         << setw(50) << "Medical Report" << endl;
    cout << string(65, '-') << endl;

    while (getline(file, line)) {
        stringstream ss(line);
        string patientId, report;
        getline(ss, patientId, ',');
        getline(ss, report, ',');

        if (patientId == username) {
            cout << left << setw(15) << patientId
                 << setw(50) << report << endl;
        }
    }

    file.close();
}

// Function to show emergency contacts
void showEmergencyContacts() {
    cout << "\n--- Emergency Contacts ---\n";
    cout << left << setw(20) << "Contact" << setw(15) << "Phone Number" << "\n";
    cout << string(40, '-') << "\n";
    cout << left << setw(20) << "Dr. A" << "1234567890" << "\n";
    cout << left << setw(20) << "Ambulance" << "108" << "\n";
}

// Function to manage notes (add, view, delete)
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
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');  // Corrected

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
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');  // Corrected

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
void viewUpcomingAppointments(const string& username) {
    cout << "\n--- Upcoming Appointments ---\n";
    ifstream in("appointments.txt");
    string line;
    bool found = false;

    cout << left << setw(5) << "No." << setw(15) << "Date" << setw(15) << "Time" << setw(15) << "Doctor" << setw(20) << "Rescheduled" << endl;
    cout << string(70, '-') << endl;

    while (getline(in, line)) {
        stringstream ss(line);
        string user, date, time, doctor, specialty;
        getline(ss, user, ',');
        getline(ss, date, ',');
        getline(ss, time, ',');
        getline(ss, doctor, ',');
        getline(ss, specialty);

        if (user == username) {
            // Here you can add logic to check if the date is in the future
            cout << left << setw(5) << "1" << setw(15) << date << setw(15) << time << setw(15) << doctor << setw(20) << specialty << endl;
            found = true;
        }
    }
    if (!found) cout << "No upcoming appointments.\n";
    in.close();
}

void viewPastAppointments(const string& username) {
    cout << "\n--- Past Appointments ---\n";
    ifstream in("appointments.txt");
    string line;
    bool found = false;

    cout << left << setw(5) << "No." << setw(15) << "Date" << setw(15) << "Time" << setw(15) << "Doctor" << setw(20) << "Specialty" << endl;
    cout << string(70, '-') << endl;

    while (getline(in, line)) {
        stringstream ss(line);
        string user, date, time, doctor, specialty;
        getline(ss, user, ',');
        getline(ss, date, ',');
        getline(ss, time, ',');
        getline(ss, doctor, ',');
        getline(ss, specialty);

        if (user == username) {
            // Here you can add logic to check if the date is in the past
            cout << left << setw(5) << "1" << setw(15) << date << setw(15) << time << setw(15) << doctor << setw(20) << specialty << endl;
            found = true;
        }
    }
    if (!found) cout << "No past appointments.\n";
    in.close();
}

// Function to manage appointments
void appointmentMenu(const string& username) {
    while (true) {
        cout << "\n========= Appointments Menu =========\n";
        cout << left << setw(3) << "1." << "Book Appointment" << "\n";
        cout << left << setw(3) << "2." << "View Upcoming Appointments" << "\n";
        cout << left << setw(3) << "3." << "View Past Appointments" << "\n";
        cout << left << setw(3) << "4." << "Back to Health Centre Menu" << "\n";
        cout << "=====================================\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');  // Corrected

        switch (choice) {
            case 1: bookAppointment(username); break;
            //case 2: viewAppointments(username); break;
            case 2: viewUpcomingAppointments(username); break;
            case 3: viewPastAppointments(username); break;
            case 4: return;
            default: cout << "Invalid choice!\n";
        }
    }
}
/*void studentFacultyMenu(const string& username) {
    while (true) {
        cout << "\n======= Health Centre Menu =======\n";
        cout << "1. Appointment Section\n";
        cout << "2. Medical Records\n";
        cout << "3. Emergency Contacts\n";
        cout << "4. Notes\n";
        cout << "5. Back to Main Menu\n";
        cout << "==================================\n";
        cout << "Enter choice: ";
        
        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                appointmentMenu(username); // Has "Back to Health Centre Menu" internally
                break;
            case 2:
                viewMedicalReports(username);
                break;
            case 3:
                showEmergencyContacts();
                break;
            case 4:
                noteMenu(username); // Also includes "Back"
                break;
            case 5:
                cout << "Logging out...\n";
                return; // Goes back to main/login screen
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }  
}*/
void studentFacultyMenu(const string& username) {
    while (true) {
        cout << "\n======= Health Centre Menu =======\n";
        cout << "1. Appointment Section\n";
        cout << "2. Medical Records\n";
        cout << "3. Emergency Contacts\n";
        cout << "4. Notes\n";
        cout << "5. Back to Main Menu\n";
        cout << "==================================\n";
        cout << "Enter choice: ";
        
        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                appointmentMenu(username); // Has "Back to Health Centre Menu" internally
                break;
            case 2:
                viewMedicalReports(username);
                break;
            case 3:
                showEmergencyContacts();
                break;
            case 4:
                noteMenu(username); // Also includes "Back"
                break;
            case 5:
                cout << "Logging out...\n";
                return; // Goes back to main/login screen
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }  
}

   


