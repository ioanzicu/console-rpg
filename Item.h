#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>

class Item
{
    public:
        Item(std::string name = "NONE", int level = 0,
             int buyValue = 0,
             int sellValue = 0,
             int rarity = 0);
        virtual ~Item();

        inline std::string debugPrint() const { return this->name; }
        // Make Item PUR VIRTUAL, prevent instanciating of Item (just Armor or Weapon)
        virtual Item* clone() const = 0;

        // Accessors
        inline const std::string& getName() const { return this->name; };
        inline const int& getLevel() const { return this->level; };
        inline const int& getByValue() const { return this->buyValue; };
        inline const int& getSellValue() const { return this->sellValue; };
        inline const int& getRarity() const { return this->rarity; };

        // Modifiers



    protected:

    private:
        std::string name;
        int level;
        int buyValue;
        int sellValue;
        int rarity;
};

#endif // ITEM_H
