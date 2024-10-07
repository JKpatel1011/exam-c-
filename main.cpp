#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Base Class: BankAccount
class BankAccount {
protected:
    string accountNumber;
    string accountHolderName;
    double balance;

public:
    BankAccount(string accNum, string holderName) : accountNumber(accNum), accountHolderName(holderName), balance(0.0) {}

    void deposit(double amount) {
        balance += amount;
        cout << fixed << setprecision(2);
        cout << "Deposited: $" << amount << "\nNew Balance: $" << balance << endl;
    }

    virtual bool withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            cout << fixed << setprecision(2);
            cout << "Withdrawn: $" << amount << "\nNew Balance: $" << balance << endl;
            return true;
        } else {
            cout << "Insufficient funds for withdrawal." << endl;
            return false;
        }
    }

    double getBalance() const {
        return balance;
    }

    void displayAccountInfo() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder Name: " << accountHolderName << endl;
        cout << "Balance: $" << fixed << setprecision(2) << balance << endl;
    }
};

// Derived Class: SavingsAccount
class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    SavingsAccount(string accNum, string holderName, double rate)
        : BankAccount(accNum, holderName), interestRate(rate) {}

    void calculateInterest() {
        double interest = balance * (interestRate / 100);
        cout << "Interest Calculated: $" << fixed << setprecision(2) << interest << endl;
    }

    bool withdraw(double amount) override {
        if (amount <= balance) {
            return BankAccount::withdraw(amount);
        } else {
            cout << "Insufficient funds in Savings Account." << endl;
            return false;
        }
    }
};

// Derived Class: CheckingAccount
class CheckingAccount : public BankAccount {
private:
    double overdraftLimit;

public:
    CheckingAccount(string accNum, string holderName, double limit)
        : BankAccount(accNum, holderName), overdraftLimit(limit) {}

    bool withdraw(double amount) override {
        if (amount <= (balance + overdraftLimit)) {
            balance -= amount;
            cout << fixed << setprecision(2);
            cout << "Withdrawn: $" << amount << "\nNew Balance: $" << balance << endl;
            return true;
        } else {
            cout << "Withdrawal exceeds overdraft limit." << endl;
            return false;
        }
    }
};

// Derived Class: FixedDepositAccount
class FixedDepositAccount : public BankAccount {
private:
    int term;

public:
    FixedDepositAccount(string accNum, string holderName, int duration)
        : BankAccount(accNum, holderName), term(duration) {}

    void calculateInterest() {
        double interest = balance * 0.05; // Fixed interest rate for example
        cout << "Interest Calculated on Fixed Deposit: $" << fixed << setprecision(2) << interest << endl;
    }
};

// Main Function
int main() {
    BankAccount* accounts[10]; // Array to hold pointers to different account types
    int accountCount = 0;
    int choice;

    do {
        cout << "\n--- Banking System ---\n";
        cout << "1. Create Savings Account\n";
        cout << "2. Create Checking Account\n";
        cout << "3. Create Fixed Deposit Account\n";
        cout << "4. Deposit\n";
        cout << "5. Withdraw\n";
        cout << "6. Display Account Info\n";
        cout << "7. Calculate Interest (Savings)\n";
        cout << "8. Calculate Interest (Fixed Deposit)\n";
        cout << "9. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string accNum, holderName;
                double interestRate;
                cout << "Enter Account Number: ";
                cin >> accNum;
                cout << "Enter Account Holder Name: ";
                cin >> holderName;
                cout << "Enter Interest Rate: ";
                cin >> interestRate;
                accounts[accountCount++] = new SavingsAccount(accNum, holderName, interestRate);
                break;
            }
            case 2: {
                string accNum, holderName;
                double overdraftLimit;
                cout << "Enter Account Number: ";
                cin >> accNum;
                cout << "Enter Account Holder Name: ";
                cin >> holderName;
                cout << "Enter Overdraft Limit: ";
                cin >> overdraftLimit;
                accounts[accountCount++] = new CheckingAccount(accNum, holderName, overdraftLimit);
                break;
            }
            case 3: {
                string accNum, holderName;
                int term;
                cout << "Enter Account Number: ";
                cin >> accNum;
                cout << "Enter Account Holder Name: ";
                cin >> holderName;
                cout << "Enter Term (in months): ";
                cin >> term;
                accounts[accountCount++] = new FixedDepositAccount(accNum, holderName, term);
                break;
            }
            case 4: {
                string accNum;
                double amount;
                cout << "Enter Account Number: ";
                cin >> accNum;
                cout << "Enter Deposit Amount: ";
                cin >> amount;
                for (int i = 0; i < accountCount; i++) {
                    if (accounts[i]->getBalance() == amount) { // For simplicity, match on amount
                        accounts[i]->deposit(amount);
                        break;
                    }
                }
                break;
            }
            case 5: {
                string accNum;
                double amount;
                cout << "Enter Account Number: ";
                cin >> accNum;
                cout << "Enter Withdrawal Amount: ";
                cin >> amount;
                for (int i = 0; i < accountCount; i++) {
                    if (accounts[i]->getBalance() == amount) { // For simplicity, match on amount
                        accounts[i]->withdraw(amount);
                        break;
                    }
                }
                break;
            }
            case 6: {
                string accNum;
                cout << "Enter Account Number: ";
                cin >> accNum;
                for (int i = 0; i < accountCount; i++) {
                    if (accounts[i]->getBalance() == 0) { // Display account info
                        accounts[i]->displayAccountInfo();
                        break;
                    }
                }
                break;
            }
            case 7: {
                string accNum;
                cout << "Enter Account Number: ";
                cin >> accNum;
                for (int i = 0; i < accountCount; i++) {
                    if (SavingsAccount* sa = dynamic_cast<SavingsAccount*>(accounts[i])) {
                        sa->calculateInterest();
                        break;
                    }
                }
                break;
            }
            case 8: {
                string accNum;
                cout << "Enter Account Number: ";
                cin >> accNum;
                for (int i = 0; i < accountCount; i++) {
                    if (FixedDepositAccount* fda = dynamic_cast<FixedDepositAccount*>(accounts[i])) {
                        fda->calculateInterest();
                        break;
                    }
                }
                break;
            }
            case 9:
                cout << "Exiting the banking system. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    } while (choice != 9);

    // Clean up allocated memory
    for (int i = 0; i < accountCount; i++) {
        delete accounts[i];
    }

    return 0;
}