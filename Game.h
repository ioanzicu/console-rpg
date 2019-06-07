#include "Character.h"
#include "functions.h"
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
    void initGame();
    void mainMenu();

    // Accessors
    inline bool getPlaying() const { return this->playing; }

    // Modifiers

    protected:

    private:
        int choice;
        bool playing;

        // Character
        Character character;

};

#endif // GAME_H
