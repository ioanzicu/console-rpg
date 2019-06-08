#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>

class Item
{
    public:
        Item();
        virtual ~Item();

        inline std::string debugPrint() const { return this->name; }

    protected:

    private:
        std::string name;
        int buyValue;
        int sellValue;

};

#endif // ITEM_H
