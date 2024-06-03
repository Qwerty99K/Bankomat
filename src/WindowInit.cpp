#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "../include/WindowInit.h"
#include <iostream>
#include <stdexcept>
#include <vector>


WindowInit::WindowInit() : window(sf::VideoMode(WIDTH, HEIGHT), MAIN_NAME) {
    const sf::Vector2f bgRectSize(BGRECT_WIDTH, BGRECT_HEIGHT);
    const sf::Vector2f buttonSizes(BGRECT_WIDTH / 2, BUTTON_HEIGHT);

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
    bankName.setCharacterSize(FONT_SIZE);
    bankName.setFillColor(sf::Color::Red);
    bankName.setPosition(BANK_POS + (bankIcoSz.x * BANK_SCALE) / 2 + X_NAME_POS, BANK_POS + (bankIcoSz.y * BANK_SCALE) / 2 - FONT_SIZE / 2);

    dimRect.setSize(sf::Vector2f(WIDTH, HEIGHT));
    dimRect.setFillColor(sf::Color(0, 0, 0, 150)); // Semi-transparent black

    // Create text for options
    logText.setFont(menuFont);
    logText.setString("Logowanie");
    logText.setCharacterSize(FONT_SIZE);

    regText.setFont(menuFont);
    regText.setString("Rejestracja");
    regText.setCharacterSize(FONT_SIZE);

    exitText.setFont(menuFont);
    exitText.setString("Wyjscie");
    exitText.setCharacterSize(FONT_SIZE);

    // Set position for options
    scrPosition = sf::Vector2f(WIDTH / 2, HEIGHT / 2);
    sf::Vector2f relativePos(scrPosition.x - bgRectSize.x / 2, scrPosition.y - bgRectSize.y / 2);
    // Set positions
    bgRect.setSize(bgRectSize);
    bgRect.setFillColor(sf::Color(253, 233, 236, 120)); // White with 150 alpha (semi-transparent)
    bgRect.setPosition(relativePos);
    
    // dac for loop / uproscic jakos koncowo
    relativePos.y += 50;
    relativePos.x += buttonSizes.x / 2;
    logButton.setSize(buttonSizes);
    logButton.setFillColor(sf::Color(253, 233, 236, 100));
    logButton.setPosition(relativePos);
    logText.setPosition(relativePos);

    relativePos.y += 75 + buttonSizes.y;
    regButton.setSize(buttonSizes);
    regButton.setFillColor(sf::Color(253, 233, 236, 100));
    regButton.setPosition(relativePos);
    regText.setPosition(relativePos);

    relativePos.y += 75 + buttonSizes.y;
    exitButton.setSize(buttonSizes);
    exitButton.setFillColor(sf::Color(253, 233, 236, 100));
    exitButton.setPosition(relativePos);
    exitText.setPosition(relativePos);
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

        window.draw(bgRect);
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
        window.clear(sf::Color::White);
        window.draw(menuBackground); // przesunac na lepszy
        window.draw(dimRect);
        window.draw(bgRect);

        window.display();
    }
}
