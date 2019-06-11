#ifndef ITEM_H
#define ITEM_H

#include "STLINCLUDE.h"

class Item
{
    public:
        Item();
        Item(
            int itemType,
            int level,
            int rarity
        );
        Item(
            int itemType,
            std::string name,
            int level,
            int buyValue,
            int sellValue,
            int rarity
        );
        virtual ~Item();

        inline std::string debugPrint() const { return this->name; }
        // Make Item PUR VIRTUAL - ITEM IS ABSTRACT CLASS,
        // prevent instanciating of Item (just Armor or Weapon)
        // we can make pointers, but not direct instances
        // BECAUSE = 0 -> child classes HAVE TO define that function
        virtual Item* clone() const = 0;
        virtual std::string toString() const = 0;

        // Accessors
        inline const std::string& getName() const { return this->name; }
        inline const int& getLevel() const { return this->level; }
        inline const int& getByValue() const { return this->buyValue; }
        inline const int& getSellValue() const { return this->sellValue; }
        inline const int& getRarity() const { return this->rarity; }
        inline const int& getItemType() const { return this->itemType; }

        // Modifiers
        inline void setName(std::string name) { this->name = name; }

    private:
        int itemType;
        std::string name;
        int level;
        int buyValue;
        int sellValue;
        int rarity;
};

enum itemType { WEAPON = 0, ARMOR = 1 };

enum rarity { COMMON = 0,
              UNCOMMON,
              RARE,
              LEGENDARY,
              EPIC };


#endif // ITEM_H
