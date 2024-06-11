#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "../include/WindowInit.h"
#include "../include/StandardAccount.h"
#include "../include/ChildAccount.h"
#include "../include/SeniorAccount.h"
#include "../include/createEntries.h"
#include <iostream>
#include <stdexcept>
#include <vector>

class BankInterface {
public:
    BankInterface(sf::Font&, sf::RectangleShape&);
    void showInterface(sf::RenderWindow&);
    void drawInterface(sf::RenderWindow&);
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
    sf::RectangleShape ageBox;
    sf::RectangleShape generateRaportBox;
    sf::RectangleShape loginBox;
    sf::RectangleShape balanceBox;
    sf::RectangleShape transferBox;
    sf::RectangleShape withdrawBox;
};

