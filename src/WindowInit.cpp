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

    if (!StAccTexture.loadFromFile("../Bankomat/resources/textures/StandardAccText.jpg")) {
        throw std::runtime_error("Cannot load the texture.");
    }

    if (!CAccTexture.loadFromFile("../Bankomat/resources/textures/ChildAccText.jpg")) {
        throw std::runtime_error("Cannot load the texture.");
    }
    // senior uninitialized

    if (!logTexture.loadFromFile("../Bankomat/resources/textures/login_icon.jpg")) {
        throw std::runtime_error("Cannot load the texture.");
    }

    if (!regTexture.loadFromFile("../Bankomat/resources/textures/register_icon.jpg")) {
        throw std::runtime_error("Cannot load the texture.");
    }

    StAccIcon.setTexture(StAccTexture);
    CAccIcon.setTexture(CAccTexture);
    logIcon.setTexture(logTexture);
    regIcon.setTexture(regTexture);

    StAccIcon.setScale(ST_ACC_SCALE, ST_ACC_SCALE);
    CAccIcon.setScale(C_ACC_SCALE, C_ACC_SCALE);
    /*logIcon.setScale(10, 10);
    regIcon.setScale(10, 10);*/


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
    regRect.setSize(sf::Vector2f(WIDTH - 200, HEIGHT - 200));

    logRect.setSize(sf::Vector2f(BGRECT_WIDTH, BGRECT_HEIGHT));
    logRect.setFillColor(sf::Color::White);

    CAccOptionRect.setSize(sf::Vector2f((WIDTH - 200) / 3 - 20, HEIGHT - 220));
    StAccOptionRect.setSize(sf::Vector2f((WIDTH - 200) / 3 - 20, HEIGHT - 220));
    SeAccOptionRect.setSize(sf::Vector2f((WIDTH - 200) / 3 - 20, HEIGHT - 220));

    CAccOptionRect.setFillColor(sf::Color::White);
    StAccOptionRect.setFillColor(sf::Color::White);
    SeAccOptionRect.setFillColor(sf::Color::White);

    CAccOptionRect.setOutlineThickness(1);
    CAccOptionRect.setOutlineColor(sf::Color::Black);
    StAccOptionRect.setOutlineThickness(1);
    StAccOptionRect.setOutlineColor(sf::Color::Black);
    SeAccOptionRect.setOutlineThickness(1);
    SeAccOptionRect.setOutlineColor(sf::Color::Black);

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
    SetText(stAccText, "Konto Standardowe", sf::Color::Black);
    SetText(cAccText, "Konto dla dziecka", sf::Color::Black);
    SetText(seAccText, "Konto dla seniora", sf::Color::Black);
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
    regRect.setPosition(100, 100);
    logRect.setPosition(logRectPos);
    StAccIcon.setPosition(185, 200);
    stAccText.setPosition(150, 400);
    CAccIcon.setPosition(545, 200); // + 360 do x dla seniora
    cAccText.setPosition(515, 400);

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

    auto temp = regRect.getPosition();
    temp.y += 10;
    temp.x += 10;
    CAccOptionRect.setPosition(temp.x, temp.y); // (100, 100)
    StAccOptionRect.setPosition(temp.x + 360, temp.y); // (460, 100)
    SeAccOptionRect.setPosition(temp.x + 720, temp.y); // (
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
        drawMainMenu();
        window.display();
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
    // Variables to keep track of which input box is active
    bool isLoginActive = false;
    bool isPasswordActive = false;

    // Initial setup for positions, etc.
    logText.setPosition(loginBox.getPosition().x, loginBox.getPosition().y - FONT_SIZE - 6);
    passText.setPosition(passwordBox.getPosition().x, passwordBox.getPosition().y - FONT_SIZE - 6);

    std::string loginInput{ "" };
    std::string passwordInput{ "" };
    sf::Text login;
    sf::Text password;
    SetText(login, "", sf::Color::Black);
    SetText(password, "", sf::Color::Black);
    login.setPosition(loginBox.getPosition());
    password.setPosition(passwordBox.getPosition());

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonPressed:
                // Check if the login box is clicked
                if (loginBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    isLoginActive = true;
                    isPasswordActive = false;
                }
                // Check if the password box is clicked
                else if (passwordBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    isLoginActive = false;
                    isPasswordActive = true;
                }
                break;

            case sf::Event::TextEntered:
                if (isLoginActive) {
                    if (event.text.unicode < 128 && event.text.unicode != 8) { // If it's a printable character
                        loginInput += static_cast<char>(event.text.unicode);
                        login.setString(loginInput);
                        std::cout << loginInput;
                    }
                    else if (event.text.unicode == 8 && !loginInput.empty()) { // If it's a backspace
                        loginInput.pop_back();
                        login.setString(loginInput);
                    }
                }
                else if (isPasswordActive) {
                    if (event.text.unicode < 128 && event.text.unicode != 8) { // If it's a printable character
                        passwordInput += static_cast<char>(event.text.unicode);
                        password.setString(passwordInput);
                        std::cout << passwordInput;
                    }
                    else if (event.text.unicode == 8 && !passwordInput.empty()) { // If it's a backspace
                        passwordInput.pop_back();
                        password.setString(passwordInput);
                    }
                }
                break;
            }
        }

        window.clear(sf::Color::White);
        window.draw(menuBackground);
        window.draw(dimRect);
        window.draw(logRect);
        window.draw(loginBox);
        window.draw(logText);
        window.draw(passwordBox);
        window.draw(passText);
        window.draw(login);    // Draw the login text
        window.draw(password); // Draw the password text
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
    window.draw(StAccOptionRect);
    window.draw(CAccOptionRect);
    window.draw(SeAccOptionRect);
    window.draw(StAccIcon);
    window.draw(stAccText);
    window.draw(CAccIcon);
    window.draw(cAccText);

}