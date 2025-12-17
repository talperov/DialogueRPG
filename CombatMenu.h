#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

enum class CombatAction { NONE = 0, LIGHT, HEAVY, POTION };

class CombatMenu
{
private:
    std::vector<sf::Text> optionTexts; // Options as text
    sf::Font font;                      // Font for options
    bool active;                        // Is the menu visible
    CombatAction selection;             // Currently selected action

public:
    CombatMenu();
    ~CombatMenu();

    void open();                       // Activate menu
    bool isActive() const;             // Check if menu is active
    void handleInput(const sf::Event& event); // Detect clicks
    void draw(sf::RenderWindow& window);      // Draw menu
    CombatAction getSelection() const;       // Return selected option
};
