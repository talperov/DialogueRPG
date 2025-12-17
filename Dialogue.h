#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Dialogue
{
public:
    // Struct for each dialogue line with speaker info
    struct DialogueLine
    {
        std::string text;       // Dialogue text
        enum class Speaker { LEFT, RIGHT } speaker; // Who is speaking
    };

private:
    std::vector<DialogueLine> lines; // Dialogue lines with speaker
    sf::Text visual;                 // On-screen text
    sf::Font font;                   // Font used
    size_t currentLine;              // Current dialogue index
    bool active;                     // Is dialogue running

public:
    Dialogue();
    ~Dialogue();

    void setLine(const std::vector<DialogueLine>& newLines); // Load dialogue
    bool nextLine();                                        // Advance dialogue
    void reset();                                           // Reset dialogue
    bool isActive() const;                                  // Check active state
    void draw(sf::RenderWindow& window);                    // Draw dialogue
    void setColor(const sf::Color& color); // Set the color of the dialogue text

};
