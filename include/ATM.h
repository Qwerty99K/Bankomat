#pragma once
#include <iostream>
#include <sqlite3.h>
#include "../include/StandardAccount.h"
//#include "../include/sqlite_use.h"

class ATM
{
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
    void create_account();
    void login();
    void transfer(std::string sender_username, std::string recipient_username, double amount);
    void withdraw(const std::string& username);
    void deposit(const std::string& username);
    void check_balance(const std::string& username);

private:
    int createUser(const std::string& username, const std::string& password);
    bool authenticateUser(const std::string& username, const std::string& password);
};