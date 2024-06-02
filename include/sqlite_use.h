#pragma once
#include <stdio.h>
#include <iostream>
#include <sqlite3.h>
#define DATABASE_PATH "../Bankomat/resources/USERS_DATABASE.db" // chujowy pomysl z absolutna sciezka, ale dziala

int createDatabase();
