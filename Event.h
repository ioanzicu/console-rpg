#ifndef EVENT_H
#define EVENT_H

#include "STLINCLUDE.h"

#include "Character.h"
#include "Enemy.h"
#include "Puzzle.h"
#include "Boss.h"

class Event
{
    public:
        Event();
        virtual ~Event();
        void generateEvent(Character &character, dArr<Enemy>& enemies);

        // Events
        void shopEncounter(Character &character);
        void enemyEncounter(Character &character, dArr<Enemy>& enemies);
        void puzzleEncounter(Character &character);
        void bossEncounter(Character &character, Boss &boss);

        // statics
        static int nrOfEvents;

    protected:

    private:

};



#endif // EVENT_H
