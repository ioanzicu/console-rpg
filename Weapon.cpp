#include "Weapon.h"

// Created ONCE FOR ALL GAME when the item is included
dArr<std::string> Weapon::names;
// STAIC FUNCTIONS CAN HANDLE JUST STATIC MEMEBER
void Weapon::initNames()
{
    Weapon::names.push("Typical Banana");
    Weapon::names.push("Plazma Gun");
    Weapon::names.push("Death Cobra Pacifist");
    Weapon::names.push("Bad Smell Alien Socks");
    Weapon::names.push("Carrot Gadget");
    Weapon::names.push("Spoiled Gegsatrons Milk");
}

Weapon::Weapon()
    : Item()
{
    this->damageMax = 0;
    this->damageMin = 0;
}

Weapon::Weapon(int level, int rarity)
     : Item(level, rarity)
{
    this->damageMax = rand() % level * rarity;
    this->damageMax += rarity * 2;
    this->damageMin = this->damageMax / 2;
}

Weapon::Weapon(int damageMin, int damageMax, std::string name, int level, int buyValue, int sellValue, int rarity)
    : Item(name, level, buyValue, sellValue, rarity)
{
    this->damageMin = damageMin;
    this->damageMax = damageMax;
}

Weapon::~Weapon()
{
    //dtor
}

// RETURN A NEW (ON HEAP) COPY OF ITSELF
Weapon* Weapon::clone() const
{
    return new Weapon(*this);
}


std::string Weapon::toString()
{
    std::string str = std:: to_string(this->damageMin) + " " + std::to_string(this->damageMax);

    return str;
}
