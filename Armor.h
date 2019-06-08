#ifndef ARMOR_H
#define ARMOR_H

#include "Item.h"

class Armor : public Item
{
    public:
        Armor(int type = 0, int defence = 0,
               std::string name = "NONE",
               int level = 0,
               int buyValue = 0,
               int sellValue = 0,
               int rarity = 0);
        virtual ~Armor();

        // PURE VIRTUAL
        virtual Armor* clone() const;

        //Functions
        std::string toString();

    protected:

    private:
        int type;
        int defence;
};

#endif // ARMOR_H
