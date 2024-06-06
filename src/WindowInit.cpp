#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "../include/WindowInit.h"
#include <iostream>
#include <stdexcept>
#include <vector>


WindowInit::WindowInit(const std::string& bgPath, const sf::Font& font) : window(sf::VideoMode(WIDTH, HEIGHT), MAIN_NAME),
bgPath(bgPath), menuFont(font), dimRect(sf::Vector2f(WIDTH, HEIGHT)) {
    window.setVerticalSyncEnabled(true);
    dimRect.setFillColor(sf::Color(0, 0, 0, 150));
}

sf::Texture WindowInit::textureInit(const std::string& texturePath) {
    sf::Texture texture;
    if (!texture.loadFromFile(texturePath)) {
        throw std::runtime_error("Cannot load the texture.");
    }
    return texture;
}

void WindowInit::shapeInit(sf::RectangleShape& obj, const sf::Color& color, const sf::Vector2f& position, const int& thickness, const sf::Color& outlineColor) {
    obj.setFillColor(color);
    obj.setPosition(position); // ewentualnie dac znowu na scale
    obj.setOutlineThickness(thickness);
    obj.setOutlineColor(outlineColor);
}

void WindowInit::buttonInit(sf::RectangleShape& obj, const sf::Color& color, const sf::Vector2f& position, const int& thickness, const sf::Color& outlineColor) {
    obj.setFillColor(color);
    obj.setPosition(position);
    obj.setOutlineThickness(thickness);
    obj.setOutlineColor(outlineColor);
}

WindowInit::~WindowInit() {
    std::cout << "[DEBUG] Program exit." << std::endl;
}

MenuInit::MenuInit(const std::string& bgPath, const sf::Font& font) : WindowInit(bgPath, font),
bankName(BANK_NAME, font, FONT_SIZE), loginMenuRect(MENU_LOGIN_SIZE), loginOptionBox(MENU_RECT_SIZE),
loginOptionText("Login", font, FONT_SIZE), registerOptionBox(MENU_RECT_SIZE), registerOptionText("Rejestracja", font, BANK_SIZE),
exitOptionBox(MENU_RECT_SIZE), exitOptionText("Wyjdz", font, FONT_SIZE) {
    bgBank.setTexture(textureInit(bgPath));
}

void MenuInit::setMenu() {

    sf::Vector2f tempPosition = RELATIVE_POSITION;
    bankName.setPosition(BANK_POS, BANK_POS);
    shapeInit(loginMenuRect, RECT_COLOR, RELATIVE_POSITION, 1, OUTLINE_COLOR);

    tempPosition.y += 50; tempPosition.x += MENU_RECT_SIZE.x / 2;
    shapeInit(loginOptionBox, RECT_COLOR, tempPosition, 1, OUTLINE_COLOR);
    loginOptionText.setPosition(tempPosition);

    tempPosition.y += 50 + MENU_RECT_SIZE.y;
    shapeInit(registerOptionBox, RECT_COLOR, tempPosition, 1, OUTLINE_COLOR);
    registerOptionText.setPosition(tempPosition);

    tempPosition.y += 50 + MENU_RECT_SIZE.y;
    shapeInit(exitOptionBox, RECT_COLOR, tempPosition, 1, OUTLINE_COLOR);
    exitOptionText.setPosition(tempPosition);
}

void MenuInit::showMenu() {
    setMenu();
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
                    LoginInit* login_window = new LoginInit(this->bgPath, this->menuFont, this->loginMenuRect, this->loginOptionBox, this->loginOptionText);
                    login_window->showLoginMenu();
                    delete login_window; login_window = nullptr;
                }
                else if (registerOptionText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    std::cout << "[DEBUG] Register selected" << std::endl;
                    RegisterInit* register_window = new RegisterInit(this->bgPath, this->menuFont, STANDARD_ACCOUNT_PATH, CHILD_ACCOUNT_PATH, SENIOR_ACCOUNT_PATH, BANK_ICO_PATH);
                    register_window->showRegisterMenu();
                }
                else if (exitOptionText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    std::cout << "[DEBUG] App closed" << std::endl;
                    window.close();
                }
                break;
            }
        }
        window.clear(sf::Color::White);
        drawMenu();
        window.display();
    }
}

