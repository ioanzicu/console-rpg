#include "UserInput.h"

UserInput::UserInput()
{
    //ctor
}

UserInput::~UserInput()
{
    //dtor
}

const int UserInput::getChoice(int &choice, const int streamSize = 1)
{
    std::cin >> setw(streamSize) >> choice; // set the stream size | one input

    while (std::cin.fail())
    {
        std::cout << std::endl << "Faulty input!" << std::endl << std::endl;
        // clear the stream
        std::cin.clear();
        // ignore all characters
        std::cin.ignore(INT_MAX, '\n');

        std::cin >> choice;
    }

}
