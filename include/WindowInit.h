#ifndef WINDOW_INIT_H
#define WINDOW_INIT_H

#include <SFML/Graphics.hpp>
#include <string>

#define WIDTH 1280
#define HEIGHT 720
#define MAIN_NAME "Bank Application"

#define BANK_NAME "My Bank"
#define FONT_SIZE 30
#define MENU_LOGIN_SIZE sf::Vector2f(600, 300)
#define MENU_RECT_SIZE sf::Vector2f(250, 50)
#define BANK_SIZE 30

#define RELATIVE_POSITION sf::Vector2f(300, 150)
#define BANK_POS 50
#define RECT_COLOR sf::Color::White
#define OUTLINE_COLOR sf::Color::Black

#define STANDARD_ACCOUNT_PATH "../Bankomat/resources/textures/StandardAccText.jpg"
#define CHILD_ACCOUNT_PATH "../Bankomat/resources/textures/ChildAccText.jpg"
#define SENIOR_ACCOUNT_PATH "../Bankomat/resources/textures/bank.jpg"
#define BANK_ICO_PATH "../Bankomat/resources/textures/bank.jpg"

#define ACCOUNT_OPTION sf::Vector2f(200, 300)
#define STANDARD_ACCOUNT_SCALE 0.5f
#define CHILD_ACCOUNT_SCALE 0.5f

#define REGISTER_BOX_SIZE sf::Vector2f(250, 50)

class WindowInit {
public:
    WindowInit(const std::string& bgPath, const sf::Font& font);
    ~WindowInit();

protected:
    sf::RenderWindow window;
    sf::Font menuFont;
    sf::RectangleShape dimRect;
    std::string bgPath;

    sf::Texture textureInit(const std::string& texturePath);
    void shapeInit(sf::RectangleShape& obj, const sf::Color& color, const sf::Vector2f& position, const int& thickness, const sf::Color& outlineColor);
    void buttonInit(sf::RectangleShape& obj, const sf::Color& color, const sf::Vector2f& position, const int& thickness, const sf::Color& outlineColor);
};

class MenuInit : public WindowInit {
public:
    MenuInit(const std::string& bgPath, const sf::Font& font);
    ~MenuInit();

    void showMenu();

private:
    sf::Sprite bgBank;
    sf::Text bankName;
    sf::RectangleShape loginMenuRect;
    sf::RectangleShape loginOptionBox;
    sf::Text loginOptionText;
    sf::RectangleShape registerOptionBox;
    sf::Text registerOptionText;
    sf::RectangleShape exitOptionBox;
    sf::Text exitOptionText;

    void setMenu();
    void drawMenu();
};

class LoginInit : public WindowInit {
public:
    LoginInit(const std::string& bgPath, const sf::Font& font, sf::RectangleShape& loginMenuRect,
        sf::RectangleShape& loginOptionBox, sf::Text& loginOptionText);
    ~LoginInit();

    void showLoginMenu();

private:
    sf::Sprite bgBank;
    sf::RectangleShape loginMenuRect;
    sf::RectangleShape loginOptionBox;
    sf::Text loginOptionText;
    sf::RectangleShape passwordOptionBox;
    sf::Text passwordOptionText;

    void drawLoginMenu();
};

class RegisterInit : public WindowInit {
public:
    RegisterInit(const std::string& bgPath, const sf::Font& font, const std::string& stTexturePath,
        const std::string& cTexturePath, const std::string& seTexturePath, const std::string& bankTexturePath);
    ~RegisterInit();

    void showRegisterMenu();

private:
    sf::Sprite bgBank;
    sf::Sprite standardAccountIcon;
    sf::Sprite childAccountIcon;
    sf::Sprite seniorAccountIcon;
    sf::RectangleShape childOptionRect;
    sf::RectangleShape standardOptionRect;
    sf::RectangleShape seniorOptionRect;
    sf::Sprite bankIcon;
    sf::Text standardText;
    sf::Text childText;
    sf::Text seniorText;

    void setRegisterMenu();
    void drawRegisterMenu();
    void createAccount();
};

#endif // WINDOW_INIT_H
