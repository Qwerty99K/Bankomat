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
ATM atmInterface;

bool isValidInput(const std::string& input) {
    size_t decimalPos = input.find('.');
    if (decimalPos == std::string::npos) {
        return true;
    }

    std::string decimalPart = input.substr(decimalPos + 1);
    return decimalPart.size() <= 2;
}

std::string formatBalance(const std::string& balanceStr) {
    float balance = std::stof(balanceStr);
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << balance; 
    return oss.str();
}

BankInterface::BankInterface(sf::Font& clsFont, sf::RectangleShape& interfaceRect, std::vector<std::string> userDetails) :
    clsFont(clsFont), interfaceRect(REGISTER_RECT_SIZE), dimRect(sf::Vector2f(WIDTH, HEIGHT)), nameBox(INTERFACE_BOX_SIZE),
    userDetails(userDetails), lastNameBox(INTERFACE_BOX_SIZE), ageBox(INTERFACE_BOX_SIZE), addressBox(INTERFACE_BOX_SIZE),
    generateRaportBox(INTERFACE_BOX_SIZE), loginBox(INTERFACE_BOX_SIZE), balanceBox(INTERFACE_BOX_SIZE),
    transferBox(INTERFACE_BOX_SIZE), withdrawBox(INTERFACE_BOX_SIZE), depositBox(INTERFACE_BOX_SIZE), nameText("IMIE: " + userDetails[1], clsFont, FONT_SIZE),
    lastNameText("NAZ: " + userDetails[2], clsFont, FONT_SIZE), addressText("ADRES: " + userDetails[3], clsFont, FONT_SIZE),
    ageText("WIEK: " + userDetails[4], clsFont, FONT_SIZE), loginText("LOGIN: " + userDetails[5], clsFont, FONT_SIZE), balanceText("$: " + formatBalance(userDetails[7]), clsFont, FONT_SIZE),
    generateRaportText("GENERUJ RAPORT", clsFont, FONT_SIZE), transferText("TRANSFER", clsFont, FONT_SIZE),
    withdrawText("WYPLAC", clsFont, FONT_SIZE), depositText("WPLAC", clsFont, FONT_SIZE), warning(clsFont), granted(clsFont){
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
    if (!(bankTexture.loadFromFile(BANK_ICO_PATH))) {
        throw std::string("Nothing to load");
    }
    else {
        bankTexture.setSmooth(true);
    }

    bgBank.setTexture(bgBankT);
    bgBank.setScale(BACKGROUND_WIDTH, BACKGROUND_HEIGHT);
    profilePicture.setTexture(profilePictureT);
    profilePicture.setScale(PROFILE_SCALE);
    dimRect.setFillColor(DIM_RECT);
    bankIcon.setTexture(bankTexture);
    bankIcon.setScale(BANK_SCALE, BANK_SCALE);
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

    sf::Vector2f tempPos2(500, 149);
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
    shapeInit(depositBox, RECT_COLOR, tempPos2, 1, OUTLINE_COLOR);
    depositText.setPosition(tempPos2);
    depositText.setFillColor(sf::Color::Black);
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
    bool isWithdrawActive = false;
    bool isRaportActive = false;
    bool isTransferActive = false;
    bool isDepositActive = false;
    std::string withdrawAmount = "";
    std::string transferAmount = "";
    std::string depositAmount = "";
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonPressed:
                if (generateRaportBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    isWithdrawActive = false;
                    isRaportActive = true;
                    isTransferActive = false;
                    isDepositActive = false;
                    reportInterface(window, userDetails[5]);
                }
                else if (withdrawBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    isWithdrawActive = true;
                    isRaportActive = false;
                    isTransferActive = false;
                    isDepositActive = false;
                    withdrawInterface(window, userDetails[5]);
                }
                else if (transferBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    isWithdrawActive = false;
                    isRaportActive = false;
                    isTransferActive = true;
                    isDepositActive = false;
                    transferInterface(window, userDetails[5]);
                }
                else if (depositBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    isWithdrawActive = false;
                    isRaportActive = false;
                    isTransferActive = false;
                    isDepositActive = true;
                    depositInterface(window, userDetails[5]);
                }
                else if (!(interfaceRect.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))) {
                    std::cout << "[DEBUG] User logged out." << std::endl;
                    return;
                }
                break;

            case sf::Event::TextEntered:
                if (isWithdrawActive) {
                    if (event.text.unicode == '\b') {
                        if (!withdrawAmount.empty()) {
                            withdrawAmount.pop_back();
                        }
                    }
                    else if (event.text.unicode == '\r') {
                        if (!withdrawAmount.empty()) {
                            try {
                                double amount = std::stod(withdrawAmount);
                                atmInterface.withdraw(userDetails[5], amount);
                                withdrawAmount.clear();
                            }
                            catch (const std::exception& e) {
                                std::cerr << "Invalid input: " << e.what() << std::endl;
                            }
                        }
                        isWithdrawActive = false;
                    }
                    else if (event.text.unicode < 128) {
                        withdrawAmount += static_cast<char>(event.text.unicode);
                    }
                    withdrawText.setString(withdrawAmount);
                }
                else if (isTransferActive) {
                    if (event.text.unicode == '\b') {
                        if (!transferAmount.empty()) {
                            transferAmount.pop_back();
                        }
                    }
                    else if (event.text.unicode == '\r') {
                        if (!transferAmount.empty()) {
                            try {
                                double amount = std::stod(transferAmount);
                                atmInterface.transfer(userDetails[5], "someone", amount);
                                transferAmount.clear();
                            }
                            catch (const std::exception& e) {
                                std::cerr << "Invalid input: " << e.what() << std::endl;
                            }
                        }
                        isTransferActive = false;
                    }
                    else if (event.text.unicode < 128) {
                        transferAmount += static_cast<char>(event.text.unicode);
                    }
                    transferText.setString(transferAmount);
                }
                else if (isDepositActive) {
                    if (event.text.unicode == '\b') {
                        if (!depositAmount.empty()) {
                            depositAmount.pop_back();
                        }
                    }
                    else if (event.text.unicode == '\r') {
                        if (!depositAmount.empty()) {
                            try {
                                double amount = std::stod(depositAmount);
                                atmInterface.deposit(userDetails[5], amount);
                                depositAmount.clear();
                            }
                            catch (const std::exception& e) {
                                std::cerr << "Invalid input: " << e.what() << std::endl;
                            }
                        }
                        isDepositActive = false;
                    }
                    else if (event.text.unicode < 128) {
                        depositAmount += static_cast<char>(event.text.unicode);
                    }
                    depositText.setString(depositAmount);
                }
                break;
            }
        }

        window.clear();
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
        window.draw(loginBox);
        window.draw(loginText);
        window.draw(balanceBox);
        window.draw(balanceText);
        window.draw(transferBox);
        window.draw(transferText);
        window.draw(withdrawBox);
        window.draw(withdrawText);
        window.draw(depositBox);
        window.draw(depositText);
        window.draw(generateRaportBox);
        window.draw(generateRaportText);
        window.draw(addressBox);
        window.draw(addressText);
        window.display();
    }
}

