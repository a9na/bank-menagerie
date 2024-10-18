#include<iostream>
#include "bankmanagement.h"
#include<cstdlib>  // For exit()
#include<conio.h>  // For getch()
#include<iomanip>  // For formatting output
#include<fstream>  // For logging actions
#include<string>   // For string handling
using namespace std;

// Function to log actions to a file
void logAction(string action) {
    ofstream logFile("bank_log.txt", ios::app);
    logFile << action << endl;
    logFile.close();
}

// Utility to get and validate account number input
int getAccountNumber() {
    int acc_number;
    cout << "Enter account number: ";
    cin >> acc_number;
    while (cin.fail() || acc_number < 0) {
        cin.clear();  // clear input buffer to restore cin to a usable state
        cin.ignore(INT_MAX, '\n');  // ignore last input
        cout << "Invalid account number. Please enter a positive number: ";
        cin >> acc_number;
    }
    return acc_number;
}

// Utility function to ask for confirmation
bool confirmAction(const string& action) {
    char confirmation;
    cout << "Are you sure you want to " << action << "? (y/n): ";
    cin >> confirmation;
    return (confirmation == 'y' || confirmation == 'Y');
}

// Utility to pause the program and display a message
void pauseScreen() {
    cout << "\nPress any key to continue...";
    getch();  // Wait for user to press a key
}

int main() {
    bankmanagement accounts[5];  // Array to hold bank accounts
    int choice, acc_number;
    bool found;
    float amount;
    string action;

    while (true) {
        system("CLS");
        cout << "===== Bank Management Menu =====\n";
        cout << "1. Create New Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Check Account Details\n";
        cout << "5. Modify Account\n";
        cout << "6. Delete Account\n";
        cout << "7. Show All Accounts\n";
        cout << "8. Export Account Info to File\n";
        cout << "9. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:  // Create new account
                found = false;
                for (int i = 0; i < 5; i++) {
                    if (accounts[i].checkavailability()) {
                        found = true;
                        accounts[i].newaccount();
                        action = "Created new account #" + to_string(accounts[i].getAccNo());
                        logAction(action);
                        break;
                    }
                }
                if (!found)
                    cout << "Account limit exceeded.\n";
                pauseScreen();
                break;

            case 2:  // Deposit money
                acc_number = getAccountNumber();
                found = false;
                for (int i = 0; i < 5; i++) {
                    if (accounts[i].searchaccount(acc_number)) {
                        found = true;
                        cout << "Enter amount to deposit: ";
                        cin >> amount;
                        while (amount <= 0) {
                            cout << "Invalid amount. Please enter a positive number: ";
                            cin >> amount;
                        }
                        accounts[i].deposit(amount);
                        action = "Deposited $" + to_string(amount) + " into account #" + to_string(acc_number);
                        logAction(action);
                        break;
                    }
                }
                if (!found)
                    cout << "Account not found.\n";
                pauseScreen();
                break;

            case 3:  // Withdraw money
                acc_number = getAccountNumber();
                found = false;
                for (int i = 0; i < 5; i++) {
                    if (accounts[i].searchaccount(acc_number)) {
                        found = true;
                        cout << "Enter amount to withdraw: ";
                        cin >> amount;
                        while (amount <= 0) {
                            cout << "Invalid amount. Please enter a positive number: ";
                            cin >> amount;
                        }
                        accounts[i].withdraw(amount);
                        action = "Withdrew $" + to_string(amount) + " from account #" + to_string(acc_number);
                        logAction(action);
                        break;
                    }
                }
                if (!found)
                    cout << "Account not found.\n";
                pauseScreen();
                break;

            case 4:  // Check account details
                acc_number = getAccountNumber();
                found = false;
                for (int i = 0; i < 5; i++) {
                    if (accounts[i].searchaccount(acc_number)) {
                        found = true;
                        accounts[i].check_account();
                        action = "Checked details for account #" + to_string(acc_number);
                        logAction(action);
                        break;
                    }
                }
                if (!found)
                    cout << "Account not found.\n";
                pauseScreen();
                break;

            case 5:  // Modify account
                acc_number = getAccountNumber();
                found = false;
                for (int i = 0; i < 5; i++) {
                    if (accounts[i].searchaccount(acc_number)) {
                        found = true;
                        if (confirmAction("modify this account")) {
                            accounts[i].modifyaccount();
                            action = "Modified account #" + to_string(acc_number);
                            logAction(action);
                        } else {
                            cout << "Modification cancelled.\n";
                        }
                        break;
                    }
                }
                if (!found)
                    cout << "Account not found.\n";
                pauseScreen();
                break;

            case 6:  // Delete account
                acc_number = getAccountNumber();
                found = false;
                for (int i = 0; i < 5; i++) {
                    if (accounts[i].searchaccount(acc_number)) {
                        found = true;
                        if (confirmAction("delete this account")) {
                            accounts[i].deleteaccount();
                            action = "Deleted account #" + to_string(acc_number);
                            logAction(action);
                            cout << "Account deleted successfully.\n";
                        } else {
                            cout << "Account deletion cancelled.\n";
                        }
                        break;
                    }
                }
                if (!found)
                    cout << "Account not found.\n";
                pauseScreen();
                break;

            case 7:  // Show all accounts
                found = false;
                for (int i = 0; i < 5; i++) {
                    if (!accounts[i].checkavailability()) {
                        found = true;
                        cout << "==============================\n";
                        cout << "Account Number: " << accounts[i].getAccNo() << endl;
                        accounts[i].check_account();
                        cout << "==============================\n";
                    }
                }
                if (!found)
                    cout << "No accounts found.\n";
                action = "Displayed all accounts";
                logAction(action);
                pauseScreen();
                break;

            case 8:  // Export all account information to file
                {
                    ofstream outfile("account_data.txt");
                    if (!outfile.is_open()) {
                        cout << "Error opening file for writing!\n";
                        break;
                    }
                    for (int i = 0; i < 5; i++) {
                        if (!accounts[i].checkavailability()) {
                            outfile << "Account Number: " << accounts[i].getAccNo() << endl;
                            accounts[i].writeToFile(outfile);  // Assuming a function in bankmanagement
                            outfile << "==============================\n";
                        }
                    }
                    outfile.close();
                    cout << "Account details exported successfully.\n";
                    action = "Exported all accounts to file";
                    logAction(action);
                }
                pauseScreen();
                break;

            case 9:  // Exit
                if (confirmAction("exit the program")) {
                    logAction("Exited the program");
                    exit(0);
                } else {
                    cout << "Exit cancelled.\n";
                }
                pauseScreen();
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
                pauseScreen();
        }
    }

    return 0;
}
