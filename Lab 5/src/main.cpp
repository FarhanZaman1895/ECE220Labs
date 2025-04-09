// 
// ECE 220 Lab - Winter 2025 - Programming for Electrical Engineering
// Lab 5: Object Oriented
// Author: Farhan Zaman
//

#include <iostream>
#include <string.h>

using namespace std;

#define MAX_NAME_LEN 40
#define OWN 1
#define RENT 0

// The 1st-level class: BankAccount
class BankAccount {
protected:
    char name[MAX_NAME_LEN];
    int account_number;
    double balance;
public:
    BankAccount();
    BankAccount(char *);
    BankAccount(char *, int, double);

    void printSummary();
    double withdraw(double);
    void deposit(double);
    double getBalance();
    void setName(char *);
    void setAccount_number(int);
    void setBalance(double);
};

// The 2nd-level class: saveBankAccount
class saveBankAccount : public BankAccount { //inheritance of BankAccount
protected:
    double interestRate;
    int MAXnoWithDraws;
    int noWithDraws;

public:
    saveBankAccount();
    saveBankAccount(char*name0, int acc_num0, double balance0, double interestRate0, int MAXnoWtdraws0);

    void printSummary();
    double withdraw(double);

    void callInterest();
    void resetWithdraws();
    void transfer(saveBankAccount &acc2, double);

};

// The 3rd-level class: CreditScoreAccount
class CreditScoreAccount : public saveBankAccount {   //inherit from saveBankAccount
protected:
    int age;
    long income;
    bool home_ownership;
    int CreditScore;
public:
    CreditScoreAccount(char*name0, int acc_num0, double balance0, double interestRate0, int MAXnoWtdraws0, int age0, long income0, bool home0);

    void CreditScoreReport();
};


int main(void) {

    // Task A
    cout << endl << "Task A" << endl;
    char tomName[] = "Tom";
    saveBankAccount tomAcc(tomName, 110011, 2000, 0.05, 1);
    tomAcc.printSummary();

    // Task B
    cout << endl << "Task B" << endl;
    tomAcc.deposit(1000);
    tomAcc.printSummary();

    tomAcc.withdraw(500);
    tomAcc.printSummary();

    tomAcc.withdraw(500);
    tomAcc.printSummary();

    cout << "Tom's Balance: " << tomAcc.getBalance() << endl;

    tomAcc.resetWithdraws();
    tomAcc.printSummary();

    tomAcc.withdraw(500);
    tomAcc.printSummary();

    tomAcc.callInterest();
    tomAcc.printSummary();

    char ericName[] = "Eric";
    saveBankAccount ericAcc(ericName, 220011, 5000, 0.04, 1);
    ericAcc.printSummary();

    ericAcc.transfer(tomAcc, 1000);

    ericAcc.printSummary();
    tomAcc.printSummary();

    // Task C
    cout << endl << "Task C" << endl;
    char amyName[] = "Amy";
    CreditScoreAccount amyCredit(amyName, 330011, 5000, 0.03, 5, 25, 80000, RENT);
    amyCredit.printSummary();
    amyCredit.CreditScoreReport();

    char kateName[] = "Kate";
    CreditScoreAccount kateCredit(kateName, 330022, 5000, 0.03, 5, 35, 120000, OWN);
    kateCredit.printSummary();
    kateCredit.CreditScoreReport();

    return 0;
}

////**********************************************
//// class BankAccount: methods
////**********************************************

BankAccount::BankAccount() {
    name[0] = 0;
    account_number = 0;
    balance = 0.0;
}

BankAccount::BankAccount(char *n) {
    strcpy(name, n);
    account_number = 0;
    balance = 0.0;
}

BankAccount::BankAccount(char *n, int a_no, double bal) {
    strcpy(name, n);
    account_number = a_no;
    balance = bal;
}

void BankAccount::printSummary() {
    cout << "---------------------" << endl;
    cout << "Name: " << name << endl;
    cout << "Account Number: " << account_number << endl;
    cout << "Balance: " << balance << endl;
    cout << "---------------------" << endl;
}

double BankAccount::withdraw(double toWD) {
    if (balance - toWD > 0) {
        balance -= toWD;
        cout << "Withdraw succeed!: " << toWD << endl;
        return toWD; //teng4 modified.
    } else {
        cout << "!!!Sorry, not enough money!!!" << endl;
        cout << "Withdraw failed!: " << toWD << endl;
        return 0;
    }
}

