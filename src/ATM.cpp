#include <iostream>
#include <sqlite3.h>
#include "../include/ATM.h"
#include "../include/WindowInit.h"
#include "../include/Status.h"

ATM::ATM() : five_hundred(0), two_hundred(0), one_hundred(0), fifty(0), twenty(0), ten(0), db(nullptr), users(nullptr) {
    int rc = sqlite3_open(ATM_DATABASE, &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    rc = sqlite3_open(USER_DATABASE, &users);
    if (rc) {
        std::cerr << "Can't open users database: " << sqlite3_errmsg(users) << std::endl;
        return;
    }

    const char* create_table_sql = "CREATE TABLE IF NOT EXISTS atm_table ("
        "id INTEGER PRIMARY KEY, "
        "five_hundred INTEGER, "
        "two_hundred INTEGER, "
        "one_hundred INTEGER, "
        "fifty INTEGER, "
        "twenty INTEGER, "
        "ten INTEGER);";
    char* err_msg = nullptr;
    rc = sqlite3_exec(db, create_table_sql, nullptr, nullptr, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << err_msg << std::endl;
        sqlite3_free(err_msg);
        return;
    }

    const char* insert_initial_values_sql = "INSERT INTO atm_table (id, five_hundred, two_hundred, one_hundred, fifty, twenty, ten) "
        "SELECT 1, 100, 100, 100, 100, 100, 100 "
        "WHERE NOT EXISTS (SELECT 1 FROM atm_table WHERE id = 1);";
    rc = sqlite3_exec(db, insert_initial_values_sql, nullptr, nullptr, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << err_msg << std::endl;
        sqlite3_free(err_msg);
        return;
    }

    const char* select_sql = "SELECT five_hundred, two_hundred, one_hundred, fifty, twenty, ten FROM atm_table WHERE id = 1;";
    sqlite3_stmt* stmt;

    rc = sqlite3_prepare_v2(db, select_sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        five_hundred = sqlite3_column_int(stmt, 0);
        two_hundred = sqlite3_column_int(stmt, 1);
        one_hundred = sqlite3_column_int(stmt, 2);
        fifty = sqlite3_column_int(stmt, 3);
        twenty = sqlite3_column_int(stmt, 4);
        ten = sqlite3_column_int(stmt, 5);
    }
    else {
        std::cerr << "Failed to retrieve data: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);

    const char* create_users_table_sql = "CREATE TABLE IF NOT EXISTS users ("
        "type TEXT NOT NULL, "
        "name TEXT NOT NULL, "
        "surname TEXT NOT NULL, "
        "address TEXT NOT NULL, "
        "age INTEGER NOT NULL, "
        "username TEXT NOT NULL PRIMARY KEY, "
        "password TEXT NOT NULL, "
        "balance REAL DEFAULT 0.0);";

    rc = sqlite3_exec(users, create_users_table_sql, nullptr, nullptr, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << err_msg << std::endl;
        sqlite3_free(err_msg);
        return;
    }

    const char* create_transactions_table_sql = "CREATE TABLE IF NOT EXISTS transactions ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "username TEXT NOT NULL, "
        "type TEXT NOT NULL, "
        "amount REAL NOT NULL, "
        "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP);";

    rc = sqlite3_exec(users, create_transactions_table_sql, nullptr, nullptr, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << err_msg << std::endl;
        sqlite3_free(err_msg);
        return;
    }
}

ATM::~ATM() {
    if (db) {
        sqlite3_close(db);
    }
    if (users) {
        sqlite3_close(users);
    }
}

void ATM::log_transaction(const std::string& username, const std::string& type, double amount) {
    std::string sql = "INSERT INTO transactions (username, type, amount) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(users, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(users) << std::endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, type.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 3, amount);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Failed to log transaction: " << sqlite3_errmsg(users) << std::endl;
    }

    sqlite3_finalize(stmt);
}

void ATM::show_money() {
    std::cout << "500 zl banknot: " << five_hundred << std::endl;
    std::cout << "200 zl banknot: " << two_hundred << std::endl;
    std::cout << "100 zl banknot: " << one_hundred << std::endl;
    std::cout << "50 zl banknot: " << fifty << std::endl;
    std::cout << "20 zl banknot: " << twenty << std::endl;
    std::cout << "10 zl banknot: " << ten << std::endl;
}

void ATM::welcome_screen() {
    std::cout << "Witaj. Co chcesz zrobic?: " << std::endl;
    std::cout << "(1) Zaloguj sie" << std::endl;
    std::cout << "(2) Stworz konto" << std::endl;
}

int ATM::createUser(AccountType accType, const std::string& name, const std::string& surname, const std::string& address, int age, const std::string& username, const std::string& password) {

    std::string sql = "INSERT INTO users (type, name, surname, address, age, username, password, balance) VALUES (?, ?, ?, ?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(users, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(users) << std::endl;
        return 1;
    }

    std::string accountTypeString;
    switch (accType) {
    case AccountType::CHILD_ACCOUNT:
        accountTypeString = "CHILD";
        break;
    case AccountType::STANDARD_ACCOUNT:
        accountTypeString = "ADULT";
        break;
    case AccountType::SENIOR_ACCOUNT:
        accountTypeString = "SENIOR";
        break;
    }

    if (sqlite3_bind_text(stmt, 1, accountTypeString.c_str(), -1, SQLITE_STATIC) != SQLITE_OK ||
        sqlite3_bind_text(stmt, 2, name.c_str(), -1, SQLITE_STATIC) != SQLITE_OK ||
        sqlite3_bind_text(stmt, 3, surname.c_str(), -1, SQLITE_STATIC) != SQLITE_OK ||
        sqlite3_bind_text(stmt, 4, address.c_str(), -1, SQLITE_STATIC) != SQLITE_OK ||
        sqlite3_bind_int(stmt, 5, age) != SQLITE_OK ||
        sqlite3_bind_text(stmt, 6, username.c_str(), -1, SQLITE_STATIC) != SQLITE_OK ||
        sqlite3_bind_text(stmt, 7, password.c_str(), -1, SQLITE_STATIC) != SQLITE_OK ||
        sqlite3_bind_double(stmt, 8, 0.0) != SQLITE_OK)
    {

        std::cerr << "Failed to bind values: " << sqlite3_errmsg(users) << std::endl;
        sqlite3_finalize(stmt);
        return 1;
    }

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        if (rc == SQLITE_CONSTRAINT) {
            std::cerr << "Error: Username already exists." << std::endl;
        }
        else {
            std::cerr << "Execution failed: " << sqlite3_errmsg(users) << std::endl;
        }
        sqlite3_finalize(stmt);
        return 1;
    }
    else {
        std::cout << "Inserted value successfully" << std::endl;
    }

    sqlite3_finalize(stmt);
    return 0;
}

