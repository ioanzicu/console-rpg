#ifndef ARMOR_H
#define ARMOR_H

#include "STLINCLUDE.h"
#include "Item.h"

enum armorType { HEAD = 0, CHEST, ARMS, LEGS };

class Armor : public Item
{
    public:
        Armor();
        Armor(int level, int rarity);
        Armor(int type,
              int defence,
               std::string name,
               int level,
               int buyValue,
               int sellValue,
               int rarity);
        virtual ~Armor();

        // PURE VIRTUAL
        virtual Armor* clone() const;

        //Functions
        virtual std::string toString() const;

        // Accessors
        inline int getDefence() const { return this->defence; };
        inline int getType() const { return this->type; };

        // Static
        static dArr<std::string> names;
        static void initNames();


    protected:

    private:
        int type;
        int defence;
};

#endif // ARMOR_H
