#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#define MAIN_NAME "Menu"
#define BANK_NAME "Bank Slonski"
#define BANK_ICO_PATH "../Bankomat/resources/textures/bank.png"
#define BANK_SCALE 0.2f
#define BANK_POS 25.f

#define FONT_PATH "../Bankomat/resources/PtRoot.ttf"

#define BG_PATH "../Bankomat/resources/textures/background.jpg"
#define BG_WIDTH_SCALE 0.265f
#define BG_HEIGHT_SCALE 0.210f
#define X_NAME_POS 100

#define WIDTH 1280
#define HEIGHT 720

#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 50

#define BGRECT_WIDTH 300
#define BGRECT_HEIGHT 350

#define FONT_SIZE 30

#define REG_GAPS 20

#define ST_ACC_SCALE 0.0215f
#define C_ACC_SCALE 0.085f


#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class WindowInit {
public:
    WindowInit();

    // Initializes the main menu loop
    void menuInit();

private:
    sf::RenderWindow window;

    // Textures and Sprites
    sf::Texture menuBGTexture;
    sf::Sprite menuBackground;
    sf::Texture bankIcoTexture;
    sf::Sprite bankIco;
    sf::Vector2u bankIcoSz;

    // Font and Text
    sf::Font menuFont;
    sf::Text bankName;
    sf::Text logText;
    sf::Text regText;
    sf::Text exitText;
    sf::Text passText;

    sf::Text stAccText;
    sf::Text cAccText;
    sf::Text seAccText;

    // Shapes
    sf::RectangleShape dimRect;
    sf::RectangleShape regRect;
    sf::RectangleShape logRect;
    sf::RectangleShape logButton;
    sf::RectangleShape regButton;
    sf::RectangleShape exitButton;
    sf::RectangleShape loginBox;
    sf::RectangleShape passwordBox;

    sf::Texture CAccTexture;
    sf::Sprite CAccIcon;
    sf::RectangleShape CAccOptionRect;

    sf::Texture StAccTexture;
    sf::Sprite StAccIcon;
    sf::RectangleShape StAccOptionRect;
    
    sf::Texture SeAccTexture;
    sf::Sprite SeAccIcon;
    sf::RectangleShape SeAccOptionRect;

    sf::Texture logTexture;
    sf::Sprite logIcon;

    sf::Texture regTexture;
    sf::Sprite regIcon;

    // Initialize functions
    void TexturesInit();
    void FontsInit();
    void ShapesInit();
    void TextInit();
    void ButtonInit(sf::RectangleShape& button, const sf::Vector2f& size);
    void SetText(sf::Text& text, const std::string& str, sf::Color color);

    // Position setting function
    void setMenuPos();

    // Menu drawing
    void drawMainMenu();
    void drawLoginMenu();
    void drawRegMenu();

    // Additional menu initializers
    void loginMenuInit();
    void regMenuInit();
};


