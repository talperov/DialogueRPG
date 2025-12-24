#include "Animation.h"
#include <iostream>

using namespace std;

Animation::Animation() {}

Animation::~Animation() {}

bool Animation::loadBackground(const sf::RenderWindow& window) {
    if (!backgroundTexture.loadFromFile("Sprites/Background/City.png")) {
        cout << "Failed to load background!\n";
        return false;
    }

    backgroundSprite = sf::Sprite();
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(0.f, 0.f);

    sf::Vector2u texSize = backgroundTexture.getSize();
    sf::Vector2u winSize = window.getSize();

    backgroundSprite.setScale(
        static_cast<float>(winSize.x) / texSize.x,
        static_cast<float>(winSize.y) / texSize.y
    );

    return true;
}

bool Animation::loadMenuBackground(const sf::RenderWindow& window) {
    if (!backgroundTexture.loadFromFile("Sprites/Background/Menu.png")) {
        cout << "Failed to load menu background!\n";
        return false;
    }

    backgroundSprite = sf::Sprite();
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(0.f, 0.f);

    sf::Vector2u texSize = backgroundTexture.getSize();
    sf::Vector2u winSize = window.getSize();

    backgroundSprite.setScale(
        static_cast<float>(winSize.x) / texSize.x,
        static_cast<float>(winSize.y) / texSize.y
    );

    return true;
}

bool Animation::createAnime() {
    if (!animeTexture.loadFromFile("Sprites/Characters/AnimeMan/AnimeLVL1.png")) {
        cout << "Failed to load AnimeMan!\n";
        return false;
    }

    animeSprite.setTexture(animeTexture);
    animeSprite.setScale(1.6f, 1.6f);
    animeSprite.setPosition(50.f, 300.f);

    return true;
}

bool Animation::createGreek() {
    if (!greekTexture.loadFromFile("Sprites/Characters/GreekMan/GreekLVL1.png")) {
        cout << "Failed to load GreekMan!\n";
        return false;
    }

    greekSprite.setTexture(greekTexture);
    greekSprite.setScale(1.5f, 1.5f);
    greekSprite.setPosition(400.f, 200.f);

    return true;
}

bool Animation::loadMenuButtons() {
    if (!playTex.loadFromFile("Sprites/MenuButtons/Play.png") ||
        !helpTex.loadFromFile("Sprites/MenuButtons/Controls.png") ||
        !exitTex.loadFromFile("Sprites/MenuButtons/Exit.png")) {
        cout << "Failed to load menu buttons!\n";
        return false;
    }

    playSprite.setTexture(playTex);
    helpSprite.setTexture(helpTex);
    exitSprite.setTexture(exitTex);

    playSprite.setScale(0.5f, 0.5f);
    helpSprite.setScale(0.5f, 0.5f);
    exitSprite.setScale(0.5f, 0.5f);

    float startX = 250.f;
    float startY = 200.f;
    float spacing = 120.f;

    playSprite.setPosition(startX, startY);
    helpSprite.setPosition(startX, startY + spacing);
    exitSprite.setPosition(startX, startY + 2 * spacing);

    return true;
}

bool Animation::loadTextBubble() {
    if (!textBubbleTexture.loadFromFile("Sprites/MenuButtons/text.png")) {
        cout << "Failed to load text bubble!\n";
        return false;
    }

    textBubbleSprite.setTexture(textBubbleTexture);
    textBubbleSprite.setScale(7.25f, 7.25f);

    sf::Vector2u winSize(800, 500);  // Assuming fixed window size; make dynamic if needed.
    sf::FloatRect bubbleBounds = textBubbleSprite.getLocalBounds();
    textBubbleSprite.setOrigin(bubbleBounds.width / 2.f, bubbleBounds.height / 2.f);
    textBubbleSprite.setPosition(static_cast<float>(winSize.x) / 2.f, static_cast<float>(winSize.y) - bubbleBounds.height);

    return true;
}

bool Animation::createEnemy(const std::string& filePath, sf::Vector2f position, float scale) {
    if (!enemyTexture.loadFromFile(filePath)) {
        return false;
    }
    enemySprite.setTexture(enemyTexture);
    enemySprite.setScale(scale, scale);
    enemySprite.setPosition(position);
    return true;
}

sf::Sprite& Animation::getEnemySprite() {
    return enemySprite;
}

sf::Sprite& Animation::getAnimeSprite() { return animeSprite; }
sf::Sprite& Animation::getGreekSprite() { return greekSprite; }
sf::Sprite& Animation::getTextBubbleSprite() { return textBubbleSprite; }
sf::Sprite& Animation::getBackground() { return backgroundSprite; }
sf::Sprite& Animation::getPlaySprite() { return playSprite; }
sf::Sprite& Animation::getHelpSprite() { return helpSprite; }
sf::Sprite& Animation::getExitSprite() { return exitSprite; }