#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "../include/WindowInit.h"
#include "../include/StandardAccount.h"
#include "../include/ChildAccount.h"
#include "../include/SeniorAccount.h"
#include "../include/Status.h"
#include "../include/ATM.h"
#include <memory>
#include <iostream>
#include <stdexcept>
#include <vector>


#define WIDTH 1280
#define HEIGHT 720
#define MAIN_NAME "Aplikacja banku"
#define BANK_NAME "Moj bank"
#define FONT_SIZE 30
#define REG_GAPS 20

#define MENU_LOGIN_SIZE sf::Vector2f(300, 350)
#define SCR_MIDPOINT sf::Vector2f(WIDTH / 2, HEIGHT / 2)
#define MENU_RECT_SIZE sf::Vector2f(200, 50)
#define REGISTER_OPTIONS_SIZE sf::Vector2f(340, 500)
#define REGISTER_RECT_SIZE sf::Vector2f(1080, 520)
#define BACKGROUND_WIDTH 0.265f
#define BACKGROUND_HEIGHT 0.210f
#define BANK_SIZE 30
#define BANK_SCALE 0.5f
#define BANK_POS 25.f
#define PROFILE_SCALE sf::Vector2f(0.35, 0.35)

#define RELATIVE_POSITION sf::Vector2f(SCR_MIDPOINT.x - MENU_LOGIN_SIZE.x / 2, SCR_MIDPOINT.y - MENU_LOGIN_SIZE.y / 2)
#define RECT_COLOR sf::Color::White
#define OUTLINE_COLOR sf::Color::Black
#define DIM_RECT sf::Color(0, 0, 0, 150)

#define BACKGROUND_PATH "../Bankomat/resources/textures/background.jpg"
#define STANDARD_ACCOUNT_PATH "../Bankomat/resources/textures/StandardAccText.jpg"
#define CHILD_ACCOUNT_PATH "../Bankomat/resources/textures/ChildAccText.jpg"
#define SENIOR_ACCOUNT_PATH "../Bankomat/resources/textures/StandardAccText.jpg"
#define BANK_ICO_PATH "../Bankomat/resources/textures/bank.png"
#define FONT_PATH "../Bankomat/resources/PtRoot.ttf"
#define PROFILE_PATH "../Bankomat/resources/textures/user_picture.png"

#define ACCOUNT_OPTION sf::Vector2f(200, 300)
#define STANDARD_ACCOUNT_SCALE 0.0215f
#define CHILD_ACCOUNT_SCALE 0.085f
#define REGISTER_BOX_SIZE sf::Vector2f(200, 30)
#define INTERFACE_BOX_SIZE sf::Vector2f(250, 60)

void shapeInit(sf::RectangleShape&, const sf::Color&, const sf::Vector2f&, const int&, const sf::Color&);
void buttonInit(sf::RectangleShape&, const sf::Color&, const sf::Vector2f&, const int&, const sf::Color&);

class WarningBox {
public:
    WarningBox(sf::Font&);
    inline sf::Text showWarning();

private:
    sf::Font clsFont;
    sf::Text warningText;
};

class GrantedBox {
public:
    GrantedBox(sf::Font&);
    inline sf::Text showGranted();
private:
    sf::Font clsFont;
    sf::Text grantedText;
};

class WindowInit {
public:
    WindowInit(sf::Font&);
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
    WarningBox warning;
    GrantedBox granted;
};

class LoginInit {
public:
    LoginInit(sf::Font&, sf::RectangleShape&,
        sf::RectangleShape&, sf::Text&);
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
    WarningBox warning;
    GrantedBox granted;
};

class RegisterInit {
public:
    RegisterInit(sf::Font&);
    virtual ~RegisterInit();
    void showRegisterMenu(sf::RenderWindow&);
    void setRegisterMenu();
    void drawRegisterMenu(sf::RenderWindow&);
    void createAccount(sf::RenderWindow&, AccountType);
    bool checkCredentials(AccountType, const std::string&, const std::string&, 
        const std::string&, const std::string&, const std::string&, const std::string&);
private:
    sf::Font clsFont;
    sf::Sprite bgBank;
    sf::Texture bgBankT;
    sf::RectangleShape dimRect;
    sf::RectangleShape registerRect;
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
    WarningBox warning;
    GrantedBox granted;
};

