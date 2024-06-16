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

BankInterface::BankInterface(sf::Font& clsFont, sf::RectangleShape& interfaceRect, std::vector<std::string> userDetails) : 
clsFont(clsFont), interfaceRect(REGISTER_RECT_SIZE), dimRect(sf::Vector2f(WIDTH, HEIGHT)), nameBox(INTERFACE_BOX_SIZE),
 userDetails(userDetails), lastNameBox(INTERFACE_BOX_SIZE), ageBox(INTERFACE_BOX_SIZE), addressBox(INTERFACE_BOX_SIZE),
				   generateRaportBox(INTERFACE_BOX_SIZE), loginBox(INTERFACE_BOX_SIZE), balanceBox(INTERFACE_BOX_SIZE), 
		transferBox(INTERFACE_BOX_SIZE), withdrawBox(INTERFACE_BOX_SIZE), nameText("IMIE: " + userDetails[1], clsFont, FONT_SIZE),
					lastNameText("NAZ: " + userDetails[2], clsFont, FONT_SIZE), addressText("ADRES: " + userDetails[3], clsFont, FONT_SIZE),
ageText("WIEK: " + userDetails[4], clsFont, FONT_SIZE), loginText("LOGIN: " + userDetails[5], clsFont, FONT_SIZE), balanceText("$: " + userDetails[7], clsFont, FONT_SIZE),
generateRaportText("GENERUJ RAPORT", clsFont, FONT_SIZE), transferText("TRANSFER", clsFont, FONT_SIZE), 
withdrawText("WYPLAC", clsFont, FONT_SIZE) {
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
	nameText.setPosition(tempPos1);
	nameText.setFillColor(sf::Color::Black);
	tempPos1.y += 80;
	shapeInit(lastNameBox, RECT_COLOR, tempPos1, 1, OUTLINE_COLOR);
	lastNameText.setPosition(tempPos1);
	lastNameText.setFillColor(sf::Color::Black);
	tempPos1.y += 80;
	shapeInit(ageBox, RECT_COLOR, tempPos1, 1, OUTLINE_COLOR);
	ageText.setPosition(tempPos1);
	ageText.setFillColor(sf::Color::Black);
	sf::Vector2f tempPos2(500, 160);
	shapeInit(loginBox, RECT_COLOR, tempPos2, 1, OUTLINE_COLOR);
	loginText.setPosition(tempPos2);
	loginText.setFillColor(sf::Color::Black);
	tempPos2.y += 80;
	shapeInit(balanceBox, RECT_COLOR, tempPos2, 1, OUTLINE_COLOR);
	balanceText.setPosition(tempPos2);
	balanceText.setFillColor(sf::Color::Black);
	tempPos2.y += 80;
	shapeInit(transferBox, RECT_COLOR, tempPos2, 1, OUTLINE_COLOR);
	transferText.setPosition(tempPos2);
	transferText.setFillColor(sf::Color::Black);
	tempPos2.y += 80;
	shapeInit(withdrawBox, RECT_COLOR, tempPos2, 1, OUTLINE_COLOR);
	withdrawText.setPosition(tempPos2);
	withdrawText.setFillColor(sf::Color::Black);
	tempPos2.y += 80;
	shapeInit(generateRaportBox, RECT_COLOR, tempPos2, 1, OUTLINE_COLOR);
	generateRaportText.setPosition(tempPos2);
	generateRaportText.setFillColor(sf::Color::Black);
	tempPos2.x += 300;
	shapeInit(addressBox, RECT_COLOR, tempPos2, 1, OUTLINE_COLOR);
	addressText.setPosition(tempPos2);
	addressText.setFillColor(sf::Color::Black);
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
	window.draw(nameText);
	window.draw(lastNameBox);
	window.draw(lastNameText);
	window.draw(ageBox);
	window.draw(ageText);
	window.draw(generateRaportBox);
	window.draw(generateRaportText);
	window.draw(loginBox);
	window.draw(loginText);
	window.draw(balanceBox);
	window.draw(balanceText);
	window.draw(transferBox);
	window.draw(transferText);
	window.draw(withdrawBox);
	window.draw(withdrawText);
	window.draw(addressBox);
	window.draw(addressText);
	return;
}