#include "HPBar.h"

HPBar::HPBar(Character* c, const sf::Vector2f& pos, const sf::Vector2f& s)
    : character(c), position(pos), size(s), color(sf::Color::Green) {
    barBack.setSize(size);
    barBack.setFillColor(sf::Color(100, 100, 100));  // Gray background.
    barBack.setPosition(position);

    barFront.setSize(size);
    barFront.setFillColor(color);
    barFront.setPosition(position);
}

void HPBar::setCharacter(Character* c) {
    character = c;
}

void HPBar::setColor(const sf::Color& c) {
    color = c;
    barFront.setFillColor(color);
}

void HPBar::draw(sf::RenderWindow& window) {
    barBack.setPosition(position);
    window.draw(barBack);

    if (!character) return;

    float ratio = static_cast<float>(character->getHP()) / character->getMaxHP();
    barFront.setSize(sf::Vector2f(size.x * ratio, size.y));
    barFront.setPosition(position);
    window.draw(barFront);
}