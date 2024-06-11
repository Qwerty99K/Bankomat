#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "../include/WindowInit.h"
#include "../include/StandardAccount.h"
#include "../include/ChildAccount.h"
#include "../include/SeniorAccount.h"
#include "../include/createEntries.h"
#include "../include/BankInterface.h"
#include <iostream>
#include <stdexcept>
#include <vector>

WindowInit::WindowInit(sf::Font& font) : window(sf::VideoMode(WIDTH, HEIGHT), MAIN_NAME),
menuFont(font), dimRect(sf::Vector2f(WIDTH, HEIGHT)) {
    window.setVerticalSyncEnabled(true);
    dimRect.setFillColor(sf::Color(0, 0, 0, 150)); // niepotrzebne te inicjalizacje dimrecta
}

void shapeInit(sf::RectangleShape& obj, const sf::Color& color, const sf::Vector2f& position, const int& thickness, const sf::Color& outlineColor) {
    obj.setFillColor(color);
    obj.setPosition(position);
    obj.setOutlineThickness(thickness);
    obj.setOutlineColor(outlineColor);
}

void buttonInit(sf::RectangleShape& obj, const sf::Color& color, const sf::Vector2f& position, const int& thickness, const sf::Color& outlineColor) {
    obj.setFillColor(color);
    obj.setPosition(position);
    obj.setOutlineThickness(thickness);
    obj.setOutlineColor(outlineColor);
}

void WindowInit::menuSiteAccessor() {
    std::unique_ptr<MenuInit> menu_access(new MenuInit(menuFont));
    menu_access->setMenu();
    menu_access->showMenu(window);

}

WindowInit::~WindowInit() {

    std::cout << "[DEBUG] Program exit." << std::endl;
}

MenuInit::MenuInit(sf::Font& font) : clsFont(font), bankName(BANK_NAME, font, FONT_SIZE), loginMenuRect(MENU_LOGIN_SIZE), loginOptionBox(MENU_RECT_SIZE),
loginOptionText("Login", font, FONT_SIZE), registerOptionBox(MENU_RECT_SIZE), registerOptionText("Rejestracja", font, FONT_SIZE),
exitOptionBox(MENU_RECT_SIZE), exitOptionText("Wyjdz", font, FONT_SIZE), dimRect(sf::Vector2f(WIDTH, HEIGHT)) { 
    if (!bgBankT.loadFromFile(BACKGROUND_PATH)) {
        throw std::string("Nothing to load.");
    }
    bgBank.setTexture(bgBankT);
    bgBank.setScale(BACKGROUND_WIDTH, BACKGROUND_HEIGHT);
    dimRect.setFillColor(DIM_RECT);
}

void MenuInit::setMenu() {
    sf::Vector2f tempPosition = RELATIVE_POSITION;
    bankName.setPosition(BANK_POS, BANK_POS);
    shapeInit(loginMenuRect, RECT_COLOR, RELATIVE_POSITION, 1, OUTLINE_COLOR);

    tempPosition.y += 50; tempPosition.x += MENU_LOGIN_SIZE.x / 4 - 25;
    shapeInit(loginOptionBox, RECT_COLOR, tempPosition, 1, OUTLINE_COLOR);
    loginOptionText.setFillColor(sf::Color::Black);
    loginOptionText.setPosition(tempPosition);

    tempPosition.y += 50 + MENU_RECT_SIZE.y;
    shapeInit(registerOptionBox, RECT_COLOR, tempPosition, 1, OUTLINE_COLOR);
    registerOptionText.setFillColor(sf::Color::Black);
    registerOptionText.setPosition(tempPosition);

    tempPosition.y += 50 + MENU_RECT_SIZE.y;
    shapeInit(exitOptionBox, RECT_COLOR, tempPosition, 1, OUTLINE_COLOR);
    exitOptionText.setFillColor(sf::Color::Black);
    exitOptionText.setPosition(tempPosition);
}

void MenuInit::showMenu(sf::RenderWindow& window) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonPressed:
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (loginOptionText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    std::cout << "[DEBUG] Login selected" << std::endl;
                    loginSiteAccessor(window);
                }
                else if (registerOptionText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    std::cout << "[DEBUG] Register selected" << std::endl;
                    registerSiteAccessor(window);
                }
                else if (exitOptionText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    std::cout << "[DEBUG] App closed" << std::endl;
                    window.close();
                }
                break;
            }
        }
        window.clear(sf::Color::White);
        window.draw(bgBank);
        drawMenu(window);
        window.display();
    }
}

