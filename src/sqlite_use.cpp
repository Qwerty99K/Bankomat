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
    char** argv = new char*[argc];
    argv[0] = new char[std::strlen(DATABASE_NAME) + 1];
    std::strcpy(argv[0], DATABASE_NAME);

    const char* tableSQLite = 
        "CREATE TABLE[SENIOR_USERS]("
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
    argv[1] = new char[std::strlen(tableSQLite) + 1];
    std::strcpy(argv[1], DATABASE_NAME);
    argv[2] = '\0';

    char* zErrMsg = 0;
    int rc;
    if (argc != 3) {
        fprintf(stderr, "Usage: %s DATABASE SQL-STATEMENT\n", argv[0]);
        return 1;
    }
    rc = sqlite3_open(argv[0], &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    rc = sqlite3_exec(db, argv[1], callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(db);
}


