#include "Animation.h"
#include <iostream>

using namespace std;

Animation::Animation() {}

Animation::~Animation(){}

// Load city/game background
bool Animation::loadBackground(const sf::RenderWindow& window)
{
    if (!backgroundTexture.loadFromFile("Sprites/Background/City.png"))
    {
        cout << "Failed to load background!\n";
        return false;
    }

    backgroundSprite = sf::Sprite();                // Reset sprite
    backgroundSprite.setTexture(backgroundTexture); // Attach texture
    backgroundSprite.setPosition(0.f, 0.f);         // Top-left anchor

    sf::Vector2u texSize = backgroundTexture.getSize(); // Texture size
    sf::Vector2u winSize = window.getSize();            // Window size

    backgroundSprite.setScale(
        float(winSize.x) / texSize.x,
        float(winSize.y) / texSize.y
    ); // Scale to fill window

    return true;
}

// Load menu background
bool Animation::loadMenuBackground(const sf::RenderWindow& window)
{
    if (!backgroundTexture.loadFromFile("Sprites/Background/Menu.png"))
    {
        cout << "Failed to load menu background!\n";
        return false;
    }

    backgroundSprite = sf::Sprite();                // Reset sprite
    backgroundSprite.setTexture(backgroundTexture); // Attach texture
    backgroundSprite.setPosition(0.f, 0.f);         // Top-left anchor

    sf::Vector2u texSize = backgroundTexture.getSize();
    sf::Vector2u winSize = window.getSize();

    backgroundSprite.setScale(
        float(winSize.x) / texSize.x,
        float(winSize.y) / texSize.y
    );

    return true;
}



// Load AnimeMan
bool Animation::createAnime()
{
    if (!animeTexture.loadFromFile("Sprites/Characters/AnimeMan/AnimeLVL1.png"))
    {
        cout << "Failed to load AnimeMan!\n";
        return false;
    }

    animeSprite.setTexture(animeTexture); // Attach texture
    animeSprite.setScale(1.6f, 1.6f);     // Scale character
    animeSprite.setPosition(50.f, 300.f); // Position left

    return true;
}

// Load GreekMan
bool Animation::createGreek()
{
    if (!greekTexture.loadFromFile("Sprites/Characters/GreekMan/GreekLVL1.png"))
    {
        cout << "Failed to load GreekMan!\n";
        return false;
    }

    greekSprite.setTexture(greekTexture);
    greekSprite.setScale(1.5f, 1.5f);
    greekSprite.setPosition(400.f, 200.f); // Position right

    return true;
}

// Load GoldMan (commented for now)
// bool Animation::createGold()
// {
//     if (!goldTexture.loadFromFile("Sprites/GoldMan/GoldV1.png"))
//     {
//         cout << "Failed to load GoldMan!\n";
//         return false;
//     }
//     goldSprite.setTexture(goldTexture);
//     goldSprite.setScale(1.5f, 1.5f);
//     goldSprite.setPosition(300.f, 100.f);
//     return true;
// }

bool Animation::loadMenuButtons()
{
    // Load button textures
    if (!playTex.loadFromFile("Sprites/MenuButtons/Play.png") ||
        !helpTex.loadFromFile("Sprites/MenuButtons/Controls.png") ||
        !exitTex.loadFromFile("Sprites/MenuButtons/Exit.png"))
    {
        cout << "Failed to load menu buttons!\n";
        return false;
    }

    // Assign textures to sprites
    playSprite.setTexture(playTex);
    helpSprite.setTexture(helpTex);
    exitSprite.setTexture(exitTex);

    // Resize buttons to fit nicely
    playSprite.setScale(0.5f, 0.5f);   // Scale to 50%
    helpSprite.setScale(0.5f, 0.5f);
    exitSprite.setScale(0.5f, 0.5f);

    // Vertical stack positions
    float startX = 250.f;  // X position (centered-ish)
    float startY = 200.f;  // Y of top button
    float spacing = 120.f; // Space between buttons

    playSprite.setPosition(startX, startY);             // Top button
    helpSprite.setPosition(startX, startY + spacing);  // Middle button
    exitSprite.setPosition(startX, startY + 2*spacing);// Bottom button

    return true;
}

bool Animation::loadTextBubble()
{
    if (!textBubbleTexture.loadFromFile("Sprites/MenuButtons/text.png"))
    {
        std::cout << "Failed to load text bubble!\n";
        return false;
    }

    textBubbleSprite.setTexture(textBubbleTexture);

    // Scale bubble to be bigger if needed
    textBubbleSprite.setScale(7.25f, 7.25f); // Adjust scale as needed

    // Center horizontally and place near bottom of screen
    sf::Vector2u winSize = sf::Vector2u(800, 500); // You can pass window size if you want dynamic
    sf::FloatRect bubbleBounds = textBubbleSprite.getLocalBounds();
    textBubbleSprite.setOrigin(bubbleBounds.width / 2.f, bubbleBounds.height / 2.f);
    textBubbleSprite.setPosition(winSize.x / 2.f, winSize.y - bubbleBounds.height);

    return true;
}

bool Animation::createEnemy(const std::string& filePath, sf::Vector2f position, float scale)
{
    if (!enemyTexture.loadFromFile(filePath))
        return false; // failed to load
    enemySprite.setTexture(enemyTexture);
    enemySprite.setScale(scale, scale);
    enemySprite.setPosition(position);
    return true;
}

// Return reference to enemy sprite
sf::Sprite& Animation::getEnemySprite()
{
    return enemySprite;
}



// Getters
sf::Sprite& Animation::getAnimeSprite() { return animeSprite; }
sf::Sprite& Animation::getGreekSprite() { return greekSprite; }
sf::Sprite& Animation::getTextBubbleSprite() { return textBubbleSprite; }
// sf::Sprite& Animation::getGoldSprite() { return goldSprite; }
sf::Sprite& Animation::getBackground() { return backgroundSprite; }
sf::Sprite& Animation::getPlaySprite() { return playSprite; }
sf::Sprite& Animation::getHelpSprite() { return helpSprite; }
sf::Sprite& Animation::getExitSprite() { return exitSprite; }
