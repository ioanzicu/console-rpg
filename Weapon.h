#ifndef WEAPON_H
#define WEAPON_H

#include "STLINCLUDE.h"
#include "Item.h"

class Weapon : public Item
{
    public:
        Weapon();
        Weapon(
            int level,
            int rarity
        );
        Weapon(
            int damageMin,
            int damageMax,
            std::string name,
            int level,
            int buyValue,
            int sellValue,
            int rarity
        );
        virtual ~Weapon();

        // IMPLEMENT VIRTUAL FUNCTIONS FORM PARENT ABSTRACT CLASS
        virtual Weapon* clone() const;

        //Functions
        virtual std::string toString() const;
        virtual std::string toStringSave() const;


        // Accessors
        inline int getDamageMin() const { return this->damageMin; };
        inline int getDamageMax() const { return this->damageMax; };

        // Modifiers

        // Static
        static dArr<std::string> names;
        static void initNames();

    private:
        int damageMin;
        int damageMax;
};

#endif // WEAPON_H
