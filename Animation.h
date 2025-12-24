#pragma once
#include <SFML/Graphics.hpp>

// Manages animations, sprites, and backgrounds for the game.
class Animation {
public:
    // Character textures and sprites.
    sf::Texture animeTexture;   // Texture for AnimeMan.
    sf::Texture greekTexture;   // Texture for GreekMan.
    sf::Sprite animeSprite;     // Sprite for AnimeMan.
    sf::Sprite greekSprite;     // Sprite for GreekMan.

    // Enemy texture and sprite.
    sf::Texture enemyTexture;   // Texture for enemy.
    sf::Sprite enemySprite;     // Sprite for enemy.

    // Background texture and sprite.
    sf::Texture backgroundTexture;  // Texture for background.
    sf::Sprite backgroundSprite;    // Sprite for background.

    // Menu button textures and sprites.
    sf::Texture playTex;    // Texture for Play button.
    sf::Texture helpTex;    // Texture for Help button.
    sf::Texture exitTex;    // Texture for Exit button.
    sf::Sprite playSprite;  // Sprite for Play button.
    sf::Sprite helpSprite;  // Sprite for Help button.
    sf::Sprite exitSprite;  // Sprite for Exit button.

    // Text bubble texture and sprite.
    sf::Texture textBubbleTexture;  // Texture for text bubble.
    sf::Sprite textBubbleSprite;    // Sprite for text bubble.

    // Constructor.
    Animation();

    // Destructor.
    ~Animation();

    // Load and create AnimeMan sprite.
    bool createAnime();

    // Load and create GreekMan sprite.
    bool createGreek();

    // Load game background.
    bool loadBackground(const sf::RenderWindow& window);

    // Load menu background.
    bool loadMenuBackground(const sf::RenderWindow& window);

    // Load menu buttons.
    bool loadMenuButtons();

    // Load text bubble.
    bool loadTextBubble();

    // Create enemy sprite from file path.
    bool createEnemy(const std::string& filePath, sf::Vector2f position, float scale = 1.5f);

    // Get reference to enemy sprite.
    sf::Sprite& getEnemySprite();

    // Get reference to AnimeMan sprite.
    sf::Sprite& getAnimeSprite();

    // Get reference to GreekMan sprite.
    sf::Sprite& getGreekSprite();

    // Get reference to text bubble sprite.
    sf::Sprite& getTextBubbleSprite();

    // Get reference to background sprite.
    sf::Sprite& getBackground();

    // Get reference to Play button sprite.
    sf::Sprite& getPlaySprite();

    // Get reference to Help button sprite.
    sf::Sprite& getHelpSprite();

    // Get reference to Exit button sprite.
    sf::Sprite& getExitSprite();
};