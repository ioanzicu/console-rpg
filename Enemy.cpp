#include "Enemy.h"


Enemy::Enemy(int level)
{
    this->level = level;
    this->hpMax = rand() % (level * 10) + (level * 2);
    this->hp = this->hpMax;
    this->damageMin = this->level * 1;
    this->damageMax = this->level * 2;
    this->dropChance = rand() % 100 + 1;
    this->defence = rand() % level * 3 + 1;
    this->accuracy = random() % level * 3 + 1;
}

Enemy::~Enemy()
{
    //dtor
}

std::string Enemy::getAsString() const
{
    std::stringstream ss;

    ss << "Level: " << this->level << "\n" <<
        " | HP: " << this->hp << " / " << this->hpMax << "\n" <<
        " | Damage: "  << this->damageMin << " / " << this->damageMax << "\n" <<
        " | Defence: " << this->defence << "\n" <<
        " | Accuracy: " << this->accuracy << "\n" <<
        " | Drop Chance: " << this->dropChance << "\n";

    return ss.str();
}

std::string Enemy::getAsStringEvent() const
{
    std::stringstream ss;

    ss << "Level: " << this->level << " " <<
        "HP: " << this->hp << " / " << this->hpMax << " " <<
        "Damage: " << this->damageMin << " / " << this->damageMax << " " <<
        "Defence: " << this->defence << " " <<
        "Accuracy: " << this->accuracy << "\n";

    return ss.str();
}

void Enemy::takeDamage(int damage)
{
    this->hp -= damage;

    if (this->hp <= 0)
    {
        this->hp = 0; // DEAD ENEMY
    }
}