void BankAccount::deposit(double toDep) {
    balance += toDep;
    cout << "Deposit succeed!: " << toDep << endl;
}

double BankAccount::getBalance() {
    return balance;
}


void BankAccount::setName(char *n) {
    strcpy(name, n);
}

void BankAccount::setAccount_number(int a_no) {
    account_number = a_no;
}

void BankAccount::setBalance(double bal) {
    balance = bal;
}



////**********************************************
//// class saveBankAccount: methods
////**********************************************

saveBankAccount::saveBankAccount() {}

saveBankAccount::saveBankAccount(
        char* name0, int acc_num0, double balance0, 
        double interestRate0, int MAXnoWtdraws0):
    BankAccount(name0, acc_num0, balance0) {
    interestRate = interestRate0;
    MAXnoWithDraws = MAXnoWtdraws0;
    noWithDraws = 0;
}

void saveBankAccount::printSummary() {
    cout << "---------------------" << endl;
    cout << "Name: " << name << endl;
    cout << "Account Number: " << account_number << endl;
    cout << "Balance: " << balance << endl;
    cout << "Iterest Rate: " << interestRate << endl;
    cout << "Current Number of Withdraws: " << noWithDraws << endl;
    cout << "Maximum Number of Withdraws: " << MAXnoWithDraws << endl;
    cout << "---------------------" << endl;
}

void saveBankAccount::callInterest() {
    double interest = balance * interestRate;
    balance += interest;
}

void saveBankAccount::resetWithdraws() {
    cout << "Number of withdraws reset" << endl;
    noWithDraws = 0;
}

double saveBankAccount::withdraw(double amount) {
    if (amount >= balance) {
        cout << "Withdraw failed, insufficient funds" << endl;
        return 0;
    }

    if (noWithDraws >= MAXnoWithDraws) {
        cout << "Withdraw failed, withdraw limit reached" << endl;
        return 0;
    }

    balance -= amount;
    noWithDraws++;
    cout << "Withdraw successful, " << amount << endl;
    return amount;
}

void saveBankAccount::transfer(saveBankAccount &acc2, double amount) {
    if (amount >= balance) {
        cout << "Transfer failed, insufficient funds" << endl;
    } else {
        cout << "Transfer successful, " << amount;
        balance -= amount;
        acc2.deposit(amount);
    }
}

////**********************************************
//// class CreditScoreAccount: methods
////**********************************************

CreditScoreAccount::CreditScoreAccount(
        char*name0, int acc_num0, double balance0, 
        double interestRate0, int MAXnoWtdraws0, 
        int age0, long income0, bool home0):
    saveBankAccount(name0, acc_num0, balance0, interestRate0, MAXnoWtdraws0) {
    age = age0;
    income = income0;
    home_ownership = home0;
    CreditScore = 0;
}

void CreditScoreAccount::CreditScoreReport() {
    int age_factor;
    int home_factor;
    int income_factor;

    // Age factor
    if (age < 22) {
        age_factor = 100;
    } else if (age < 26) {
        age_factor = 120;
    } else if (age < 29) {
        age_factor = 185;
    } else if (age < 32) {
        age_factor = 200;
    } else if (age < 37) {
        age_factor = 210;
    } else if (age < 42) {
        age_factor = 225;
    } else {
        age_factor = 250;
    }

    // Home Factor
    if (home_ownership) {
        home_factor = 225;
    } else {
        home_factor = 110;
    }

    // Income Factor
    if (income < 10000) {
        income_factor = 120;
    } else if (income < 17000) {
        income_factor = 140;
    } else if (income < 28000) {
        income_factor = 180;
    } else if (income < 35000) {
        income_factor = 200;
    } else if (income < 42000) {
        income_factor = 225;
    } else if (income < 58000) {
        income_factor = 230;
    } else {
        income_factor = 260;
    }
    CreditScore = age_factor + home_factor + income_factor;

    cout << "---------------------" << endl;
    cout << "Credit report for " << name << endl;
    cout << "Age " << age_factor << endl;
    cout << "Income " << income_factor << endl;
    cout << "Home " << home_factor << endl;
    cout << "Credit Score: " << CreditScore << endl;
    cout << "" << endl;
    if (CreditScore < 600) {
        cout << "Sorry, " << name << " is not eligible!" << endl;
    } else {
        cout << "Congratulations!! " << name << " is eligible!" << endl;
    }
    cout << "---------------------" << endl;
}