void MenuInit::loginSiteAccessor(sf::RenderWindow& window) {
    std::unique_ptr<LoginInit> login_window(new LoginInit(this->clsFont, this->loginMenuRect, this->loginOptionBox, this->loginOptionText));
    login_window->showLoginMenu(window);
    // jesli koniec to zniszcz tego pointera
    return;
}

void MenuInit::registerSiteAccessor(sf::RenderWindow& window) {
    std::unique_ptr<RegisterInit> register_window(new RegisterInit(this->clsFont));
    register_window->setRegisterMenu();
    register_window->showRegisterMenu(window);
    return;
}

void MenuInit::drawMenu(sf::RenderWindow& window) {
    window.draw(dimRect);
    window.draw(bankName);
    window.draw(loginMenuRect);
    window.draw(loginOptionBox);
    window.draw(loginOptionText);
    window.draw(registerOptionBox);
    window.draw(registerOptionText);
    window.draw(exitOptionBox);
    window.draw(exitOptionText);
}

MenuInit::~MenuInit() {
    std::cout << "[DEBUG] Class MenuInit -> exit" << std::endl;
}

LoginInit::LoginInit(sf::Font& font, sf::RectangleShape& loginMenuRect,
    sf::RectangleShape& loginOptionBox, sf::Text& loginOptionText) : clsFont(font),
    loginMenuRect(loginMenuRect), loginOptionBox(loginOptionBox), loginOptionText(loginOptionText),
    passwordOptionBox(MENU_RECT_SIZE), passwordOptionText("Haslo", font, FONT_SIZE), dimRect(sf::Vector2f(WIDTH, HEIGHT)) {
    if (!bgBankT.loadFromFile(BACKGROUND_PATH)) {
        throw std::string("Nothing to load.");
    }
    bgBank.setTexture(bgBankT);
    bgBank.setScale(BACKGROUND_WIDTH, BACKGROUND_HEIGHT);
    dimRect.setFillColor(DIM_RECT);
}


void LoginInit::showLoginMenu(sf::RenderWindow& window) {

    sf::Vector2f loginOptionBoxPos = loginOptionBox.getPosition();
    sf::Vector2f passwordOptionBoxPos = loginOptionBoxPos;
    passwordOptionBoxPos.y += 125;
    shapeInit(passwordOptionBox, RECT_COLOR, passwordOptionBoxPos, 1, OUTLINE_COLOR);

    loginOptionText.setPosition(loginOptionBoxPos.x, loginOptionBoxPos.y - (FONT_SIZE + 6));
    passwordOptionText.setPosition(passwordOptionBoxPos.x, passwordOptionBoxPos.y - (FONT_SIZE + 6));
    passwordOptionText.setFillColor(sf::Color::Black);

    std::string loginInput{ "" };
    std::string passwordInput{ "" };

    sf::Text userLoginText("", clsFont, FONT_SIZE);
    userLoginText.setFillColor(sf::Color::Black);
    sf::Text userPasswordText("", clsFont, FONT_SIZE);
    userPasswordText.setFillColor(sf::Color::Black);
    sf::Text loginButtonText("Zaloguj", clsFont, FONT_SIZE);
    loginButtonText.setFillColor(sf::Color::Black);
    sf::RectangleShape loginButtonRect(MENU_RECT_SIZE);
    userLoginText.setPosition(loginOptionBoxPos);
    userPasswordText.setPosition(passwordOptionBoxPos);
    passwordOptionBoxPos.y += 100;
    shapeInit(loginButtonRect, RECT_COLOR, passwordOptionBoxPos, 1, OUTLINE_COLOR);
    loginButtonText.setPosition(loginButtonRect.getPosition());
    bool isLoginActive = false;
    bool isPasswordActive = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonPressed:
                // Check if the userLoginText box is clicked
                if (loginOptionBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    isLoginActive = true; isPasswordActive = false;
                }
                // Check if the userPasswordText box is clicked
                else if (passwordOptionBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    isPasswordActive = true; isLoginActive = false;
                }
                else if (loginButtonRect.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    // znajdz czy sa poprawne jesli sa to przejdz dalej
                    std::unique_ptr<BankInterface> bank_interface(new BankInterface(this->clsFont, this->loginMenuRect));
                    bank_interface->showInterface(window);
                    std::cout << "[DEBUG] Initializing logging..." << std::endl;
                }
                break;

            case sf::Event::TextEntered:
                if (isLoginActive) {
                    if (event.text.unicode < 128 && event.text.unicode != 8) { // If it's a printable character
                        loginInput += static_cast<char>(event.text.unicode);
                        userLoginText.setString(loginInput);
                        std::cout << loginInput;
                    }
                    else if (event.text.unicode == 8 && !loginInput.empty()) { // If it's a backspace
                        loginInput.pop_back();
                        userLoginText.setString(loginInput);
                    }
                }
                else if (isPasswordActive) {
                    if (event.text.unicode < 128 && event.text.unicode != 8) { // If it's a printable character
                        passwordInput += static_cast<char>(event.text.unicode);
                        userPasswordText.setString(passwordInput);
                        std::cout << passwordInput;
                    }
                    else if (event.text.unicode == 8 && !passwordInput.empty()) { // If it's a backspace
                        passwordInput.pop_back();
                        userPasswordText.setString(passwordInput);
                    }
                }
                break;
            }
        }
        drawLoginMenu(window);
        window.draw(userLoginText);    // Draw the userLoginText text
        window.draw(userPasswordText); // Draw the userPasswordText text
        window.draw(loginButtonRect);
        window.draw(loginButtonText);
        window.display();
    }
}

