#include <iostream>
#include "../include/StandardAccount.h"
#include "../include/SeniorAccount.h"
#include "../tests/importTests.h"
#include "../include/sqlite_use.h"
#include "../include/WindowInit.h"

int main() {
	WindowInit* menu = new WindowInit();
	menu->menuInit();
	return 0;
}

// poprawic scalowanie na fullscreenie, 
// numer konta
// zhashowac potem te dane
// powiadomienia - zobaczy sie potem, jak bedziemy czytac dane (kazdy przelew daje ping?)
// dodac limity na wyplaty / wplaty.
// sprawdzic jakie funkcjonalnosci ma bank xd