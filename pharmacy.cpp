#include "pharmacy.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm> 
using namespace std;

bool isValidString(const string& input) {
    return !input.empty() && any_of(input.begin(), input.end(), [](char c){ return !isspace(c); });
}

Pharmacy::Pharmacy() {
    loadInventory();
}

void Pharmacy::loadInventory() {
    ifstream file("medicine_inventory.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string medName;
        int quantity;
        double price;
        getline(ss, medName, '|');
        ss >> quantity;
        ss.ignore();
        ss >> price;
        inventory[medName] = {quantity, price};
    }
    file.close();
}

void Pharmacy::checkAvailability(const string& medicine) {
    auto it = inventory.find(medicine);
    if (it != inventory.end() && it->second.quantity > 0) {
        cout << "\nAvailable\nPrice per unit: Rs. " << it->second.price << endl;
    } else {
        cout << "\nNot available at the moment.\n";
    }
}

void Pharmacy::orderMedicine(const string& medicine, int quantity) {
    auto it = inventory.find(medicine);
    if (it != inventory.end() && it->second.quantity >= quantity) {
        double total = quantity * it->second.price;
        cout << "\nOrder placed successfully! Total amount: Rs. " << total << endl;
        inventory[medicine].quantity -= quantity;
        saveInventory();
    } else {
        cout << "\nInsufficient stock or medicine not available.\n";
    }
}

void Pharmacy::displayInventory() {
    cout << "\n========= Current Inventory =========\n";
    for (const auto& pair : inventory) {
        cout << pair.first << " - Qty: " << pair.second.quantity
             << ", Price: Rs. " << pair.second.price << endl;
    }
    cout << "====================================\n";
}

void Pharmacy::updateInventory(const string& medicine, int newQuantity, double newPrice) {
    inventory[medicine] = {newQuantity, newPrice};
    saveInventory();
    cout << "\nInventory updated for " << medicine << endl;
}

void Pharmacy::saveInventory() {
    ofstream file("medicine_inventory.txt");
    for (const auto& pair : inventory) {
        file << pair.first << "|" << pair.second.quantity << "|" << pair.second.price << endl;
    }
    file.close();
}

void uploadPrescription(const string& username) {
    ofstream file("prescriptions.txt", ios::app);
    string doctor, medicine, dosage;

    cout << "\nEnter Doctor Name: ";
    getline(cin, doctor);
    if (!isValidString(doctor)) {
        cout << "Invalid input. Doctor name cannot be blank.\n";
        return;
    }

    cout << "Enter Medicine Name: ";
    getline(cin, medicine);
    if (!isValidString(medicine)) {
        cout << "Invalid input. Medicine name cannot be blank.\n";
        return;
    }

    cout << "Enter Dosage Instructions: ";
    getline(cin, dosage);
    if (!isValidString(dosage)) {
        cout << "Invalid input. Dosage instructions cannot be blank.\n";
        return;
    }

    file << username << "|" << doctor << "|" << medicine << "|" << dosage << endl;
    file.close();

    cout << "\nPrescription uploaded successfully!\n";
}

bool authenticateStaff() {
    string staffPassword;
    cout << "\nEnter Staff Password to Continue: ";
    getline(cin, staffPassword);
    return staffPassword == "admin123";
}

int getValidatedInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cout << "Invalid input. Please enter an integer.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

double getValidatedDouble(const string& prompt) {
    double value;
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

void pharmacyMenu(const string& username, const string& role) {
    Pharmacy pharmacy;
    int choice;
    do {
        cout << "\n========== Pharmacy Section ==========" << endl;
        cout << "1. Check Medicine Availability" << endl;
        cout << "2. Order Medicine" << endl;
        cout << "3. Upload Prescription" << endl;
        cout << "4. Display Inventory" << endl;

        if (role == "HealthCentreStaff") {
            cout << "5. Update Inventory (Staff Only)" << endl;
        }

        cout << "0. Exit" << endl;
        cout << "======================================" << endl;

        choice = getValidatedInt("Enter choice: ");

        string medicine;
        int quantity;
        double price;

        switch (choice) {
            case 1:
                cout << "\nEnter medicine name: ";
                getline(cin, medicine);
                if (!isValidString(medicine)) {
                    cout << "Invalid input. Medicine name cannot be blank.\n";
                    break;
                }
                pharmacy.checkAvailability(medicine);
                break;
            case 2:
                cout << "\nEnter medicine name: ";
                getline(cin, medicine);
                if (!isValidString(medicine)) {
                    cout << "Invalid input. Medicine name cannot be blank.\n";
                    break;
                }
                quantity = getValidatedInt("Enter quantity: ");
                pharmacy.orderMedicine(medicine, quantity);
                break;
            case 3:
                uploadPrescription(username);
                break;
            case 4:
                pharmacy.displayInventory();
                break;
            case 5:
                if (role == "HealthCentreStaff") {
                    if (authenticateStaff()) {
                        cout << "\nEnter medicine name: ";
                        getline(cin, medicine);
                        if (!isValidString(medicine)) {
                            cout << "Invalid input. Medicine name cannot be blank.\n";
                            break;
                        }
                        quantity = getValidatedInt("Enter new quantity: ");
                        price = getValidatedDouble("Enter new price: ");
                        pharmacy.updateInventory(medicine, quantity, price);
                    } else {
                        cout << "\nIncorrect password. Access denied.\n";
                    }
                } else {
                    cout << "\nAccess denied. You must be a staff member to update the inventory.\n";
                }
                break;
            case 0:
                cout << "\nExiting Pharmacy Section.\n";
                break;
            default:
                cout << "\nInvalid choice. Try again.\n";
        }
    } while (choice != 0);
}
