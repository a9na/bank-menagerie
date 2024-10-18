#ifndef BANKMANAGEMENT_H
#define BANKMANAGEMENT_H

#include<string>
using namespace std;

// Class to represent a bank account
class bankmanagement
{
private:
    int accno;              // Account number
    string name, address;    // Account holder's name and address
    char actype;             // Account type (saving or current)
    float amount;            // Account balance

public:
    bankmanagement();        // Constructor to initialize account attributes
    bool checkavailability(); // Check if the account slot is available
    bool searchaccount(int);  // Search for an account by account number
    void newaccount();        // Create a new bank account
    void deposit();           // Deposit money into an account
    void withdraw();          // Withdraw money from an account
    void check_account();     // Display account details
    void modifyaccount();     // Modify account information
    void deleteaccount();     // Delete an account
};

#endif
