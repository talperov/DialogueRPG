#pragma once
#include <string>

// Represents a character in the game with stats and actions.
class Character {
private:
    std::string name;      // Character's name.
    int hp;                // Current health points.
    int maxHP;             // Maximum health points.
    int lightAttack;       // Damage from light attack.
    int heavyAttack;       // Damage from heavy attack.
    int potionHeal;        // Healing amount from potion.
    int level;             // Current level (starts at 1).

public:
    // Constructor to initialize character stats.
    Character(const std::string& n, int maxHp, int lightAtk, int heavyAtk, int potion);

    // Apply damage to the character.
    void takeDamage(int amount);

    // Heal the character.
    void heal(int amount);

    // Level up the character (caps at level 3).
    void levelUp();

    // Get current HP.
    int getHP() const { return hp; }

    // Get max HP.
    int getMaxHP() const { return maxHP; }

    // Get light attack damage.
    int getLightAttack() const { return lightAttack; }

    // Get heavy attack damage.
    int getHeavyAttack() const { return heavyAttack; }

    // Get potion heal amount.
    int getPotionHeal() const { return potionHeal; }

    // Get character name.
    std::string getName() const { return name; }

    // Get current level.
    int getLevel() const { return level; }
};