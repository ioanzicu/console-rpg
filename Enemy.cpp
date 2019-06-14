#include "Enemy.h"


Enemy::Enemy(int level)
{
    this->setLevel(level);
    this->setHpMax(rand() % (level * 10) + (level * 2));
    this->setHp(this->getHpMax());
    this->setDamageMin(this->getLevel() * 1);
    this->setDamageMax(this->getLevel() * 2);
    this->setDefence(rand() % this->getLevel() * 3 + 1);
    this->setAccuracy(rand() % this->getLevel() * 3 + 1);

    this->dropChance = rand() % 100 + 1;
}

Enemy::~Enemy()
{
    //dtor
}

std::string Enemy::getAsString() const
{
    std::stringstream ss;

    ss << "Level: " << this->getLevel() << "\n" <<
        " | HP: " << this->getHp() << " / " << this->getHpMax() << "\n" <<
        " | Damage: "  << this->getDamageMin() << " / " << this->getDamageMax() << "\n" <<
        " | Defence: " << this->getDefence() << "\n" <<
        " | Accuracy: " << this->getAccuracy() << "\n" <<
        " | Drop Chance: " << this->dropChance << "\n";

    return ss.str();
}

std::string Enemy::getAsStringEvent() const
{
    std::stringstream ss;

    ss << "Level: " << this->getLevel() << " " <<
        "HP: " << this->getHp() << " / " << this->getHpMax() << " " <<
        "Damage: " << this->getDamageMin() << " / " << this->getDamageMax() << " " <<
        "Defence: " << this->getDefence() << " " <<
        "Accuracy: " << this->getAccuracy() << "\n";

    return ss.str();
}

void Enemy::takeDamage(int damage)
{
    this->setHp(this->getHp() - damage);

    if (this->getHp() <= 0)
    {
        this->setHp(0); // DEAD ENEMY
    }
}
