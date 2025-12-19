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

enum class GameState { MENU, GAME, HELP, SELECT_FIGHTER, COMBAT, VICTORY, DEFEAT };
enum class ActiveCharacter { NONE, LEFT, RIGHT };

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML RPG");
    Animation animation;
    Dialogue dialogue;
    CombatMenu combatMenu;

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Characters — levels persist!
    Character leftChar("AnimeMan", 100, 10, 20, 25);
    Character rightChar("GreekMan", 100, 12, 18, 30);
    Character enemy("Evil Boss", 100, 15, 25, 0);

    HPBar playerBar(&leftChar, sf::Vector2f(50.f, 20.f), sf::Vector2f(200.f, 20.f));
    HPBar enemyBar(&enemy, sf::Vector2f(550.f, 20.f), sf::Vector2f(200.f, 20.f));

    GameState state = GameState::MENU;
    ActiveCharacter activeCharacter = ActiveCharacter::NONE;

    bool showLeft = false;
    bool showRight = false;
    bool startedRightDialogue = false;
    bool combatStarted = false;

    animation.loadMenuBackground(window);
    animation.loadMenuButtons();
    animation.createAnime();
    animation.createGreek();

    sf::Font font;
    if (!font.loadFromFile("Sprites/Fonts/Retro.ttf")) return 1;

    // Combat log
    std::vector<std::string> combatLog;
    sf::Text logText("", font, 16);
    logText.setFillColor(sf::Color::White);

    auto addCombatLog = [&](const std::string& msg) {
        combatLog.push_back(msg);
        if (combatLog.size() > 5) combatLog.erase(combatLog.begin());
        std::string full;
        for (const auto& s : combatLog) full += s + "\n";
        logText.setString(full);
        };

    // Name + talk
    sf::Text playerNameText("", font, 18), enemyNameText("", font, 18);
    sf::Text playerTalkText("", font, 16), enemyTalkText("", font, 16);
    playerNameText.setFillColor(sf::Color::White); playerNameText.setPosition(50.f, 55.f);
    enemyNameText.setFillColor(sf::Color::Red);   enemyNameText.setPosition(550.f, 55.f);
    playerTalkText.setFillColor(sf::Color::White); playerTalkText.setPosition(50.f, 90.f);
    enemyTalkText.setFillColor(sf::Color::Red);   enemyTalkText.setPosition(550.f, 90.f);

    // Level text only
    sf::Text playerLevelText("", font, 14);
    playerLevelText.setFillColor(sf::Color::Yellow);
    playerLevelText.setPosition(50.f, 8.f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();

            // MENU
            if (state == GameState::MENU && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f m = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (animation.getPlaySprite().getGlobalBounds().contains(m))
                {
                    state = GameState::GAME;
                    animation.loadBackground(window);
                    showLeft = showRight = startedRightDialogue = false;
                    dialogue.reset();
                    dialogue.setLine(animeIntroLeft.dialogueLines);
                }
            }

            // STORY
            if (state == GameState::GAME && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                if (dialogue.isActive()) dialogue.nextLine();
                if (!dialogue.isActive())
                {
                    if (!showLeft) { showLeft = true; dialogue.setLine(animeIntroLeft.dialogueLines); }
                    else if (!showRight) { showRight = true; dialogue.setLine(animeIntroRight.dialogueLines); }
                    else if (!startedRightDialogue) { startedRightDialogue = true; dialogue.setLine(sceneBattleStart.dialogueLines); }
                    else state = GameState::SELECT_FIGHTER;
                }
            }

            // SELECT FIGHTER
            if (state == GameState::SELECT_FIGHTER && event.type == sf::Event::KeyPressed)
            {
                animation.createEnemy("Sprites/Characters/Bosses/Evil" + std::to_string(std::rand() % 6 + 1) + ".png",
                    sf::Vector2f(215.f, 100.f), 5.5f);

                // Fresh enemy every time
                int playerLevel = (event.key.code == sf::Keyboard::Num1) ? leftChar.getLevel() : rightChar.getLevel();
                int enemyHP = 100 + (playerLevel - 1) * 60;
                int enemyLight = 15 + (playerLevel - 1) * 5;
                int enemyHeavy = 25 + (playerLevel - 1) * 8;
                enemy = Character("Evil Boss", enemyHP, enemyLight, enemyHeavy, 0);
                enemyBar.setCharacter(&enemy);

                if (event.key.code == sf::Keyboard::Num1)
                {
                    activeCharacter = ActiveCharacter::LEFT;
                    playerBar.setCharacter(&leftChar);
                    playerNameText.setString("AnimeMan");
                    playerTalkText.setString("I'm ready!");
                    logText.setPosition(500.f, 520.f);
                }
                else if (event.key.code == sf::Keyboard::Num2)
                {
                    activeCharacter = ActiveCharacter::RIGHT;
                    playerBar.setCharacter(&rightChar);
                    playerNameText.setString("GreekMan");
                    playerTalkText.setString("Let's fight!");
                    logText.setPosition(50.f, 520.f);
                }

                enemyNameText.setString("Evil Boss");
                enemyTalkText.setString("You will fall!");

                combatLog.clear();
                addCombatLog("Battle begins!");
                combatStarted = false;
                state = GameState::COMBAT;
            }

            // COMBAT
            if (state == GameState::COMBAT)
            {
                if (!combatStarted) { combatMenu.open(); combatStarted = true; }
                combatMenu.handleInput(event);

                if (!combatMenu.isActive() && combatMenu.getSelection() != CombatAction::NONE)
                {
                    Character* player = (activeCharacter == ActiveCharacter::LEFT) ? &leftChar : &rightChar;
                    CombatAction action = combatMenu.getSelection();
                    combatMenu.resetSelection();

                    int dmg = 0;
                    std::string msg;

                    if (action == CombatAction::LIGHT)
                    {
                        dmg = player->getLightAttack() + (std::rand() % 5 - 2);
                        enemy.takeDamage(dmg);
                        playerTalkText.setString("Take this!");
                        msg = player->getName() + " Light: " + std::to_string(dmg);
                    }
                    else if (action == CombatAction::HEAVY)
                    {
                        dmg = player->getHeavyAttack() + (std::rand() % 8 - 4);
                        enemy.takeDamage(dmg);
                        playerTalkText.setString("DIE!!!");
                        msg = player->getName() + " HEAVY: " + std::to_string(dmg);
                        combatMenu.triggerHeavyCooldown();
                    }
                    else if (action == CombatAction::POTION)
                    {
                        int heal = player->getPotionHeal();
                        player->heal(heal);
                        playerTalkText.setString("Healing!");
                        msg = player->getName() + " Potion: +" + std::to_string(heal);
                    }

                    addCombatLog(msg);

                    if (enemy.getHP() <= 0)
                    {
                        addCombatLog(">>> VICTORY! <<<");
                        enemyTalkText.setString("Impossible...");

                        // WIN = LEVEL UP!
                        player->levelUp();
                        addCombatLog(player->getName() + " is now LEVEL " + std::to_string(player->getLevel()) + "!");

                        // Update sprite
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
                    if (choice < 60)
                    {
                        dmg = enemy.getLightAttack() + (std::rand() % 4 - 2);
                        player->takeDamage(dmg);
                        enemyTalkText.setString("Pathetic!");
                        addCombatLog("Boss Light: " + std::to_string(dmg));
                    }
                    else if (choice < 90)
                    {
                        dmg = enemy.getHeavyAttack() + (std::rand() % 6 - 3);
                        player->takeDamage(dmg);
                        enemyTalkText.setString("CRUSHED!");
                        addCombatLog("Boss HEAVY: " + std::to_string(dmg));
                    }
                    else
                    {
                        enemyTalkText.setString("Feel my power...");
                        addCombatLog("Boss charges...");
                    }

                    if (player->getHP() <= 0)
                    {
                        addCombatLog(">>> DEFEATED <<<");
                        playerTalkText.setString("I... failed...");
                        state = GameState::DEFEAT;
                        continue;
                    }

                    combatMenu.open();
                }
            }

            if ((state == GameState::VICTORY || state == GameState::DEFEAT) && event.type == sf::Event::MouseButtonPressed)
            {
                state = GameState::MENU;
                combatStarted = false;
            }
        }

        window.clear(sf::Color::Black);

        Character* currentPlayer = (activeCharacter == ActiveCharacter::LEFT) ? &leftChar : &rightChar;

        if (state == GameState::MENU)
        {
            window.draw(animation.getBackground());
            window.draw(animation.getPlaySprite());
            window.draw(animation.getHelpSprite());
            window.draw(animation.getExitSprite());
        }
        else if (state == GameState::GAME)
        {
            window.draw(animation.getBackground());
            if (showLeft) window.draw(animation.getAnimeSprite());
            if (showRight) window.draw(animation.getGreekSprite());
            dialogue.draw(window);
        }
        else if (state == GameState::SELECT_FIGHTER)
        {
            window.draw(animation.getBackground());
            window.draw(animation.getAnimeSprite());
            window.draw(animation.getGreekSprite());
            sf::Text prompt("Press 1 for Saed | 2 for Brett", font, 16);
            prompt.setFillColor(sf::Color::White);
            prompt.setPosition(150.f, 50.f);
            window.draw(prompt);
        }
        else if (state == GameState::COMBAT)
        {
            window.draw(animation.getBackground());
            window.draw(animation.getEnemySprite());
            if (activeCharacter == ActiveCharacter::LEFT) window.draw(animation.getAnimeSprite());
            else window.draw(animation.getGreekSprite());

            playerBar.draw(window);
            enemyBar.draw(window);

            // Level text only
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
        else if (state == GameState::VICTORY || state == GameState::DEFEAT)
        {
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