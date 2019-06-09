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
    // EXPE BETWEEN 1 and 10
    int gainExp = (chances * character.getLevel() * (rand() % 10 + 1));

    std::cout << "Travel " << std::endl;

    Puzzle puzzle("Puzzles/puzzle1.txt");

    while (!completed && chances > 0)
    {
        std::cout << "Chances: " << chances << std::endl;
        // Decrement the chance
        chances--;

        // Display Question
        std::cout << puzzle.getAsString() << std::endl;

        std::cout << "\nYour ANSWER: ";
        std::cin >> userAns;
        std::cout << "\n";

        // Error checking for input
        // loop until the input is valid/correct
        // numerical value, NOT string or char
        while (std::cin.fail())
        {
            std::cout << "Faulty input!" << "\n";
            // clear the stream
            std::cin.clear();
            // ignore 100 chars
            std::cin.ignore(100, '\n');
            // enter chice again
            std::cout << "\nYour ANSWER: ";
            std::cin >> userAns;
        }

        std::cin.ignore(100, '\n');
        std::cout << "\n";

        if (puzzle.getCorrectAns() == userAns)
        {
            completed = true;
            // Get addiction la exp for correct answer
            character.gainExp(gainExp);
            std::cout << "YOU GAINED " << gainExp << " EXP!" << std::endl << std::endl;
        }
    }

    if (completed)
    {
        std::cout << "Congratulations, You are Right!!!\n\b";
    }
    else
    {
        std::cout << "You LOST :(\n\n";
    }
}
