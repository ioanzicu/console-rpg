#include "Item.h"

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
