#include "Event.h"

// Total Events
int Event::nrOfEvents = 3;

Event::Event()
{

}

Event::~Event()
{
    //dtor
}

// Generate EVENTS
void Event::generateEvent(Character &character, dArr<Enemy> &enemies)
{
    int i = rand() % Event::nrOfEvents; // Generate an event from 0 to 2

    switch (i)
    {
        case 0: // ENEMY
            this->enemyEncounter(character, enemies);
            break;
        case 1: // PUZZLE
            this->puzzleEncounter(character);
            break;
        case 2: // SHOP
            this->shopEncounter(character);
            break;
        default:
            std::cout << "UNKNOWN ENCOUNTER EVENT" << std::endl;
            break;
    }
}

// EVENTS

// SHOP
void Event::shopEncounter(Character &character)
{
    system("clear");

    int choice = 0;
    bool shopping = true;
    Inventory merchantInv;
    std::string inv;

    // Init merchant inventory
    int nrOfItems = rand() % 20 + 10; // from 10 to 20
    bool coinToss = false;

    for (size_t i = 0; i < nrOfItems; i++)
    {
        coinToss = rand() % 2; // False (0) or True (1)

        // Add ITEMS TO INVENTORY
        if (coinToss > 0)
        { // WEAPON
            merchantInv.addItem(Weapon(character.getLevel() + rand() % 5, rand() % 5));
        }
        else
        { // ARMOR
            merchantInv.addItem(Armor(character.getLevel() + rand() % 5, rand() % 5));
        }
    }

    while (shopping)
    {
        std::stringstream menu_str;

        menu_str << GuiDisplay::menuTitle("SHOP MENU", '-');

        menu_str << GuiDisplay::menuItem(0, "Back");
        menu_str << GuiDisplay::menuItem(1, "Buy");
        menu_str << GuiDisplay::menuItem(2, "Sell") << std::endl;

        UserInput::getChoice(choice, menu_str.str(), 1); // Get Choice

        while (choice < 0 || choice > 3) // validate choice between 0 and 3
        {
            std::cout << GuiDisplay::error("UNKNOWN STAT");

            UserInput::getChoice(choice, " - Try again ... \n", 1);
        }

        menu_str.clear();

        // SHOP
        switch (choice)
        {
            case 0: // LEAVE
                shopping = false;
                break;

            case 1: // BUY
                {
                    std::cout << GuiDisplay::menuTitle("BUY MENU");
                    std::cout << " - You Have " << character.getGold() << " GOLD" << std::endl << std::endl;

                    inv.clear(); // Clear Inventory String

                    for (size_t i = 1; i < merchantInv.size(); i++)
                    {   // Add Items in inv string
                        inv += "  " + std::to_string(i) + ": " + merchantInv[i].toString() +
                               "\n   - PRICE: " + std::to_string(merchantInv[i].getBuyValue()) + "\n";
                    }

                    std::cout << inv << std::endl; // display inventory

                    std::cout << " - You Have " << character.getGold() << " GOLD" << std::endl << std::endl;
                    std::cout << GuiDisplay::menuItem(0, "Back to Main Menu");

                    UserInput::getChoice(choice, "", 1); // Get Choice

                    while (choice > merchantInv.size() || choice < 0) // validate choice
                    {
                        std::cout << GuiDisplay::error("UNKNOWN STAT");

                        UserInput::getChoice(choice, "", 1);
                    }

                    if (choice == 0) // Back To Main Menu
                    {
                        std::cout << " - Cancelled..." << std::endl << std::endl;
                    } // Buy ITEM
                    else if (character.getGold() >= merchantInv[choice].getBuyValue())
                    {
                        character.payGold(merchantInv[choice].getBuyValue()); // Gold -= Item Price
                        character.addItem(merchantInv[choice]);               // Add Item to Character Inventory

                        std::cout << " - Bought item: " << merchantInv[choice].getName() << " -"
                                  << merchantInv[choice].getBuyValue() << std::endl;

                        merchantInv.removeItem(choice); // Remove Bought Item from the Shop
                    }
                    else // NOT GOLD
                    {
                        std::cout << " - Not enough GOLD!!!" << std::endl;
                    }
                }

                break;

            case 2: // SELL

                menu_str << character.getInvAsString(true) << std::endl;  // (true) - Print Sell Value

                menu_str << GuiDisplay::menuTitle("SELL MENU", '-');

                menu_str << " - You Have " << character.getGold() << " GOLD" << std::endl << std::endl;
                menu_str << GuiDisplay::menuItem(0, "Back to Main Menu");

                if (character.getInventorySize() > 0) // Inventory is NOT Empty
                {
                    UserInput::getChoice(choice, menu_str.str(), 1); // Get Choice

                    while (choice > character.getInventorySize() || choice < 0) // validate choice
                    {
                        std::cout << GuiDisplay::error("UNKNOWN STAT");

                        UserInput::getChoice(choice, menu_str.str(), 1);
                    }

                    if (choice == 0) // Back to Main Menu
                    {
                        std::cout << " - Cancelled..." << std::endl << std::endl;
                    }
                    else
                    {
                        character.gainGold(character.getItem(choice).getSellValue());
                        std::cout << " - Item sold!" << std::endl;
                        std::cout << " - Gold earned: " << character.getItem(choice).getSellValue() << std::endl << std::endl;;
                        character.removeItem(choice); // Remove Sold Item form Character's Inventory
                    }
                }
                else
                {
                    std::cout << "The Inventory is EMPTY!" << std::endl << std::endl;
                }

                break;

            default:
                std::cout << GuiDisplay::error("UNKNOWN STAT");
                break;
        }
    }

    std::cout << " - You left the shop..." << std::endl << std::endl;
    std::cout << " ENTER to continue..." << "\n";
    // Wait for a character / keyboard enter
    std::cin.get();
}

