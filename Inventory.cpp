#include "Inventory.h"

Inventory::Inventory()
{
    this->capacity = 10;
    this->nrOfItems = 0;
    // Initialiaze Pointer to Pointer Array with new Pointer Array
    this->itemArr = new Item*[this->capacity];
}

Inventory::~Inventory()
{
    for (size_t i = 0; i < this->nrOfItems; i++)
    {
        // delete individual pointer in array
        delete this->itemArr[i];
    }
    // delete the pointer (to) array
    delete[] itemArr;
}

void Inventory::expend()
{
    // Duble the capacity
    this->capacity *= 2;
    //Create new Temp Pointer to pointer arr -> hold double capacity
    Item **tempArr = new Item*[this->capacity];

    for (size_t i = 0; i < this->nrOfItems; i++)
    {
        // Copy elements from itemArr to tempArr
         tempArr[i] = this->itemArr[i];
    }

    // delete pointer itemArr - old version
    delete[] this->itemArr;
    // assign itemArr to new inventory (tempArr)
    this->itemArr = tempArr;
    // initialize the rest of the position to nullPointer ->  prevent error on deleting the pointer
    this->initialize(this->nrOfItems);
}

// Initialize pointer to null for preventing error at the deleting pointer
// if we delete an uninitialized pointer we will recieve error
// used for initialize the remainded elements in the itemArr pointer
void Inventory::initialize(const int from)
{
    for (size_t i = from; i < capacity; i++)
    {
        // set pointer to null (initialize all of them)
        this->itemArr[i] = nullptr;
    }
}

// Add new Item to the itemArr, item passed by reference
void Inventory::addItem(const Item& item)
{

    if (this->nrOfItems >= this->capacity)
    {
        expend();
    }
    // Add new item -> hang it to the (next) pointe
    this->itemArr[this->nrOfItems++] = item.clone(); //copy
}

// Remove item, find by index and remove
void Inventory::removeItem(int index)
{

}
