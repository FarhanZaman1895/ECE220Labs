#include <iostream>
#include <string.h>

#define NAME_MAXL 30

class BankAccount {
private:
    char m_name[NAME_MAXL];
    int m_account_number;
    double m_balance;
public:
    // Constructors
    BankAccount(): 
        m_name {0}, 
        m_account_number {0}, 
        m_balance {0} {
        
    }

    BankAccount(char* name):
        m_account_number {0},
        m_balance {0} {
        strcpy(m_name, name);
    }

    BankAccount(char* name, int account_number, double balance):
        m_account_number {new int} {

        }
};
