#ifndef INVENTORY_H
#define INVENTORY_H

#include "Weapon.h"
#include "Armor.h"

class Inventory
{
    public:
        Inventory();
        virtual ~Inventory();
        // Functions
        void addItem(const Item& item);
        void removeItem(int index);
        inline void debugPrint() const
        {
            for (size_t i = 0; i < this->nrOfItems; i++)
            {
                std::cout << this->itemArr[i]->debugPrint() << std::endl;
            }
        }

    protected:

    private:
        int capacity;
        int nrOfItems;
        // Pointer Array Which holds Pointer Elements
        Item **itemArr; // Pointer of Pointer -> very efficient
        void expend();
        void initialize(const int from);
};

#endif // INVENTORY_H
