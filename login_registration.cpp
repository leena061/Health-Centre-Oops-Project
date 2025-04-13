#include "login_registration.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <conio.h> // For _getch() on Windows
using namespace std;

User::User() {}

User::User(string n, string p, string e, string a, string g, string u, string pass, string r)
    : name(n), phone(p), email(e), age(a), gender(g), username(u), password(pass), role(r) {}

void User::saveToFile() {
    ofstream file("users.txt", ios::app);
    file << role << "|" << name << "|" << phone << "|" << email << "|"
         << age << "|" << gender << "|" << username << "|" << password << endl;
    file.close();
}

bool userExists(const string& username) {
    ifstream file("users.txt");
    string line;
    while (getline(file, line)) {
        if (line.find(username) != string::npos)
            return true;
    }
    return false;
}

bool verifyLogin(const string& username, const string& password, string& role) {
    ifstream file("users.txt");
    string line;
    int matchCount = 0;
    string lastMatchPhone;

    while (getline(file, line)) {
        stringstream ss(line);
        string storedRole, name, storedPhone, email, age, gender, storedUsername, storedPassword;

        getline(ss, storedRole, '|');
        getline(ss, name, '|');
        getline(ss, storedPhone, '|');
        getline(ss, email, '|');
        getline(ss, age, '|');
        getline(ss, gender, '|');
        getline(ss, storedUsername, '|');
        getline(ss, storedPassword, '|');

        if (storedUsername == username && storedPassword == password) {
            matchCount++;
            role = storedRole;
            lastMatchPhone = storedPhone;
        }
    }

    // If exactly one match, return true (ensures uniqueness by phone)
    return matchCount == 1;
}

string maskPassword() {
    string password;
    char ch;
    while ((ch = _getch()) != '\r') { // Enter key
        if (ch == '\b') { // Backspace
            if (!password.empty()) {
                cout << "\b \b";
                password.pop_back();
            }
        } else {
            password += ch;
            cout << '*';
        }
    }
    cout << endl;
    return password;
}

void registerUser() {
    string role, name, phone, email, username, password, age, gender;
    cout << "\n--- Register ---\n";
    cout << "Are you a: \n1. Student/Faculty\n2. Health Centre Staff\nEnter choice: ";
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 1) role = "Student/Faculty";
    else if (choice == 2) role = "HealthCentreStaff";
    else {
        cout << "Invalid role!\n";
        return;
    }

    cout << "Enter Name: "; getline(cin, name);
    cout << "Enter Phone Number: "; getline(cin, phone);
    cout << "Enter Email: "; getline(cin, email);
    cout << "Enter Age: "; getline(cin, age);
    cout << "Enter Gender: "; getline(cin, gender);
    cout << "Enter Username: "; getline(cin, username);
    cout << "Enter Password: ";
    password = maskPassword();

    if (userExists(username)) {
        cout << "Username already exists!\n";
        return;
    }

    User newUser(name, phone, email, age, gender, username, password, role);
    newUser.saveToFile();
    cout << "Registration successful!\n";
}

void forgotPassword() {
    string username;
    cout << "Enter your username: ";
    cin >> username;
    ifstream file("users.txt");
    string line;
    bool found = false;
    while (getline(file, line)) {
        if (line.find(username) != string::npos) {
            found = true;
            size_t pos = line.rfind('|');
            cout << "Your password is: " << line.substr(pos + 1) << endl;
            break;
        }
    }
    if (!found)
        cout << "Username not found.\n";
}