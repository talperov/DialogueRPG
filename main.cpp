#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Test"); // Create window

    sf::Texture animeTexture;
    if (!animeTexture.loadFromFile("Sprites/Characters/AnimeMan/AnimeLVL1.png")) // Load AnimeMan
    {
        std::cout << "Failed to load AnimeMan!\n";
        return -1;
    }
    sf::Sprite animeSprite(animeTexture); // Create sprite
    animeSprite.setPosition(50.f, 300.f); // Position left

    sf::Texture greekTexture;
    if (!greekTexture.loadFromFile("Sprites/Characters/GreekMan/GreekLVL1.png")) // Load GreekMan
    {
        std::cout << "Failed to load GreekMan!\n";
        return -1;
    }
    sf::Sprite greekSprite(greekTexture);
    greekSprite.setPosition(500.f, 300.f); // Position right

    sf::Texture goldTexture;
    if (!goldTexture.loadFromFile("Sprites/GoldMan/GoldV1.png")) // Load GoldMan
    {
        std::cout << "Failed to load GoldMan!\n";
        return -1;
    }
    sf::Sprite goldSprite(goldTexture);
    goldSprite.setPosition(300.f, 100.f); // Position middle/top

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) // Event polling
        {
            if (event.type == sf::Event::Closed)
            {
                window.close(); // Close window
            }
        }

        window.clear(sf::Color::White); // Clear screen
        window.draw(animeSprite);       // Draw left character
        window.draw(greekSprite);       // Draw right character
        window.draw(goldSprite);        // Draw GoldMan
        window.display();               // Show everything
    }

    return 0; // End program
}