void BankInterface::transferInterface(sf::RenderWindow& window, const std::string& send_us_name) {
    setInterface();
    sf::RectangleShape receiverBox(REGISTER_BOX_SIZE);
    sf::RectangleShape amountBox(REGISTER_BOX_SIZE);
    sf::RectangleShape activeAcceptBox(REGISTER_BOX_SIZE);
    sf::RectangleShape inactiveAcceptBox(REGISTER_BOX_SIZE);
    sf::Vector2f basePosition(180, 180);

    sf::Text receiverText("Odbiorca", clsFont, FONT_SIZE);
    receiverText.setFillColor(sf::Color::Black);
    sf::Text amountText("Kwota", clsFont, FONT_SIZE);
    amountText.setFillColor(sf::Color::Black);
    float spacing = 60.f;
    float shift = 180.f;
    float baseX = basePosition.x;
    float baseY = basePosition.y;

    receiverText.setPosition(baseX, baseY + 4 * spacing);
    shapeInit(receiverBox, RECT_COLOR, sf::Vector2f(baseX + shift, baseY + 4 * spacing), 1, OUTLINE_COLOR);

    amountText.setPosition(baseX, baseY + 5 * spacing);
    shapeInit(amountBox, RECT_COLOR, sf::Vector2f(baseX + shift, baseY + 5 * spacing), 1, OUTLINE_COLOR);

    sf::Vector2f acceptBoxPosition(baseX + 650, baseY + 5 * spacing);
    shapeInit(activeAcceptBox, sf::Color::Green, acceptBoxPosition, 1, OUTLINE_COLOR);
    shapeInit(inactiveAcceptBox, RECT_COLOR, acceptBoxPosition, 1, OUTLINE_COLOR);

    std::string receiverInput{ "" };
    std::string amountInput{ "" };

    sf::Text receiver("", clsFont, FONT_SIZE);
    receiver.setFillColor(sf::Color::Black);
    sf::Text amount("", clsFont, FONT_SIZE);
    amount.setFillColor(sf::Color::Black);

    receiver.setPosition(receiverBox.getPosition().x + 5, receiverBox.getPosition().y);
    amount.setPosition(amountBox.getPosition().x + 5, amountBox.getPosition().y);

    sf::Text acceptText("Potwierdzam wykonanie przelewu", clsFont, FONT_SIZE);
    acceptText.setFillColor(sf::Color::Black);
    acceptText.setPosition(basePosition.x + 500, basePosition.y + 4 * spacing - FONT_SIZE);

    bankIcon.setPosition(acceptText.getPosition().x - 175, acceptText.getPosition().y - 275);

    bool isReceiverActive = false;
    bool isamountActive = false;
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
                if (receiverBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    isReceiverActive = true;
                    isamountActive = false;
                    isAcceptBoxActive = false;
                }
                else if (amountBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    isReceiverActive = false;
                    isamountActive = true;
                    isAcceptBoxActive = false;
                }

                else if (activeAcceptBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)) && !isAcceptBoxActive) {
                    isReceiverActive = false;
                    isamountActive = false;
                    isAcceptBoxActive = true;
                    std::cout << "[DEBUG] Active box" << std::endl;
                }
                else if (inactiveAcceptBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)) && isAcceptBoxActive) {
                    isReceiverActive = false;
                    isamountActive = false;
                    isAcceptBoxActive = false;
                    std::cout << "[DEBUG] Inactive box" << std::endl;
                }
                if (activeAcceptBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)) && isAcceptBoxActive) {
                    try {
                        std::cout << "[DEBUG] " << receiverInput << std::endl;
                        std::cout << "[DEBUG] " << amountInput << std::endl;
                    }
                    catch (std::string& e) {
                        std::cerr << "[DEBUG] " << e << std::endl;
                        isAcceptBoxActive = false;
                        continue;
                    }
                }
                else if (!(interfaceRect.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))) {
                    return;
                }
                break;

            case sf::Event::TextEntered:
                if (event.text.unicode < 128 && event.text.unicode != 8) {
                    char enteredChar = static_cast<char>(event.text.unicode);
                    if (isReceiverActive) {
                        receiverInput += enteredChar;
                        receiver.setString(receiverInput);
                    }
                    else if (isamountActive) {
                        amountInput += enteredChar;
                        amount.setString(amountInput);
                    }
                }
                else if (event.text.unicode == 8) {
                    if (isReceiverActive && !receiverInput.empty()) {
                        receiverInput.pop_back();
                        receiver.setString(receiverInput);
                    }
                    else if (isamountActive && !amountInput.empty()) {
                        amountInput.pop_back();
                        amount.setString(amountInput);
                    }
                }
                break;
            }
            window.clear(sf::Color::White);
            window.draw(bgBank);
            window.draw(dimRect);
            window.draw(interfaceRect);
            window.draw(receiverBox);
            window.draw(receiverText);
            window.draw(amountBox);
            window.draw(amountText);
            window.draw(receiver);
            window.draw(amount);
            window.draw(bankIcon);

            switch (event.type) {
            case sf::Event::MouseButtonPressed:
                if (activeAcceptBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)) && isAcceptBoxActive) {
                    isAcceptBoxActive = true;
                    std::cout << "[DEBUG] Active box" << std::endl;
                    try {
                        if (isValidInput(amountInput)) {
                            double amountValue = std::stod(amountInput);
                            if (amountValue > 0) {
                                atmInterface.transfer(send_us_name, receiverInput, amountValue);
                                std::cout << "Valid input. Double value: " << amountValue << std::endl;
                            }
                            else {
                                std::cout << "Input cannot be less than 0." << std::endl;
                            }
                        }
                        else
                        {
                            std::cout << "Invalid input. More than two decimal places " << std::endl;
                        }
                    }
                    catch (const std::invalid_argument& e) {

                    }
                    catch (const std::out_of_range& e) {

                    }
                }
                else if (inactiveAcceptBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)) && isAcceptBoxActive) {
                    isAcceptBoxActive = false;
                    std::cout << "[DEBUG] Inactive box" << std::endl;
                }
            }
            window.draw(acceptText);
            window.draw(activeAcceptBox);
            window.draw(inactiveAcceptBox);
            window.display();
        }
    }

}