void MenuInit::drawMenu() {
    window.draw(bgBank);
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

LoginInit::LoginInit(const std::string& bgPath, const sf::Font& font, sf::RectangleShape& loginMenuRect,
    sf::RectangleShape& loginOptionBox, sf::Text& loginOptionText) : WindowInit(bgPath, font),
    loginMenuRect(loginMenuRect), loginOptionBox(loginOptionBox), loginOptionText(loginOptionText),
    passwordOptionBox(MENU_RECT_SIZE), passwordOptionText("Haslo", font, FONT_SIZE) {}

void LoginInit::showLoginMenu() {
    bool isLoginActive = false;
    bool isPasswordActive = false;
    sf::Vector2f loginOptionBoxPos = loginOptionBox.getPosition();
    sf::Vector2f passwordOptionBoxPos = passwordOptionBox.getPosition();

    loginOptionText.setPosition(loginOptionBoxPos.x, loginOptionBoxPos.y - (FONT_SIZE + 6));
    passwordOptionText.setPosition(passwordOptionBoxPos.x, passwordOptionBoxPos.y - (FONT_SIZE + 6));

    std::string loginInput{ "" };
    std::string passwordInput{ "" };

    sf::Text userLoginText("", menuFont, FONT_SIZE);
    sf::Text userPasswordText("", menuFont, FONT_SIZE);
    sf::Text loginButtonText("Zaloguj", menuFont, FONT_SIZE);
    sf::RectangleShape loginButtonRect(MENU_RECT_SIZE);
    userPasswordText.setPosition(passwordOptionBoxPos);
    passwordOptionBoxPos.y += 75;
    userLoginText.setPosition(loginOptionBoxPos);
    shapeInit(loginButtonRect, RECT_COLOR, passwordOptionBoxPos, 1, OUTLINE_COLOR);

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
                    isLoginActive = true;
                    isPasswordActive = false;
                }
                // Check if the userPasswordText box is clicked
                else if (passwordOptionBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    isLoginActive = false;
                    isPasswordActive = true;
                }
                else if (loginButtonRect.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    std::cout << "[DEBUG] Initializing logging..." << std::endl;
                    // pass credentials and see if the account exists
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
        drawLoginMenu();
        window.draw(userLoginText);    // Draw the userLoginText text
        window.draw(userPasswordText); // Draw the userPasswordText text
        window.draw(loginButtonRect);
        window.draw(loginButtonText);
        window.display();
    }
}

void LoginInit::drawLoginMenu() {
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
    std::cout << "[DEBUG] Login Init exit" << std::endl;
}

RegisterInit::RegisterInit(const std::string& bgPath, const sf::Font& font, const std::string& stTexturePath,
    const std::string& cTexturePath, const std::string& seTexturePath, const std::string& bankTexturePath) :
    WindowInit(bgPath, font), childOptionRect(ACCOUNT_OPTION),
    standardOptionRect(ACCOUNT_OPTION), seniorOptionRect(ACCOUNT_OPTION),
    standardText("Konto Standardowe", font, FONT_SIZE), childText("Konto dla dzieci", font, FONT_SIZE),
    seniorText("Konto dla seniora", font, FONT_SIZE) {
    bgBank.setTexture(textureInit(bankTexturePath));
    standardAccountIcon.setTexture(textureInit(stTexturePath));
    childAccountIcon.setTexture(textureInit(cTexturePath));
    seniorAccountIcon.setTexture(textureInit(seTexturePath));
}

void RegisterInit::showRegisterMenu() {
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
                    createAccount();
                    std::cout << "[DEBUG] Standard Account selected" << std::endl;
                }
                else if (childOptionRect.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    std::cout << "[DEBUG] Child Account selected" << std::endl;
                }
                else if (seniorOptionRect.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    std::cout << "[DEBUG] Senior Account selected" << std::endl;
                }
                break;
            }
        }
        drawRegisterMenu();
        window.display();
    }
}

void RegisterInit::drawRegisterMenu() {
    window.draw(bgBank);
    window.draw(dimRect);
    window.draw(standardOptionRect);
    window.draw(childOptionRect);
    window.draw(seniorOptionRect);
    window.draw(standardAccountIcon);
    window.draw(standardText);
    window.draw(childAccountIcon);
    window.draw(childText);
    // here senior icon
    window.draw(seniorText);
}

