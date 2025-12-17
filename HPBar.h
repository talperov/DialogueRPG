#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"

class HPBar
{
private:
    Character* character;          // Character to track
    sf::RectangleShape barBack;    // Background of bar
    sf::RectangleShape barFront;   // Front bar showing HP
    sf::Vector2f position;
    sf::Vector2f size;
    sf::Color color;

public:
    HPBar(Character* c, const sf::Vector2f& pos, const sf::Vector2f& s);

    void setCharacter(Character* c);        // <-- Add this
    void setColor(const sf::Color& c);
    void draw(sf::RenderWindow& window);
};
