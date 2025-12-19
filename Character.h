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

    // Only level now — no XP
    int level = 1;

public:
    Character(const std::string& n, int maxHp, int lightAtk, int heavyAtk, int potion);

    // Getters
    int getHP() const { return hp; }
    int getMaxHP() const { return maxHP; }
    int getLightAttack() const { return lightAttack; }
    int getHeavyAttack() const { return heavyAttack; }
    int getPotionHeal() const { return potionHeal; }
    std::string getName() const { return name; }
    int getLevel() const { return level; }

    void takeDamage(int amount);
    void heal(int amount);

    // NEW: Level up on win
    void levelUp();
};