bool ATM::authenticateUser(const std::string& username, const std::string& password) {
    std::string sql = "SELECT * FROM users WHERE username = ? AND password = ?";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(users, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(users) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    int stepResult = sqlite3_step(stmt);
    bool authenticated = (stepResult == SQLITE_ROW);
    sqlite3_finalize(stmt);
    return authenticated;
}

std::vector<std::string> ATM::getUserCredentials(const std::string& login, const std::string& password) {
    if (!authenticateUser(login, password)) {
        throw std::string("Trying to breach the database");
        return std::vector<std::string>(0);
    }
    else {
        std::string sql = "SELECT type, name, surname, address, age, username, password, balance FROM users WHERE username = ?;";
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(users, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            std::cerr << "SQL error: " << sqlite3_errmsg(users) << std::endl;
            return std::vector<std::string>(0);
        }
        std::vector<std::string>userDetails(8);
        sqlite3_bind_text(stmt, 1, login.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            userDetails[0] = (const char*) sqlite3_column_text(stmt, 0); // type
            userDetails[1] = (const char*) sqlite3_column_text(stmt, 1); // name
            userDetails[2] = (const char*) sqlite3_column_text(stmt, 2); // surname
            userDetails[3] = (const char*) sqlite3_column_text(stmt, 3); // address
            userDetails[4] = std::to_string(sqlite3_column_int(stmt, 4));                // age
            userDetails[5] = (const char*) sqlite3_column_text(stmt, 5); // username
            userDetails[6] = (const char*) sqlite3_column_text(stmt, 6); // password
            userDetails[7] = std::to_string(sqlite3_column_double(stmt, 7));              // balance
        }
        else {
            std::cerr << "No user found with the given credentials" << std::endl;
            return std::vector<std::string>(0);
        }
        sqlite3_finalize(stmt);
        return userDetails;
    }
}

void ATM::updateBalance(const std::string& username) {
    std::string check_balance_sql = "SELECT balance FROM users WHERE username = ?";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(users, check_balance_sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(users) << std::endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

    // Wykonanie zapytania
    int stepResult = sqlite3_step(stmt);
    if (stepResult == SQLITE_ROW) {
        double balance = sqlite3_column_double(stmt, 0);
        std::cout << "Saldo uzytkownika " << username << " wynosi: " << balance << " zz" << std::endl;
    }
    else {
        std::cerr << "Blad: Nie mozna pobrac salda dla uzytkownika " << username << std::endl;
    }
    sqlite3_finalize(stmt);
}

void ATM::transfer(std::string sender_username, std::string recipient_username, double amount) {

    std::cout << sender_username << " " << recipient_username << " " << amount << std::endl;

    if (amount <= 0) {
        std::cerr << "Kwota przelewu musi byc wieksza niz zero." << std::endl;
        return;
    }

    sqlite3_exec(users, "BEGIN TRANSACTION;", nullptr, nullptr, nullptr);

    std::string check_balance_sql = "SELECT balance FROM users WHERE username = ?";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(users, check_balance_sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(users) << std::endl;
        sqlite3_exec(users, "ROLLBACK;", nullptr, nullptr, nullptr);
        return;
    }

    sqlite3_bind_text(stmt, 1, sender_username.c_str(), -1, SQLITE_STATIC);

    int stepResult = sqlite3_step(stmt);
    if (stepResult != SQLITE_ROW) {
        std::cerr << "Bład: Nie znaleziono nadawcy o nazwie uzytkownika " << sender_username << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_exec(users, "ROLLBACK;", nullptr, nullptr, nullptr);
        return;
    }

    double sender_balance = sqlite3_column_double(stmt, 0);
    sqlite3_finalize(stmt);

    if (sender_balance < amount) {
        std::cerr << "Blad: Niewystarczajace saldo." << std::endl;
        sqlite3_exec(users, "ROLLBACK;", nullptr, nullptr, nullptr);
        return;
    }

    sqlite3_prepare_v2(users, check_balance_sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, recipient_username.c_str(), -1, SQLITE_STATIC);

    stepResult = sqlite3_step(stmt);
    if (stepResult != SQLITE_ROW) {
        std::cerr << "Blad: Nie znaleziono odbiorcy o nazwie uzytkownika " << recipient_username << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_exec(users, "ROLLBACK;", nullptr, nullptr, nullptr);
        return;
    }

    sqlite3_finalize(stmt);

    std::string update_sender_balance_sql = "UPDATE users SET balance = balance - ? WHERE username = ?";
    if (sqlite3_prepare_v2(users, update_sender_balance_sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(users) << std::endl;
        sqlite3_exec(users, "ROLLBACK;", nullptr, nullptr, nullptr);
        return;
    }

    sqlite3_bind_double(stmt, 1, amount);
    sqlite3_bind_text(stmt, 2, sender_username.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Blad: Nie udalo sie zaktualizowac salda nadawcy." << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_exec(users, "ROLLBACK;", nullptr, nullptr, nullptr);
        return;
    }

    sqlite3_finalize(stmt);

    std::string update_recipient_balance_sql = "UPDATE users SET balance = balance + ? WHERE username = ?";
    if (sqlite3_prepare_v2(users, update_recipient_balance_sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(users) << std::endl;
        sqlite3_exec(users, "ROLLBACK;", nullptr, nullptr, nullptr);
        return;
    }

    sqlite3_bind_double(stmt, 1, amount);
    sqlite3_bind_text(stmt, 2, recipient_username.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Blad: Nie udalo sie zaktualizowac salda odbiorcy." << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_exec(users, "ROLLBACK;", nullptr, nullptr, nullptr);
        return;
    }

    sqlite3_finalize(stmt);

    sqlite3_exec(users, "COMMIT;", nullptr, nullptr, nullptr);

    log_transaction(sender_username, "transfer out", amount);
    log_transaction(recipient_username, "transfer in", amount);

    std::cout << "Przelew w wysokosci " << amount << " zl od " << sender_username << " do " << recipient_username << " zostal pomyslnie zrealizowany." << std::endl;
}

void ATM::withdraw(const std::string& username, double& amount) {
    if (amount <= 0) {
        std::cerr << "Kwota wyplaty musi byc wieksza od 0." << std::endl;
        return;
    }

    sqlite3_exec(users, "BEGIN TRANSACTION;", nullptr, nullptr, nullptr);

    std::string check_balance_sql = "SELECT balance FROM users WHERE username = ?";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(users, check_balance_sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(users) << std::endl;
        sqlite3_exec(users, "ROLLBACK;", nullptr, nullptr, nullptr);
        return;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

    int stepResult = sqlite3_step(stmt);
    if (stepResult != SQLITE_ROW) {
        std::cerr << "Error: User not found." << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_exec(users, "ROLLBACK;", nullptr, nullptr, nullptr);
        return;
    }

    double current_balance = sqlite3_column_double(stmt, 0);
    sqlite3_finalize(stmt);

    if (current_balance < amount) {
        std::cerr << "Error: Insufficient balance." << std::endl;
        sqlite3_exec(users, "ROLLBACK;", nullptr, nullptr, nullptr);
        return;
    }

    std::string update_balance_sql = "UPDATE users SET balance = balance - ? WHERE username = ?";
    if (sqlite3_prepare_v2(users, update_balance_sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(users) << std::endl;
        sqlite3_exec(users, "ROLLBACK;", nullptr, nullptr, nullptr);
        return;
    }

    sqlite3_bind_double(stmt, 1, amount);
    sqlite3_bind_text(stmt, 2, username.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Error: Failed to update balance." << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_exec(users, "ROLLBACK;", nullptr, nullptr, nullptr);
        return;
    }

    sqlite3_finalize(stmt);

    sqlite3_exec(users, "COMMIT;", nullptr, nullptr, nullptr);

    log_transaction(username, "withdrawal", amount);

    std::cout << "Withdrawal successful!" << std::endl;
}

void ATM::deposit(const std::string& username, double amount) {


    std::string sql = "UPDATE users SET balance = balance + ? WHERE username = ?";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(users, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(users) << std::endl;
        return;
    }

    sqlite3_bind_double(stmt, 1, amount);
    sqlite3_bind_text(stmt, 2, username.c_str(), -1, SQLITE_STATIC);

    int stepResult = sqlite3_step(stmt);
    if (stepResult != SQLITE_DONE) {
        std::cerr << "SQL error: " << sqlite3_errmsg(users) << std::endl;
        sqlite3_finalize(stmt);
        return;
    }

    sqlite3_finalize(stmt);
    log_transaction(username, "deposit", amount);
    std::cout << "Deposit successful!" << std::endl;
}




std::string ATM::generate_report(const std::string& username) {
    std::string sql = "SELECT type, amount, timestamp FROM transactions WHERE username = ? ORDER BY timestamp DESC;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(users, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(users) << std::endl;
        return "";
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

    std::ostringstream report;
    report << "Transaction report for " << username << ":\n";
    report << "Type\t\tAmount\t\tTimestamp\n";
    report << "-------------------------------------------\n";

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        double amount = sqlite3_column_double(stmt, 1);
        std::string timestamp = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

        // Format the amount to 2 decimal places
        std::ostringstream amountStream;
        amountStream << std::fixed << std::setprecision(2) << amount;

        report << type << "\t" << amountStream.str() << "\t" << timestamp << "\n";
    }

    sqlite3_finalize(stmt);
    return report.str();
}
