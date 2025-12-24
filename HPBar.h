#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"

// Displays a health bar for a character.
class HPBar {
private:
    Character* character;          // Pointer to the tracked character.
    sf::RectangleShape barBack;    // Background rectangle of the bar.
    sf::RectangleShape barFront;   // Foreground rectangle showing current HP.
    sf::Vector2f position;         // Position of the bar.
    sf::Vector2f size;             // Size of the bar.
    sf::Color color;               // Color of the foreground bar.

public:
    // Constructor to initialize the bar with character, position, and size.
    HPBar(Character* c, const sf::Vector2f& pos, const sf::Vector2f& s);

    // Update the tracked character.
    void setCharacter(Character* c);

    // Set the color of the foreground bar.
    void setColor(const sf::Color& c);

    // Draw the bar on the window.
    void draw(sf::RenderWindow& window);
};