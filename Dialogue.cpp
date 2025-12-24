#include "Dialogue.h"
#include <iostream>

Dialogue::Dialogue() : currentLine(0), active(false) {
    if (!font.loadFromFile("Sprites/Fonts/Retro.ttf")) {
        std::cout << "Failed to load font!\n";
    }

    // Setup text.
    visual.setFont(font);
    visual.setCharacterSize(16);
    visual.setFillColor(sf::Color::White);
    visual.setPosition(110.f, 80.f);
    visual.setStyle(sf::Text::Bold);

    // Setup background box.
    background.setSize(sf::Vector2f(580.f, 80.f));
    background.setFillColor(sf::Color(0, 0, 0, 200));  // Semi-transparent black.
    background.setOutlineThickness(3.f);
    background.setOutlineColor(sf::Color::Yellow);
    background.setPosition(110.f, 60.f);
}

Dialogue::~Dialogue() {}

void Dialogue::setLine(const std::vector<DialogueLine>& newLines) {
    lines = newLines;
    currentLine = 0;
    active = !lines.empty();

    if (active) {
        updateTextAndColor();
    }
}

bool Dialogue::nextLine() {
    if (!active) return false;

    currentLine++;
    if (currentLine >= lines.size()) {
        active = false;
        return false;
    }

    updateTextAndColor();
    return true;
}

void Dialogue::updateTextAndColor() {
    visual.setString(lines[currentLine].text);

    // Set color based on speaker.
    if (lines[currentLine].speaker == DialogueLine::Speaker::LEFT ||
        lines[currentLine].speaker == DialogueLine::Speaker::RIGHT) {
        visual.setFillColor(sf::Color::White);
    }
    else {  // ENEMY.
        visual.setFillColor(sf::Color::Red);
    }
}

void Dialogue::reset() {
    lines.clear();
    currentLine = 0;
    active = false;
}

bool Dialogue::isActive() const {
    return active;
}

void Dialogue::draw(sf::RenderWindow& window) {
    if (active) {
        window.draw(background);  // Draw background first.
        window.draw(visual);      // Draw text on top.
    }
}

void Dialogue::setColor(const sf::Color& color) {
    visual.setFillColor(color);
}