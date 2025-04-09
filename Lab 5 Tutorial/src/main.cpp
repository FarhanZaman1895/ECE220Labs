#include <cmath>
#include <iomanip>
#include <iostream>
#include <string.h>

#define NAME_MAXL 30

class BankAccount {
private:
    char m_name[NAME_MAXL];
    int m_accountNumber;
    double m_balance;
public:
    // Constructors
    BankAccount(): 
        m_name {0}, 
        m_accountNumber {0}, 
        m_balance {0} {
        
    }

    BankAccount(const char* name):
        m_accountNumber {0},
        m_balance {0} {
        strcpy(m_name, name);
    }

    BankAccount(const char* name, int accountNumber, double balance):
        m_accountNumber {accountNumber},
        m_balance {balance} {
        strcpy(m_name, name);
    }

    void printSummary() {
        std::cout << "Name: " << m_name << "\n";
        std::cout << "Account Number: " << m_accountNumber << "\n";
        std::cout << "Balance: " << 
            std::fixed << std::setprecision(2) << m_balance << "\n\n";
    }

    void setName(const char* name) {
        strcpy(m_name, name);
    }

    void setAccountNumber(int accountNumber) {
        m_accountNumber = accountNumber;
    }

    void setBalance(float balance) {
        m_balance = balance;
    }

    double withdraw(double amount) {
        if (amount > m_balance) {
            std::cout << "Withdrawal failed, insufficient funds in balance.\n\n";
            return 0;
        }

        m_balance -= amount;
        std::cout << "$" << amount << " withdrawn.\n\n";
        return amount;
    }

    void deposit(double amount) {
        m_balance += amount;
        std::cout << "$" << amount << " deposited.\n\n";
    }
};

int main() {

    BankAccount daveAcc;
    BankAccount cindyAcc("Cindy");
    BankAccount billAcc("Bill", 123456, 2000);

    daveAcc.printSummary();
    cindyAcc.printSummary();
    billAcc.printSummary();

    billAcc.withdraw(500);
    billAcc.withdraw(2500);
    billAcc.printSummary();
    billAcc.deposit(1250);
    billAcc.printSummary();

    return 0;
}
