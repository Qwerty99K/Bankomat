#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "../include/WindowInit.h"
#include "../include/Status.h"


WindowInit::WindowInit() {
    window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), MAIN_NAME);
    window->setVerticalSyncEnabled(true);

    if (!(menuBGTexture)->loadFromFile(BG_PATH)) {
        throw std::string("Cannot load the texture.");
    }
    menuBackground->setTexture(*menuBGTexture);
    menuBackground->setScale(BG_WIDTH_SCALE, BG_HEIGHT_SCALE);
    
    if (!bankIcoTexture->loadFromFile(BANK_ICO_PATH)) { 
        throw std::string("Cannot load the texture."); 
    }
    bankIcoTexture->setSmooth(true);

    bankIco->setTexture(*bankIcoTexture);
    bankIco->setScale(BANK_SCALE, BANK_SCALE);
    bankIco->setPosition(sf::Vector2f(BANK_POS, BANK_POS)); // absolute position

    bankIcoSz = bankIcoTexture->getSize();

    if (!menuFont->loadFromFile(FONT_PATH)) { 
        throw std::string("Cannot load the font."); 
    }
    bankName = new sf::Text(BANK_NAME, *menuFont, 30);
    bankName->setFillColor(sf::Color::Red);
    bankName->setPosition(BANK_POS + (bankIcoSz.x * BANK_SCALE) / 2 + X_NAME_POS, BANK_POS + (bankIcoSz.y * BANK_SCALE) / 2); // wywalic tego tasiemca kiedys

    dimRect = new sf::RectangleShape(sf::Vector2f(WIDTH, HEIGHT));
    dimRect->setFillColor(sf::Color(0, 0, 0, 150)); // Semi-transparent black

    // Create text for options
    logText = new sf::Text("Zaloguj sie", *menuFont, 30);
    regText = new sf::Text("Rejestracja", *menuFont, 30);
    exitText = new sf::Text("Wyjdz", *menuFont, 30);

    // Set position for options
    scrPosition = new sf::Vector2f(WIDTH / 2 - 75, HEIGHT/ 2); //565, 360

    // Set positions
    bgButton = new sf::RectangleShape(sf::Vector2f(400, 300));
    bgButton->setFillColor(sf::Color(253, 233, 236, 30)); // White with 150 alpha (semi-transparent)
    bgButton->setPosition(*scrPosition);

    logButton = new sf::RectangleShape(sf::Vector2f(225, 75));
    logButton->setFillColor(sf::Color::Green);
    logButton->setPosition(*scrPosition);
    logText->setPosition(*scrPosition);

    scrPosition->y += 100;
    regButton = new sf::RectangleShape(sf::Vector2f(200, 50));
    regButton->setFillColor(sf::Color::Blue);
    regButton->setPosition(*scrPosition);
    regText->setPosition(*scrPosition);

    scrPosition->y += 100;
    exitButton = new sf::RectangleShape(sf::Vector2f(200, 50));
    exitButton->setFillColor(sf::Color::Red);
    exitButton->setPosition(*scrPosition);
    exitText->setPosition(*scrPosition);
}

void WindowInit::menuInit() {
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window->close();

            case sf::Event::MouseButtonPressed:
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                if (logText->getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "LOGIN clicked!" << std::endl;
                    loginMenuInit();
                }
                else if (regText->getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "REGISTER clicked!" << std::endl;
                }
                else if (exitText->getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    window->close();
                }
            }
        }
        window->clear(sf::Color::White);

        window->draw(*menuBackground); // przesunac na lepszy
        window->draw(*dimRect);
        window->draw(*bankIco);
        window->draw(*bankName);

        window->draw(*bgButton);
        window->draw(*logButton);
        window->draw(*logText);

        window->draw(*regButton);
        window->draw(*regText);

        window->draw(*exitButton);
        window->draw(*exitText);
        window->display();
    }
}

void WindowInit::loginMenuInit() {
    while (window->isOpen()) {
        sf::Event event;
        while(window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
        }
    window->display();
    }
}


//while (window->isOpen()) {
//        sf::Event event;
//        while (window->pollEvent(event)) {
//            switch (event.type) {
//            case sf::Event::Closed:
//                window->close();
//
//            case sf::Event::MouseButtonPressed:
//                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
//                if (loginText.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
//                    std::cout << "LOGIN clicked!" << std::endl;
//                    initLogMenu(window);
//                }
//                else if (registerText.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
//                    std::cout << "REGISTER clicked!" << std::endl;
//                } 
//                else if (exitText.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
//                    window->close();
//                }
//            }
//        }        
//        window->clear(sf::Color::White);
//
//        window->draw(bg); // przesunac na lepszy
//        window->draw(dimRect);
//        window->draw(bankIcon);
//        window->draw(bankName);
//
//        window->draw(buttonBg);
//        window->draw(loginButton);
//        window->draw(loginText);
//
//        window->draw(registerButton);
//        window->draw(registerText);
//        
//        window->draw(exitButton);
//        window->draw(exitText);
//        window->display();
//    }
//}  













//void setBackground(sf::Sprite& buttonBg) {
//    sf::Texture tbg;
//    if (!tbg.loadFromFile(BG_PATH)) {
//        throw std::string("Cannot load the texture.");
//    }
//    buttonBg.setTexture(tbg);
//    buttonBg.setScale(BG_WIDTH_SCALE, BG_HEIGHT_SCALE);
//      zobaczyc potem czemu nie dziala
//}

