#include <SFML/Graphics.hpp>
#include "Animation.h"

enum class GameState { MENU, GAME, HELP }; // Game states

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML RPG"); // Create window
    Animation animation; // Animation object
    GameState state = GameState::MENU; // Start in menu

    animation.loadMenuBackground(window); // Load menu background
    animation.loadMenuButtons();          // Load menu buttons

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) // Event polling
        {
            if (event.type == sf::Event::Closed)
                window.close(); // Close window

            // Mouse click detection
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window)); // Mouse coords

                if (state == GameState::MENU)
                {
                    if (animation.getPlaySprite().getGlobalBounds().contains(mousePos))
                    {
                        state = GameState::GAME;          // Switch to game
                        animation.loadBackground(window); // Load game background
                        animation.createAnime();          // Load AnimeMan
                        animation.createGreek();          // Load GreekMan
                        // animation.createGold();         // Keep GoldMan commented
                    }
                    else if (animation.getHelpSprite().getGlobalBounds().contains(mousePos))
                    {
                        state = GameState::HELP; // Switch to help
                    }
                    else if (animation.getExitSprite().getGlobalBounds().contains(mousePos))
                    {
                        window.close(); // Exit game
                    }
                }
            }
        }

        window.clear(sf::Color::Black); // Clear screen

        if (state == GameState::MENU)
        {
            window.draw(animation.getBackground()); // Draw menu background
            window.draw(animation.getPlaySprite());  // Draw Play button
            window.draw(animation.getHelpSprite());  // Draw Help button
            window.draw(animation.getExitSprite());  // Draw Exit button
        }
        else if (state == GameState::GAME)
        {
            window.draw(animation.getBackground());    // Draw game background
            window.draw(animation.getAnimeSprite());   // Draw AnimeMan
            window.draw(animation.getGreekSprite());   // Draw GreekMan
            // window.draw(animation.getGoldSprite()); // Keep GoldMan commented
        }
        else if (state == GameState::HELP)
        {
            window.clear(sf::Color::Blue); // Placeholder help screen
        }

        window.display(); // Show everything
    }

    return 0; // End program
}
