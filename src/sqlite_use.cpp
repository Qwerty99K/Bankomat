#include <stdio.h>
#include <iostream>
#include <sqlite3.h>
#include "../include/sqlite_use.h"

static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    int i;
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int createDatabase() {
    sqlite3* db;
    constexpr int argc = 3;
    const char* tableSQLite = 
        "CREATE TABLE[THIS_IS_TEST_TABLE2]("
            "  [ID] TEXT NOT NULL"
            ", [NAME] TEXT NOT NULL"
            ", [LAST_NAME] TEXT NOT NULL"
            ", [ADDRESS] TEXT NOT NULL"
            ", [BALANCE] NUMERIC NOT NULL"
            ", [AGE] NUMERIC NOT NULL"
            ", [LIMIT] NUMERIC NOT NULL"
            ", [LOGIN] TEXT NOT NULL"
            ", [PASSWORD] TEXT NOT NULL"
            ", CONSTRAINT[PK_STANDARD_USERS] PRIMARY KEY([ID])"
            "); ";
    char* zErrMsg = 0;
    int rc;
    if (argc != 3) {
        fprintf(stderr, "Usage: %s DATABASE SQL-STATEMENT\n", DATABASE_PATH);
        return 1;
    }
    rc = sqlite3_open(DATABASE_PATH, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    rc = sqlite3_exec(db, tableSQLite, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(db);
}


