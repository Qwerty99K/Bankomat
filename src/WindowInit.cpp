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
    // here icon
    seAccText.setPosition(875, 400);

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
                    std::cout << "[DEBUG] Login selected" << std::endl;
                    loginMenuInit();
                }
                else if (regText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    regMenuInit();
                    std::cout << "[DEBUG] Register selected" << std::endl;
                }
                else if (exitText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    std::cout << "[DEBUG] App closed" << std::endl;
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

    // put it later into class definition
    sf::Text logIntoAccount;
    SetText(logIntoAccount, "Zaloguj", sf::Color::Black);
    sf::RectangleShape logIntoAccountRect;
    logIntoAccountRect.setSize(loginBox.getSize());
    logIntoAccountRect.setOutlineColor(sf::Color::Black);
    logIntoAccountRect.setOutlineThickness(1);
    logIntoAccountRect.setPosition(passwordBox.getPosition().x, passwordBox.getPosition().y + 75);
    logIntoAccount.setPosition(logIntoAccountRect.getPosition());
    // dac do gory troche te elementy ^

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
                else if (logIntoAccountRect.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    std::cout << "[DEBUG] Initializing logging..." << std::endl;
                    // pass credentials and see if the account exists
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
        drawLoginMenu();
        window.draw(login);    // Draw the login text
        window.draw(password); // Draw the password text
        window.draw(logIntoAccountRect);
        window.draw(logIntoAccount);
        window.display();
    }
}

void WindowInit::drawLoginMenu() {
    window.clear(sf::Color::White);
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
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonPressed:
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (StAccOptionRect.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    createAccount();
                    std::cout << "[DEBUG] Standard Account selected" << std::endl;
                }
                else if (CAccOptionRect.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    std::cout << "[DEBUG] Child Account selected" << std::endl;
                }
                else if (SeAccOptionRect.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    std::cout << "[DEBUG] Senior Account selected" << std::endl;
                }
                break;
            }
        }
        drawRegMenu();
        window.display();
    }
}

void WindowInit::drawRegMenu() {
    window.draw(menuBackground);
    window.draw(dimRect);
    //window.draw(regRect);
    window.draw(StAccOptionRect);
    window.draw(CAccOptionRect);
    window.draw(SeAccOptionRect);
    window.draw(StAccIcon);
    window.draw(stAccText);
    window.draw(CAccIcon);
    window.draw(cAccText);
    // here senior icon
    window.draw(seAccText);


}

