#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "../include/WindowInit.h"
#include "../include/StandardAccount.h"
#include "../include/ChildAccount.h"
#include "../include/SeniorAccount.h"
// #include "../include/createEntries.h"
#include "../include/ATM.h"
#include <memory>
#include <iostream>
#include <stdexcept>
#include <vector>


class BankInterface {
public:
    BankInterface(sf::Font&, sf::RectangleShape&, std::vector<std::string>);
    void showInterface(sf::RenderWindow&);
    void drawInterface(sf::RenderWindow&);
    void setInterface();
    /*
    loginMenuRect(loginMenuRect), loginOptionBox(loginOptionBox), loginOptionText(loginOptionText),
    passwordOptionBox(MENU_RECT_SIZE), passwordOptionText("Haslo", font, FONT_SIZE), dimRect(sf::Vector2f(WIDTH, HEIGHT))
    */

private:
    sf::Font clsFont;
    sf::Sprite bgBank; // load
    sf::Texture bgBankT; // load
    sf::Sprite profilePicture; // load
    sf::Texture profilePictureT; // load

    sf::RectangleShape dimRect;
    sf::RectangleShape interfaceRect;

    sf::RectangleShape nameBox;
    sf::RectangleShape lastNameBox;
    sf::RectangleShape addressBox;
    sf::RectangleShape ageBox;
    sf::RectangleShape generateRaportBox;
    sf::RectangleShape loginBox;
    sf::RectangleShape balanceBox;
    sf::RectangleShape transferBox;
    sf::RectangleShape withdrawBox;

    sf::Text nameText;
    sf::Text lastNameText;
    sf::Text addressText;
    sf::Text ageText;
    sf::Text generateRaportText;
    sf::Text loginText;
    sf::Text balanceText;
    sf::Text transferText;
    sf::Text withdrawText;
    std::vector<std::string> userDetails;
};

