#ifndef USERINPUT_H
#define USERINPUT_H

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

class UserInput
{
    public:
        UserInput();
        virtual ~UserInput();

        static const int getChoice(int &choice, const std::string menu_str, const int streamSize);


    protected:

    private:
};

#endif // USERINPUT_H
