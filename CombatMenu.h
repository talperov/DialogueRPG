#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

// Enum for combat actions.
enum class CombatAction { NONE = 0, LIGHT, HEAVY, POTION };

// Manages the combat menu for player actions.
class CombatMenu {
private:
    std::vector<sf::Text> optionTexts;  // Texts for menu options.
    sf::Font font;                      // Font for menu text.
    bool active;                        // Whether the menu is active.
    CombatAction selection;             // Selected action.
    int heavyCooldown;                  // Cooldown for heavy attack.

public:
    // Constructor.
    CombatMenu();

    // Destructor.
    ~CombatMenu();

    // Open the menu.
    void open();

    // Check if menu is active.
    bool isActive() const;

    // Get selected action.
    CombatAction getSelection() const;

    // Handle input events.
    void handleInput(const sf::Event& event);

    // Draw the menu.
    void draw(sf::RenderWindow& window);

    // Reset selection.
    void resetSelection();

    // Trigger heavy attack cooldown.
    void triggerHeavyCooldown();

    // Reduce cooldown.
    void reduceCooldown();
};