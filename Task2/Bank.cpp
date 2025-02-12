#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Bank Account Class
class BankAccount {
private:
    string accountNumber;
    string accountHolder;
    double balance;
    string pin;

public:
    BankAccount(string accNum, string holder, string pinCode, double initialDeposit) {
        accountNumber = accNum;
        accountHolder = holder;
        pin = pinCode;
        balance = initialDeposit;
    }

    string getAccountNumber() { return accountNumber; }
    string getAccountHolder() { return accountHolder; }
    double getBalance() { return balance; }

    bool authenticate(string enteredPin) {
        return pin == enteredPin;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposit successful. New balance: " << balance << endl;
        } else {
            cout << "Invalid deposit amount." << endl;
        }
    }

    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawal successful. New balance: " << balance << endl;
            return true;
        } else {
            cout << "Insufficient balance or invalid amount." << endl;
            return false;
        }
    }

    bool transfer(BankAccount &recipient, double amount) {
        if (withdraw(amount)) {
            recipient.deposit(amount);
            cout << "Transfer successful to " << recipient.getAccountHolder() << endl;
            return true;
        } else {
            cout << "Transfer failed." << endl;
            return false;
        }
    }
};

vector<BankAccount> accounts;

// Function to find account by account number
BankAccount* findAccount(string accNum) {
    for (auto &acc : accounts) {
        if (acc.getAccountNumber() == accNum) {
            return &acc;
        }
    }
    return nullptr;
}

int main() {
    int choice;
    string accNum, name, pin, recipientAccNum;
    double amount;

    while (true) {
        cout << "\nOnline Banking System" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Deposit Money" << endl;
        cout << "3. Withdraw Money" << endl;
        cout << "4. Transfer Money" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Account Number: "; cin >> accNum;
            cout << "Enter Account Holder Name: "; cin >> name;
            cout << "Set a 4-digit PIN: "; cin >> pin;
            cout << "Initial Deposit Amount: "; cin >> amount;
            accounts.push_back(BankAccount(accNum, name, pin, amount));
            cout << "Account created successfully!" << endl;
            break;

        case 2:
            cout << "Enter Account Number: "; cin >> accNum;
            cout << "Enter PIN: "; cin >> pin;
            if (BankAccount* acc = findAccount(accNum)) {
                if (acc->authenticate(pin)) {
                    cout << "Enter amount to deposit: "; cin >> amount;
                    acc->deposit(amount);
                } else {
                    cout << "Invalid PIN." << endl;
                }
            } else {
                cout << "Account not found." << endl;
            }
            break;

        case 3:
            cout << "Enter Account Number: "; cin >> accNum;
            cout << "Enter PIN: "; cin >> pin;
            if (BankAccount* acc = findAccount(accNum)) {
                if (acc->authenticate(pin)) {
                    cout << "Enter amount to withdraw: "; cin >> amount;
                    acc->withdraw(amount);
                } else {
                    cout << "Invalid PIN." << endl;
                }
            } else {
                cout << "Account not found." << endl;
            }
            break;

        case 4:
            cout << "Enter Your Account Number: "; cin >> accNum;
            cout << "Enter Your PIN: "; cin >> pin;
            if (BankAccount* sender = findAccount(accNum)) {
                if (sender->authenticate(pin)) {
                    cout << "Enter Recipient Account Number: "; cin >> recipientAccNum;
                    if (BankAccount* receiver = findAccount(recipientAccNum)) {
                        cout << "Enter amount to transfer: "; cin >> amount;
                        sender->transfer(*receiver, amount);
                    } else {
                        cout << "Recipient account not found." << endl;
                    }
                } else {
                    cout << "Invalid PIN." << endl;
                }
            } else {
                cout << "Account not found." << endl;
            }
            break;

        case 5:
            cout << "Thank you for using Online Banking System!" << endl;
            return 0;

        default:
            cout << "Invalid choice. Try again." << endl;
        }
    }
}
