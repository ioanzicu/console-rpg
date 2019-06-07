#include "Character.h"

Character::Character()
{
    name = "";
    level = 0;
    exp = 0;
    expNext = 0;
    hp = 0;
    hpMax = 0;
    stamina = 0;
    damageMin = 0;
    damageMax = 0;
    defence = 0;
}

Character::~Character()
{
    //dtor
}

// Functions
void Character::initialize(int level, std::string name)
{
    this->name = name;
    this->level = level;
    this->exp = 0;
    this->expNext = level * 100;
    this->hp = 10;
    this->hpMax = 10;
    this->stamina = 10;
    this->damageMin = 2;
    this->damageMax = 4;
    this->defence = 1;
}
