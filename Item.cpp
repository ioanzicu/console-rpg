#include "Item.h"

Item::Item()
{
    this->name = "EMPTY";
    this->level = 0;
    this->buyValue = 0;
    this->sellValue = 0;
    this->rarity = 0;
}

Item::Item(int level, int rarity)
{
    this->name = "RANDOM";
    this->level = rand() % (level + 2) + 1; // item form lvl 1 to current
    this-> buyValue = level * this->rarity * 10;
    this->sellValue = this->buyValue / 2;
    this->rarity = rarity;
}

Item::Item(std::string name, int level, int sellValue, int buyValue, int rarity)
{
    this->name = name;
    this->level = level;
    this->buyValue = buyValue;
    this->sellValue = sellValue;
    this->rarity = rarity;
}

Item::~Item()
{
    //dtor
}
