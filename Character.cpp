#include "Character.h"
#include <algorithm>

Character::Character(const std::string& n, int maxHp, int lightAtk, int heavyAtk, int potion)
    : name(n), hp(maxHp), maxHP(maxHp), lightAttack(lightAtk), heavyAttack(heavyAtk), potionHeal(potion), level(1) {
}  // Initialize level to 1.

void Character::takeDamage(int amount) {
    hp -= amount;
    if (hp < 0) hp = 0;
}

void Character::heal(int amount) {
    hp += amount;
    if (hp > maxHP) hp = maxHP;
}

void Character::levelUp() {
    if (level >= 3) return;  // Max level 3.
    level++;
    maxHP += 30;
    hp = maxHP;  // Full heal on level up.
    lightAttack += 5;
    heavyAttack += 8;
    potionHeal += 10;
}