#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

enum class CombatAction { NONE = 0, LIGHT, HEAVY, POTION };

class CombatMenu
{
private:
    std::vector<sf::Text> optionTexts;
    sf::Font font;
    bool active;
    CombatAction selection;
    int heavyCooldown;  // 0 = ready, >0 = turns left

public:
    CombatMenu();
    ~CombatMenu();

    void open();
    bool isActive() const;
    CombatAction getSelection() const;
    void handleInput(const sf::Event& event);
    void draw(sf::RenderWindow& window);

    void resetSelection();
    void triggerHeavyCooldown();
    void reduceCooldown();
};