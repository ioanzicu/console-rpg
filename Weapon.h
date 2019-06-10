#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"

class Weapon : public Item
{
    public:
        Weapon(int damageMin = 0,
               int damageMax = 0,
               std::string name = "NONE",
               int level = 0,
               int buyValue = 0,
               int sellValue = 0,
               int rarity = 0);
        virtual ~Weapon();

        // PURE VIRTUAL
        virtual Weapon* clone() const;

        //Functions
        std::string toString();

        // Accessors
        inline int getDamageMin() const { return this->damageMin; };
        inline int getDamageMax() const { return this->damageMax; };

        // Modifiers



    protected:

    private:
        int damageMin;
        int damageMax;
};

#endif // WEAPON_H
