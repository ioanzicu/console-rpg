#include "UserInput.h"
#include <bits/stdc++.h>

UserInput::UserInput()
{
    //ctor
}

UserInput::~UserInput()
{
    //dtor
}

const int UserInput::getChoice(int &choice, const std::string menu_str, const int streamSize = 1)
{
    std::cout << menu_str;

    std::cout << " - Choice: ";
    std::cin >> std::setw(streamSize) >> choice; // set the stream size | one input

    while (std::cin.fail())
    {
        std::system("clear");
        std::cout << std::endl << "Faulty input!" << std::endl << std::endl;
        // std::system("pause");
        std::cout << std::endl;
        //
        //std::system("clear");

        // clear the stream  (error flag for cin)
        std::cin.clear();
        // ignore all characters
        std::cin.ignore(INT_MAX, '\n');

        std::cout << menu_str << std::endl << std::endl;
        std::cout << " - Choice: ";
        std::cin >> std::setw(streamSize) >> choice;
    }

    std::cout << std::endl;

    std::cin.clear();
    // ignore all characters
    std::cin.ignore(INT_MAX, '\n');
}
