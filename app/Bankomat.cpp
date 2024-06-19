#include <iostream>
#include "../include/StandardAccount.h"
#include "../include/SeniorAccount.h"
#include "../include/WindowInit.h"
#include "../include/ATM.h"

int main() {
	sf::Font font;
	if (!font.loadFromFile(FONT_PATH)) {
		throw std::string("Nothing to load.");
	}
	WindowInit* window = new WindowInit(font);
	window->menuSiteAccessor();

	delete window; window = nullptr;
	return 0;
}
