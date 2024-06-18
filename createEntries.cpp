//#include <stdio.h>
//#include <iostream>
//#include <sqlite3.h>
//#include "../include/createEntries.h"
//
//static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
//    for (int i = 0; i < argc; i++) {
//        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
//    }
//    printf("\n");
//    return 0;
//}
//
//int createEntry(const AccountType& accType, const std::string& id, const std::string& password, const std::string& name,
//    const std::string& lastName, const std::string& address, const double& balance, const std::string& age) {
//    sqlite3* db;
//    const char* accTable;
//
//    switch (accType) {
//    case AccountType::STANDARD_ACCOUNT:
//        accTable = "STANDARD_ACCOUNT";
//        break;
//    case AccountType::CHILD_ACCOUNT:
//        accTable = "CHILD_ACCOUNT";
//        break;
//    case AccountType::SENIOR_ACCOUNT:
//        accTable = "SENIOR_ACCOUNT";
//        break;
//    default:
//        fprintf(stderr, "Invalid account type\n");
//        return 1;
//    }
//
//    // Create the table creation SQL statement
//    std::string tableSQLite = "CREATE TABLE IF NOT EXISTS " + std::string(accTable) + " ("
//        "  ID TEXT              NOT NULL, "
//        "  PASSWORD TEXT        NOT NULL, "
//        "  NAME TEXT            NOT NULL, "
//        "  LAST_NAME TEXT       NOT NULL, "
//        "  ADDRESS TEXT         NOT NULL, "
//        "  BALANCE NUMERIC      NOT NULL, "
//        "  AGE TEXT             NOT NULL"
//        ");";
//
//    std::string insertSQL =
//        "INSERT INTO " + std::string(accTable) + " (ID, PASSWORD, NAME, LAST_NAME, ADDRESS, BALANCE, AGE) "
//        "VALUES (?, ?, ?, ?, ?, ?, ?);";
//
//    char* zErrMsg = 0;
//    int rc;
//
//    // Open the database
//    rc = sqlite3_open(DATABASE_PATH, &db);
//    if (rc) {
//        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
//        return 1;
//    }
//
//    // Execute table creation statement
//    rc = sqlite3_exec(db, tableSQLite.c_str(), callback, 0, &zErrMsg);
//    if (rc != SQLITE_OK) {
//        fprintf(stderr, "SQL error: %s\n", zErrMsg);
//        sqlite3_free(zErrMsg);
//        sqlite3_close(db);
//        return 1;
//    }
//
//    // Prepare the insert statement
//    sqlite3_stmt* stmt;
//    rc = sqlite3_prepare_v2(db, insertSQL.c_str(), -1, &stmt, 0);
//    if (rc != SQLITE_OK) {
//        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
//        sqlite3_close(db);
//        return 1;
//    }
//
//    // Bind parameters
//    sqlite3_bind_text(stmt, 1, id.c_str(), -1, SQLITE_STATIC);
//    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
//    sqlite3_bind_text(stmt, 3, name.c_str(), -1, SQLITE_STATIC);
//    sqlite3_bind_text(stmt, 4, lastName.c_str(), -1, SQLITE_STATIC);
//    sqlite3_bind_text(stmt, 5, address.c_str(), -1, SQLITE_STATIC);
//    sqlite3_bind_double(stmt, 6, balance);
//    sqlite3_bind_text(stmt, 7, age.c_str(), -1, SQLITE_STATIC);
//
//    // Execute the statement
//    rc = sqlite3_step(stmt);
//    if (rc != SQLITE_DONE) {
//        fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
//        sqlite3_finalize(stmt);
//        sqlite3_close(db);
//        return 1;
//    }
//
//    // Finalize and close
//    sqlite3_finalize(stmt);
//    sqlite3_close(db);
//    return 0;
//}
//
//
//// zhashowac te dane potem -> po hashu dopiero ta funkcja jest dostaje
//static int selectCallback(void* data, int argc, char** argv, char** azColName) {
//    bool* passwordMatch = static_cast<bool*>(data);
//    if (argc > 0) {
//        std::string retrievedPassword = argv[0] ? argv[0] : "";
//        std::string providedPassword = reinterpret_cast<char*>(data); // Provided password passed as data
//        *passwordMatch = (retrievedPassword == providedPassword);
//    }
//    return 0;
//}
//
//int readEntry(const AccountType& accType, const std::string& id, const std::string& password) {
//    sqlite3* db;
//    const char* accTable;
//
//    switch (accType) {
//    case AccountType::STANDARD_ACCOUNT:
//        accTable = "STANDARD_ACCOUNT";
//        break;
//    case AccountType::CHILD_ACCOUNT:
//        accTable = "CHILD_ACCOUNT";
//        break;
//    case AccountType::SENIOR_ACCOUNT:
//        accTable = "SENIOR_ACCOUNT";
//        break;
//    default:
//        std::cerr << "Invalid account type\n";
//        return 1;
//    }
//
//    // Open the database
//    int rc = sqlite3_open(DATABASE_PATH, &db);
//    if (rc) {
//        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
//        return 1;
//    }
//
//    // Create the SQL select statement
//    std::string selectSQL = "SELECT PASSWORD FROM " + std::string(accTable) + " WHERE ID = ?;";
//
//    // Prepare the select statement
//    sqlite3_stmt* stmt;
//    rc = sqlite3_prepare_v2(db, selectSQL.c_str(), -1, &stmt, 0);
//    if (rc != SQLITE_OK) {
//        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
//        sqlite3_close(db);
//        return 1;
//    }
//
//    // Bind the ID parameter
//    sqlite3_bind_text(stmt, 1, id.c_str(), -1, SQLITE_STATIC);
//
//    // Execute the statement and check the password
//    bool passwordMatch = false;
//    while (sqlite3_step(stmt) == SQLITE_ROW) {
//        const unsigned char* dbPassword = sqlite3_column_text(stmt, 0);
//        if (dbPassword && password == reinterpret_cast<const char*>(dbPassword)) {
//            passwordMatch = true;
//        }
//    }
//
//    // Finalize and close
//    sqlite3_finalize(stmt);
//    sqlite3_close(db);
//
//    return passwordMatch ? 0 : 1;
//}