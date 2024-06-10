#include "../include/ATM.h"

ATM::ATM() : five_hundred(0), two_hundred(0), one_hundred(0), fifty(0), twenty(0), ten(0), db(nullptr) {
    int rc = sqlite3_open("atm.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    // Create table if it doesn't exist
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

    // Insert initial values if table is empty
    const char* insert_initial_values_sql = "INSERT INTO atm_table (id, five_hundred, two_hundred, one_hundred, fifty, twenty, ten) "
        "SELECT 1, 100, 200, 300, 400, 500, 600 "
        "WHERE NOT EXISTS (SELECT 1 FROM atm_table WHERE id = 1);";
    rc = sqlite3_exec(db, insert_initial_values_sql, nullptr, nullptr, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << err_msg << std::endl;
        sqlite3_free(err_msg);
        return;
    }

    // Retrieve the values from the database
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
}

ATM::~ATM() {
    if (db) {
        sqlite3_close(db);
    }
}

void ATM::show_money() {
    std::cout << "500 notes: " << five_hundred << std::endl;
    std::cout << "200 notes: " << two_hundred << std::endl;
    std::cout << "100 notes: " << one_hundred << std::endl;
    std::cout << "50 notes: " << fifty << std::endl;
    std::cout << "20 notes: " << twenty << std::endl;
    std::cout << "10 notes: " << ten << std::endl;
}
