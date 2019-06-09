#ifndef DARR_H
#define DARR_H

/*
GENERIC TYPE -> Type wich will came in RUNTIME (NOT COMPILE TIME)
*/

template<typename T>
class dArr
{
private:
    unsigned capacity;
    unsigned initialCap;
    unsigned nrOfElements;
    T* *arr;

    void expand();
    void initialize(unsigned from);
public:
    dArr(unsigned size = 5);
    dArr(const dArr& obj);
    ~dArr();

    T& operator[] (const unsigned index);
    void operator= (const dArr& obj);

    unsigned maxCap();
    unsigned size();
    void push(const T element);
    // if ordered true - longer type of deleting, else fast deleting
    void remove(const unsigned index, bool ordered = false);
};

template<typename T>
dArr<T>::dArr(unsigned size)
{
    this->initialCap = size;
    this->capacity = size;
    this->nrOfElements = 0;

    this->arr = new T*[this->capacity];

    this->initialize(0);
}

// Copy Constructor is called when an object (which doesn't exist)
// is created from another object
template<typename T>
dArr<T>::dArr(const dArr& obj)
{
    this->initialCap = obj.initialCap;
    this->capacity = obj.capacity;
    this->nrOfElements = obj.nrOfElements;

    this->arr = new T*[this->capacity];

    for (size_t i = 0; i < this->nrOfElements; i++)
    {
        this->arr[i] = new T(*obj.arr[i]);
    }

    this->initialize(0);
}

template<typename T>
dArr<T>::~dArr()
{
    for (size_t i = 0; i < this->nrOfElements; i++)
    {
        delete this->arr[i];
    }
    delete[] arr;
}

template<typename T>
T& dArr<T>::operator[] (const unsigned index)
{
    if (index < 0 || index >= this->nrOfElements)
        throw "OUT OF BOUNDS INDEXING OPERATOR.";

    return *this->arr[index];
}


// Assignment operator is called when both objects exists
// both with own data
//  s1 = s2
template<typename T>
void dArr<T>::operator= (const dArr& obj)
{
    // Delete the data wich is in object already
    for (size_t i = 0; i < this->nrOfElements; i++)
    {
        delete this->arr[i];
    }
    delete[] arr;

    // Set new data
    this->initialCap = obj.initialCap;
    this->capacity = obj.capacity;
    this->nrOfElements = obj.nrOfElements;
    // Make new array
    this->arr = new T*[this->capacity];
    // copy elements all elements to new array
    for (size_t i = 0; i < this->nrOfElements; i++)
    {
        this->arr[i] = new T(*obj.arr[i]);
    }

    this->initialize(0);
}

template<typename T>
void dArr<T>::expand()
{
    // double capacity
    this->capacity *= 2;

    // create temporary array
    T* *tempArr = new T*[this->capacity];

    // copy existing elements to new array
    for (size_t i = 0; i < this->nrOfElements; i++)
    {
        tempArr[i] = this->arr[i];
    }

    // delete current array
    delete[] arr;

    // make old array to point to new array
    this->arr = tempArr;

    // initialize
    this->initialize(this->nrOfElements);
}

template<typename T>
void dArr<T>::initialize(unsigned from)
{
    for (size_t i = from; i < this->capacity; i++)
    {
        this->arr[i] = nullptr;
    }
}

// total size of array
template<typename T>
unsigned dArr<T>::maxCap()
{
    return this->capacity;
}

// current number of elements
template<typename T>
unsigned dArr<T>::size()
{
    return this->nrOfElements;
}

template<typename T>
void dArr<T>::push(const T element)
{
    // make sure that there is space for all elements
    if (this->nrOfElements >= this->capacity)
        this->expand();

    // Add new element in Array
    this->arr[this->nrOfElements++] = new T(element);
}

// if ordered true - longer type of deleting, else fast deleting
template<typename T>
void dArr<T>::remove(const unsigned index, bool ordered)
{
    // Check the if index is in the BOUND
    if (index < 0 || index >= this->nrOfElements)
        throw "OUT OF BOUNDS REMOVE.";


    if (ordered)
    {
        // delete the item at index position
        delete this->arr[index];

        // loop untill the end of array
        for (size_t i = 0; i < this->nrOfElements-1; i++)
        {
            this->arr[i] = this->arr[i + 1];
        }

        // set the before last element to null
        this->arr[--this->nrOfElements] = nullptr;
    }
    else // Not ordered
    {
        // remove the item at index position
        delete this->arr[index];

        /*
                                                            nrOfElements - alway empty
        Elements            [1]  [2]  [3]  [4]  [5]  [6]  [7]  []
        Ptr to Elements     [*1] [*2] [*3] [*4] [*5] [*6] [*7] []


        REMOVE 4                                               nrOfElements - alway empty
        Elements            [1]  [2]  [3]  []   [5]  [6]  [7]  []
        Make 4 pointer to point to 7
        Ptr to Elements     [*1] [*2] [*3] [*7] [*5] [*6] [*7] []
        Remove 7 pointer
        Ptr to Elements     [*1] [*2] [*3] [*7] [*5] [*6] [] []
        Reduce nrOfElements
        Ptr to Elements     [*1] [*2] [*3] [*7] [*5] [*6] []

        */

        // set the removed pointer to pint to the before last element
        this->arr[index] = this->arr[this->nrOfElements - 1];
        // set before last element to null
        this->arr[--this->nrOfElements] = nullptr;
    }
}


#endif // DARR_H
