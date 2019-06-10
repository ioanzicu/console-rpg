#include "Enemy.h"


Enemy::Enemy(int level)
{
    this->level = level;
    this->hpMax = level * 10;
    this->hp = this->hpMax;
    this->damageMin = this->level * 1;
    this->damageMax = this->level * 2;
    this->dropChance = rand() % 100 + 1;
    this->defence = rand() % level*3 + 1;
    this->accuracy = random() % level*3 + 1;

}

Enemy::~Enemy()
{
    //dtor
}

std::string Enemy::getAsString() const
{
    return "Level: " + std::to_string(this->level) + "\n" +
        "HP: " + std::to_string(this->hp) + " / " + std::to_string(this->hpMax) + "\n" +
        "Damage: " + std::to_string(this->damageMin) + " / " + std::to_string(this->damageMax) + "\n" +
        "Defence: " + std::to_string(this->defence) + "\n" +
        "Accuracy: " + std::to_string(this->accuracy) + "\n" +
        "Drop Chance: " + std::to_string(this->dropChance) + "\n";
}

void Enemy::takeDamage(int damage)
{
    this->hp -= damage;

    //  if hp == 0, ,make him dead
    if (this->hp <= 0)
    {
        this->hp = 0;
    }
}
