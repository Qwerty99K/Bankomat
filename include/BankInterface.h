#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "../include/WindowInit.h"
#include "../include/StandardAccount.h"
#include "../include/ChildAccount.h"
#include "../include/SeniorAccount.h"
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
    void transferInterface(sf::RenderWindow&, const std::string&);
    void setTransferInterface();
    void setInterface();
    void reportInterface(sf::RenderWindow&, const std::string&);
    void withdrawInterface(sf::RenderWindow&, const std::string&);
    void depositInterface(sf::RenderWindow&, const std::string&);


private:
    sf::Font clsFont;
    sf::Sprite bgBank; 
    sf::Texture bgBankT; 
    sf::Sprite profilePicture; 
    sf::Texture profilePictureT;
    sf::Sprite bankIcon;
    sf::Texture bankTexture;

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
    sf::RectangleShape depositBox;

    sf::Text nameText;
    sf::Text lastNameText;
    sf::Text addressText;
    sf::Text ageText;
    sf::Text generateRaportText;
    sf::Text loginText;
    sf::Text balanceText;
    sf::Text transferText;
    sf::Text withdrawText;
    sf::Text depositText;
    std::vector<std::string> userDetails;

    WarningBox warning;
    GrantedBox granted;
};

