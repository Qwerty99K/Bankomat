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

    regRect.setFillColor(sf::Color::White);
    regRect.setSize(sf::Vector2f(WIDTH - 400, HEIGHT - 200));
    regRect.setPosition(200, 100); // polowa przesuniec

    // Create text for options
    logText.setFont(menuFont);
    logText.setString("Login");
    logText.setCharacterSize(FONT_SIZE);
    logText.setFillColor(sf::Color::Black);

    regText.setFont(menuFont);
    regText.setString("Register");
    regText.setCharacterSize(FONT_SIZE);
    regText.setFillColor(sf::Color::Black);

    exitText.setFont(menuFont);
    exitText.setString("Exit");
    exitText.setCharacterSize(FONT_SIZE);
    exitText.setFillColor(sf::Color::Black);

    passText.setFont(menuFont);
    passText.setString("Password");
    passText.setCharacterSize(FONT_SIZE);
    passText.setFillColor(sf::Color::Black);

    // Set position for options
    scrPosition = sf::Vector2f(WIDTH / 2, HEIGHT / 2);
    sf::Vector2f relativePos(scrPosition.x - bgRectSize.x / 2, scrPosition.y - bgRectSize.y / 2);
    // Set positions
    logRect.setSize(bgRectSize);
    logRect.setFillColor(sf::Color::White); // White with 150 alpha (semi-transparent)
    logRect.setPosition(relativePos);
    
    // dac for loop / uproscic jakos koncowo
    // lepiej skopiowac te same parametry, prostsze.
    // stworzyc to niezalezne od siebie
    relativePos.y += 50;
    relativePos.x += buttonSizes.x / 2;
    logButton.setSize(buttonSizes);
    logButton.setFillColor(sf::Color::White);
    logButton.setOutlineThickness(1);
    logButton.setOutlineColor(sf::Color::Black);
    logButton.setPosition(relativePos);
    // relativePos.y += 25;
    logText.setPosition(relativePos);

    relativePos.y += 50 + buttonSizes.y;
    regButton.setSize(buttonSizes);
    regButton.setFillColor(sf::Color::White);
    regButton.setOutlineThickness(1);
    regButton.setOutlineColor(sf::Color::Black);
    regButton.setPosition(relativePos);
    regText.setPosition(relativePos);

    relativePos.y += 50 + buttonSizes.y;
    exitButton.setSize(buttonSizes);
    exitButton.setOutlineThickness(1);
    exitButton.setOutlineColor(sf::Color::Black);
    exitButton.setFillColor(sf::Color::White);
    exitButton.setPosition(relativePos);
    exitText.setPosition(relativePos);


    sf::Vector2u logRectPos(logRect.getPosition());
    loginBox.setSize(buttonSizes);
    loginBox.setFillColor(sf::Color::White);
    loginBox.setOutlineThickness(1);
    loginBox.setPosition(logRectPos.x + buttonSizes.x / 2, logRectPos.y + buttonSizes.y / 2 + 50);
    loginBox.setOutlineColor(sf::Color::Black);

    passwordBox.setSize(buttonSizes);
    passwordBox.setFillColor(sf::Color::White);
    passwordBox.setOutlineThickness(1);
    passwordBox.setPosition(logRectPos.x + buttonSizes.x / 2, logRectPos.y + buttonSizes.y / 2 + 175);
    passwordBox.setOutlineColor(sf::Color::Black);

}

// wrzucic set positions tu
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
                    regMenuInit();
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

        window.draw(logRect);
        window.draw(logButton);
        window.draw(logText);

        window.draw(regButton);
        window.draw(regText);

        window.draw(exitButton);
        window.draw(exitText);
        window.display();
    }
}

// dodac loading ??

void WindowInit::loginMenuInit() {
    window.clear(sf::Color::White);
    /*loginBox.setPosition(logRectPos.x + buttonSizes.x / 2, logRectPos.y + buttonSizes.y / 2 + 50);
    registerBox.setPosition(logRectPos.x + buttonSizes.x / 2, logRectPos.y + buttonSizes.y / 2 + 50);*/
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.draw(menuBackground); // przesunac na lepszy
        window.draw(dimRect);
        window.draw(logRect);
        window.draw(loginBox);
        window.draw(passwordBox);
        window.display();
    }
}

void WindowInit::regMenuInit() {
    window.clear(sf::Color::White);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.draw(menuBackground); // przesunac na lepszy
        window.draw(dimRect);
        window.draw(regRect);


        window.display();
    }
}