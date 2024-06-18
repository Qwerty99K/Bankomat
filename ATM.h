#pragma once
#include <iostream>
#include <sqlite3.h>
#include <sstream>
#include <iomanip>
#include "../include/ATM.h"
#include "../include/WindowInit.h"
#include "../include/Status.h"


class ATM {
private:
    int five_hundred;
    int two_hundred;
    int one_hundred;
    int fifty;
    int twenty;
    int ten;
    sqlite3* db;    // money database
    sqlite3* users; // users database
    char chosen_option;


public:
    ATM();
    ~ATM();
    void show_money();
    void welcome_screen();
    void login();
    void transfer(std::string sender_username, std::string recipient_username, double amount);
    void withdraw(const std::string& username, double& amount);
    void deposit(const std::string& username, double amount);
    void updateBalance(const std::string& username);
    bool authenticateUser(const std::string& username, const std::string& password);
    int createUser(AccountType, const std::string& name, const std::string& surname, const std::string& address, int age, const std::string& username, const std::string& password);
    std::vector<std::string> getUserCredentials(const std::string&, const std::string&);
    std::string generate_report(const std::string& username);
    void log_transaction(const std::string& username, const std::string& type, double amount);
};