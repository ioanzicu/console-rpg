#include "Armor.h"

// Created ONCE FOR ALL GAME when the item is included
dArr<std::string> Armor::names;
// STAIC FUNCTIONS CAN HANDLE JUST STATIC MEMEBER
void Armor::initNames()
{
    Armor::names.push("Marsian Defender");
    Armor::names.push("Wet Wipes");
    Armor::names.push("Laser Shield");
    Armor::names.push("Ignoring Other");
    Armor::names.push("Alien Blanket");
    Armor::names.push("Iron Sheets");
}

Armor::Armor()
    : Item()
{
    this->defence = 0;
}

Armor::Armor(int level, int rarity)
    : Item(level, rarity)
{
    this->defence = rand() % (level * rarity); // +1 to prvent zero
    this->defence += rarity * 2;
}

Armor::Armor(int type, int defence, std::string name, int level, int buyValue, int sellValue, int rarity)
    : Item(name, level, buyValue, sellValue, rarity)
{
    this->type = type;
    this->defence = defence;
}

Armor::~Armor()
{
    //dtor
}

std::string Armor::toString()
{
    std::string str = std:: to_string(this->type) + " " + std::to_string(this->defence);

    return str;
}

// RETURN A NEW (ON HEAP) COPY OF ITSELF
Armor* Armor::clone() const
{
    return new Armor(*this);
}
