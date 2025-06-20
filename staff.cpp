#include "staff.h"
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <limits>
#include <algorithm>
#include "appointment_data.h"


// Staff class function definitions
Staff::Staff(string name, string role, string schedule, bool isAvailable)
    : name(name), role(role), schedule(schedule), isAvailable(isAvailable) {}

void Staff::updateSchedule(const string& newSchedule) {
    schedule = newSchedule;
}

void Staff::toggleAvailability() {
    isAvailable = !isAvailable;
}

void Staff::display() {
    cout << left << setw(20) << name << setw(15) << role
         << setw(20) << schedule << setw(15)
         << (isAvailable ? "Available" : "Not Available") << endl;
}

// ================== Management Functions ===================
// Function prototypes
void editAppointment();
void writeMedicalReport();
void DoctorSchedule() {
    cout << "\n--- Doctor Section ---\n";
    vector<Staff> doctors = {
        Staff("Dr. A", "General Medicine", "Mon/Wed/Fri 10am - 1pm", true),
        Staff("Dr. B", "Gynecologist", "Tue/Thu 2pm - 5pm", true),
        Staff("Dr. C", "Dermatologist", "Mon/Fri 11am - 3pm", true),
        Staff("Dr. D", "Lab Pathologist", "Wed/Sat 9am - 12pm", false)
    };

    int choice;
    while (true) {
        cout << "\n1. View Doctor Schedule\n";
        cout << "2. Update Doctor Schedule\n";
        cout << "3. Toggle Doctor Availability\n";
        cout << "4. View Appointments Booked\n";
        cout << "5. Edit Appointment\n";
        cout << "6. Write Medical Reports\n";
        cout << "7. Back\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            cout << "\n--- Doctor Schedules ---\n";
            cout << left << setw(20) << "Doctor" << setw(15) << "Role"
                 << setw(20) << "Schedule" << setw(15) << "Availability" << endl;
            cout << string(70, '-') << endl;
            for (auto& doc : doctors) doc.display();

        } else if (choice == 2) {
            string doctorName, newSchedule;
            cout << "Enter doctor's name to update schedule: ";
            getline(cin, doctorName);
            if (doctorName.empty()) {
                cout << "Invalid input. Doctor name cannot be empty.\n";
                continue;
            }
            cout << "Enter new schedule: ";
            getline(cin, newSchedule);
            if (newSchedule.empty()) {
                cout << "Invalid input. Schedule cannot be empty.\n";
                continue;
            }

            bool found = false;
            for (auto& doc : doctors) {
                if (doc.name == doctorName) {
                    doc.updateSchedule(newSchedule);
                    cout << "Schedule updated for " << doctorName << ".\n";
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Doctor not found.\n";

        } else if (choice == 3) {
            string doctorName;
            cout << "Enter doctor's name to toggle availability: ";
            getline(cin, doctorName);
            if (doctorName.empty()) {
                cout << "Invalid input. Doctor name cannot be empty.\n";
                continue;
            }
            bool found = false;
            for (auto& doc : doctors) {
                if (doc.name == doctorName) {
                    doc.toggleAvailability();
                    cout << "Availability toggled for " << doctorName << ".\n";
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Doctor not found.\n";

        } else if (choice == 4) {
            viewDoctorAppointments();

        } else if (choice == 5) {
            editAppointment();

        } else if (choice == 6) {
            writeMedicalReport();

        } else if (choice == 7) {
            break;

        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }
}

void editAppointment() {
    string appointmentId;
    cout << "Enter appointment ID to edit: ";
    getline(cin, appointmentId);

    if (appointmentId.empty()) {
        cout << "Invalid input. Appointment ID cannot be empty.\n";
        return;
    }

    ifstream file("appointments.txt");
    if (!file) {
        cout << "Error opening appointments file.\n";
        return;
    }

    vector<string> updatedAppointments;
    string line;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string id, patientId, doctorId, date, time;
        getline(ss, id, ',');
        getline(ss, patientId, ',');
        getline(ss, doctorId, ',');
        getline(ss, date, ',');
        getline(ss, time, ',');

        if (id == appointmentId) {
            cout << "Enter new date: ";
            getline(cin, date);
            if (date.empty()) {
                cout << "Invalid input. Date cannot be empty.\n";
                return;
            }

            cout << "Enter new time: ";
            getline(cin, time);
            if (time.empty()) {
                cout << "Invalid input. Time cannot be empty.\n";
                return;
            }

            updatedAppointments.push_back(id + "," + patientId + "," + doctorId + "," + date + "," + time);
            found = true;
        } else {
            updatedAppointments.push_back(line);
        }
    }
    file.close();

    if (!found) {
        cout << "Appointment not found.\n";
        return;
    }

    ofstream outFile("appointments.txt", ios::trunc);
    for (const string& appt : updatedAppointments) {
        outFile << appt << endl;
    }
    outFile.close();

    cout << "Appointment edited successfully.\n";
}

void writeMedicalReport() {
    string patientId;
    cout << "Enter patient ID to write medical report: ";
    getline(cin, patientId);

    if (patientId.empty()) {
        cout << "Invalid input. Patient ID cannot be empty.\n";
        return;
    }

    string report;
    cout << "Enter medical report: ";
    getline(cin, report);

    if (report.empty()) {
        cout << "Invalid input. Medical report cannot be empty.\n";
        return;
    }

    ofstream outFile("medical_reports.txt", ios::app);
    if (!outFile) {
        cout << "Error: Unable to open file for writing.\n";
        return;
    }

    outFile << patientId << "," << report << endl;
    outFile.close();

    cout << "Medical report written successfully.\n";
}


// Function to manage pathologist schedules
void PathologistSchedule() {
    cout << "\n---  Pathologist Schedules ---\n";
    vector<Staff> pathologists = {
        Staff("Dr. X", "Pathologist", "Mon/Wed/Fri 8am - 12pm", true),
        Staff("Dr. Y", "Pathologist", "Tue/Thu 1pm - 5pm", false)
    };

    int choice;
    while (true) {
        cout << "\n1. View Pathologist Schedules\n";
        cout << "2. Update Pathologist Schedule\n";
        cout << "3. Toggle Pathologist Availability\n";
        cout << "4. Back\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            cout << "\n--- Pathologist Schedules ---\n";
            cout << left << setw(20) << "Pathologist" << setw(15) << "Role" << setw(20) << "Schedule" << setw(15) << "Availability" << endl;
            cout << string(70, '-') << endl;
            for (auto& path : pathologists) {
                path.display();
            }
        } else if (choice == 2) {
            string pathologistName, newSchedule;
            cout << "Enter pathologist's name to update schedule: ";
            getline(cin, pathologistName);
            cout << "Enter new schedule: ";
            getline(cin, newSchedule);

            bool found = false;
            for (auto& path : pathologists) {
                if (path.name == pathologistName) {
                    path.updateSchedule(newSchedule);
                    cout << "Schedule updated for " << pathologistName << ".\n";
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Pathologist not found.\n";
            }
        } else if (choice == 3) {
            string pathologistName;
            cout << "Enter pathologist's name to toggle availability: ";
            getline(cin, pathologistName);

            bool found = false;
            for (auto& path : pathologists) {
                if (path.name == pathologistName) {
                    path.toggleAvailability();
                    cout << "Availability toggled for " << pathologistName << ".\n";
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Pathologist not found.\n";
            }
        } else if (choice == 4) {
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }
}

// Function to manage nurse schedules
void NurseSchedule() {
    cout << "\n---  Nurse Schedules ---\n";
    vector<Staff> nurses = {
        Staff("Nurse A", "Nurse", "Mon-Sun 8am - 5pm", true),
        Staff("Nurse B", "Nurse", "Mon-Fri 9am - 6pm", false)
    };

    int choice;
    while (true) {
        cout << "\n1. View Nurse Schedules\n";
        cout << "2. Update Nurse Schedule\n";
        cout << "3. Toggle Nurse Availability\n";
        cout << "4. Back\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            cout << "\n--- Nurse Schedules ---\n";
            cout << left << setw(20) << "Nurse" << setw(15) << "Role" << setw(20) << "Schedule" << setw(15) << "Availability" << endl;
            cout << string(70, '-') << endl;
            for (auto& nurse : nurses) {
                nurse.display();
            }
        } else if (choice == 2) {
            string nurseName, newSchedule;
            cout << "Enter nurse's name to update schedule: ";
            getline(cin, nurseName);
            cout << "Enter new schedule: ";
            getline(cin, newSchedule);

            bool found = false;
            for (auto& nurse : nurses) {
                if (nurse.name == nurseName) {
                    nurse.updateSchedule(newSchedule);
                    cout << "Schedule updated for " << nurseName << ".\n";
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Nurse not found.\n";
            }
        } else if (choice == 3) {
            string nurseName;
            cout << "Enter nurse's name to toggle availability: ";
            getline(cin, nurseName);

            bool found = false;
            for (auto& nurse : nurses) {
                if (nurse.name == nurseName) {
                    nurse.toggleAvailability();
                    cout << "Availability toggled for " << nurseName << ".\n";
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Nurse not found.\n";
            }
        } else if (choice == 4) {
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }
}
/*void manageMedicalRecords() {
    int choice;
    string username, record;
    
    cout << "\n--- Manage Medical Records ---\n";
    cout << "1. Add Record\n2. View All Records\nEnter choice: ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        cout << "Enter patient username: ";
        getline(cin, username);
        cout << "Enter medical record (short description): ";
        getline(cin, record);

        ofstream out("medical_records.txt", ios::app);
        out << username << "," << record << endl;
        out.close();

        cout << "Record added.\n";
    } else if (choice == 2) {
        ifstream in("medical_records.txt");
        if (!in) {
            cout << "No records found.\n";
            return;
        }
        string line;
        cout << "\nUsername\t\tRecord\n";
        cout << "------------------------------------------\n";
        while (getline(in, line)) {
            stringstream ss(line);
            string user, rec;
            getline(ss, user, ',');
            getline(ss, rec, ',');
            cout << user << "\t\t" << rec << endl;
        }
        in.close();
    } else {
        cout << "Invalid choice.\n";
    }
}*/
void manageLeaveRequests() {
    int choice;
    cout << "\n--- Manage Leave Requests ---\n";
    cout << "1. Apply for Leave\n";
    cout << "2. View Leave Requests\n";
    cout << "3. Approve/Reject Request\n";
    cout << "4. Back\n";
    cout << "Enter choice: ";
    cin >> choice;

    // Handle invalid or failed input
    if (cin.fail()) {
        cin.clear(); // Clear error state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
        cout << "Invalid input.\n";
        return;
    }
    cin.ignore(); // Ignore newline

    if (choice == 1) {
        string name, role, reason, date;
        cout << "Enter your name: ";
        getline(cin, name);
        if (name.empty()) {
            cout << "Invalid input. Name cannot be empty.\n";
            return;
        }

        cout << "Enter your role (Doctor/Pathologist/Nurse): ";
        getline(cin, role);
        if (role.empty()) {
            cout << "Invalid input. Role cannot be empty.\n";
            return;
        }

        cout << "Enter reason for leave: ";
        getline(cin, reason);
        if (reason.empty()) {
            cout << "Invalid input. Reason cannot be empty.\n";
            return;
        }

        cout << "Enter leave date (DD-MM-YYYY): ";
        getline(cin, date);
        if (date.empty()) {
            cout << "Invalid input. Date cannot be empty.\n";
            return;
        }

        ofstream out("leave_requests.txt", ios::app);
        out << name << "," << role << "," << reason << "," << date << endl;
        out.close();

        cout << "Leave request submitted.\n";
    } 
    else if (choice == 2) {
        ifstream file("leave_requests.txt");
        if (!file) {
            cout << "No leave requests found.\n";
            return;
        }

        string line;
        cout << "\nName\t\tRole\t\tReason\t\tDate\n";
        cout << "------------------------------------------------------------\n";
        while (getline(file, line)) {
            stringstream ss(line);
            string name, role, reason, date;
            getline(ss, name, ',');
            getline(ss, role, ',');
            getline(ss, reason, ',');
            getline(ss, date, ',');

            cout << left << setw(15) << name
                 << setw(15) << role
                 << setw(20) << reason
                 << setw(15) << date << endl;
        }
        file.close();
    } 
    else if (choice == 3) {
        string userToProcess, decision;
        cout << "Enter name of staff to approve/reject: ";
        getline(cin, userToProcess);
        if (userToProcess.empty()) {
            cout << "Invalid input. Name cannot be empty.\n";
            return;
        }

        cout << "Enter decision (Approve/Reject): ";
        getline(cin, decision);
        if (decision.empty()) {
            cout << "Invalid input. Decision cannot be empty.\n";
            return;
        }

        ofstream log("leave_decisions.txt", ios::app);
        log << userToProcess << "," << decision << endl;
        log.close();

        cout << "Decision recorded for " << userToProcess << ".\n";
    } 
    else {
        cout << "Invalid option.\n";
    }
}

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <algorithm>

using namespace std;

void manageEmergencyContacts() {
    int choice;
    cout << "\n--- Manage Emergency Contacts ---\n";
    cout << "1. Add Contact\n2. View Contacts\n3. Remove Contact\n4. Back\nEnter choice: ";
    cin >> choice;

    if (cin.fail()) {
        cin.clear(); // clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard bad input
        cout << "Invalid input. Please enter a valid number.\n";
        return;
    }

    cin.ignore(); // clear the newline after entering choice

    if (choice == 1) {
        string name, number;
        cout << "Enter contact name: ";
        getline(cin, name);

        if (name.empty()) {
            cout << "Invalid input. Name cannot be empty.\n";
            return;
        }

        cout << "Enter 10-digit contact number: ";
        getline(cin, number);
        number.erase(remove(number.begin(), number.end(), ' '), number.end());

        if (number.length() != 10 || !all_of(number.begin(), number.end(), ::isdigit)) {
            cout << "Invalid input. Contact number must be a 10-digit number.\n";
            return;
        }

        ofstream file("emergency_contacts.txt", ios::app);
        if (!file) {
            cout << "Error: Cannot open file to save contact.\n";
            return;
        }

        file << name << "," << number << endl;
        file.close();
        cout << "Contact added successfully.\n";

    } else if (choice == 2) {
        ifstream file("emergency_contacts.txt");
        if (!file) {
            cout << "No emergency contacts found.\n";
            return;
        }

        string line;
        cout << "\nName\t\tContact Number\n";
        cout << "-------------------------------\n";
        while (getline(file, line)) {
            stringstream ss(line);
            string name, number;
            getline(ss, name, ',');
            getline(ss, number);
            cout << name << "\t\t" << number << endl;
        }
        file.close();

    } else if (choice == 3) {
        string nameToRemove;
        cout << "Enter contact name to remove: ";
        getline(cin, nameToRemove);

        if (nameToRemove.empty()) {
            cout << "Invalid input. Name cannot be empty.\n";
            return;
        }

        ifstream file("emergency_contacts.txt");
        ofstream temp("temp.txt");

        if (!file || !temp) {
            cout << "Error: Unable to access contact files.\n";
            return;
        }

        string line;
        bool found = false;

        while (getline(file, line)) {
            if (line.substr(0, line.find(',')) != nameToRemove) {
                temp << line << endl;
            } else {
                found = true;
            }
        }

        file.close();
        temp.close();
        remove("emergency_contacts.txt");
        rename("temp.txt", "emergency_contacts.txt");

        if (found)
            cout << "Contact removed successfully.\n";
        else
            cout << "Contact name not found.\n";

    } else if (choice == 4) {
        return;
    } else {
        cout << "Invalid option.\n";
    }
}


void managePatientCareNotes() {
    int choice;
    cout << "\n--- Manage Patient Care Notes ---\n";
    cout << "1. Add Note\n2. View Notes\n3.Back\nEnter choice: ";
    cin >> choice;

    if (cin.fail()) {
        cin.clear(); // clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
        cout << "Invalid input. Please enter a valid number.\n";
        return;
    }

    cin.ignore(); // clear leftover newline

    if (choice == 1) {
        string user, note;
        cout << "Enter username: ";
        getline(cin, user);
        if (user.empty()) {
            cout << "Invalid input. Username cannot be empty.\n";
            return;
        }

        cout << "Enter care note: ";
        getline(cin, note);
        if (note.empty()) {
            cout << "Invalid input. Care note cannot be empty.\n";
            return;
        }

        ofstream out("care_notes.txt", ios::app);
        if (!out) {
            cout << "Error: Unable to write to care_notes.txt\n";
            return;
        }

        out << user << "," << note << endl;
        out.close();
        cout << "Note added.\n";
    } 
    else if (choice == 2) {
        ifstream file("care_notes.txt");
        if (!file) {
            cout << "No care notes found.\n";
            return;
        }

        string line;
        cout << "\nUsername\t\tNote\n";
        cout << "----------------------------------------\n";
        while (getline(file, line)) {
            stringstream ss(line);
            string user, note;
            getline(ss, user, ',');
            getline(ss, note, ',');
            cout << user << "\t\t" << note << endl;
        }
        file.close();
    } 
    else {
        cout << "Invalid option.\n";
    }
}

void viewDoctorAppointments() {
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
        string username, date, time, doctor;
        getline(ss, username, ',');
        getline(ss, date, ',');
        getline(ss, time, ',');
        getline(ss, doctor, ',');  // doctor is last

        cout << left << setw(15) << username
             << setw(20) << date
             << setw(15) << time
             << setw(25) << doctor << endl;
    }

    file.close();
}

void staffMenu() {
    int roleChoice;
    while (true) {
        cout << "\n=== Staff Menu ===\n";
        cout << "1. Doctor Section\n";
        cout << "2. Pathologist Schedules\n";
        cout << "3. Nurse Schedules\n";
       // cout << "4. Manage Medical Records\n";
        cout << "4. Manage Leave Requests\n";
        cout << "5. Manage Emergency Contacts\n";
        cout << "6. Manage Patient Care Notes\n";
        cout << "7. Back\n";
        cout << "Enter choice: ";
        cin >> roleChoice;
        cin.ignore();

        switch (roleChoice) {
            case 1: DoctorSchedule(); break;
            case 2: PathologistSchedule(); break;
            case 3: NurseSchedule(); break;
          //  case 4: manageMedicalRecords(); break;
            case 4: manageLeaveRequests(); break;
            case 5: manageEmergencyContacts(); break;
            case 6: managePatientCareNotes(); break;
            case 7: return;
            default: cout << "Invalid choice. Try again.\n";
        }
    }
}
