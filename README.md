# Banking Management System

A **console-based Banking Management System** developed in **C++** with **MySQL** as the backend database. The project demonstrates how a C++ application can interact with a relational database to perform core banking operations while maintaining transaction records.

---

## Overview

This project simulates a simple banking system where users can create accounts, manage balances, transfer funds, and maintain transaction history. It showcases CRUD operations, database connectivity, and object-oriented programming concepts in C++.

---

## Features

-  Create a new bank account
-  View account details
-  Deposit money
-  Withdraw money
-  Transfer funds between accounts
-  Automatic transaction logging
-  Persistent data storage using MySQL

---

## Tech Stack

| Category | Technology |
|----------|------------|
| Language | C++ |
| Database | MySQL |
| Connector | MySQL C API |
| Compiler | g++ |

---

## Project Structure

```
Banking-System/
│── BankingSystem.h        # Class declaration
│── BankingSystem.cpp      # Implementation & main function
│── README.md
```

---

## Database Schema

### Accounts Table

```sql
CREATE TABLE Accounts (
    account_id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(50) NOT NULL,
    email VARCHAR(50) UNIQUE NOT NULL,
    balance DOUBLE DEFAULT 0.0
);
```

### Transactions Table

```sql
CREATE TABLE Transactions (
    transaction_id INT AUTO_INCREMENT PRIMARY KEY,
    account_id INT,
    type VARCHAR(20),
    amount DOUBLE,
    date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (account_id) REFERENCES Accounts(account_id)
);
```

---

## Setup Instructions

### 1. Install MySQL

```bash
sudo apt update
sudo apt install mysql-server
```

---

### 2. Create Database

```sql
CREATE DATABASE BankingDB;
USE BankingDB;
```

Create the **Accounts** and **Transactions** tables using the SQL commands above.

---

### 3. Configure Database Credentials

Open `BankingSystem.cpp` and update the MySQL connection credentials if required.

```cpp
mysql_real_connect(
    conn,
    "localhost",
    "your_username",
    "your_password",
    "BankingDB",
    0,
    NULL,
    0
);
```

---

### 4. Compile the Project

```bash
g++ BankingSystem.cpp -o BankingSystem `mysql_config --cflags --libs`
```

---

### 5. Run

```bash
./BankingSystem
```

---

## Menu

```
--- Banking System Menu ---

1. Create Account
2. View Account
3. Deposit
4. Withdraw
5. Transfer
6. Exit
```

---

## Workflow

```
Start
   │
   ▼
Connect to MySQL Database
   │
   ▼
Display Banking Menu
   │
   ├── Create Account
   ├── View Account
   ├── Deposit
   ├── Withdraw
   ├── Transfer Funds
   └── Exit
```

---

## Example Usage

### Create Account

```
Name : Shivam Kumar
Email : shivam@gmail.com
Initial Deposit : 5000
```

---

### Deposit

```
Account ID : 1
Amount : 2000
```

---

### Withdraw

```
Account ID : 1
Amount : 1000
```

---

### Transfer

```
Sender Account : 1
Receiver Account : 2
Amount : 1500
```

---

## Key Concepts Demonstrated

- Object-Oriented Programming
- Classes and Objects
- MySQL Database Connectivity
- SQL Queries
- CRUD Operations
- Transaction Logging
- File Organization
- Console-Based User Interface

---

## Future Improvements

- User Authentication
- PIN/Password Protection
- Account Statement Generation
- Interest Calculation
- Loan Management
- Fixed Deposit Module
- Input Validation
- Exception Handling
- Prepared Statements for SQL Injection Prevention
- GUI using Qt or GTK

---