void LoginInit::drawLoginMenu(sf::RenderWindow& window) {
    window.clear(sf::Color::White);
    window.draw(bgBank);
    window.draw(dimRect);
    window.draw(loginMenuRect);
    window.draw(loginOptionBox);
    window.draw(loginOptionText);
    window.draw(passwordOptionBox);
    window.draw(passwordOptionText);
}

LoginInit::~LoginInit() {
    std::cout << "[DEBUG] Class LoginInit -> exit" << std::endl;
}

RegisterInit::RegisterInit(sf::Font& font) : clsFont(font), childOptionRect(REGISTER_OPTIONS_SIZE), standardOptionRect(REGISTER_OPTIONS_SIZE), seniorOptionRect(REGISTER_OPTIONS_SIZE),
    standardText("Konto Standardowe", font, FONT_SIZE), childText("Konto dla dzieci", font, FONT_SIZE),
    seniorText("Konto dla seniora", font, FONT_SIZE), registerRect(REGISTER_RECT_SIZE), dimRect(sf::Vector2f(WIDTH, HEIGHT)) {
    if (!standardAccontIconT.loadFromFile(STANDARD_ACCOUNT_PATH)) {
        throw std::string("Nothing to load.");
    }
    if (!seniorAccountIconT.loadFromFile(SENIOR_ACCOUNT_PATH)) {
        throw std::string("Nothing to load.");
    }
    if (!childAccountIconT.loadFromFile(CHILD_ACCOUNT_PATH)) {
        throw std::string("Nothing to load.");
    }
    if (!bankIconT.loadFromFile(BANK_ICO_PATH)) {
        throw std::string("Nothing to load.");
    }
    if (!bgBankT.loadFromFile(BACKGROUND_PATH)) {
        throw std::string("Nothing to load.");
    }
    bgBank.setTexture(bgBankT);
    bgBank.setScale(BACKGROUND_WIDTH, BACKGROUND_HEIGHT);
    dimRect.setFillColor(DIM_RECT);
    standardAccountIcon.setTexture(standardAccontIconT);
    seniorAccountIcon.setTexture(seniorAccountIconT);
    childAccountIcon.setTexture(childAccountIconT);
    bankIcon.setTexture(bankIconT);
    bankIcon.setScale(BANK_SCALE, BANK_SCALE);

}

void RegisterInit::showRegisterMenu(sf::RenderWindow& window) {
    window.clear(sf::Color::White);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonPressed:
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (standardOptionRect.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    AccountType selectedAccount = AccountType::STANDARD_ACCOUNT;
                    std::cout << "[DEBUG] Standard Account selected" << std::endl;
                    createAccount(window, selectedAccount);
                    return;
                }
                else if (childOptionRect.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    AccountType selectedAccount = AccountType::CHILD_ACCOUNT;
                    std::cout << "[DEBUG] Child Account selected" << std::endl;
                    createAccount(window, selectedAccount);
                    return;
                }
                else if (seniorOptionRect.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    AccountType selectedAccount = AccountType::SENIOR_ACCOUNT;
                    std::cout << "[DEBUG] Senior Account selected" << std::endl;
                    createAccount(window, selectedAccount);
                    return;
                }
                break;
            }
        }
        drawRegisterMenu(window);
        window.display();
    }
}

