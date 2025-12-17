#pragma once
#include <string>

class Character
{
private:
    std::string name;
    int hp;
    int maxHP;
    int lightAttack;
    int heavyAttack;
    int potionHeal;

public:
    Character(const std::string& n, int maxHp, int lightAtk, int heavyAtk, int potion);

    int getHP() const;          // Current HP
    int getMaxHP() const;       // Max HP
    int getLightAttack() const; // Light attack value
    int getHeavyAttack() const; // Heavy attack value
    int getPotionHeal() const;  // Potion heal value

    void takeDamage(int amount); // Reduce HP
    void heal(int amount);       // Increase HP (up to max)
    std::string getName() const; // Character name
};
