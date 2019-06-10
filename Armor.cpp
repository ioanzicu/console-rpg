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
    Armor::names.push("Friend ZONE");
}

Armor::Armor()
    : Item()
{
    this->defence = 0;
}

Armor::Armor(int level, int rarity)
    : Item(level, rarity)
{
    this->defence = rand() % (level * (rarity + 1)); // +1 to prvent zero
    this->defence += (rarity + 1) * 5;
    this->type = rand() % 4;
    this->setName(Armor::names[rand() % Armor::names.size()]);

    switch(this->type)
    {
        case armorType::HEAD:
            this->typeStr = "Head";
            break;
        case armorType::CHEST:
            this->typeStr = "Chest";
            break;
        case armorType::ARMS:
            this->typeStr = "Arms";
            break;
        case armorType::LEGS:
            this->typeStr = "Legs";
            break;
        default:
            break;
    }

    if (rarity == 3) // LEGENDARY
        this->defence += level * 5; // extra damage
    // If level 10, get 100 extra defence
    else if (rarity == 4) // EPIC
        this->defence += level * 10;
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

// RETURN A NEW (ON HEAP) COPY OF ITSELF
Armor* Armor::clone() const
{
    return new Armor(*this);
}

std::string Armor::toString() const
{
    std::string str =
        this->getName()
        + " Lvl: " +
        std::to_string(this->getLevel())
        + " Defence: " +
        std::to_string(this->defence)
        + " Type: " +
        this->typeStr
        + " Rarity: " +
        std::to_string(this->getRarity())
        + " $: " +
        std::to_string(this->getSellValue());

    return str;
}
