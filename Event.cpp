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
    // while()

}

void Event::puzzleEncounter(Character &character)
{
    bool completed = false;
    int userAns = 0;
    int chances = 3;

    std::cout << "Travel " << std::endl;

    Puzzle puzzle("Puzzles/puzzle1.txt");

    while (!completed && chances > 0)
    {
        // Decrement the chance
        chances--;
        // Display Question
        std::cout << puzzle.getAsString() << std::endl;

        std::cout << "\nYour ANSWER: ";
        std::cin >> userAns;
        std::cout << "\n";

        if (puzzle.getCorrectAns() == userAns)
        {
            completed = true;
            // GIVE USER EXP ETC AND CONTINUE
        }
    }

    if (completed)
    {
        std::cout << "Congratulations, You are Right!!!" << std::endl;
    }
    else
    {
        std::cout << "You LOST :(" << std::endl;
    }
}