void RegisterInit::drawRegisterMenu(sf::RenderWindow& window) {
    window.draw(bgBank);
    window.draw(dimRect);
    window.draw(standardOptionRect);
    window.draw(childOptionRect);
    window.draw(seniorOptionRect);
    window.draw(standardAccountIcon);
    window.draw(standardText);
    window.draw(childAccountIcon);
    window.draw(childText);
    window.draw(seniorText);
}

void RegisterInit::setRegisterMenu() {
    shapeInit(registerRect, RECT_COLOR, sf::Vector2f(100, 100), 1, OUTLINE_COLOR);

    shapeInit(childOptionRect, RECT_COLOR, sf::Vector2f(110, 110), 1, OUTLINE_COLOR);
    childAccountIcon.setPosition(545, 200);
    childText.setPosition(530, 400);
    childText.setFillColor(sf::Color::Black);
    childAccountIcon.setScale(CHILD_ACCOUNT_SCALE, CHILD_ACCOUNT_SCALE);
    
    shapeInit(standardOptionRect, RECT_COLOR, sf::Vector2f(475, 110), 1, OUTLINE_COLOR);
    standardAccountIcon.setPosition(185, 200);
    standardText.setPosition(150, 400);
    standardText.setFillColor(sf::Color::Black);
    standardAccountIcon.setScale(STANDARD_ACCOUNT_SCALE, STANDARD_ACCOUNT_SCALE);
    
    shapeInit(seniorOptionRect, RECT_COLOR, sf::Vector2f(840, 110), 1, OUTLINE_COLOR);
    seniorText.setPosition(890, 400);
    seniorText.setFillColor(sf::Color::Black);
    //loginBox.setPosition(logRectPos.x + buttonSizes.x / 2, logRectPos.y + buttonSizes.y / 2 + 50);
    //passwordBox.setPosition(logRectPos.x + buttonSizes.x / 2, logRectPos.y + buttonSizes.y / 2 + 175);
}

