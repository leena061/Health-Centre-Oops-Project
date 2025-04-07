#include <iostream>
#include "login_registration.h"

using namespace std;

int main() {
    while (true) {
        cout << "\n=== Health Centre Login System ===\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Forgot Password\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cin.ignore(); // to clear newline from input buffer

        if (choice == 1) {
            registerUser();
        } else if (choice == 2) {
            string username, password;
            cout << "\n--- Login ---\n";
            cout << "Enter Username: ";
            getline(cin, username);
            cout << "Enter Password: ";
            password = maskPassword();

            if (verifyLogin(username, password)) {
                cout << "Login successful!\n";
                // You can add your dashboard() call here later
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
    }

    return 0;
}