void WindowInit::createAccount() {

    // Variables to keep track of which input box is active
    bool isLoginActive = false;
    bool isPasswordActive = false;
    bool isNameActive = false;
    bool isLastNameActive = false;
    bool isAddressActive = false;
    bool isAgeActive = false;
    bool isAcceptBoxActive = false;

    // Create input boxes and labels
    sf::RectangleShape nameBox(sf::Vector2f(200, 30));
    sf::RectangleShape lastNameBox(sf::Vector2f(200, 30));
    sf::RectangleShape addressBox(sf::Vector2f(200, 30));
    sf::RectangleShape ageBox(sf::Vector2f(200, 30));
    sf::RectangleShape loginBox(sf::Vector2f(200, 30));
    sf::RectangleShape passwordBox(sf::Vector2f(200, 30));
    sf::RectangleShape activeAcceptBox(sf::Vector2f(200, 30)); // activate the terms box
    sf::RectangleShape inactiveAcceptBox(sf::Vector2f(200, 30)); // disactive the terms box


    // Set outlines
    nameBox.setOutlineThickness(2);
    nameBox.setOutlineColor(sf::Color::Black);
    lastNameBox.setOutlineThickness(2);
    lastNameBox.setOutlineColor(sf::Color::Black);
    addressBox.setOutlineThickness(2);
    addressBox.setOutlineColor(sf::Color::Black);
    ageBox.setOutlineThickness(2);
    ageBox.setOutlineColor(sf::Color::Black);
    loginBox.setOutlineThickness(2);
    loginBox.setOutlineColor(sf::Color::Black);
    passwordBox.setOutlineThickness(2);
    passwordBox.setOutlineColor(sf::Color::Black);
    activeAcceptBox.setOutlineThickness(2);
    activeAcceptBox.setOutlineColor(sf::Color::Black);
    activeAcceptBox.setFillColor(sf::Color::Green);
    inactiveAcceptBox.setOutlineThickness(2);
    inactiveAcceptBox.setOutlineColor(sf::Color::Black);

    // Create labels for the boxes
    sf::Text nameText;
    sf::Text lastNameText;
    sf::Text addressText;
    sf::Text ageText;
    sf::Text loginText;
    sf::Text passwordText;

    // Set initial properties for the labels
    SetText(nameText, "Imie:", sf::Color::Black);
    SetText(lastNameText, "Nazwisko:", sf::Color::Black);
    SetText(addressText, "Adres:", sf::Color::Black);
    SetText(ageText, "Wiek:", sf::Color::Black);
    SetText(loginText, "Login:", sf::Color::Black);
    SetText(passwordText, "Haslo:", sf::Color::Black);

    // Position the boxes relative to the regRect
    sf::Vector2f basePosition = regRect.getPosition() + sf::Vector2f(80, 80);
    float spacing = 60; // Vertical spacing between elements
    float xShift = 180; // Horizontal offset for labels relative to the text boxes

    // Position the labels and boxes
    nameText.setPosition(basePosition);
    nameBox.setPosition(nameText.getPosition().x + xShift, nameText.getPosition().y);

    lastNameText.setPosition(basePosition.x, basePosition.y + spacing);
    lastNameBox.setPosition(lastNameText.getPosition().x + xShift, lastNameText.getPosition().y);

    addressText.setPosition(basePosition.x, basePosition.y + 2 * spacing);
    addressBox.setPosition(addressText.getPosition().x + xShift, addressText.getPosition().y);

    ageText.setPosition(basePosition.x, basePosition.y + 3 * spacing);
    ageBox.setPosition(ageText.getPosition().x + xShift, ageText.getPosition().y);

    loginText.setPosition(basePosition.x, basePosition.y + 4 * spacing);
    loginBox.setPosition(loginText.getPosition().x + xShift, loginText.getPosition().y);

    passwordText.setPosition(basePosition.x, basePosition.y + 5 * spacing);
    passwordBox.setPosition(passwordText.getPosition().x + xShift, passwordText.getPosition().y);

    inactiveAcceptBox.setPosition(basePosition.x + 650, basePosition.y + 5 * spacing);
    activeAcceptBox.setPosition(basePosition.x + 650, basePosition.y + 5 * spacing);
    // Variables to store user input
    std::string nameInput{ "" };
    std::string lastNameInput{ "" };
    std::string addressInput{ "" };
    std::string ageInput{ "" };
    std::string loginInput{ "" };
    std::string passwordInput{ "" };

    // Create SFML Text objects for displaying user input
    sf::Text name;
    sf::Text lastName;
    sf::Text address;
    sf::Text age;
    sf::Text login;
    sf::Text password;

    // Set initial properties for the SFML Text objects
    SetText(name, "", sf::Color::Black);
    SetText(lastName, "", sf::Color::Black);
    SetText(address, "", sf::Color::Black);
    SetText(age, "", sf::Color::Black);
    SetText(login, "", sf::Color::Black);
    SetText(password, "", sf::Color::Black);

    // Position the SFML Text objects
    name.setPosition(nameBox.getPosition().x + 5, nameBox.getPosition().y);
    lastName.setPosition(lastNameBox.getPosition().x + 5, lastNameBox.getPosition().y);
    address.setPosition(addressBox.getPosition().x + 5, addressBox.getPosition().y);
    age.setPosition(ageBox.getPosition().x + 5, ageBox.getPosition().y);
    login.setPosition(loginBox.getPosition().x + 5, loginBox.getPosition().y);
    password.setPosition(passwordBox.getPosition().x + 5, passwordBox.getPosition().y);
    bankIco.setPosition(age.getPosition().x + 425, lastName.getPosition().y - 125);

    sf::Text acceptText;
    SetText(acceptText, "Akceptuje regulamin banku", sf::Color::Black);
    acceptText.setPosition(basePosition.x + 575, basePosition.y + 4 * spacing - FONT_SIZE); // Ustawienie pozycji nad activeAcceptBox


    // Helper function to create a masked string of asterisks
    auto createAsteriskString = [](const std::string& input) {
        return std::string(input.size(), '*');
        };

    // Main event loop
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
        window.draw(menuBackground);
        window.draw(dimRect);
        window.draw(regRect);
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
        window.draw(login);    // Draw the login text
        window.draw(password); // Draw the password text
        window.draw(bankIco);
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



// pozbyc sie tyle ifow i else ifow
// nie trzeba niektorych rzeczy inicjalizowac, mozna wywalic do funkcji
// 