void RegisterInit::setRegisterMenu() {
    shapeInit(standardOptionRect, RECT_COLOR, sf::Vector2f(360, 100), 1, OUTLINE_COLOR);
    shapeInit(childOptionRect, RECT_COLOR, sf::Vector2f(100, 100), 1, OUTLINE_COLOR);
    shapeInit(seniorOptionRect, RECT_COLOR, sf::Vector2f(820, 100), 1, OUTLINE_COLOR);
    standardAccountIcon.setPosition(185, 200);
    standardText.setPosition(150, 400);
    standardAccountIcon.setScale(STANDARD_ACCOUNT_SCALE, STANDARD_ACCOUNT_SCALE);

    childAccountIcon.setPosition(545, 200);
    childText.setPosition(515, 400);
    childAccountIcon.setScale(CHILD_ACCOUNT_SCALE, CHILD_ACCOUNT_SCALE);

    seniorText.setPosition(875, 400);
    //loginBox.setPosition(logRectPos.x + buttonSizes.x / 2, logRectPos.y + buttonSizes.y / 2 + 50);
    //passwordBox.setPosition(logRectPos.x + buttonSizes.x / 2, logRectPos.y + buttonSizes.y / 2 + 175);
}
void RegisterInit::createAccount() {
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
    sf::Text nameText("Imie", menuFont, FONT_SIZE);
    sf::Text lastNameText("Nazwisko", menuFont, FONT_SIZE);
    sf::Text addressText("Adres", menuFont, FONT_SIZE);
    sf::Text ageText("Wiek", menuFont, FONT_SIZE);
    sf::Text loginText("Login", menuFont, FONT_SIZE);
    sf::Text passwordText("Haslo", menuFont, FONT_SIZE);

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
    shapeInit(activeAcceptBox, RECT_COLOR, acceptBoxPosition, 1, OUTLINE_COLOR);
    shapeInit(inactiveAcceptBox, RECT_COLOR, acceptBoxPosition, 1, OUTLINE_COLOR);

    std::string nameInput{ "" };
    std::string lastNameInput{ "" };
    std::string addressInput{ "" };
    std::string ageInput{ "" };
    std::string loginInput{ "" };
    std::string passwordInput{ "" };

    // Create SFML Text objects for displaying user input
    sf::Text name("", menuFont, FONT_SIZE);
    sf::Text lastName("", menuFont, FONT_SIZE);
    sf::Text address("", menuFont, FONT_SIZE);
    sf::Text age("", menuFont, FONT_SIZE);
    sf::Text login("", menuFont, FONT_SIZE);
    sf::Text password("", menuFont, FONT_SIZE);

    // Position the SFML Text objects
    name.setPosition(nameBox.getPosition().x + 5, nameBox.getPosition().y);
    lastName.setPosition(lastNameBox.getPosition().x + 5, lastNameBox.getPosition().y);
    address.setPosition(addressBox.getPosition().x + 5, addressBox.getPosition().y);
    age.setPosition(ageBox.getPosition().x + 5, ageBox.getPosition().y);
    login.setPosition(loginBox.getPosition().x + 5, loginBox.getPosition().y);
    password.setPosition(passwordBox.getPosition().x + 5, passwordBox.getPosition().y);
    bankIcon.setPosition(age.getPosition().x + 425, lastName.getPosition().y - 125);

    sf::Text acceptText("Akceptuje regulamin banku", menuFont, FONT_SIZE);
    acceptText.setPosition(basePosition.x + 575, basePosition.y + 4 * spacing - FONT_SIZE); // Ustawienie pozycji nad activeAcceptBox

    auto createAsteriskString = [](const std::string& input) {
        return std::string(input.size(), '*');
        };

    while (window.isOpen()) {
        bool isLoginActive = false;
        bool isPasswordActive = false;
        bool isNameActive = false;
        bool isLastNameActive = false;
        bool isAddressActive = false;
        bool isAgeActive = false;
        bool isAcceptBoxActive = false;
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
                }
                else if (lastNameBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    isLastNameActive = true;
                }
                else if (addressBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    isAddressActive = true;
                }
                else if (ageBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    isAgeActive = true;
                }
                else if (loginBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    isLoginActive = true;
                }
                else if (passwordBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
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
        }

        window.clear(sf::Color::White);
        window.draw(bgBank);
        window.draw(dimRect);
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

RegisterInit::~RegisterInit() {
    std::cout << "[DEBUG] Register exit." << std::endl;
}
