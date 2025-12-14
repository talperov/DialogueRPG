#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Dialogue.h"
#include "Scenes.h" // Struct-based scenes

enum class GameState { MENU, GAME, HELP };           // Game states
enum class ActiveCharacter { NONE, LEFT, RIGHT };   // Active fighter
enum class Speaker { NONE, LEFT, RIGHT };           // For dialogue text color

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML RPG"); // Create window
    Animation animation; // Animation object
    Dialogue dialogue;   // Dialogue object
    GameState state = GameState::MENU;           // Start in menu
    ActiveCharacter activeCharacter = ActiveCharacter::NONE; // No active character yet
    Speaker currentSpeaker = Speaker::LEFT;      // Start with left character

    // Staggered reveal flags
    bool showLeft = false;             // Anime
    bool showRight = false;            // Greek
    bool startedRightDialogue = false; // Tracks if Greek dialogue has started

    Scene currentScene = animeIntroLeft; // Start with left character
    dialogue.setLine(currentScene.dialogueLines); // Set initial dialogue
    dialogue.setColor(sf::Color::Yellow);          // Left character color

    animation.loadMenuBackground(window); // Load menu background
    animation.loadMenuButtons();          // Load menu buttons

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Left Mouse Button = Next
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                // MENU click
                if (state == GameState::MENU)
                {
                    if (animation.getPlaySprite().getGlobalBounds().contains(mousePos))
                    {
                        state = GameState::GAME;
                        animation.loadBackground(window);
                        dialogue.setLine(currentScene.dialogueLines); // Start left dialogue
                        dialogue.setColor(sf::Color::Yellow);
                    }
                    else if (animation.getHelpSprite().getGlobalBounds().contains(mousePos))
                        state = GameState::HELP;
                    else if (animation.getExitSprite().getGlobalBounds().contains(mousePos))
                        window.close();
                }
                // GAME click
                else if (state == GameState::GAME)
                {
                    if (dialogue.isActive())
                    {
                        dialogue.nextLine(); // Advance current dialogue
                    }
                    else
                    {
                        // Step 1: Reveal left character (Anime)
                        if (!showLeft)
                        {
                            showLeft = true;
                            animation.createAnime();
                            currentSpeaker = Speaker::LEFT;
                            dialogue.setLine(animeIntroLeft.dialogueLines);
                            dialogue.setColor(sf::Color::Yellow);
                        }
                        // Step 2: Reveal right character (Greek)
                        else if (!showRight)
                        {
                            showRight = true;
                            animation.createGreek();
                        }
                        // Step 3: Start right dialogue (Greek)
                        else if (showRight && !startedRightDialogue)
                        {
                            startedRightDialogue = true;
                            currentSpeaker = Speaker::RIGHT;
                            dialogue.setLine(animeIntroRight.dialogueLines);
                            dialogue.setColor(sf::Color::Cyan);
                        }
                        // Step 4: Start battle dialogue
                        else if (showRight && startedRightDialogue && !dialogue.isActive())
                        {
                            currentSpeaker = Speaker::LEFT; // Reset to default if needed
                            dialogue.setLine(sceneBattleStart.dialogueLines);
                            dialogue.setColor(sf::Color::Yellow);
                            currentScene = sceneBattleStart;
                        }
                    }
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

            if (showLeft)
                window.draw(animation.getAnimeSprite());
            if (showRight)
                window.draw(animation.getGreekSprite());

            if (dialogue.isActive())
                dialogue.draw(window);
        }
        // HELP render
        else if (state == GameState::HELP)
        {
            window.clear(sf::Color::Blue); // Placeholder
        }

        window.display();
    }

    return 0;
}
