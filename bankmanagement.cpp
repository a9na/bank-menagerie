#include<iostream>
#include "bankmanagement.h"
using namespace std;

// Constructor
bankmanagement::bankmanagement()
{
    accno = 0;
    name = "";
    address = "";
    actype = '\0';
    amount = 0.0;
}

// Check if account slot is available
bool bankmanagement::checkavailability()
{
    return accno == 0 && name == "" && address == "" && actype == '\0' && amount == 0.0;
}

// Search for account by account number
bool bankmanagement::searchaccount(int a)
{
    return accno == a;
}

// Create new account
void bankmanagement::newaccount()
{
    cout << "Enter account no: ";
    cin >> accno;
    
    cout << "Enter your full name: ";
    cin.ignore();
    getline(cin, name);
    
    cout << "Enter your address: ";
    getline(cin, address);
    
    cout << "Account type (s for Saving, c for Current): ";
    cin >> actype;
    
    cout << "Initial deposit: ";
    cin >> amount;
    
    cout << "Account created successfully.\n";
}

// Deposit money
void bankmanagement::deposit()
{
    float deposit_amount;
    cout << "Enter amount to deposit: ";
    cin >> deposit_amount;
    amount += deposit_amount;
    cout << "Deposit successful. New balance: " << amount << endl;
}

// Withdraw money
void bankmanagement::withdraw()
{
    float withdraw_amount;
    cout << "Enter amount to withdraw: ";
    cin >> withdraw_amount;
    
    if (withdraw_amount <= amount)
    {
        amount -= withdraw_amount;
        cout << "Withdrawal successful. Remaining balance: " << amount << endl;
    }
    else
    {
        cout << "Insufficient balance.\n";
    }
}

// Check account details
void bankmanagement::check_account()
{
    cout << "Account No.: " << accno << endl;
    cout << "Account Holder: " << name << endl;
    cout << "Address: " << address << endl;
    cout << "Account Type: " << actype << endl;
    cout << "Balance: " << amount << endl;
}

// Modify account information
void bankmanagement::modifyaccount()
{
    cout << "Enter new name: ";
    cin.ignore();
    getline(cin, name);
    
    cout << "Enter new address: ";
    getline(cin, address);
    
    cout << "Enter new account type (s for Saving, c for Current): ";
    cin >> actype;
    
    cout << "Account modified successfully.\n";
}

// Delete account
void bankmanagement::deleteaccount()
{
    accno = 0;
    name = "";
    address = "";
    actype = '\0';
    amount = 0.0;
    cout << "Account deleted successfully.\n";
}
