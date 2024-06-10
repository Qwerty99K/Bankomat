#pragma once
#include <stdio.h>
#include <iostream>
#include <sqlite3.h>
#define DATABASE_PATH "../Bankomat/resources/USERS_DATABASE.db" // chujowy pomysl z absolutna sciezka, ale dziala
#include "../include/StandardAccount.h"

class ATM
{
private:
	int five_hundred;
	int two_hundred;
	int one_hundred;
	int fifty;
	int twenty;
	int ten;
	sqlite3* db;

public:
	ATM();
	~ATM();
	void show_money();

};