void RegisterInit::createAccount(sf::RenderWindow& window, AccountType selectedAcc) {
    setRegisterMenu();
    sf::RectangleShape nameBox(REGISTER_BOX_SIZE);
    sf::RectangleShape lastNameBox(REGISTER_BOX_SIZE);
    sf::RectangleShape addressBox(REGISTER_BOX_SIZE);
    sf::RectangleShape ageBox(REGISTER_BOX_SIZE);
    sf::RectangleShape loginBox(REGISTER_BOX_SIZE);
    sf::RectangleShape passwordBox(REGISTER_BOX_SIZE);
    sf::RectangleShape activeAcceptBox(REGISTER_BOX_SIZE); // activate the terms box
    sf::RectangleShape inactiveAcceptBox(REGISTER_BOX_SIZE); // disactive the terms   
    sf::Vector2f basePosition(180, 180);

    // Create labels for the boxes
    sf::Text nameText("Imie", clsFont, FONT_SIZE);
    nameText.setFillColor(sf::Color::Black);
    sf::Text lastNameText("Nazwisko", clsFont, FONT_SIZE);
    lastNameText.setFillColor(sf::Color::Black);
    sf::Text addressText("Adres", clsFont, FONT_SIZE);
    addressText.setFillColor(sf::Color::Black);
    sf::Text ageText("Wiek", clsFont, FONT_SIZE);
    ageText.setFillColor(sf::Color::Black);
    sf::Text loginText("Login", clsFont, FONT_SIZE);
    loginText.setFillColor(sf::Color::Black);
    sf::Text passwordText("Haslo", clsFont, FONT_SIZE);
    passwordText.setFillColor(sf::Color::Black);
    float spacing = 60.f;
    float shift = 180.f;
    float baseX = basePosition.x;
    float baseY = basePosition.y;

    nameText.setPosition(baseX, baseY);
    shapeInit(nameBox, RECT_COLOR, sf::Vector2f(baseX + shift, baseY), 1, OUTLINE_COLOR);

    lastNameText.setPosition(baseX, baseY + spacing);
    shapeInit(lastNameBox, RECT_COLOR, sf::Vector2f(baseX + shift, baseY + spacing), 1, OUTLINE_COLOR);

    addressText.setPosition(baseX, baseY + 2 * spacing);
    shapeInit(addressBox, RECT_COLOR, sf::Vector2f(baseX + shift, baseY + 2 * spacing), 1, OUTLINE_COLOR);

    ageText.setPosition(baseX, baseY + 3 * spacing);
    shapeInit(ageBox, RECT_COLOR, sf::Vector2f(baseX + shift, baseY + 3 * spacing), 1, OUTLINE_COLOR);

    loginText.setPosition(baseX, baseY + 4 * spacing);
    shapeInit(loginBox, RECT_COLOR, sf::Vector2f(baseX + shift, baseY + 4 * spacing), 1, OUTLINE_COLOR);

    passwordText.setPosition(baseX, baseY + 5 * spacing);
    shapeInit(passwordBox, RECT_COLOR, sf::Vector2f(baseX + shift, baseY + 5 * spacing), 1, OUTLINE_COLOR);

    sf::Vector2f acceptBoxPosition(baseX + 650, baseY + 5 * spacing);
    shapeInit(activeAcceptBox, sf::Color::Green, acceptBoxPosition, 1, OUTLINE_COLOR);
    shapeInit(inactiveAcceptBox, RECT_COLOR, acceptBoxPosition, 1, OUTLINE_COLOR);

    std::string nameInput{ "" };
    std::string lastNameInput{ "" };
    std::string addressInput{ "" };
    std::string ageInput{ "" };
    std::string loginInput{ "" };
    std::string passwordInput{ "" };

    // Create SFML Text objects for displaying user input
    sf::Text name("", clsFont, FONT_SIZE);
    name.setFillColor(sf::Color::Black);
    sf::Text lastName("", clsFont, FONT_SIZE);
    lastName.setFillColor(sf::Color::Black);
    sf::Text address("", clsFont, FONT_SIZE);
    address.setFillColor(sf::Color::Black);
    sf::Text age("", clsFont, FONT_SIZE);
    age.setFillColor(sf::Color::Black);
    sf::Text login("", clsFont, FONT_SIZE);
    login.setFillColor(sf::Color::Black);
    sf::Text password("", clsFont, FONT_SIZE);
    password.setFillColor(sf::Color::Black);

    // Position the SFML Text objects
    name.setPosition(nameBox.getPosition().x + 5, nameBox.getPosition().y);
    lastName.setPosition(lastNameBox.getPosition().x + 5, lastNameBox.getPosition().y);
    address.setPosition(addressBox.getPosition().x + 5, addressBox.getPosition().y);
    age.setPosition(ageBox.getPosition().x + 5, ageBox.getPosition().y);
    login.setPosition(loginBox.getPosition().x + 5, loginBox.getPosition().y);
    password.setPosition(passwordBox.getPosition().x + 5, passwordBox.getPosition().y);
    bankIcon.setPosition(age.getPosition().x + 425, lastName.getPosition().y - 125);

    sf::Text acceptText("Akceptuje regulamin banku", clsFont, FONT_SIZE);
    acceptText.setFillColor(sf::Color::Black);
    acceptText.setPosition(basePosition.x + 575, basePosition.y + 4 * spacing - FONT_SIZE); // Ustawienie pozycji nad activeAcceptBox

    auto createAsteriskString = [](const std::string& input) {
        return std::string(input.size(), '*');
        };

    bool isLoginActive = false;
    bool isPasswordActive = false;
    bool isNameActive = false;
    bool isLastNameActive = false;
    bool isAddressActive = false;
    bool isAgeActive = false;
    bool isAcceptBoxActive = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonPressed:
                // Check which box is clicked
                if (nameBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    isNameActive = true;
                    isLastNameActive = false;
                    isAddressActive = false;
                    isAgeActive = false;
                    isLoginActive = false;
                    isPasswordActive = false;
                }
                else if (lastNameBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    isNameActive = false;
                    isLastNameActive = true;
                    isAddressActive = false;
                    isAgeActive = false;
                    isLoginActive = false;
                    isPasswordActive = false;
                }
                else if (addressBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    isNameActive = false;
                    isLastNameActive = false;
                    isAddressActive = true;
                    isAgeActive = false;
                    isLoginActive = false;
                    isPasswordActive = false;
                }
                else if (ageBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    isNameActive = false;
                    isLastNameActive = false;
                    isAddressActive = false;
                    isAgeActive = true;
                    isLoginActive = false;
                    isPasswordActive = false;
                }
                else if (loginBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    isNameActive = false;
                    isLastNameActive = false;
                    isAddressActive = false;
                    isAgeActive = false;
                    isLoginActive = true;
                    isPasswordActive = false;
                }
                else if (passwordBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    isNameActive = false;
                    isLastNameActive = false;
                    isAddressActive = false;
                    isAgeActive = false;
                    isLoginActive = false;
                    isPasswordActive = true;
                }
                else if (activeAcceptBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)) && !isAcceptBoxActive) {
                    isAcceptBoxActive = true;
                    std::cout << "[DEBUG] Active box" << std::endl;
                }
                else if (inactiveAcceptBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)) && isAcceptBoxActive) {
                    isAcceptBoxActive = false;
                    std::cout << "[DEBUG] Inactive box" << std::endl;
                }
                if (activeAcceptBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)) && isAcceptBoxActive) {
                    createEntry(selectedAcc, loginInput, passwordInput, nameInput, lastNameInput, addressInput, 100, ageInput);
                    return;
                    // tu powinien byc testcase, np wyslanie 1 ze sie udalo i wtedy koniec programu

                }
                break;
            case sf::Event::TextEntered:
                if (isNameActive) {
                    if (event.text.unicode < 128 && event.text.unicode != 8) { // If it's a printable character
                        nameInput += static_cast<char>(event.text.unicode);
                        name.setString(nameInput);
                        std::cout << nameInput;
                    }
                    else if (event.text.unicode == 8 && !nameInput.empty()) { // If it's a backspace
                        nameInput.pop_back();
                        name.setString(nameInput);
                    }
                }
                else if (isLastNameActive) {
                    if (event.text.unicode < 128 && event.text.unicode != 8) { // If it's a printable character
                        lastNameInput += static_cast<char>(event.text.unicode);
                        lastName.setString(lastNameInput);
                        std::cout << lastNameInput;
                    }
                    else if (event.text.unicode == 8 && !lastNameInput.empty()) { // If it's a backspace
                        lastNameInput.pop_back();
                        lastName.setString(lastNameInput);
                    }
                }
                else if (isAddressActive) {
                    if (event.text.unicode < 128 && event.text.unicode != 8) { // If it's a printable character
                        addressInput += static_cast<char>(event.text.unicode);
                        address.setString(addressInput);
                        std::cout << addressInput;
                    }
                    else if (event.text.unicode == 8 && !addressInput.empty()) { // If it's a backspace
                        addressInput.pop_back();
                        address.setString(addressInput);
                    }
                }
                else if (isAgeActive) {
                    if (event.text.unicode < 128 && event.text.unicode != 8) { // If it's a printable character
                        ageInput += static_cast<char>(event.text.unicode);
                        age.setString(ageInput);
                        std::cout << ageInput;
                    }
                    else if (event.text.unicode == 8 && !ageInput.empty()) { // If it's a backspace
                        ageInput.pop_back();
                        age.setString(ageInput);
                    }
                }
                else if (isLoginActive) {
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
                        password.setString(createAsteriskString(passwordInput));
                        std::cout << passwordInput;
                    }
                    else if (event.text.unicode == 8 && !passwordInput.empty()) { // If it's a backspace
                        passwordInput.pop_back();
                        password.setString(createAsteriskString(passwordInput));
                    }
                }
                break;
            }
            window.clear(sf::Color::White);
            window.draw(bgBank);
            window.draw(dimRect);
            window.draw(registerRect);
            window.draw(nameBox);
            window.draw(lastNameBox);
            window.draw(addressBox);
            window.draw(ageBox);
            window.draw(loginBox);
            window.draw(passwordBox);
            window.draw(nameText);
            window.draw(lastNameText);
            window.draw(addressText);
            window.draw(ageText);
            window.draw(loginText);
            window.draw(passwordText);
            window.draw(name);     // Draw the name text
            window.draw(lastName); // Draw the last name text
            window.draw(address);  // Draw the address text
            window.draw(age);      // Draw the age text
            window.draw(login);    // Draw the userLoginText text
            window.draw(password); // Draw the userPasswordText text
            window.draw(bankIcon);
            if (isAcceptBoxActive) {
                window.draw(activeAcceptBox);
            }
            else {
                window.draw(inactiveAcceptBox);
            }
            window.draw(acceptText);
            window.display();
        }
    }
}

RegisterInit::~RegisterInit() {
    std::cout << "[DEBUG] Register exit." << std::endl;
}