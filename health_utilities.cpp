// health_utils.cpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

void viewAppointments() {
    ifstream file("appointments.txt");
    string line;
    cout << "\n--- Appointments ---\n";
    cout << left << setw(15) << "Username" << setw(25) << "Doctor" << setw(20) << "Date" << setw(15) << "Time" << endl;
    cout << string(75, '-') << endl;
    while (getline(file, line)) {
        stringstream ss(line);
        string username, doctor, date, time;
        getline(ss, username, ',');
        getline(ss, doctor, ',');
        getline(ss, date, ',');
        getline(ss, time, ',');
        cout << left << setw(15) << username << setw(25) << doctor << setw(20) << date << setw(15) << time << endl;
    }
    file.close();
}

void updateAppointments(const string& username, const string& doctor, const string& date, const string& time) {
    ofstream file("appointments.txt", ios::app);
    if (file.is_open()) {
        file << username << "," << doctor << "," << date << "," << time << endl;
        file.close();
        cout << "Appointment updated successfully.\n";
    } else {
        cout << "Error opening appointment file.\n";
    }
}
