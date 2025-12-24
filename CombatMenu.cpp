#include "CombatMenu.h"
#include <iostream>
#include <string>

CombatMenu::CombatMenu() : active(false), selection(CombatAction::NONE), heavyCooldown(0) {
    if (!font.loadFromFile("Sprites/Fonts/Retro.ttf")) {
        std::cout << "Failed to load font for combat menu\n";
    }

    std::string options[3] = { "Light Attack", "Heavy Attack", "Health Potion" };
    optionTexts.resize(3);

    for (int i = 0; i < 3; ++i) {
        optionTexts[i].setFont(font);
        optionTexts[i].setCharacterSize(18);
        optionTexts[i].setString(options[i]);
        optionTexts[i].setFillColor(sf::Color::Green);
        optionTexts[i].setStyle(sf::Text::Bold);
        optionTexts[i].setPosition(0.f, 0.f);
    }
}

CombatMenu::~CombatMenu() {}

void CombatMenu::open() {
    active = true;
    selection = CombatAction::NONE;
    reduceCooldown();  // Decrease cooldown at start of turn.

    float startX = 400.f;
    float startY = 400.f;
    float spacing = 50.f;

    for (int i = 0; i < optionTexts.size(); ++i) {
        sf::FloatRect bounds = optionTexts[i].getLocalBounds();
        optionTexts[i].setOrigin(bounds.width / 2.f, bounds.height / 2.f);
        optionTexts[i].setPosition(startX, startY + i * spacing);
    }
}

bool CombatMenu::isActive() const { return active; }

CombatAction CombatMenu::getSelection() const { return selection; }

void CombatMenu::resetSelection() { selection = CombatAction::NONE; }

void CombatMenu::triggerHeavyCooldown() { heavyCooldown = 2; }

void CombatMenu::reduceCooldown() {
    if (heavyCooldown > 0) heavyCooldown--;
}

void CombatMenu::handleInput(const sf::Event& event) {
    if (!active) return;

    // Handle mouse click.
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
        for (int i = 0; i < optionTexts.size(); ++i) {
            if (optionTexts[i].getGlobalBounds().contains(mousePos)) {
                if (i == 1 && heavyCooldown > 0) break;  // Block heavy if on cooldown.
                selection = static_cast<CombatAction>(i + 1);
                active = false;
                break;
            }
        }
    }

    // Handle keyboard input.
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Num1) {
            selection = CombatAction::LIGHT;
            active = false;
        }
        else if (event.key.code == sf::Keyboard::Num2 && heavyCooldown <= 0) {
            selection = CombatAction::HEAVY;
            active = false;
        }
        else if (event.key.code == sf::Keyboard::Num3) {
            selection = CombatAction::POTION;
            active = false;
        }
    }
}

void CombatMenu::draw(sf::RenderWindow& window) {
    if (!active) return;

    // Update heavy attack text and color based on cooldown.
    if (heavyCooldown > 0) {
        optionTexts[1].setFillColor(sf::Color(128, 128, 128));  // Gray for cooldown.
        optionTexts[1].setString("Heavy Attack (CD: " + std::to_string(heavyCooldown) + ")");
    }
    else {
        optionTexts[1].setFillColor(sf::Color::Green);
        optionTexts[1].setString("Heavy Attack");
    }

    for (auto& t : optionTexts) {
        window.draw(t);
    }
}