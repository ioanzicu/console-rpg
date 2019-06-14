#include "Entity.h"

Entity::Entity()
{
    this->hp = 0;
    this->hpMax = 0;
    this->level = 0;
    this->damageMin = 0;
    this->damageMax = 0;
    this->defence = 0;
    this->accuracy = 0;
}

Entity::Entity(int hp, int level)
{
     this->hp = hp;
     this->hpMax = 0;
     this->level = level;
     this->damageMin = 0;
     this->damageMax = 0;
     this->defence = 0;
     this->accuracy = 0;
}

Entity::~Entity()
{
    //dtor
}