//extern void initLogMenu(sf::RenderWindow* window);
//void setBankTexture(sf::Texture& tbank_ico) {
//    if (!tbank_ico.loadFromFile(BANK_ICO_PATH)) {
//        throw std::string("Cannot load the texture.");
//    }
//    tbank_ico.setSmooth(true);
//}
//
//void setBankIcon(sf::Sprite& bank_ico, const sf::Texture& texture) {
//    bank_ico.setTexture(texture);
//    bank_ico.setScale(BANK_SCALE, BANK_SCALE);
//    bank_ico.setPosition(sf::Vector2f(BANK_POS, BANK_POS)); // absolute position
//}
//
//void setBankName(sf::Text& bank_name, const sf::Vector2<unsigned int>& iconSize) {
//    bank_name.setFillColor(sf::Color::Red);
//    bank_name.setPosition(BANK_POS + (iconSize.x * BANK_SCALE) / 2 + X_NAME_POS, BANK_POS + (iconSize.y * BANK_SCALE) / 2); // wywalic tego tasiemca kiedys
//}
//
//void initInterface(const int& width, const int& height) {
//    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(width, height), MAIN_NAME);
//    window->setVerticalSyncEnabled(true);
//    // setBackground(bg);
//
//    sf::Sprite bg;
//    sf::Texture tbg;
//    if (!tbg.loadFromFile(BG_PATH)) {
//        throw std::string("Cannot load the texture.");
//    }
//
//    bg.setTexture(tbg);
//    bg.setScale(BG_WIDTH_SCALE, BG_HEIGHT_SCALE);
//
//    sf::Texture tBankIcon;
//    setBankTexture(tBankIcon);
//    sf::Sprite bankIcon;
//    setBankIcon(bankIcon, tBankIcon);
//    auto bankIcoSz = tBankIcon.getSize();
//
//    sf::Font font;
//    if (!font.loadFromFile(FONT_PATH)) {
//        throw std::string("Cannot load the font.");
//    }
//    sf::Text bankName(BANK_NAME, font, 30);
//    setBankName(bankName, bankIcoSz);
//
//    sf::RectangleShape dimRect(sf::Vector2f(width, height));
//    dimRect.setFillColor(sf::Color(0, 0, 0, 150)); // Semi-transparent black
//    
//    // Create text for options
//    sf::Text loginText("Zaloguj sie", font, 30);
//    sf::Text registerText("Rejestracja", font, 30);
//    sf::Text exitText("Wyjdz", font, 30);
//
//    // Set position for options
//    sf::Vector2f midValues(width / 2 - 75, height / 2); //565, 360
//
//    // Set positions
//    sf::RectangleShape buttonBg(sf::Vector2f(400, 300));
//    buttonBg.setFillColor(sf::Color(253, 233, 236, 30)); // White with 150 alpha (semi-transparent)
//    buttonBg.setPosition(midValues);
//
//
//
//    // Set colors
//    sf::RectangleShape loginButton(sf::Vector2f(225, 75));
//    loginButton.setFillColor(sf::Color::Green);
//    loginButton.setPosition(midValues);
//    loginText.setPosition(midValues);
//    
//    midValues.y += 100;
//    sf::RectangleShape registerButton(sf::Vector2f(200, 50));
//    registerButton.setFillColor(sf::Color::Blue);
//    registerButton.setPosition(midValues);
//    registerText.setPosition(midValues);
//    
//    midValues.y += 100;
//    sf::RectangleShape exitButton(sf::Vector2f(200, 50));
//    exitButton.setFillColor(sf::Color::Red);
//    exitButton.setPosition(midValues);
//    exitText.setPosition(midValues);
    
    // fajny interfejs potem, byle dziala.
//
//    while (window->isOpen()) {
//        sf::Event event;
//        while (window->pollEvent(event)) {
//            switch (event.type) {
//            case sf::Event::Closed:
//                window->close();
//
//            case sf::Event::MouseButtonPressed:
//                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
//                if (loginText.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
//                    std::cout << "LOGIN clicked!" << std::endl;
//                    initLogMenu(window);
//                }
//                else if (registerText.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
//                    std::cout << "REGISTER clicked!" << std::endl;
//                } 
//                else if (exitText.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
//                    window->close();
//                }
//            }
//        }        
//        window->clear(sf::Color::White);
//
//        window->draw(bg); // przesunac na lepszy
//        window->draw(dimRect);
//        window->draw(bankIcon);
//        window->draw(bankName);
//
//        window->draw(buttonBg);
//        window->draw(loginButton);
//        window->draw(loginText);
//
//        window->draw(registerButton);
//        window->draw(registerText);
//        
//        window->draw(exitButton);
//        window->draw(exitText);
//        window->display();
//    }
//}   

// wrzucic to w klase
// login -> strona bankowa
// rejestracja -> baza danych -> login
// exit -> exit


//void initLogMenu(sf::RenderWindow* window) {
//    while (window->isOpen()) {
//        sf::Event event;
//        while (window->pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window->close();
//            }
//        }
//        //
//        window->display();
//    }
//}












