#ifndef INVENTORY_H
#define INVENTORY_H

#include "STLINCLUDE.h"
#include "Weapon.h"
#include "Armor.h"

class Inventory
{
    public:
        Inventory();
        virtual ~Inventory();
        Inventory(const Inventory &obj); // Copy Constructor
        inline int size() const { return this->nrOfItems; };
        // Return a reference to item
        Item& operator[](const int index); // Index Operator Overloading
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
        void initialize(const int from = 0);
};

#endif // INVENTORY_H