// BATTLE
void Event::enemyEncounter(Character &character, dArr<Enemy> &enemies)
{
    bool playerTurn = false;
    int choice = 0;

    // Coin toss for turn
    int coinToss = rand() % 2 + 1; // From 1 to 2
    // Check who's turn is
    if (coinToss == 1)
        playerTurn = true;
    else
        playerTurn = false;

    // End Conditions
    bool escape = false;
    bool playerDefeated = false;
    bool enemiesDefeated = false;

    enemies.clear(); // Clear Old Enemies

    int nrOfEnemies = rand() % 3 + 1; // 1 - 3 enemies

    // CREATE ENEMIES with LEVEL (MAX) +2 Greather then Character's Level
    for (size_t i = 0; i < nrOfEnemies; i++)
    {
        enemies.push(Enemy(character.getLevel() + rand() % 3));
    }

    // Battle Variables
    int damage = 0;
    int gainExp = 0;
    int gainGold = 0;
    int playerTotal = 0;
    int enemyTotal = 0;
    int combatTotal = 0;
    int combatRollPlayer = 0;
    int combatRollEnemy = 0;

    while (!escape && !playerDefeated && !enemiesDefeated)
    {
        if (playerTurn && !playerDefeated) // Player Turn and Player is Alive
        {
            // MENU
            system("clear"); // Clear the Console

            std::stringstream menu_str;

            std::cout << GuiDisplay::menuTitle("BATTLE MENU", '*');
            std::cin.get();

            menu_str << " - Player Turn " << std::endl << std::endl;

            menu_str << character.getMenuBar() << std::endl;

            menu_str << GuiDisplay::menuItem(0, "Escape");
            menu_str << GuiDisplay::menuItem(1, "Attack");
            menu_str << GuiDisplay::menuItem(2, "Use Item") << std::endl;

            UserInput::getChoice(choice, menu_str.str(), 1); // Get Choice

            // Move
            switch (choice)
            {
                case 0: // ESCAPE
                    escape = true;
                    break;

                case 1: // ATTACK

                    system("clear");

                    // Select enemy MENU
                    menu_str.clear();

                    menu_str << std::endl << " * SELECT ENEMY: " << std::endl << std::endl;

                    for (size_t i = 0; i < enemies.size(); i++) // Display Enemies
                    {
                        menu_str << GuiDisplay::menuItem(i, enemies[i].getAsStringEvent());
                    }

                    UserInput::getChoice(choice, menu_str.str(), 1);

                    // Attack Roll Player Turn
                    combatTotal = enemies[choice].getDefence() + character.getAccuracy();
                    enemyTotal = enemies[choice].getAccuracy() / static_cast<double>(combatTotal) * 100; // calculate procentage
                    playerTotal = character.getAccuracy() / static_cast<double>(combatTotal) * 100;
                    combatRollPlayer = rand() % playerTotal + 1;
                    combatRollEnemy = rand() % enemyTotal + 1;

                    std::cout << std::string(30, '-') << std::endl;
                    std::cout << " | Combat total: " << combatTotal << std::endl;
                    std::cout << " | Enemy percent: " << enemyTotal << std::endl;
                    std::cout << " | Player percent: " << playerTotal << std::endl;
                    std::cout << " | Player roll: " << combatRollPlayer << std::endl;
                    std::cout << " | Enemy roll: " << combatRollEnemy << std::endl;
                    std::cout << std::string(30, '-') << std::endl << std::endl;

                    if (combatRollPlayer > combatRollEnemy) // HIT
                    {
                        damage = character.getDamage();
                        enemies[choice].takeDamage(damage);

                        std::cout << " - HIT! " << std::endl << std::endl;
                        std::cout << " - Enemy HP: " << enemies[choice].getHp() << "/" << enemies[choice].getHpMax()
                                  << std::endl << std::endl;

                        if (!enemies[choice].isAlive())
                        {
                            std::cout << " - [ ENEMY DEFEATED! ] "  << std::endl;
                            gainExp = enemies[choice].getExp();
                            character.gainExp(gainExp);
                            gainGold = rand() % enemies[choice].getLevel() * 10 + 1;
                            character.gainGold(gainGold);
                            std::cout << " - EXP GAINED: " << gainExp << std::endl;
                            std::cout << " - GOLD GAINED: " << gainGold << std::endl << std::endl;

                            // Item roll
                            int roll = rand() % 100 + 1; // 1 to 100
                            int rarity = -1;

                            if (roll > 20)
                            {
                                rarity = 0; // Common Item
                                roll = rand() % 100 + 1; // 1 to 100
                                if (roll > 30)
                                {
                                    rarity = 1; // Uncommon Item

                                    roll = rand() % 100 + 1;
                                    if (roll > 50)
                                    {
                                        rarity = 2; // Rare Item

                                        roll = rand() % 100 + 1;
                                        if (roll > 70)
                                        {
                                            rarity = 3; // Legendary Item

                                            roll = rand() % 100 + 1;
                                            if (roll > 90)
                                            {
                                                rarity = 4; // EPIC Item
                                            }
                                        }
                                    }
                                }
                            }

                            if (rarity >= 0)
                            {
                                // GET RANDOM ARMOR OR WEAPON
                                roll = rand() % 100 + 1;

                                if (roll > 50) // WEAPON
                                {
                                    Weapon tempW(character.getLevel(), rarity);
                                    character.addItem(tempW);
                                    std::cout << " - WEAPON DROP!" << std::endl;
                                }
                                else    // ARMOR
                                {
                                    Armor tempA(character.getLevel(), rarity);
                                    character.addItem(tempA);
                                    std::cout << " - ARMOR DROP!" << std::endl;
                                }
                            }
                            // REMOVE THE DEAD ENEMY
                            enemies.remove(choice);
                        }
                    }
                    else // MISS
                    {
                        std::cout << " - MISSED!" << std::endl << std::endl;
                    }

                    break;

                case 2: // USE ITEM
                    system("clear");

                    menu_str.clear();

                    menu_str << GuiDisplay::menuTitle("Use ITEM:");

                    menu_str << GuiDisplay::menuItem(0, "Back");
                    menu_str << GuiDisplay::menuItem(1, "Flask");

                    UserInput::getChoice(choice, menu_str.str(), 1);

                    switch (choice)
                    {
                        case 0:
                            GuiDisplay::alert("... Back to menu ...");
                            std::cin.get();
                            break;
                        case 1:
                            if (character.consumeFlask())
                            {
                                std::cout << " - Flask Used!" << std::endl;
                            }
                            else
                            {
                                std::cout << " - No Flask Available!" << std::endl;
                            }

                            break;

                        default:
                            std::cout << GuiDisplay::error("No Such Menu Option!");
                            break;
                    }

                    break;

                default:
                    std::cout << GuiDisplay::error("UNKNOWN STAT");
                    break;
            }

            // END TURN
            playerTurn = false;
            std::cout << std::endl;
            std::cin.get();
        }
        else if (!playerTurn && !playerDefeated && !escape && !enemiesDefeated) // ENEMIES TURN
        {
            system("clear");

            std::cout << GuiDisplay::menuTitle("BATTLE MENU", 'x');

            std::cout << " - Enemy Turn" << std::endl << std::endl;

            // Choose a Random Enemy to Attack
            int enemyIndex = rand() % enemies.size();
            Enemy* enemy = &enemies[enemyIndex];

            // Enemy attack
            std::cout << "Enemy: " << enemyIndex << std::endl << std::endl;

            // Attack Roll For Enemy Turn
            combatTotal = enemy->getAccuracy() + (character.getDefence() + character.getAddedDefence());
            enemyTotal = enemy->getDefence() / static_cast<double>(combatTotal) * 100; // calculate procentage
            playerTotal = enemy->getAccuracy() / static_cast<double>(combatTotal) * 100;
            combatRollPlayer = rand() % playerTotal + 1;
            combatRollEnemy = rand() % enemyTotal + 1;

            std::cout << std::string(30, '-') << std::endl;
            std::cout << " | Combat total: " << combatTotal << std::endl;
            std::cout << " | Enemy percent: " << enemyTotal << std::endl;
            std::cout << " | Player percent: " << playerTotal << std::endl;
            std::cout << " | Player roll: " << combatRollPlayer << std::endl;
            std::cout << " | Enemy roll: " << combatRollEnemy << std::endl;
            std::cout << std::string(30, '-') << std::endl << std::endl;

            if (combatRollPlayer < combatRollEnemy) // HIT
            {
                damage = enemy->getDamage();
                character.takeDamage(damage);

                std::cout << " - HIT: " << damage << "!" << std::endl << std::endl;
                std::cout << " - Player HP: " << character.getHp() << "/" << character.getHpMax()
                          << std::endl << std::endl;

                if (!character.isAlive())
                {
                    std::cout << " - [ You are DEFEATED! ] -" << std::endl;
                    playerDefeated = true;
                }
            }
            else // MISS
            {
                std::cout << " - MISSED!" << std::endl << std::endl;
            }

            // End turn
            playerTurn = true;
            std::cout << std::endl;
            std::cin.get(); // pause
        }

        // Conditions
        if (!character.isAlive()) // Check if Character is ALIVE
        {
            playerDefeated = true;
        }
        else if (enemies.size() <= 0) // Check if ALL enemies are DEFEATED
        {
            enemiesDefeated = true;
        }
    }
}

