#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "../include/mainMenu.h"
#include "../include/Status.h"

//void setBackground(sf::Sprite& background) {
//    sf::Texture tbg;
//    if (!tbg.loadFromFile(BG_PATH)) {
//        throw std::string("Cannot load the texture.");
//    }
//    background.setTexture(tbg);
//    background.setScale(BG_WIDTH_SCALE, BG_HEIGHT_SCALE);
//      zobaczyc potem czemu nie dziala
//}
extern void initLogMenu(sf::RenderWindow* window);
void setBankTexture(sf::Texture& tbank_ico) {
    if (!tbank_ico.loadFromFile(BANK_ICO_PATH)) {
        throw std::string("Cannot load the texture.");
    }
    tbank_ico.setSmooth(true);
}

void setBankIcon(sf::Sprite& bank_ico, const sf::Texture& texture) {
    bank_ico.setTexture(texture);
    bank_ico.setScale(BANK_SCALE, BANK_SCALE);
    bank_ico.setPosition(sf::Vector2f(BANK_POS, BANK_POS)); // absolute position
}

void setBankName(sf::Text& bank_name, const sf::Vector2<unsigned int>& iconSize) {
    bank_name.setFillColor(sf::Color::Red);
    bank_name.setPosition(BANK_POS + (iconSize.x * BANK_SCALE) / 2 + X_NAME_POS, BANK_POS + (iconSize.y * BANK_SCALE) / 2); // wywalic tego tasiemca kiedys
}

void initInterface(const int& width, const int& height) {
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(width, height), MAIN_NAME);
    window->setVerticalSyncEnabled(true);
    // setBackground(bg);

    sf::Sprite bg;
    sf::Texture tbg;
    if (!tbg.loadFromFile(BG_PATH)) {
        throw std::string("Cannot load the texture.");
    }

    bg.setTexture(tbg);
    bg.setScale(BG_WIDTH_SCALE, BG_HEIGHT_SCALE);

    sf::Texture tBankIcon;
    setBankTexture(tBankIcon);
    sf::Sprite bankIcon;
    setBankIcon(bankIcon, tBankIcon);
    auto bankIcoSz = tBankIcon.getSize();

    sf::Font font;
    if (!font.loadFromFile(FONT_PATH)) {
        throw std::string("Cannot load the font.");
    }
    sf::Text bankName(BANK_NAME, font, 30);
    setBankName(bankName, bankIcoSz);

    sf::RectangleShape dimRect(sf::Vector2f(width, height));
    dimRect.setFillColor(sf::Color(0, 0, 0, 150)); // Semi-transparent black
    
    // Create text for options
    sf::Text loginText("Zaloguj sie", font, 30);
    sf::Text registerText("Rejestracja", font, 30);
    sf::Text exitText("Wyjdz", font, 30);

    // Set position for options
    sf::Vector2f midValues(width / 2 - 75, height / 2); //565, 360
    loginText.setPosition(midValues);
    midValues.y += 100;
    registerText.setPosition(midValues);
    midValues.y += 100;
    exitText.setPosition(midValues);
    
    // fajny interfejs potem, byle dziala.

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window->close();

            // Check if mouse clicked
            if (event.type == sf::Event::MouseButtonPressed) {
                // Get mouse position
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

                // Check if clicked on LOGIN
                if (loginText.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    // Handle login
                    // For now, just print a message
                    std::cout << "LOGIN clicked!" << std::endl;
                    initLogMenu(window);
                }

                // Check if clicked on REGISTER
                if (registerText.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    // Handle register
                    // For now, just print a message
                    std::cout << "REGISTER clicked!" << std::endl;
                }

                // Check if clicked on EXIT
                if (exitText.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    // Close window
                    window->close();
                }
            }
        }
        window->clear(sf::Color::White);
        window->draw(bg); // przesunac na lepszy
        window->draw(dimRect);
        window->draw(bankIcon);
        window->draw(bankName);

        window->draw(loginText);
        window->draw(registerText);
        window->draw(exitText);
        window->display();
    }
}   

// wrzucic to w klase
// login -> strona bankowa
// rejestracja -> baza danych -> login
// exit -> exit


void initLogMenu(sf::RenderWindow* window) {
    window->setVerticalSyncEnabled(true);
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
        }
        window->clear(sf::Color::White);
        window->display();
    }
}












