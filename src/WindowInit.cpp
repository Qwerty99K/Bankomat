#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "../include/WindowInit.h"
#include <iostream>
#include <stdexcept>
#include <vector>


WindowInit::WindowInit() : window(sf::VideoMode(WIDTH, HEIGHT), MAIN_NAME) {
    window.setVerticalSyncEnabled(true);
    TexturesInit();
    FontsInit();
    ShapesInit();
    TextInit();
    setMenuPos();
}

void WindowInit::TexturesInit() {
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
    bankIcoSz = bankIcoTexture.getSize();
}

void WindowInit::FontsInit() {
    if (!menuFont.loadFromFile(FONT_PATH)) {
        throw std::runtime_error("Cannot load the font.");
    }
}

void WindowInit::ShapesInit() {
    dimRect.setSize(sf::Vector2f(WIDTH, HEIGHT));
    dimRect.setFillColor(sf::Color(0, 0, 0, 150));

    regRect.setFillColor(sf::Color::White);
    regRect.setSize(sf::Vector2f(WIDTH - 400, HEIGHT - 200));

    logRect.setSize(sf::Vector2f(BGRECT_WIDTH, BGRECT_HEIGHT));
    logRect.setFillColor(sf::Color::White);

    sf::Vector2f buttonSizes(BGRECT_WIDTH / 2, BUTTON_HEIGHT);

    ButtonInit(logButton, buttonSizes);
    ButtonInit(regButton, buttonSizes);
    ButtonInit(exitButton, buttonSizes);
    ButtonInit(loginBox, buttonSizes);
    ButtonInit(passwordBox, buttonSizes);
}

void WindowInit::ButtonInit(sf::RectangleShape& button, const sf::Vector2f& size) {
    button.setSize(size);
    button.setFillColor(sf::Color::White);
    button.setOutlineThickness(1);
    button.setOutlineColor(sf::Color::Black);
}

void WindowInit::TextInit() {
    SetText(bankName, BANK_NAME, sf::Color::Red);

    SetText(logText, "Login", sf::Color::Black);
    SetText(regText, "Register", sf::Color::Black);
    SetText(exitText, "Exit", sf::Color::Black);
    SetText(passText, "Password", sf::Color::Black);
}

void WindowInit::SetText(sf::Text& text, const std::string& str, sf::Color color) {
    text.setFont(menuFont);
    text.setString(str);
    text.setCharacterSize(FONT_SIZE);
    text.setFillColor(color);
}

void WindowInit::setMenuPos() {
    sf::Vector2f scrPosition(WIDTH / 2, HEIGHT / 2);
    sf::Vector2f bgRectSize(BGRECT_WIDTH, BGRECT_HEIGHT);
    sf::Vector2f buttonSizes(BGRECT_WIDTH / 2, BUTTON_HEIGHT);
    sf::Vector2f relativePos(scrPosition.x - bgRectSize.x / 2, scrPosition.y - bgRectSize.y / 2);
    sf::Vector2f logRectPos(relativePos);

    bankIco.setPosition(sf::Vector2f(BANK_POS, BANK_POS));
    bankName.setPosition(BANK_POS + (bankIcoSz.x * BANK_SCALE) / 2 + X_NAME_POS, BANK_POS + (bankIcoSz.y * BANK_SCALE) / 2 - FONT_SIZE / 2);
    regRect.setPosition(200, 100);
    logRect.setPosition(logRectPos);

    relativePos.y += 50;
    relativePos.x += buttonSizes.x / 2;
    logButton.setPosition(relativePos);
    logText.setPosition(relativePos);

    relativePos.y += 50 + buttonSizes.y;
    regButton.setPosition(relativePos);
    regText.setPosition(relativePos);

    relativePos.y += 50 + buttonSizes.y;
    exitButton.setPosition(relativePos);
    exitText.setPosition(relativePos);

    loginBox.setPosition(logRectPos.x + buttonSizes.x / 2, logRectPos.y + buttonSizes.y / 2 + 50);
    passwordBox.setPosition(logRectPos.x + buttonSizes.x / 2, logRectPos.y + buttonSizes.y / 2 + 175);
}

void WindowInit::menuInit() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            handleEvent(event);
        }
        window.clear(sf::Color::White);
        drawMainMenu();
        window.display();
    }
}

void WindowInit::handleEvent(sf::Event& event) {
    switch (event.type) {
    case sf::Event::Closed:
        window.close();
        break;

    case sf::Event::MouseButtonPressed:
        handleMouseClick();
        break;

    default:
        break;
    }
}

void WindowInit::handleMouseClick() {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (logText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        std::cout << "LOGIN clicked!" << std::endl;
        loginMenuInit();
    }
    else if (regText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        std::cout << "REGISTER clicked!" << std::endl;
        regMenuInit();
    }
    else if (exitText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        window.close();
    }
}

void WindowInit::drawMainMenu() {
    window.draw(menuBackground);
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
}

void WindowInit::loginMenuInit() {
    logText.setPosition(loginBox.getPosition().x, loginBox.getPosition().y - FONT_SIZE - 6);
    passText.setPosition(passwordBox.getPosition().x, passwordBox.getPosition().y - FONT_SIZE - 6);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::White);
        drawLoginMenu();
        window.display();
    }
}

void WindowInit::drawLoginMenu() {
    window.draw(menuBackground);
    window.draw(dimRect);
    window.draw(logRect);
    window.draw(loginBox);
    window.draw(logText);
    window.draw(passwordBox);
    window.draw(passText);
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
        drawRegMenu();
        window.display();
    }
}

void WindowInit::drawRegMenu() {
    window.draw(menuBackground);
    window.draw(dimRect);
    window.draw(regRect);
}
