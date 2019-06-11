#include "Inventory.h"

Inventory::Inventory()
{
    this->capacity = 5;
    this->nrOfItems = 0;
    // Initialiaze Pointer to Pointer Array with new Pointer Array
    this->itemArr = new Item*[this->capacity];
    // initialize all pointer to nullptr - to not
    // get errors on deleting uninitialized pointer
    this->initialize();
}

Inventory::~Inventory()
{
    for (size_t i = 0; i < this->nrOfItems; i++)
    {
        // delete individual pointer in array
        delete this->itemArr[i];
    }
    // delete the pointer (to) array
    delete[] this->itemArr;
}

// copy object with it's particular fields
Inventory::Inventory(const Inventory &obj)
{
    this->capacity = obj.capacity;
    this->nrOfItems = obj.nrOfItems;
    this->itemArr = new Item*[this->capacity]; // create new Item Pointer Array

    // Copy each element itemArr in new Item Array
    for (size_t i = 0; i < this->nrOfItems; i++)
    {
        this->itemArr[i] = obj.itemArr[i]->clone();
    }
    // initialize to nullptr the pointer inside the array
    initialize(this->nrOfItems);
}

// Overloaded index operator
// Make sure that the index is in the bound of the array
Item& Inventory::operator[](const int index)
{
    if (index < 0 || index >= this->nrOfItems)
        throw("BAD INDEX!");

    // return an object
    return *this->itemArr[index];
}

void Inventory::operator=(const Inventory &obj)
{
    // DELETE EVERITHING from the LEFT SIDE OBJECT
    for (size_t i = 0; i < this->nrOfItems; i++)
    {
        // delete individual pointer in array
        delete this->itemArr[i];
    }
    // delete the pointer (to) array
    delete[] this->itemArr;

    // COPY EVERITHING FORM RIGHT SIDE TO LEFT SIDE OBJECT
    this->capacity = obj.capacity;
    this->nrOfItems = obj.nrOfItems;
    this->itemArr = new Item*[this->capacity]; // create new Item Pointer Array

    // Copy each element itemArr in new Item Array
    for (size_t i = 0; i < this->nrOfItems; i++)
    {
        this->itemArr[i] = obj.itemArr[i]->clone();
    }
    // initialize to nullptr the pointer inside the array
    initialize(this->nrOfItems);
}

// Double size of the inventory
void Inventory::expend()
{
    // Double the capacity
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
    // if nr of item is bigger than capacity, expand (*2)
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
    if (index < 0 || index >= this->nrOfItems)
        throw("OUT OF BOUNDS REMOVE ITEM INVENTORY");

    // delete selected item at given index
    delete this->itemArr[index];
    // make the deleted item to point to the last item in the array
    this->itemArr[index] = this->itemArr[this->nrOfItems - 1];
    // set the last pointer to item to null (remove from array)_
    this->itemArr[--this->nrOfItems] = nullptr;
}
