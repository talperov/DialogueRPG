#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Dialogue.h"
#include "Scenes.h"
#include "CombatMenu.h"
#include "Character.h"
#include "HPBar.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

enum class GameState { MENU, GAME, HELP, SELECT_FIGHTER, COMBAT };
enum class ActiveCharacter { NONE, LEFT, RIGHT };

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML RPG"); // Create window
    Animation animation;
    Dialogue dialogue;
    CombatMenu combatMenu;

    // Seed random for enemies
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Team characters
    Character leftChar("AnimeMan", 100, 10, 20, 25);
    Character rightChar("GreekMan", 120, 12, 18, 30);

    // Enemy placeholder (will randomize later)
    Character enemy("Enemy", 150, 15, 25, 0);

    // HP bars
    HPBar playerBar(&leftChar, sf::Vector2f(50.f, 20.f), sf::Vector2f(200.f, 20.f));   // Top-left
    HPBar enemyBar(&enemy, sf::Vector2f(550.f, 20.f), sf::Vector2f(200.f, 20.f));      // Top-right

    GameState state = GameState::MENU;
    ActiveCharacter activeCharacter = ActiveCharacter::NONE;

    bool showLeft = false;
    bool showRight = false;
    bool startedRightDialogue = false;

    Scene currentScene = animeIntroLeft;
    dialogue.setLine(currentScene.dialogueLines);
    dialogue.setColor(sf::Color::Yellow);

    animation.loadMenuBackground(window);
    animation.loadMenuButtons();
    animation.createAnime();
    animation.createGreek();

    sf::Font font;
    font.loadFromFile("Sprites/Fonts/Retro.ttf");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // MENU input
            if (state == GameState::MENU)
            {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (animation.getPlaySprite().getGlobalBounds().contains(mousePos))
                    {
                        state = GameState::GAME;
                        animation.loadBackground(window);
                        showLeft = false; showRight = false; startedRightDialogue = false;
                        dialogue.setLine(animeIntroLeft.dialogueLines);
                        dialogue.setColor(sf::Color::Yellow);
                    }
                    else if (animation.getHelpSprite().getGlobalBounds().contains(mousePos))
                        state = GameState::HELP;
                    else if (animation.getExitSprite().getGlobalBounds().contains(mousePos))
                        window.close();
                }
            }

            // GAME input
            if (state == GameState::GAME && event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left)
            {
                if (dialogue.isActive())
                    dialogue.nextLine();
                else
                {
                    if (!showLeft)
                    {
                        showLeft = true;
                        dialogue.setLine(animeIntroLeft.dialogueLines);
                        dialogue.setColor(sf::Color::Yellow);
                    }
                    else if (!showRight)
                    {
                        showRight = true;
                        dialogue.setLine(animeIntroRight.dialogueLines);
                        dialogue.setColor(sf::Color::Cyan);
                    }
                    else if (!startedRightDialogue)
                    {
                        startedRightDialogue = true;
                        dialogue.setLine(sceneBattleStart.dialogueLines);
                        dialogue.setColor(sf::Color::Yellow);
                    }
                    else
                        state = GameState::SELECT_FIGHTER; // Choose fighter
                }
            }

            // SELECT_FIGHTER input
            if (state == GameState::SELECT_FIGHTER && event.type == sf::Event::KeyPressed)
            {
                // Randomize enemy sprite
                int randNum = std::rand() % 6 + 1; // 1 to 6
                std::string enemyFile = "Sprites/Characters/Bosses/Evil" + std::to_string(randNum) + ".png";
                animation.createEnemy(enemyFile, sf::Vector2f(215.f, 100.f), 5.5f);

                if (event.key.code == sf::Keyboard::Num1)
                {
                    activeCharacter = ActiveCharacter::LEFT;
                    playerBar = HPBar(&leftChar, sf::Vector2f(50.f, 20.f), sf::Vector2f(200.f, 20.f));
                    enemyBar = HPBar(&enemy, sf::Vector2f(550.f, 20.f), sf::Vector2f(200.f, 20.f));
                    combatMenu.open();
                    state = GameState::COMBAT;
                }
                else if (event.key.code == sf::Keyboard::Num2)
                {
                    activeCharacter = ActiveCharacter::RIGHT;
                    playerBar = HPBar(&rightChar, sf::Vector2f(50.f, 20.f), sf::Vector2f(200.f, 20.f));
                    enemyBar = HPBar(&enemy, sf::Vector2f(550.f, 20.f), sf::Vector2f(200.f, 20.f));
                    combatMenu.open();
                    state = GameState::COMBAT;
                }
            }

            // COMBAT input
            if (state == GameState::COMBAT)
            {
                combatMenu.handleInput(event);

                if (!combatMenu.isActive() && combatMenu.getSelection() != CombatAction::NONE)
                {
                    Character* player = (activeCharacter == ActiveCharacter::LEFT) ? &leftChar : &rightChar;
                    CombatAction action = combatMenu.getSelection();

                    if (action == CombatAction::LIGHT)
                    {
                        enemy.takeDamage(player->getLightAttack());
                        std::cout << player->getName() << " used Light Attack!\n";
                    }
                    else if (action == CombatAction::HEAVY)
                    {
                        enemy.takeDamage(player->getHeavyAttack());
                        std::cout << player->getName() << " used Heavy Attack!\n";
                    }
                    else if (action == CombatAction::POTION)
                    {
                        player->heal(player->getPotionHeal());
                        std::cout << player->getName() << " used Health Potion!\n";
                    }

                    // Reopen menu for next turn
                    combatMenu.open();
                }
            }
        }

        window.clear(sf::Color::Black);

        // MENU render
        if (state == GameState::MENU)
        {
            window.draw(animation.getBackground());
            window.draw(animation.getPlaySprite());
            window.draw(animation.getHelpSprite());
            window.draw(animation.getExitSprite());
        }
        // GAME render
        else if (state == GameState::GAME)
        {
            window.draw(animation.getBackground());
            if (showLeft) window.draw(animation.getAnimeSprite());
            if (showRight) window.draw(animation.getGreekSprite());
            if (dialogue.isActive()) dialogue.draw(window);
        }
        // SELECT_FIGHTER render
        else if (state == GameState::SELECT_FIGHTER)
        {
            window.draw(animation.getBackground());
            window.draw(animation.getAnimeSprite());
            window.draw(animation.getGreekSprite());

            sf::Text prompt("Press 1 for Saed, 2 for Brett", font, 18);
            prompt.setFillColor(sf::Color::White);
            prompt.setPosition(150.f, 50.f);
            window.draw(prompt);
        }
        // COMBAT render
        else if (state == GameState::COMBAT)
        {
            window.draw(animation.getBackground());

            // Enemy behind player
            window.draw(animation.getEnemySprite());

            if (activeCharacter == ActiveCharacter::LEFT) window.draw(animation.getAnimeSprite());
            else if (activeCharacter == ActiveCharacter::RIGHT) window.draw(animation.getGreekSprite());

            playerBar.draw(window); // Top-left
            enemyBar.draw(window);  // Top-right

            combatMenu.draw(window); // Combat options
        }
        // HELP render
        else if (state == GameState::HELP)
            window.clear(sf::Color::Blue);

        window.display();
    }

    return 0;
}
