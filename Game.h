#include "Functions.h"
#include "Event.h"

#include <ctime>
#include <vector>
#include <fstream>
#include <sstream>

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
    void createCharacter();
    void saveCharacters();
    void loadCharacters();
    void Travel();

    // Accessors
    inline bool getPlaying() const { return this->playing; }

    // Modifiers

    protected:

    private:
        int choice;
        bool playing;

        // Character related
        int activeCharacter;
        std::vector<Character> characters;
        std::string fileName;
};

#endif // GAME_H
