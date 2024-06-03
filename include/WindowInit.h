#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#define MAIN_NAME "Menu"
#define BANK_NAME "Bank Slonski"
#define BANK_ICO_PATH "../Bankomat/resources/textures/bank.png"
#define BANK_SCALE 0.2f
#define BANK_POS 25.f
#define FONT_PATH "../Bankomat/resources/NerdFont.ttf"
#define BG_PATH "../Bankomat/resources/textures/background.jpg"
#define BG_WIDTH_SCALE 0.265f
#define BG_HEIGHT_SCALE 0.210f
#define X_NAME_POS 100
#define WIDTH 1280
#define HEIGHT 720

class WindowInit {
public:
    WindowInit();
    void menuInit();
    void loginMenuInit();

private:
    sf::RenderWindow window;
    sf::Sprite menuBackground; // bg
    sf::Texture menuBGTexture; // tbg

    sf::Sprite bankIco;
    sf::Vector2u bankIcoSz;
    sf::Texture bankIcoTexture;

    sf::Font menuFont;
    sf::Text bankName;

    sf::Text logText;
    sf::Text regText;
    sf::Text exitText;

    sf::Vector2f scrPosition; // the mid points of screen
    sf::RectangleShape bgButton;
    sf::RectangleShape dimRect;
    sf::RectangleShape logButton;
    sf::RectangleShape regButton;
    sf::RectangleShape exitButton;
};
