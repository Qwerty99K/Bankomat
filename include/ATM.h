#pragma once
#include <iostream>
#include <sqlite3.h>
#include <sstream>
#include <iomanip>
#include "../include/ATM.h"
#include "../include/WindowInit.h"
#include "../include/Status.h"
#define ATM_DATABASE "../Bankomat/resources/atm.db"
#define USER_DATABASE "../Bankomat/resources/users.db"

class ATM {
private:
    int five_hundred;
    int two_hundred;
    int one_hundred;
    int fifty;
    int twenty;
    int ten;
    sqlite3* db;
    sqlite3* users; 
    char chosen_option;


public:
    ATM();
    ~ATM();
    void show_money();
    void welcome_screen();
    void login();
    void transfer(std::string, std::string, double);
    void withdraw(const std::string&, double&);
    void deposit(const std::string&, double);
    void updateBalance(const std::string&);
    bool authenticateUser(const std::string&, const std::string&);
    int createUser(AccountType, const std::string&, const std::string&, const std::string&, int, const std::string&, const std::string&);
    std::vector<std::string> getUserCredentials(const std::string&, const std::string&);
    std::string generate_report(const std::string&);
    void log_transaction(const std::string&, const std::string&, double);
};