void BankInterface::depositInterface(sf::RenderWindow& window, const std::string& send_us_name) {
    setInterface();
    sf::RectangleShape depositBox(REGISTER_BOX_SIZE);
    sf::RectangleShape amountBox(REGISTER_BOX_SIZE);
    sf::RectangleShape activeAcceptBox(REGISTER_BOX_SIZE);
    sf::RectangleShape inactiveAcceptBox(REGISTER_BOX_SIZE);
    sf::Vector2f basePosition(180, 180);

    sf::Text depositText("Wplata", clsFont, FONT_SIZE);
    depositText.setFillColor(sf::Color::Black);
    sf::Text amountText("Kwota", clsFont, FONT_SIZE);
    amountText.setFillColor(sf::Color::Black);
    float spacing = 60.f;
    float shift = 180.f;
    float baseX = basePosition.x;
    float baseY = basePosition.y;

    depositText.setPosition(baseX, baseY + 4 * spacing);
    shapeInit(depositBox, RECT_COLOR, sf::Vector2f(baseX + shift, baseY + 4 * spacing), 1, OUTLINE_COLOR);

    amountText.setPosition(baseX, baseY + 5 * spacing);
    shapeInit(amountBox, RECT_COLOR, sf::Vector2f(baseX + shift, baseY + 5 * spacing), 1, OUTLINE_COLOR);

    sf::Vector2f acceptBoxPosition(baseX + 650, baseY + 5 * spacing);
    shapeInit(activeAcceptBox, sf::Color::Green, acceptBoxPosition, 1, OUTLINE_COLOR);
    shapeInit(inactiveAcceptBox, RECT_COLOR, acceptBoxPosition, 1, OUTLINE_COLOR);
    std::string amountInput{ "" };

    sf::Text amount("", clsFont, FONT_SIZE);
    amount.setFillColor(sf::Color::Black);

    amount.setPosition(amountBox.getPosition().x + 5, amountBox.getPosition().y);

    sf::Text acceptText("Potwierdzam depozyt", clsFont, FONT_SIZE);
    acceptText.setFillColor(sf::Color::Black);
    acceptText.setPosition(basePosition.x + 600, basePosition.y + 4 * spacing - FONT_SIZE);
    bankIcon.setPosition(acceptText.getPosition().x - 275, acceptText.getPosition().y - 275);

    bool isamountActive = false;
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
                if (amountBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) { // jesli kliknieto dany przycisk
                    isamountActive = true;
                    isAcceptBoxActive = false;
                }
                else if (activeAcceptBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    isamountActive = false;
                    isAcceptBoxActive = true;
                    try {
                        if (isValidInput(amountInput)) {
                            double amountValue = std::stod(amountInput);
                            if (amountValue > 0) {
                                atmInterface.deposit(send_us_name, amountValue);
                                std::cout << "Valid input. Double value: " << amountValue << std::endl;
                            }
                            else {
                                std::cout << "Input cannot be less than 0." << std::endl;
                            }
                        }
                        else
                        {
                            std::cout << "Invalid input. More than two decimal places " << std::endl;
                        }
                    }
                    catch (const std::invalid_argument& e) {
                        
                    }
                    catch (const std::out_of_range& e) {
                        
                    }
                }
                else if (!(interfaceRect.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))) {
                    return;
                }
                break;

            case sf::Event::TextEntered:
                if (isamountActive) {
                    if (event.text.unicode < 128 && event.text.unicode != 8) {
                        char enteredChar = static_cast<char>(event.text.unicode);
                        amountInput += enteredChar;
                        amount.setString(amountInput);
                    }
                    else if (event.text.unicode == 8 && !amountInput.empty()) {
                        amountInput.pop_back();
                        amount.setString(amountInput);
                    }
                }
                break;
            }
        }

        window.clear(sf::Color::White);
        window.draw(bgBank);
        window.draw(dimRect);
        window.draw(interfaceRect);
        window.draw(amountBox);
        window.draw(amountText);
        window.draw(amount);
        window.draw(acceptText);
        window.draw(bankIcon);
        if (isAcceptBoxActive) {
            window.draw(activeAcceptBox);
        }
        else {
            window.draw(inactiveAcceptBox);
        }

        window.display();
    }
}

