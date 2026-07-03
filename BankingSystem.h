#ifndef BANKINGSYSTEM_H
#define BANKINGSYSTEM_H

#include <iostream>
#include <mysql/mysql.h>
#include <string>

using namespace std;

class BankingSystem {
private:
    MYSQL* conn;
    void logTransaction(int account_id, const string& type, double amount);

public:
    BankingSystem();
    ~BankingSystem();

    void createAccount();
    void viewAccount();
    void deposit();
    void withdraw();
    void transfer();
};

#endif
