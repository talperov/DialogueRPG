#include "Character.h"
#include <algorithm>

Character::Character(const std::string& n, int maxHp, int lightAtk, int heavyAtk, int potion)
    : name(n), hp(maxHp), maxHP(maxHp), lightAttack(lightAtk), heavyAttack(heavyAtk), potionHeal(potion)
{
}

// Accessors
int Character::getHP() const { return hp; }
int Character::getMaxHP() const { return maxHP; }
int Character::getLightAttack() const { return lightAttack; }
int Character::getHeavyAttack() const { return heavyAttack; }
int Character::getPotionHeal() const { return potionHeal; }
std::string Character::getName() const { return name; }

// Actions
void Character::takeDamage(int amount)
{
    hp -= amount;
    if (hp < 0) hp = 0;
}

void Character::heal(int amount)
{
    hp += amount;
    if (hp > maxHP) hp = maxHP;
}
