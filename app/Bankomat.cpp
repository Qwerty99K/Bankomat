#include <iostream>
#include "../include/StandardAccount.h"
#include "../include/SeniorAccount.h"
#include "../tests/importTests.h"
#include "../include/sqlite_use.h"
int main() {
	//assertValues();
	createDatabase();
	// baza nie dziala
	return 0;
}

// numer konta
// zhashowac potem te dane
// powiadomienia - zobaczy sie potem, jak bedziemy czytac dane (kazdy przelew daje ping?)
// dodac limity na wyplaty / wplaty.
// sprawdzic jakie funkcjonalnosci ma bank xd