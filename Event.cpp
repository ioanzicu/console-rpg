#include "Event.h"

Event::Event()
{
    this->nrOfEvents = 2;
}

Event::~Event()
{
    //dtor
}

void Event::generateEvent(Character &character, dArr<Enemy>& enemies)
{
    // Generate an event from 0 to 1
    int i = rand() % this->nrOfEvents;

    switch (i)
    {
        case 0:
            // Enemy encounter
            enemyEncounter(character, enemies);
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

// BATTLE
void Event::enemyEncounter(Character &character, dArr<Enemy>& enemies)
{
    bool playerTurn = false;
    int choice = 0;

    // Coin toss for turn
    int coinToss = rand() % 100 + 1;
    // Check who's turn is
    if (coinToss == 1)
        playerTurn = true;
    else
        playerTurn = false;

    // End Conditions
    bool escape = false;
    bool playerDefeated = false;
    bool enemieDefeated = false;

    // Enemies
    int nrOfEnemies = rand() % 5 + 1; // prevent 0 enemies

    for (size_t i = 0; i < nrOfEnemies; i++)
    {
        // Create enemies
        enemies.push( Enemy(character.getLevel()));
    }

    // Batte variables
    int attackRoll = 0;
    int defendRoll = 0;
    int damage = 0;
    int gainExp = 0;

    while (!escape & !playerDefeated && !enemieDefeated)
    {
        if (playerTurn && !playerDefeated)
        {
            // MENU
            // force to clear stream
            // std::cout << std::flush;
            std::cout << "* BATTLE MENU *" << std::endl << std::endl;

            std::cout << "0: Escape" << std::endl;
            std::cout << "1: Attack" << std::endl;
            std::cout << "2: Defend" << std::endl;
            std::cout << "3: Use Item" << std::endl << std::endl;

            std::cout << "Choice: " << std::endl;
            std::cin >> choice;

            while (std::cin.fail() || choice > 3 || choice < 0)
            {
                // force to clear stream
                std::cout << std::flush;

                std::cout << std::endl << "Faulty input!" << std::endl << std::endl;
                // clear the stream
                std::cin.clear();
                // ignore 100 chars
                std::cin.ignore(100, '\n');
                // enter choice again
                std::cout << "0: Escape" << std::endl;
                std::cout << "1: Attack" << std::endl;
                std::cout << "2: Defend" << std::endl;
                std::cout << "3: Use Item" << std::endl << std::endl;

                std::cout << "Choice: " << std::endl;
                std::cin >> choice;
            }

            std::cin.ignore(100, '\n');
            std::cout << std::endl;

            // Move
            switch (choice)
            {
                case 0: // ESCAPE
                    escape = true;
                    break;

                case 1: // ATTACK

                    // Select enemy MENU
                    // force to clear stream
                    // std::cout << std::flush;
                    std::cout << "* SELECT ENEMY: *" << std::endl << std::endl;

                    for (size_t i = 0; i < enemies.size(); i++)
                    {
                        std::cout << i << ": "
                            << "Level: " << enemies[i].getLevel() << std::endl
                            << "HP: " << enemies[i].getHp() << "/" << enemies[i].getHpMax() << std::endl;
                    }

                    std::cout << std::endl << "Choice: " << std::endl;
                    std::cin >> choice;

                    while (std::cin.fail() || choice >= enemies.size() || choice < 0)
                    {
                        std::cout << std::endl << "Faulty input!" << std::endl << std::endl;
                        // clear the stream
                        std::cin.clear();
                        // ignore 100 chars
                        std::cin.ignore(100, '\n');

                        // enter choice again
                        std::cout << "* SELECT ENEMY: *" << std::endl << std::endl;
                        std::cout << "Choice: " << std::endl;
                        std::cin >> choice;
                    }

                    std::cin.ignore(100, '\n');
                    std::cout << std::endl;

                    attackRoll = rand() % 100 + 1;

                    if (attackRoll > 50) // HIT
                    {
                        std::cout << "HIT! " << std::endl << std::endl;

                        damage = character.getDamage();
                        enemies[choice].takeDamage(character.getDamage());
                        if (!enemies[choice].isAlive())
                        {
                            std::cout << "ENEMY DEFEATED!" << std::endl << std::endl;
                            gainExp = enemies[choice].getExp();
                            character.gainExp(gainExp);
                            std::cout << "EXP GAINED: " << gainExp << std::endl << std::endl;
                            enemies.remove(choice);
                        }

                        std::cout << "Damage: " << damage << "!" << std::endl;
                    }
                    else // MISS
                    {
                        std::cout << "MISSED!" << std::endl << std::endl;
                    }

                    break;

                case 2: // DEFEND

                    break;

                case 3: //

                    break;

                default:

                    break;
            }

            // Leave turn
            playerTurn = false;
        }
        else if (!playerTurn && !escape && !enemieDefeated) // ENEMIES TURN
        {
            // Enemy attack
            for (size_t i = 0; i < enemies.size(); i++)
            {

            }

            // End turn
            playerTurn = true;
        }

        // Conditions

        if (!character.isAlive())
        {
            playerDefeated = true;
        }
        else if (enemies.size() <= 0)
        {
            enemieDefeated = true;
        }
    }
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
