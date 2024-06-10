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


#define WIDTH 1280
#define HEIGHT 720
#define MAIN_NAME "Bank Application"
#define BANK_NAME "My Bank"
#define FONT_SIZE 30
#define REG_GAPS 20

#define MENU_LOGIN_SIZE sf::Vector2f(300, 350)
#define SCR_MIDPOINT sf::Vector2f(WIDTH / 2, HEIGHT / 2)
//#define MENU_LOGIN_SIZE sf::Vector2f(600, 300)
#define MENU_RECT_SIZE sf::Vector2f(200, 50)
#define REGISTER_OPTIONS_SIZE sf::Vector2f(340, 500)
#define REGISTER_RECT_SIZE sf::Vector2f(1080, 520)
#define BACKGROUND_WIDTH 0.265f
#define BACKGROUND_HEIGHT 0.210f
#define BANK_SIZE 30
#define BANK_SCALE 0.5f
#define BANK_POS 25.f

#define RELATIVE_POSITION sf::Vector2f(SCR_MIDPOINT.x - MENU_LOGIN_SIZE.x / 2, SCR_MIDPOINT.y - MENU_LOGIN_SIZE.y / 2)
#define RECT_COLOR sf::Color::White
#define OUTLINE_COLOR sf::Color::Black
#define DIM_RECT sf::Color(0, 0, 0, 150)

#define BACKGROUND_PATH "../Bankomat/resources/textures/background.jpg"
#define STANDARD_ACCOUNT_PATH "../Bankomat/resources/textures/StandardAccText.jpg"
#define CHILD_ACCOUNT_PATH "../Bankomat/resources/textures/ChildAccText.jpg"
#define SENIOR_ACCOUNT_PATH "../Bankomat/resources/textures/bank.png"
#define BANK_ICO_PATH "../Bankomat/resources/textures/bank.png"
#define FONT_PATH "../Bankomat/resources/PtRoot.ttf"

#define ACCOUNT_OPTION sf::Vector2f(200, 300)
#define STANDARD_ACCOUNT_SCALE 0.0215f
#define CHILD_ACCOUNT_SCALE 0.085f
#define REGISTER_BOX_SIZE sf::Vector2f(200, 30)



void shapeInit(sf::RectangleShape&, const sf::Color&, const sf::Vector2f&, const int&, const sf::Color&);
void buttonInit(sf::RectangleShape&, const sf::Color&, const sf::Vector2f&, const int&, const sf::Color&);
class WindowInit {
public:
    WindowInit(sf::Font&);
    friend void shapeInit(sf::RectangleShape&, const sf::Color&, const sf::Vector2f&, const int&, const sf::Color&);
    friend void buttonInit(sf::RectangleShape&, const sf::Color&, const sf::Vector2f&, const int&, const sf::Color&);
    void menuSiteAccessor();
    ~WindowInit();
protected:
    sf::Font menuFont;
    sf::RenderWindow window;
    sf::RectangleShape dimRect;
};

class MenuInit {
public:
    MenuInit(sf::Font&);
    friend void shapeInit(sf::RectangleShape&, const sf::Color&, const sf::Vector2f&, const int&, const sf::Color&);
    friend void buttonInit(sf::RectangleShape&, const sf::Color&, const sf::Vector2f&, const int&, const sf::Color&);
    void loginSiteAccessor(sf::RenderWindow&);
    void registerSiteAccessor(sf::RenderWindow&);
    ~MenuInit();
    void setMenu();
    void drawMenu(sf::RenderWindow&);
    void showMenu(sf::RenderWindow&);
private:
    sf::Font clsFont;
    sf::Sprite bgBank;
    sf::Texture bgBankT;
    sf::RectangleShape dimRect;
    sf::Text bankName;
    sf::RectangleShape loginMenuRect;
    sf::RectangleShape loginOptionBox;
    sf::Text loginOptionText;
    sf::RectangleShape registerOptionBox;
    sf::Text registerOptionText;
    sf::RectangleShape exitOptionBox;
    sf::Text exitOptionText;
};

class LoginInit {
public:
    LoginInit(sf::Font& font, sf::RectangleShape& loginMenuRect,
        sf::RectangleShape& loginOptionBox, sf::Text& loginOptionText);
    friend void shapeInit(sf::RectangleShape&, const sf::Color&, const sf::Vector2f&, const int&, const sf::Color&);
    friend void buttonInit(sf::RectangleShape&, const sf::Color&, const sf::Vector2f&, const int&, const sf::Color&);
    ~LoginInit();
    void drawLoginMenu(sf::RenderWindow&);
    void showLoginMenu(sf::RenderWindow&);
private:
    sf::Font clsFont;
    sf::Sprite bgBank;
    sf::Texture bgBankT;
    sf::RectangleShape dimRect;
    sf::RectangleShape loginMenuRect;
    sf::RectangleShape loginOptionBox;
    sf::Text loginOptionText;
    sf::RectangleShape passwordOptionBox;
    sf::Text passwordOptionText;

};

class RegisterInit {
public:
    RegisterInit(sf::Font& font);
    friend void shapeInit(sf::RectangleShape&, const sf::Color&, const sf::Vector2f&, const int&, const sf::Color&);
    friend void buttonInit(sf::RectangleShape&, const sf::Color&, const sf::Vector2f&, const int&, const sf::Color&);
    virtual ~RegisterInit();
    void showRegisterMenu(sf::RenderWindow&);
    void setRegisterMenu();
    void drawRegisterMenu(sf::RenderWindow&);
    void createAccount(sf::RenderWindow&, AccountType);
private:
    sf::Font clsFont;
    sf::Sprite bgBank;
    sf::Texture bgBankT;
    sf::RectangleShape dimRect;
    sf::RectangleShape registerRect; // inicjalizacja
    sf::Sprite standardAccountIcon;
    sf::Texture standardAccontIconT;
    sf::Sprite childAccountIcon;
    sf::Texture childAccountIconT;
    sf::Sprite seniorAccountIcon;
    sf::Texture seniorAccountIconT;
    sf::Sprite bankIcon;
    sf::Texture bankIconT;
    sf::RectangleShape childOptionRect;
    sf::RectangleShape standardOptionRect;
    sf::RectangleShape seniorOptionRect;
    sf::Text standardText;
    sf::Text childText;
    sf::Text seniorText;
};

