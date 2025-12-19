#include "Dialogue.h"
#include <iostream>

Dialogue::Dialogue()
    : currentLine(0), active(false)
{
    if (!font.loadFromFile("Sprites/Fonts/Retro.ttf"))
        std::cout << "Failed to load font!\n";

    // Text setup
    visual.setFont(font);
    visual.setCharacterSize(16);
    visual.setFillColor(sf::Color::White);
    visual.setPosition(110.f, 80.f);        // Inside the box
    visual.setStyle(sf::Text::Bold);

    // Background box (semi-transparent black + yellow border)
    background.setSize(sf::Vector2f(580.f, 80.f));
    background.setFillColor(sf::Color(0, 0, 0, 200));        // Dark semi-transparent
    background.setOutlineThickness(3.f);
    background.setOutlineColor(sf::Color::Yellow);
    background.setPosition(110.f, 60.f);                     // Box starts here
}

Dialogue::~Dialogue() {}

void Dialogue::setLine(const std::vector<DialogueLine>& newLines)
{
    lines = newLines;
    currentLine = 0;
    active = !lines.empty();

    if (active)
    {
        updateTextAndColor();
    }
}

bool Dialogue::nextLine()
{
    if (!active) return false;

    currentLine++;
    if (currentLine >= lines.size())
    {
        active = false;
        return false;
    }

    updateTextAndColor();
    return true;
}

// Helper function to avoid duplicating color logic
void Dialogue::updateTextAndColor()
{
    visual.setString(lines[currentLine].text);

    // Player (LEFT or RIGHT) = White, Enemy = Red
    if (lines[currentLine].speaker == DialogueLine::Speaker::LEFT ||
        lines[currentLine].speaker == DialogueLine::Speaker::RIGHT)
    {
        visual.setFillColor(sf::Color::White);
    }
    else // ENEMY (we'll add this speaker type later)
    {
        visual.setFillColor(sf::Color::Red);
    }
}

void Dialogue::reset()
{
    lines.clear();
    currentLine = 0;
    active = false;
}

bool Dialogue::isActive() const
{
    return active;
}

void Dialogue::draw(sf::RenderWindow& window)
{
    if (active)
    {
        window.draw(background);  // Draw box first
        window.draw(visual);      // Then text on top
    }
}

void Dialogue::setColor(const sf::Color& color)
{
    visual.setFillColor(color);
}