void BankInterface::reportInterface(sf::RenderWindow& window, const std::string& send_us_name) {
    setInterface();

    sf::RectangleShape activeAcceptBox(REGISTER_BOX_SIZE);
    sf::RectangleShape inactiveAcceptBox(REGISTER_BOX_SIZE);

    sf::Vector2f basePosition(50, 50);

    float spacing = 30.f;
    float shift = 0.f;
    float baseX = basePosition.x;
    float baseY = basePosition.y;

    sf::Vector2f acceptBoxPosition(window.getSize().x - 150, window.getSize().y - 100);

    sf::Text acceptText("Wyjdz", clsFont, FONT_SIZE);
    acceptText.setFillColor(sf::Color::Black);
    acceptText.setPosition(acceptBoxPosition.x, acceptBoxPosition.y - FONT_SIZE);
    bankIcon.setPosition(acceptText.getPosition().x - 275, acceptText.getPosition().y - 275);
    bool isAcceptBoxActive = false;

    ATM atm;
    std::string report = atm.generate_report(send_us_name);

    std::vector<std::string> reportLines;
    std::istringstream reportStream(report);
    std::string line;
    while (std::getline(reportStream, line)) {
        reportLines.push_back(line);
    }

    std::vector<sf::Text> reportTextLines;
    for (size_t i = 0; i < reportLines.size(); ++i) {
        sf::Text textLine;
        textLine.setFont(clsFont);
        textLine.setString(reportLines[i]);
        textLine.setCharacterSize(FONT_SIZE);
        textLine.setFillColor(sf::Color::Black);
        textLine.setPosition(baseX + shift, baseY + i * (FONT_SIZE + 5)); // Adjusted line spacing
        reportTextLines.push_back(textLine);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonPressed:
                if (activeAcceptBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    isAcceptBoxActive = true;
                    std::cout << "[DEBUG] Active box" << std::endl;
                }
                else if (inactiveAcceptBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    isAcceptBoxActive = false;
                    std::cout << "[DEBUG] Inactive box" << std::endl;
                }
                else if (isAcceptBoxActive) {
                    try {
                        std::cout << "[DEBUG] OK" << std::endl;
                    }
                    catch (std::string& e) {
                        std::cerr << "[DEBUG] " << e << std::endl;
                        isAcceptBoxActive = false;
                        continue;
                    }
                }
                else if (acceptText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    return;
                }
                break;
            }
        }

        window.clear(sf::Color::White);

        for (const auto& textLine : reportTextLines) {
            window.draw(textLine);
        }
        window.draw(acceptText);

        window.display();
    }
}

