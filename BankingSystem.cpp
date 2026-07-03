#include "BankingSystem.h"
#include <iomanip>
#include <sstream>

BankingSystem::BankingSystem() {
    conn = mysql_init(0);
    if (!mysql_real_connect(conn, "localhost", "cppuser", "Nishant@123", "BankingDB", 0, NULL, 0)) {
        cout << "Connection Failed: " << mysql_error(conn) << endl;
        exit(1);
    }
}

BankingSystem::~BankingSystem() {
    mysql_close(conn);
}

void BankingSystem::logTransaction(int account_id, const string& type, double amount) {
    stringstream ss;
    ss << "INSERT INTO Transactions(account_id, type, amount) VALUES("
       << account_id << ", '" << type << "', " << amount << ")";
    mysql_query(conn, ss.str().c_str());
}

void BankingSystem::createAccount() {
    string name, email;
    double balance;
    cout << "Enter Name: "; cin >> ws; getline(cin, name);
    cout << "Enter Email: "; cin >> email;
    cout << "Initial Deposit: "; cin >> balance;

    string query = "INSERT INTO Accounts(name, email, balance) VALUES('" + name + "', '" + email + "', " + to_string(balance) + ")";
    if (mysql_query(conn, query.c_str()) == 0) {
        cout << "Account Created Successfully!" << endl;
        logTransaction(mysql_insert_id(conn), "Deposit", balance);
    } else {
        cout << "Error: " << mysql_error(conn) << endl;
    }
}

void BankingSystem::viewAccount() {
    int acc_id;
    cout << "Enter Account ID: "; cin >> acc_id;
    string query = "SELECT * FROM Accounts WHERE account_id = " + to_string(acc_id);

    if (mysql_query(conn, query.c_str()) == 0) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row;
        if ((row = mysql_fetch_row(res)) != NULL) {
            cout << "ID: " << row[0] << "\nName: " << row[1] << "\nEmail: " << row[2] 
                 << "\nBalance: " << row[3] << endl;
        } else {
            cout << "Account not found!" << endl;
        }
        mysql_free_result(res);
    }
}

void BankingSystem::deposit() {
    int acc_id;
    double amount;
    cout << "Enter Account ID: "; cin >> acc_id;
    cout << "Enter Amount to Deposit: "; cin >> amount;

    string query = "UPDATE Accounts SET balance = balance + " + to_string(amount) + " WHERE account_id = " + to_string(acc_id);
    if (mysql_query(conn, query.c_str()) == 0) {
        cout << "Amount Deposited Successfully!" << endl;
        logTransaction(acc_id, "Deposit", amount);
    }
}

void BankingSystem::withdraw() {
    int acc_id;
    double amount;
    cout << "Enter Account ID: "; cin >> acc_id;
    cout << "Enter Amount to Withdraw: "; cin >> amount;

    string check = "SELECT balance FROM Accounts WHERE account_id = " + to_string(acc_id);
    mysql_query(conn, check.c_str());
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(res);
    double balance = stod(row[0]);
    mysql_free_result(res);

    if (balance >= amount) {
        string query = "UPDATE Accounts SET balance = balance - " + to_string(amount) + " WHERE account_id = " + to_string(acc_id);
        mysql_query(conn, query.c_str());
        cout << "Withdrawal Successful!" << endl;
        logTransaction(acc_id, "Withdrawal", amount);
    } else {
        cout << "Insufficient Balance!" << endl;
    }
}

void BankingSystem::transfer() {
    int from_id, to_id;
    double amount;
    cout << "Enter Sender Account ID: "; cin >> from_id;
    cout << "Enter Receiver Account ID: "; cin >> to_id;
    cout << "Enter Amount: "; cin >> amount;

    // Check balance
    string check = "SELECT balance FROM Accounts WHERE account_id = " + to_string(from_id);
    mysql_query(conn, check.c_str());
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(res);
    double balance = stod(row[0]);
    mysql_free_result(res);

    if (balance >= amount) {
        string q1 = "UPDATE Accounts SET balance = balance - " + to_string(amount) + " WHERE account_id = " + to_string(from_id);
        string q2 = "UPDATE Accounts SET balance = balance + " + to_string(amount) + " WHERE account_id = " + to_string(to_id);
        mysql_query(conn, q1.c_str());
        mysql_query(conn, q2.c_str());
        cout << "Transfer Successful!" << endl;
        logTransaction(from_id, "Transfer Sent", amount);
        logTransaction(to_id, "Transfer Received", amount);
    } else {
        cout << "Insufficient Balance!" << endl;
    }
}

int main() {
    BankingSystem bank;
    int choice;

    while (true) {
        cout << "\n--- Banking System Menu ---\n";
        cout << "1. Create Account\n2. View Account\n3. Deposit\n4. Withdraw\n5. Transfer\n6. Exit\n";
        cout << "Enter choice: "; cin >> choice;

        switch (choice) {
            case 1: bank.createAccount(); break;
            case 2: bank.viewAccount(); break;
            case 3: bank.deposit(); break;
            case 4: bank.withdraw(); break;
            case 5: bank.transfer(); break;
            case 6: return 0;
            default: cout << "Invalid Choice!" << endl;
        }
    }
}

