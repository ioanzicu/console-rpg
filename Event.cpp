#include "Event.h"

Event::Event()
{
    this->nrOfEvents = 2;
}

Event::~Event()
{
    //dtor
}

void Event::generateEvent(Character &character)
{
    // Generate an event from 0 to 1
    int i = rand() % this->nrOfEvents;

    switch (i)
    {
        case 0:
            // Enemy encounter
            enemyEncounter(character);
            break;

        case 1:
            // Puzzle
            puzzleEncounter(character);
            break;
        default:
            break;
    }
}

// Different events
void Event::enemyEncounter(Character &character)
{

}

void Event::puzzleEncounter(Character &character)
{

}