// PUZZLES
void Event::puzzleEncounter(Character &character)
{
    bool completed = false;
    int userAnswer = 0;
    int chances = 3;
    // EXP  = LEVEL * RANGE (1 and 10)
    int gainExp = (chances * character.getLevel() * (rand() % 10 + 1));
    // GOLD = LEVEL * RANGE (1 and 10)
    int gainGold = (chances * character.getLevel() * (rand() % 10 + 1));

    std::cout << "Travel " << std::endl;

    // Get a Random Puzzle
    int puzzleNumber = 3;
    int randomPuzzle = rand() % puzzleNumber + 1;
    std::string puzzleFile = "Puzzles/" + std::to_string(randomPuzzle) + ".txt";

    Puzzle puzzle(puzzleFile);

    while (!completed && chances > 0)
    {
        std::cout << " - Chances: " << chances << std::endl;
        // Decrement the chance
        chances--;

        // Display Question
        std::string puzzleQuestion = puzzle.getAsString() + "\n Your ANSWER:";

        UserInput::getChoice(userAnswer, puzzleQuestion, 1); // Get User Input

        // Get additional EXP and GOLD for Correct Answer
        if (puzzle.getCorrectAns() == userAnswer)
        {
            completed = true;
            character.gainExp(gainExp);
            character.gainGold(gainGold);
            std::cout << "YOU GAINED " << gainExp << " EXP!" << std::endl << std::endl;
            std::cout << "YOU GAINED " << gainGold << " GOLD!" << std::endl << std::endl;
        }
    }

    if (completed)
    {
        std::cout << "Congratulations, You are Right!!!" << std::endl << std::endl;
    }
    else
    {
        std::cout << "You LOST :(" << std::endl << std::endl;
    }
}