void BankInterface::withdrawInterface(sf::RenderWindow& window, const std::string& send_us_name) {
    setInterface();

    sf::RectangleShape withdrawBox(REGISTER_BOX_SIZE);
    sf::RectangleShape amountBox(REGISTER_BOX_SIZE);
    sf::RectangleShape activeAcceptBox(REGISTER_BOX_SIZE);
    sf::RectangleShape inactiveAcceptBox(REGISTER_BOX_SIZE);
    sf::Vector2f basePosition(180, 180);

    sf::Text withdrawText("Wyplata", clsFont, FONT_SIZE);
    withdrawText.setFillColor(sf::Color::Black);
    float spacing = 60.f;
    float shift = 180.f;
    float baseX = basePosition.x;
    float baseY = basePosition.y;

    withdrawText.setPosition(baseX, baseY + 4 * spacing);
    shapeInit(withdrawBox, RECT_COLOR, sf::Vector2f(baseX + shift, baseY + 4 * spacing), 1, OUTLINE_COLOR);

    sf::Text amountText("Kwota", clsFont, FONT_SIZE);
    amountText.setFillColor(sf::Color::Black);

    amountText.setPosition(baseX, baseY + 5 * spacing);
    shapeInit(amountBox, RECT_COLOR, sf::Vector2f(baseX + shift, baseY + 5 * spacing), 1, OUTLINE_COLOR);

    sf::Vector2f acceptBoxPosition(baseX + 650, baseY + 5 * spacing);
    shapeInit(activeAcceptBox, sf::Color::Green, acceptBoxPosition, 1, OUTLINE_COLOR);
    shapeInit(inactiveAcceptBox, RECT_COLOR, acceptBoxPosition, 1, OUTLINE_COLOR);

    std::string amountInput;

    sf::Text amount("", clsFont, FONT_SIZE);
    amount.setFillColor(sf::Color::Black);
    amount.setPosition(amountBox.getPosition().x + 5, amountBox.getPosition().y);

    sf::Text acceptText("Potwierdzam wyplate", clsFont, FONT_SIZE);
    acceptText.setFillColor(sf::Color::Black);
    acceptText.setPosition(basePosition.x + 575, basePosition.y + 4 * spacing - FONT_SIZE);

    bool isAmountActive = false;
    bool isAcceptBoxActive = false;

    while (window.isOpen()) {
        sf::Event event;
        sf::Vector2i mousePos;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonPressed:
                mousePos = sf::Mouse::getPosition(window);
                if (amountBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    isAmountActive = true;
                    isAcceptBoxActive = false;
                }
                else if (activeAcceptBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    isAmountActive = false;
                    isAcceptBoxActive = true;
                    try {
                        if (isValidInput(amountInput)) {
                            double amountValue = std::stod(amountInput);
                            if (amountValue > 0) {
                                atmInterface.withdraw(send_us_name, amountValue);
                                std::cout << "Valid input. Double value: " << amountValue << std::endl;
                            }
                            else {
                                std::cout << "Input cannot be less than 0." << std::endl;
                            }
                        }
                        else
                        {
                            std::cout << "Invalid input. More than two decimal places " << std::endl;
                        }
                    }
                    catch (const std::invalid_argument& e) {
                        std::cerr << "Invalid input for amount: " << amountInput << std::endl;
                    }
                    catch (const std::out_of_range& e) {
                        std::cerr << "Amount out of range: " << amountInput << std::endl;
                    }
                    amountInput.clear();
                    amount.setString(amountInput);
                }
                else if (!(interfaceRect.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))) {
                    return;
                }
                break;

            case sf::Event::TextEntered:
                if (isAmountActive) {
                    if (event.text.unicode < 128 && event.text.unicode != 8) {
                        char enteredChar = static_cast<char>(event.text.unicode);
                        if (std::isdigit(enteredChar) || enteredChar == '.') {
                            amountInput += enteredChar;
                            amount.setString(amountInput);
                        }
                    }
                    else if (event.text.unicode == 8 && !amountInput.empty()) {
                        amountInput.pop_back();
                        amount.setString(amountInput);
                    }
                }
                break;

            default:
                break;
            }
        }

        window.clear(sf::Color::White);
        window.draw(bgBank);
        window.draw(dimRect);
        window.draw(interfaceRect);
        window.draw(amountBox);
        window.draw(amountText);
        window.draw(amount);
        window.draw(bankIcon);
        window.draw(acceptText);
        if (isAcceptBoxActive) {
            window.draw(activeAcceptBox);
        }
        else {
            window.draw(inactiveAcceptBox);
        }
        window.display();
    }
}