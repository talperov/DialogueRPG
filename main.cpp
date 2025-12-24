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
#include <string>

enum class GameState { MENU, GAME, HELP, SELECT_FIGHTER, COMBAT, VICTORY, DEFEAT };
enum class ActiveCharacter { NONE, LEFT, RIGHT };

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML RPG");
    Animation animation;
    Dialogue dialogue;
    CombatMenu combatMenu;

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Updated character names
    Character leftChar("Bald Saed", 100, 10, 20, 25);      // Left character
    Character rightChar("Chat Brett", 100, 12, 18, 30);    // Right character
    Character enemy("Evil Boss", 100, 15, 25, 0);

    HPBar playerBar(&leftChar, sf::Vector2f(50.f, 20.f), sf::Vector2f(200.f, 20.f));
    HPBar enemyBar(&enemy, sf::Vector2f(550.f, 20.f), sf::Vector2f(200.f, 20.f));

    GameState state = GameState::MENU;
    ActiveCharacter activeCharacter = ActiveCharacter::NONE;

    bool showLeft = false;
    bool showRight = false;
    bool startedRightDialogue = false;

    animation.loadMenuBackground(window);
    animation.loadMenuButtons(); // Loads Play, Controls, Exit sprites
    animation.createAnime();
    animation.createGreek();

    sf::Font font;
    if (!font.loadFromFile("Sprites/Fonts/Retro.ttf")) {
        std::cerr << "Failed to load font!\n";
        return 1;
    }

    // ==================== HELP / CONTROLS SCREEN ====================
    sf::Text helpTitle("CONTROLS", font, 36);
    helpTitle.setFillColor(sf::Color::Yellow);
    helpTitle.setStyle(sf::Text::Bold);
    sf::FloatRect titleRect = helpTitle.getLocalBounds();
    helpTitle.setOrigin(titleRect.width / 2, titleRect.height / 2);
    helpTitle.setPosition(400.f, 80.f);

    sf::Text helpSummary(
        "A neon-lit action RPG where two unlikely heroes\n"
        "Bald Saed and Chat Brett join forces to defeat\n"
        "powerful evil bosses. Choose your fighter,\n level up,"
        "and survive the battles!\n\n",
        font, 15);
    helpSummary.setFillColor(sf::Color::White);
    helpSummary.setPosition(80.f, 140.f);

    sf::Text helpControls(
        "CONTROLS\n\n"
        "Story Scenes:\n"
        " Left Click — Advance dialogue\n\n"
        "Choose Fighter:\n"
        " Press 1 Select Bald Saed\n"
        " Press 2 Select Chat Brett\n\n"
        "Combat:\n"
        " Click option or press:\n"
        "  1  Light Attack\n"
        "  2  Heavy Attack (2-turn cooldown)\n"
        "  3  Health Potion\n\n"
        "Victory / Defeat:\n"
        " Click anywhere  Return to main menu\n\n"
        "Main Menu:\n"
        " Click Play, Controls, or Exit\n\n"
        "Click anywhere or press ESC to return",
        font, 15);
    helpControls.setFillColor(sf::Color::Cyan);
    helpControls.setPosition(80.f, 240.f);

    // Combat log (debug)
    std::vector<std::string> combatLog;
    sf::Text logText("", font, 14);
    logText.setFillColor(sf::Color::White);
    logText.setStyle(sf::Text::Bold);

    auto addCombatLog = [&](const std::string& msg) {
        combatLog.push_back(msg);
        if (combatLog.size() > 5) combatLog.erase(combatLog.begin());
        std::string full;
        for (const auto& s : combatLog) full += s + "\n";
        logText.setString(full);
        };

    auto updateCombatLogPosition = [&]() {
        if (activeCharacter == ActiveCharacter::LEFT) {
            logText.setPosition(520.f, 460.f);
        }
        else if (activeCharacter == ActiveCharacter::RIGHT) {
            logText.setPosition(10.f, 460.f);
        }
        };

    sf::Text playerNameText("", font, 18);
    sf::Text enemyNameText("", font, 18);
    sf::Text playerLevelText("", font, 14);

    playerNameText.setFillColor(sf::Color::White);
    playerNameText.setPosition(50.f, 55.f);

    enemyNameText.setFillColor(sf::Color::Red);
    enemyNameText.setPosition(550.f, 55.f);

    playerLevelText.setFillColor(sf::Color::Yellow);
    playerLevelText.setPosition(50.f, 8.f);

    sf::Text enemyTalkText("", font, 18);
    enemyTalkText.setFillColor(sf::Color::Red);
    enemyTalkText.setPosition(550.f, 90.f);

    sf::Text playerTalkText("", font, 32);
    playerTalkText.setFillColor(sf::Color::White);
    playerTalkText.setStyle(sf::Text::Bold);
    playerTalkText.setOutlineColor(sf::Color::Black);
    playerTalkText.setOutlineThickness(3.f);

    auto updatePlayerTalkPosition = [&]() {
        if (activeCharacter == ActiveCharacter::LEFT) {
            playerTalkText.setPosition(100.f, 120.f);
        }
        else if (activeCharacter == ActiveCharacter::RIGHT) {
            playerTalkText.setPosition(500.f, 120.f);
        }
        };

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // MAIN MENU
            if (state == GameState::MENU && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

                if (animation.getPlaySprite().getGlobalBounds().contains(worldPos)) {
                    state = GameState::GAME;
                    animation.loadBackground(window);
                    showLeft = showRight = startedRightDialogue = false;
                    dialogue.reset();
                    dialogue.setLine(animeIntroLeft.dialogueLines);
                    continue;
                }
                else if (animation.getHelpSprite().getGlobalBounds().contains(worldPos)) {
                    state = GameState::HELP;
                    continue;
                }
                else if (animation.getExitSprite().getGlobalBounds().contains(worldPos)) {
                    window.close();
                    continue;
                }
            }

            // HELP SCREEN
            if (state == GameState::HELP) {
                if (event.type == sf::Event::MouseButtonPressed ||
                    (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                    state = GameState::MENU;
                    continue;
                }
            }

            // STORY DIALOGUE
            if (state == GameState::GAME && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (dialogue.isActive()) {
                    dialogue.nextLine();
                }
                else {
                    if (!showLeft) {
                        showLeft = true;
                        dialogue.setLine(animeIntroLeft.dialogueLines);
                    }
                    else if (!showRight) {
                        showRight = true;
                        dialogue.setLine(animeIntroRight.dialogueLines);
                    }
                    else if (!startedRightDialogue) {
                        startedRightDialogue = true;
                        dialogue.setLine(sceneBattleStart.dialogueLines);
                    }
                    else {
                        state = GameState::SELECT_FIGHTER;
                    }
                }
                continue;
            }

            // SELECT FIGHTER
            if (state == GameState::SELECT_FIGHTER && event.type == sf::Event::KeyPressed) {
                animation.createEnemy("Sprites/Characters/Bosses/Evil" + std::to_string(std::rand() % 6 + 1) + ".png",
                    sf::Vector2f(215.f, 100.f), 5.5f);

                int playerLevel = (event.key.code == sf::Keyboard::Num1) ? leftChar.getLevel() : rightChar.getLevel();
                int enemyHP = 100 + (playerLevel - 1) * 60;
                int enemyLight = 15 + (playerLevel - 1) * 5;
                int enemyHeavy = 25 + (playerLevel - 1) * 8;
                enemy = Character("Evil Boss", enemyHP, enemyLight, enemyHeavy, 0);
                enemyBar.setCharacter(&enemy);

                if (event.key.code == sf::Keyboard::Num1) {
                    activeCharacter = ActiveCharacter::LEFT;
                    playerBar.setCharacter(&leftChar);
                    playerNameText.setString("Bald Saed");
                }
                else if (event.key.code == sf::Keyboard::Num2) {
                    activeCharacter = ActiveCharacter::RIGHT;
                    playerBar.setCharacter(&rightChar);
                    playerNameText.setString("Chat Brett");
                }

                enemyNameText.setString("Evil Boss");
                state = GameState::COMBAT;
                combatMenu.open();
                combatLog.clear();
                addCombatLog("Combat starts!");
                playerTalkText.setString("");
                enemyTalkText.setString("");

                updatePlayerTalkPosition();
                updateCombatLogPosition();
                continue;
            }

            // COMBAT
            if (state == GameState::COMBAT) {
                combatMenu.handleInput(event);

                if (!combatMenu.isActive() && combatMenu.getSelection() != CombatAction::NONE) {
                    Character* player = (activeCharacter == ActiveCharacter::LEFT) ? &leftChar : &rightChar;
                    int dmg = 0;
                    std::string msg;

                    switch (combatMenu.getSelection()) {
                    case CombatAction::LIGHT:
                        dmg = player->getLightAttack() + (std::rand() % 4 - 2);
                        enemy.takeDamage(dmg);
                        playerTalkText.setString("Take this!");
                        msg = player->getName() + " Light: " + std::to_string(dmg);
                        break;
                    case CombatAction::HEAVY:
                        dmg = player->getHeavyAttack() + (std::rand() % 6 - 3);
                        enemy.takeDamage(dmg);
                        playerTalkText.setString("SMASH!");
                        msg = player->getName() + " HEAVY: " + std::to_string(dmg);
                        combatMenu.triggerHeavyCooldown();
                        break;
                    case CombatAction::POTION:
                        player->heal(player->getPotionHeal());
                        playerTalkText.setString("Healing...");
                        msg = player->getName() + " heals " + std::to_string(player->getPotionHeal());
                        break;
                    default:
                        break;
                    }

                    addCombatLog(msg);
                    combatMenu.resetSelection();

                    if (enemy.getHP() <= 0) {
                        addCombatLog(">>> VICTORY! <<<");
                        enemyTalkText.setString("Impossible...");
                        player->levelUp();
                        addCombatLog(player->getName() + " is now LEVEL " + std::to_string(player->getLevel()) + "!");

                        std::string path = "Sprites/Characters/";
                        path += (activeCharacter == ActiveCharacter::LEFT) ? "AnimeMan/AnimeLVL" : "GreekMan/GreekLVL";
                        path += std::to_string(player->getLevel()) + ".png";
                        if (activeCharacter == ActiveCharacter::LEFT)
                            animation.animeTexture.loadFromFile(path);
                        else
                            animation.greekTexture.loadFromFile(path);

                        state = GameState::VICTORY;
                        continue;
                    }

                    // Enemy turn
                    int choice = std::rand() % 100;
                    if (choice < 60) {
                        dmg = enemy.getLightAttack() + (std::rand() % 4 - 2);
                        player->takeDamage(dmg);
                        enemyTalkText.setString("Pathetic!");
                        addCombatLog("Boss Light: " + std::to_string(dmg));
                    }
                    else if (choice < 90) {
                        dmg = enemy.getHeavyAttack() + (std::rand() % 6 - 3);
                        player->takeDamage(dmg);
                        enemyTalkText.setString("CRUSHED!");
                        addCombatLog("Boss HEAVY: " + std::to_string(dmg));
                    }
                    else {
                        enemyTalkText.setString("Feel my power...");
                        addCombatLog("Boss charges...");
                    }

                    if (player->getHP() <= 0) {
                        addCombatLog(">>> DEFEATED <<<");
                        playerTalkText.setString("I... failed...");
                        state = GameState::DEFEAT;
                        continue;
                    }

                    combatMenu.open();
                }
            }

            // Return to menu after win/loss
            if ((state == GameState::VICTORY || state == GameState::DEFEAT) && event.type == sf::Event::MouseButtonPressed) {
                state = GameState::MENU;
                continue;
            }
        }

        window.clear(sf::Color::Black);

        Character* currentPlayer = (activeCharacter == ActiveCharacter::LEFT) ? &leftChar : &rightChar;

        if (state == GameState::MENU) {
            window.draw(animation.getBackground());
            window.draw(animation.getPlaySprite());
            window.draw(animation.getHelpSprite());
            window.draw(animation.getExitSprite());
        }
        else if (state == GameState::HELP) {
            window.draw(animation.getBackground());
            window.draw(helpTitle);
            window.draw(helpSummary);
            window.draw(helpControls);
        }
        else if (state == GameState::GAME) {
            window.draw(animation.getBackground());
            if (showLeft) window.draw(animation.getAnimeSprite());
            if (showRight) window.draw(animation.getGreekSprite());
            dialogue.draw(window);
        }
        else if (state == GameState::SELECT_FIGHTER) {
            window.draw(animation.getBackground());
            window.draw(animation.getAnimeSprite());
            window.draw(animation.getGreekSprite());
            sf::Text prompt("Press 1 for Bald Saed | 2 for Chat Brett", font, 16);
            prompt.setFillColor(sf::Color::White);
            prompt.setPosition(150.f, 50.f);
            window.draw(prompt);
        }
        else if (state == GameState::COMBAT) {
            window.draw(animation.getBackground());
            window.draw(animation.getEnemySprite());

            if (activeCharacter == ActiveCharacter::LEFT)
                window.draw(animation.getAnimeSprite());
            else
                window.draw(animation.getGreekSprite());

            playerBar.draw(window);
            enemyBar.draw(window);

            playerLevelText.setString("LVL " + std::to_string(currentPlayer->getLevel()));
            window.draw(playerLevelText);
            window.draw(playerNameText);
            window.draw(enemyNameText);

            window.draw(playerTalkText);
            window.draw(enemyTalkText);

            dialogue.draw(window);
            combatMenu.draw(window);
            window.draw(logText);
        }
        else if (state == GameState::VICTORY || state == GameState::DEFEAT) {
            sf::Text result(state == GameState::VICTORY ? "VICTORY!" : "DEFEATED...", font, 40);
            result.setFillColor(state == GameState::VICTORY ? sf::Color::Green : sf::Color::Red);
            result.setPosition(200.f, 230.f);
            window.draw(result);
            window.draw(logText);
        }

        window.display();
    }

    return 0;
} 