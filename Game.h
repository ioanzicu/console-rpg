#ifndef GAME_H
#define GAME_H

#include "STLINCLUDE.h"
#include "Event.h"

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
    void levelUpCharacter();
    void characterMenu();
    void saveCharacters();
    void loadCharacters();
    void selectCharacters();
    void travel();
    void rest();

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

        // Enemies
        dArr<Enemy> enemies;
};

#endif // GAME_H
