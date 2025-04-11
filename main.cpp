#include <iostream>
#include "login_registration.h"
#include "pharmacy.h"
#include "student_faculty.h"

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
                string username, password;
                cout << "\n--------------- Login ---------------\n";
                cout << "Enter Username: ";
                getline(cin, username);
                cout << "Enter Password: ";
                password = maskPassword();

                if (verifyLogin(username, password)) {
                    cout << "Login successful!\n";
                    currentUser = username;
                    loggedIn = true;
                } else {
                    cout << "Invalid credentials.\n";
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
            cout << "\n========== Logged In Menu ==========" << endl;
            cout << "1. Student/Faculty Menu" << endl;
            cout << "2. Staff Menu" << endl;
            cout << "3. Pharmacy" << endl;
            cout << "4. Logout" << endl;
            cout << "5. Exit Program" << endl;
            cout << "=====================================\n";

            int opt = getValidatedIntMain("Enter choice: ");

            if (opt == 1) {
                studentFacultyMenu(currentUser);
            } else if (opt == 2) {
                cout << "\n[Staff Menu Placeholder]\n";
                // Add staffMenu(currentUser); later if needed
            } else if (opt == 3) {
                pharmacyMenu(currentUser);
            } else if (opt == 4) {
                loggedIn = false;
                currentUser = "";
            } else if (opt == 5) {
                cout << "Exiting...\n";
                break;
            } else {
                cout << "Invalid option. Try again.\n";
            }
        }
    }

    return 0;
}

//g++ main.cpp login_registration.cpp pharmacy.cpp student_faculty.cpp -o main.exe
//.\main.exe