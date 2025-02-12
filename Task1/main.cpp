#include <iostream>
#include <vector>
#include <string>
#include <ctime>

class Transaction {
public:
    std::string type;
    double amount;
    std::string date;

    Transaction(std::string t, double a, std::string d) : type(t), amount(a), date(d) {}

    void displayTransaction() const {
        std::cout << "Type: " << type << ", Amount: " << amount << ", Date: " << date << "\n";
    }
};

class ATM {
private:
    std::string accountNumber;
    std::string pin;
    double balance;
    std::vector<Transaction> transactions;
    bool loanApplied;
    double loanAmount;

public:
    ATM(std::string accNo, std::string pinNo) : accountNumber(accNo), pin(pinNo), balance(0), loanApplied(false), loanAmount(0) {}

    bool authenticate(std::string enteredPin) {
        return enteredPin == pin;
    }

    void deposit(double amount) {
        balance += amount;
        transactions.push_back(Transaction("Deposit", amount, currentDate()));
    }

    void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            transactions.push_back(Transaction("Withdraw", amount, currentDate()));
        } else {
            std::cout << "Insufficient funds!\n";
        }
    }

    void applyForLoan(double amount) {
        if (loanApplied) {
            std::cout << "Loan application already in progress.\n";
            return;
        }
        loanAmount = amount;
        loanApplied = true;
        std::cout << "Loan application of amount " << loanAmount << " submitted.\n";
        transactions.push_back(Transaction("Loan Application", loanAmount, currentDate()));
    }

    void payLoan(double amount) {
        if (loanApplied && loanAmount > 0) {
            if (amount <= balance) {
                balance -= amount;
                loanAmount -= amount;
                std::cout << "Payment of " << amount << " towards loan successful.\n";
                transactions.push_back(Transaction("Loan Payment", amount, currentDate()));
            } else {
                std::cout << "Insufficient balance for loan payment.\n";
            }
        } else {
            std::cout << "No active loan to pay.\n";
        }
    }

    void checkLoanStatus() const {
        if (loanApplied && loanAmount > 0) {
            std::cout << "Loan application in progress. Loan Amount: " << loanAmount << "\n";
        } else {
            std::cout << "No active loan application.\n";
        }
    }

    void viewTransactionHistory() const {
        std::cout << "\n===== Transaction History =====\n";
        for (const auto& transaction : transactions) {
            transaction.displayTransaction();
        }
    }

    void viewFilteredTransactionHistory() const {
        std::string type;
        std::string startDate, endDate;

        std::cout << "Enter transaction type (or leave blank for all): ";
        std::cin.ignore();
        std::getline(std::cin, type);

        std::cout << "Enter start date (YYYY-MM-DD) or leave blank: ";
        std::getline(std::cin, startDate);

        std::cout << "Enter end date (YYYY-MM-DD) or leave blank: ";
        std::getline(std::cin, endDate);

        std::cout << "\n===== Filtered Transaction History =====\n";
        for (const auto& transaction : transactions) {
            bool match = true;

            if (!type.empty() && transaction.type != type) {
                match = false;
            }

            if (!startDate.empty() && transaction.date < startDate) {
                match = false;
            }

            if (!endDate.empty() && transaction.date > endDate) {
                match = false;
            }

            if (match) {
                transaction.displayTransaction();
            }
        }
    }

    void changePIN(std::string oldPin, std::string newPin) {
        if (oldPin == pin) {
            pin = newPin;
            std::cout << "PIN successfully changed.\n";
        } else {
            std::cout << "Incorrect old PIN.\n";
        }
    }

    double getBalance() const { return balance; }

private:
    std::string currentDate() const {
        time_t t = time(0);
        struct tm* now = localtime(&t);
        char buf[80];
        strftime(buf, sizeof(buf), "%Y-%m-%d", now);
        return std::string(buf);
    }
};

int main() {
    ATM atm("1234567890", "1234");

    std::string enteredPin;
    std::cout << "Enter Account Number: ";
    std::string accountNumber;
    std::cin >> accountNumber;
    std::cout << "Enter PIN: ";
    std::cin >> enteredPin;

    if (!atm.authenticate(enteredPin)) {
        std::cout << "Authentication failed!\n";
        return 0;
    }

    std::cout << "Authentication successful!\n";

    int option;
    do {
        std::cout << "\n===== ATM Menu =====\n";
        std::cout << "1. Check Balance\n";
        std::cout << "2. Deposit Money\n";
        std::cout << "3. Withdraw Money\n";
        std::cout << "4. View Transaction History\n";
        std::cout << "5. View Filtered Transaction History\n";
        std::cout << "6. Calculate Interest\n";
        std::cout << "7. Change PIN\n";
        std::cout << "8. Apply for Loan\n";
        std::cout << "9. Pay Loan\n";
        std::cout << "10. Check Loan Status\n";
        std::cout << "11. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> option;

        switch (option) {
            case 1:
                std::cout << "Balance: " << atm.getBalance() << "\n";
                break;
            case 2: {
                double amount;
                std::cout << "Enter deposit amount: ";
                std::cin >> amount;
                atm.deposit(amount);
                break;
            }
            case 3: {
                double amount;
                std::cout << "Enter withdrawal amount: ";
                std::cin >> amount;
                atm.withdraw(amount);
                break;
            }
            case 4:
                atm.viewTransactionHistory();
                break;
            case 5:
                atm.viewFilteredTransactionHistory();
                break;
            case 6:
                std::cout << "Interest calculation is not implemented yet.\n";
                break;
            case 7: {
                std::string oldPin, newPin;
                std::cout << "Enter old PIN: ";
                std::cin >> oldPin;
                std::cout << "Enter new PIN (4 digits): ";
                std::cin >> newPin;
                atm.changePIN(oldPin, newPin);
                break;
            }
            case 8: {
                double loanAmount;
                std::cout << "Enter loan amount: ";
                std::cin >> loanAmount;
                atm.applyForLoan(loanAmount);
                break;
            }
            case 9: {
                double paymentAmount;
                std::cout << "Enter payment amount: ";
                std::cin >> paymentAmount;
                atm.payLoan(paymentAmount);
                break;
            }
            case 10:
                atm.checkLoanStatus();
                break;
            case 11:
                std::cout << "Exiting the ATM. Thank you for using our service!\n";
                break;
            default:
                std::cout << "Invalid input! Please choose a valid option (1-11): ";
        }
    } while (option != 11);  // Continue until the user chooses to exit

    return 0;
}
