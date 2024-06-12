#pragma once
#include <stdio.h>
#include <iostream>
#include <sqlite3.h>
#define DATABASE_PATH "../Bankomat/resources/USERS_DATABASE.db" // chujowy pomysl z absolutna sciezka, ale dziala

enum class AccountType {
    STANDARD_ACCOUNT,
    CHILD_ACCOUNT,
    SENIOR_ACCOUNT,
};

int createEntry(const AccountType&, const std::string&, const std::string&, const std::string&,
    const std::string&, const std::string&, const double&, const std::string&);

int readEntry(const AccountType&, const std::string&, const std::string&);
