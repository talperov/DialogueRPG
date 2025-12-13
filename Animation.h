#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
private:
    // Character textures and sprites
    sf::Texture animeTexture;
    sf::Texture greekTexture;
    // sf::Texture goldTexture; 
    sf::Sprite animeSprite;
    sf::Sprite greekSprite;
    // sf::Sprite goldSprite;

    // Background texture and sprite
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    // Menu button textures and sprites
    sf::Texture playTex;
    sf::Texture helpTex;
    sf::Texture exitTex;
    sf::Sprite playSprite;
    sf::Sprite helpSprite;
    sf::Sprite exitSprite;

public:
    Animation();

    // Character creation
    bool createAnime();
    bool createGreek();
    // bool createGold();

    // Backgrounds
    bool loadBackground(const sf::RenderWindow& window);
    bool loadMenuBackground(const sf::RenderWindow& window);

    // Menu buttons
    bool loadMenuButtons();

    // Getters
    sf::Sprite& getAnimeSprite();
    sf::Sprite& getGreekSprite();
    // sf::Sprite& getGoldSprite();
    sf::Sprite& getBackground();
    sf::Sprite& getPlaySprite();
    sf::Sprite& getHelpSprite();
    sf::Sprite& getExitSprite();
};
