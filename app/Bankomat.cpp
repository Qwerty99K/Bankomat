#include <iostream>
#include "../include/StandardAccount.h"
#include "../include/SeniorAccount.h"
#include "../tests/importTests.h"
#include "../include/sqlite_use.h"
#include "../include/WindowInit.h"

int main() {
	sf::Font font;
	if (!font.loadFromFile(FONT_PATH)) {
		throw std::string("Nothing to load.");
	}
	WindowInit* window = new WindowInit(BACKGROUND_PATH, font);
	MenuInit* menu_window = new MenuInit(window->bgPath, window->menuFont);
	menu_window->showMenu();
	return 0;
}

// poprawic scalowanie na fullscreenie, 
// numer konta
// zhashowac potem te dane
// powiadomienia - zobaczy sie potem, jak bedziemy czytac dane (kazdy przelew daje ping?)
// dodac limity na wyplaty / wplaty.
// sprawdzic jakie funkcjonalnosci ma bank xd