#include "CombatMenu.h"
#include <iostream>

CombatMenu::CombatMenu() : active(false), selection(CombatAction::NONE)
{
    // Load font for options
    if (!font.loadFromFile("Sprites/Fonts/Retro.ttf"))
        std::cout << "Failed to load font for combat menu\n";

    std::string options[3] = { "Light Attack", "Heavy Attack", "Health Potion" };
    optionTexts.resize(3);

    // Initialize option texts
    for (int i = 0; i < 3; ++i)
    {
        optionTexts[i].setFont(font);
        optionTexts[i].setCharacterSize(18);      // Smaller text
        optionTexts[i].setString(options[i]);
        optionTexts[i].setFillColor(sf::Color::Green);
        optionTexts[i].setStyle(sf::Text::Bold);
        optionTexts[i].setPosition(0.f, 0.f);    // Will reposition in open()
    }
}

CombatMenu::~CombatMenu() {}

void CombatMenu::open()
{
    active = true;
    selection = CombatAction::NONE;

    // Position options centered horizontally, spaced vertically
    float startX = 400.f; // Adjust based on characters
    float startY = 400.f;
    float spacing = 50.f;

    for (int i = 0; i < optionTexts.size(); ++i)
    {
        sf::FloatRect bounds = optionTexts[i].getLocalBounds();
        optionTexts[i].setOrigin(bounds.width / 2.f, bounds.height / 2.f); // center origin
        optionTexts[i].setPosition(startX, startY + i * spacing);
    }
}

bool CombatMenu::isActive() const
{
    return active;
}

CombatAction CombatMenu::getSelection() const
{
    return selection;
}

// Handle both mouse and keyboard input safely
void CombatMenu::handleInput(const sf::Event& event)
{
    if (!active) return;

    // Mouse click
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

        for (int i = 0; i < optionTexts.size(); ++i)
        {
            if (optionTexts[i].getGlobalBounds().contains(mousePos))
            {
                selection = static_cast<CombatAction>(i + 1); // 1 = Light, 2 = Heavy, 3 = Potion
                active = false; // Menu disappears after selection
                break;
            }
        }
    }

    // Keyboard input (1, 2, 3)
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Num1)
        {
            selection = CombatAction::LIGHT;
            active = false;
        }
        else if (event.key.code == sf::Keyboard::Num2)
        {
            selection = CombatAction::HEAVY;
            active = false;
        }
        else if (event.key.code == sf::Keyboard::Num3)
        {
            selection = CombatAction::POTION;
            active = false;
        }
    }
}

void CombatMenu::draw(sf::RenderWindow& window)
{
    if (!active) return;

    for (auto& t : optionTexts)
        window.draw(t);
}
