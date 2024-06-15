#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "../include/WindowInit.h"
#include "../include/BankInterface.h"
#include "../include/StandardAccount.h"
#include "../include/ChildAccount.h"
#include "../include/SeniorAccount.h"
#include "../include/Status.h"
#include <iostream>
#include <stdexcept>
#include <vector>

BankInterface::BankInterface(sf::Font& clsFont, sf::RectangleShape& interfaceRect) : clsFont(clsFont), interfaceRect(REGISTER_RECT_SIZE),
dimRect(sf::Vector2f(WIDTH, HEIGHT)), nameBox(INTERFACE_BOX_SIZE),
lastNameBox(INTERFACE_BOX_SIZE), ageBox(INTERFACE_BOX_SIZE),
generateRaportBox(INTERFACE_BOX_SIZE), loginBox(INTERFACE_BOX_SIZE),
balanceBox(INTERFACE_BOX_SIZE), transferBox(INTERFACE_BOX_SIZE),
withdrawBox(INTERFACE_BOX_SIZE) {
	if (!bgBankT.loadFromFile(BACKGROUND_PATH)) {
		throw std::string("Nothing to load");
	}
	else {
		bgBankT.setSmooth(true);
	}
	if (!profilePictureT.loadFromFile(PROFILE_PATH)) {
		throw std::string("Nothing to load");
	}
	else {
		profilePictureT.setSmooth(true);
	}

	bgBank.setTexture(bgBankT);
	bgBank.setScale(BACKGROUND_WIDTH, BACKGROUND_HEIGHT);
	profilePicture.setTexture(profilePictureT);
	profilePicture.setScale(PROFILE_SCALE);
	dimRect.setFillColor(DIM_RECT);
	
}
void BankInterface::setInterface() {
	sf::Vector2f tempPos1(100, 100);
	interfaceRect.setPosition(tempPos1);
	tempPos1.x += 60; tempPos1.y += 40;
	profilePicture.setPosition(tempPos1);
	tempPos1.y += 250;
	shapeInit(nameBox, RECT_COLOR, tempPos1, 1, OUTLINE_COLOR);
	tempPos1.y += 80;
	shapeInit(lastNameBox, RECT_COLOR, tempPos1, 1, OUTLINE_COLOR);
	tempPos1.y += 80;
	shapeInit(ageBox, RECT_COLOR, tempPos1, 1, OUTLINE_COLOR);
	sf::Vector2f tempPos2(500, 160);
	shapeInit(loginBox, RECT_COLOR, tempPos2, 1, OUTLINE_COLOR);
	tempPos2.y += 80;
	shapeInit(balanceBox, RECT_COLOR, tempPos2, 1, OUTLINE_COLOR);
	tempPos2.y += 80;
	shapeInit(transferBox, RECT_COLOR, tempPos2, 1, OUTLINE_COLOR);
	tempPos2.y += 80;
	shapeInit(withdrawBox, RECT_COLOR, tempPos2, 1, OUTLINE_COLOR);
	tempPos2.y += 80;
	shapeInit(generateRaportBox, RECT_COLOR, tempPos2, 1, OUTLINE_COLOR);
}

void BankInterface::showInterface(sf::RenderWindow& window) {
	setInterface();
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
		window.clear(sf::Color::White);
		drawInterface(window);
		window.display();
	}
}

void BankInterface::drawInterface(sf::RenderWindow& window) {
	window.draw(bgBank);
	window.draw(dimRect);
	window.draw(interfaceRect);
	window.draw(profilePicture);
	window.draw(nameBox);
	window.draw(lastNameBox);
	window.draw(ageBox);
	window.draw(generateRaportBox);
	window.draw(loginBox);
	window.draw(balanceBox);
	window.draw(transferBox);
	window.draw(withdrawBox);
}