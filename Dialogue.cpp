#include "Dialogue.h"
#include <iostream>

Dialogue::Dialogue()
    : currentLine(0), active(false) // Initialize state
{
    if (!font.loadFromFile("Sprites/Fonts/Retro.ttf")) // Load font
    {
        std::cout << "Failed to load font!\n";
    }

    visual.setFont(font);        // Assign font
    visual.setCharacterSize(18); // Text size
    visual.setPosition(55.f, 20.f); // Text position
}

Dialogue::~Dialogue() {}

void Dialogue::setLine(const std::vector<DialogueLine>& newLines)
{
    lines = newLines;          // Store dialogue
    currentLine = 0;           // Start at first line
    active = !lines.empty();   // Activate dialogue

    if (active)
    {
        // Set color based on speaker
        if (lines[currentLine].speaker == DialogueLine::Speaker::LEFT)
        {
            visual.setFillColor(sf::Color::Yellow);
        }
        else
        {
            visual.setFillColor(sf::Color::Cyan);
        }

        visual.setString(lines[currentLine].text); // Show first line
    }
}

bool Dialogue::nextLine()
{
    if (!active) return false; // Safety check

    currentLine++; // Move to next line

    if (currentLine >= lines.size())
    {
        active = false; // Dialogue finished
        return false;
    }

    // Update color based on speaker
    if (lines[currentLine].speaker == DialogueLine::Speaker::LEFT)
        visual.setFillColor(sf::Color::Yellow);
    else
        visual.setFillColor(sf::Color::Cyan);

    visual.setString(lines[currentLine].text); // Update text
    return true;
}

void Dialogue::reset()
{
    lines.clear();     // Clear dialogue
    currentLine = 0;   // Reset index
    active = false;    // Disable dialogue
}

bool Dialogue::isActive() const
{
    return active; // Return dialogue state
}

void Dialogue::draw(sf::RenderWindow& window)
{
    if (active)
    {
        window.draw(visual); // Draw dialogue text
    }
}

void Dialogue::setColor(const sf::Color& color)
{
    visual.setFillColor(color); // Change text color
}

