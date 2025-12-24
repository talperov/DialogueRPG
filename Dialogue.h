#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

// Manages dialogue display in the game.
class Dialogue {
public:
    // Struct for a single dialogue line with speaker.
    struct DialogueLine {
        std::string text;                   // Text of the line.
        enum class Speaker { LEFT, RIGHT, ENEMY };  // Speaker type.
        Speaker speaker;                    // Who is speaking.
    };

private:
    std::vector<DialogueLine> lines;    // List of dialogue lines.
    sf::Text visual;                    // Text object for display.
    sf::Font font;                      // Font for text.
    size_t currentLine;                 // Index of current line.
    bool active;                        // Whether dialogue is active.
    sf::RectangleShape background;      // Background box for text.

public:
    // Constructor.
    Dialogue();

    // Destructor.
    ~Dialogue();

    // Set new dialogue lines.
    void setLine(const std::vector<DialogueLine>& newLines);

    // Advance to the next line.
    bool nextLine();

    // Reset dialogue state.
    void reset();

    // Check if dialogue is active.
    bool isActive() const;

    // Draw dialogue on the window.
    void draw(sf::RenderWindow& window);

    // Set text color.
    void setColor(const sf::Color& color);

    // Update text and color for current line (internal helper).
    void updateTextAndColor();
};