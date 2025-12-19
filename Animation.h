#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
public:
    // Character textures and sprites
    sf::Texture animeTexture;
    sf::Texture greekTexture;
    // sf::Texture goldTexture; 
    sf::Sprite animeSprite;
    sf::Sprite greekSprite;
    // sf::Sprite goldSprite;

    // Enemy sprite
    sf::Texture enemyTexture;  // Enemy texture
    sf::Sprite enemySprite;    // Enemy sprite

    // Background texture and sprite
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Texture textTexture;

    // Menu button textures and sprites
    sf::Texture playTex;
    sf::Texture helpTex;
    sf::Texture exitTex;
    sf::Sprite playSprite;
    sf::Sprite helpSprite;
    sf::Sprite exitSprite;

    //Text Bubble Textures and Sprites
    sf::Texture textBubbleTexture; // Bubble texture
    sf::Sprite  textBubbleSprite;  // Bubble sprite

    Animation();
    ~Animation();


    // Character creation
    bool createAnime();
    bool createGreek();
    // bool createGold();

    // Backgrounds
    bool loadBackground(const sf::RenderWindow& window);
    bool loadMenuBackground(const sf::RenderWindow& window);

    // Menu buttons
    bool loadMenuButtons();

    //Text Bubble
    bool loadTextBubble();


    // Functions to create enemy
    bool createEnemy(const std::string& filePath, sf::Vector2f position, float scale = 1.5f);
    sf::Sprite& getEnemySprite(); // Access enemy sprite

    // Getters
    sf::Sprite& getAnimeSprite();
    sf::Sprite& getGreekSprite();
    sf::Sprite& getTextBubbleSprite();
    // sf::Sprite& getGoldSprite();
    sf::Sprite& getBackground();
    sf::Sprite& getPlaySprite();
    sf::Sprite& getHelpSprite();
    sf::Sprite& getExitSprite();
};