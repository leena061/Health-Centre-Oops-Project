#ifndef PHARMACY_H
#define PHARMACY_H

#include <string>
#include <unordered_map>
#include <limits> // For input validation
using namespace std;

struct Medicine {
    int quantity;
    double price;
};

class Pharmacy {
private:
    unordered_map<string, Medicine> inventory;
    void saveInventory();

public:
    Pharmacy();
    void loadInventory();
    void checkAvailability(const string& medicine);
    void orderMedicine(const string& medicine, int quantity);
    void displayInventory();
    void updateInventory(const string& medicine, int newQuantity, double newPrice);
};

// Prescription and Staff Authentication
void uploadPrescription(const string& username);
bool authenticateStaff();
void pharmacyMenu(const string& username);

// Input validation helper
int getValidatedInt(const string& prompt);
double getValidatedDouble(const string& prompt);

#endif

