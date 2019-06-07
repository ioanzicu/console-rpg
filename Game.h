#pragma once

#include "Character.h"
#include "functions.h"
#include <iostream>
#include <iomanip>
#include <ctime>




#ifndef GAME_H
#define GAME_H


class Game
{
    public:
        Game();
        virtual ~Game();
    // Operators

    // Functions
    void mainMenu();

    // Accessors
    inline bool getPlaying() const { return this->playing; }

    // Modifiers

    protected:

    private:
        int choice;
        bool playing;

};

#endif // GAME_H
