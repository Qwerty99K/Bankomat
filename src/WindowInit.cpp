#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "../include/WindowInit.h"
#include <iostream>
#include <stdexcept>

WindowInit::WindowInit() : window(sf::VideoMode(WIDTH, HEIGHT), MAIN_NAME) {
    window.setVerticalSyncEnabled(true);

    if (!menuBGTexture.loadFromFile(BG_PATH)) {
        throw std::runtime_error("Cannot load the texture.");
    }
    menuBackground.setTexture(menuBGTexture);
    menuBackground.setScale(BG_WIDTH_SCALE, BG_HEIGHT_SCALE);

    if (!bankIcoTexture.loadFromFile(BANK_ICO_PATH)) {
        throw std::runtime_error("Cannot load the texture.");
    }
    bankIcoTexture.setSmooth(true);

    bankIco.setTexture(bankIcoTexture);
    bankIco.setScale(BANK_SCALE, BANK_SCALE);
    bankIco.setPosition(sf::Vector2f(BANK_POS, BANK_POS)); // absolute position

    bankIcoSz = bankIcoTexture.getSize();

    if (!menuFont.loadFromFile(FONT_PATH)) {
        throw std::runtime_error("Cannot load the font.");
    }
    bankName.setFont(menuFont);
    bankName.setString(BANK_NAME);
    bankName.setCharacterSize(30);
    bankName.setFillColor(sf::Color::Red);
    bankName.setPosition(BANK_POS + (bankIcoSz.x * BANK_SCALE) / 2 + X_NAME_POS, BANK_POS + (bankIcoSz.y * BANK_SCALE) / 2);

    dimRect.setSize(sf::Vector2f(WIDTH, HEIGHT));
    dimRect.setFillColor(sf::Color(0, 0, 0, 150)); // Semi-transparent black

    // Create text for options
    logText.setFont(menuFont);
    logText.setString("Zaloguj sie");
    logText.setCharacterSize(30);

    regText.setFont(menuFont);
    regText.setString("Rejestracja");
    regText.setCharacterSize(30);

    exitText.setFont(menuFont);
    exitText.setString("Wyjdz");
    exitText.setCharacterSize(30);

    // Set position for options
    scrPosition = sf::Vector2f(WIDTH / 2 - 75, HEIGHT / 2);

    // Set positions
    bgButton.setSize(sf::Vector2f(400, 300));
    bgButton.setFillColor(sf::Color(253, 233, 236, 150)); // White with 150 alpha (semi-transparent)
    bgButton.setPosition(scrPosition);

    logButton.setSize(sf::Vector2f(225, 75));
    logButton.setFillColor(sf::Color::Green);
    logButton.setPosition(scrPosition);
    logText.setPosition(scrPosition);

    scrPosition.y += 100;
    regButton.setSize(sf::Vector2f(200, 50));
    regButton.setFillColor(sf::Color::Blue);
    regButton.setPosition(scrPosition);
    regText.setPosition(scrPosition);

    scrPosition.y += 100;
    exitButton.setSize(sf::Vector2f(200, 50));
    exitButton.setFillColor(sf::Color::Red);
    exitButton.setPosition(scrPosition);
    exitText.setPosition(scrPosition);
}

void WindowInit::menuInit() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonPressed:
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (logText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    std::cout << "LOGIN clicked!" << std::endl;
                    loginMenuInit();
                }
                else if (regText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    std::cout << "REGISTER clicked!" << std::endl;
                }
                else if (exitText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    window.close();
                }
                break;
            }
        }
        window.clear(sf::Color::White);

        window.draw(menuBackground); // przesunac na lepszy
        window.draw(dimRect);
        window.draw(bankIco);
        window.draw(bankName);

        window.draw(bgButton);
        window.draw(logButton);
        window.draw(logText);

        window.draw(regButton);
        window.draw(regText);

        window.draw(exitButton);
        window.draw(exitText);
        window.display();
    }
}

void WindowInit::loginMenuInit() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.display();
    }
}
