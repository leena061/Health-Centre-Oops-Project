#ifndef LOGIN_REGISTRATION_H
#define LOGIN_REGISTRATION_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <conio.h> // For password masking on Windows
using namespace std;

class User {
public:
    string name, phone, email, username, password, role, age, gender;

    User();
    User(string n, string p, string e, string a, string g, string u, string pass, string r);
    void saveToFile();
};

bool userExists(const string& username);
bool verifyLogin(const string& username, const string& password, string& role);
void registerUser();
void forgotPassword();
string maskPassword();

#endif
