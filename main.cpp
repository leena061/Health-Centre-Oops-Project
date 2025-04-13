#include <iostream>
#include "login_registration.h"
#include "pharmacy.h"
#include "student_faculty.h"
#include "staff.h"

using namespace std;

int getValidatedIntMain(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

int main() {
    bool loggedIn = false;
    string currentUser;
    string role;

    while (true) {
        if (!loggedIn) {
            cout << "\n=========== Health Centre Login System ===========\n";
            cout << "1. Register\n";
            cout << "2. Login\n";
            cout << "3. Forgot Password\n";
            cout << "4. Exit\n";
            cout << "==================================================\n";

            int choice = getValidatedIntMain("Enter your choice: ");

            if (choice == 1) {
                registerUser();
            } else if (choice == 2) {
                string username, password, phone;
                cout << "\n--------------- Login ---------------\n";
                cout << "Enter Username: ";
                getline(cin, username);
                cout << "Enter Password: ";
                password = maskPassword();

                if (verifyLogin(username, password, role)) {
                    cout << "Login successful! Welcome, " << username << " (" << role << ")\n";
                    currentUser = username;
                    loggedIn = true;
                } else {
                    cout << "Invalid credentials or phone number mismatch.\n";
                }
            } else if (choice == 3) {
                forgotPassword();
            } else if (choice == 4) {
                cout << "Exiting...\n";
                break;
            } else {
                cout << "Invalid choice. Try again.\n";
            }
        } else {
            cout << "\n========== Logged In Menu ==========\n";
            if (role == "Student/Faculty") {
                cout << "1. Student/Faculty Menu\n";
                cout << "2. Pharmacy\n";
                cout << "3. Logout\n";
                cout << "4. Exit Program\n";
                cout << "=====================================\n";

                int opt = getValidatedIntMain("Enter choice: ");
                if (opt == 1) {
                    studentFacultyMenu(currentUser);
                } else if (opt == 2) {
                    pharmacyMenu(currentUser, role);
                } else if (opt == 3) {
                    loggedIn = false;
                    currentUser = "";
                    role = "";
                } else if (opt == 4) {
                    cout << "Exiting...\n";
                    break;
                } else {
                    cout << "Invalid option. Try again.\n";
                }

            } else if (role == "HealthCentreStaff") {
                cout << "1. Staff Menu\n";
                cout << "2. Pharmacy\n";
                cout << "3. Logout\n";
                cout << "4. Exit Program\n";
                cout << "=====================================\n";

                int opt = getValidatedIntMain("Enter choice: ");
                if (opt == 1) {
                    staffMenu();
                } else if (opt == 2) {
                    pharmacyMenu(currentUser, role);
                } else if (opt == 3) {
                    loggedIn = false;
                    currentUser = "";
                    role = "";
                } else if (opt == 4) {
                    cout << "Exiting...\n";
                    break;
                } else {
                    cout << "Invalid option. Try again.\n";
                }

            } else {
                cout << "Unknown role. Logging out...\n";
                loggedIn = false;
                currentUser = "";
                role = "";
            }
        }
    }

    return 0;
}

// g++ main.cpp login_registration.cpp pharmacy.cpp staff.cpp student_faculty.cpp -o main.exe
// .\main.exe
