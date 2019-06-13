#include "Event.h"


// Total Wvents
int Event::nrOfEvents = 3;

Event::Event()
{

}

Event::~Event()
{
    //dtor
}

void Event::generateEvent(Character &character, dArr<Enemy>& enemies)
{
    // Generate an event from 0 to 3
    int i = rand() % Event::nrOfEvents;

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
        case 3: // BOSS
            std::cout << "Boss encounter under construction..." << std::endl;
            break;
        default:
            std::cout << "UNKNOWN ENCOUNTER EVENT" << std::endl;
            break;
    }
}

// Different events

// SHOP
void Event::shopEncounter(Character &character)
{
    int choice = 0;
    bool shopping = true;
    Inventory merchantInv;
    std::string inv;

    // Init merchant inventory
    int nrOfItems = rand() % 20 + 10;
    bool coinToss = false;

    for (size_t i = 0; i < nrOfItems; i++)
    {
        coinToss = rand() % 2; // False or True

        // Add to inventory WEAPON or ARMOR
        if (coinToss > 0)
        {
            merchantInv.addItem(Weapon(character.getLevel() + rand() % 5, rand() % 5));
        }
        else
        {
            merchantInv.addItem(Armor(character.getLevel() + rand() % 5, rand() % 5));
        }
    }

    while (shopping)
    {
        //system("clear");
        std::cin.get();
        std::cout << "---------------------------" << std::endl;
        std::cout << "***      SHOP MENU      ***" << std::endl;
        std::cout << "---------------------------" << std::endl << std::endl;
        std::cout << "Continue..." << std::endl;
        std::cin.get();

        std::cout << "0: Leave" << std::endl;
        std::cout << "1: Buy" << std::endl;
        std::cout << "2: Sell" << std::endl;

        std::cout << "Choice: ";
        std::cin >> choice;

        while (std::cin.fail() || choice > 3 || choice < 0)
        {
            std::cout << std::endl << "Faulty input!" << std::endl << std::endl;
            // clear the stream
            std::cin.clear();
            // ignore 100 chars
            std::cin.ignore(100, '\n');
            // enter choice again

            std::cout << "* SHOP MENU *" << std::endl;

            std::cout << "0: Leave" << std::endl;
            std::cout << "1: Buy" << std::endl;
            std::cout << "2: Sell" << std::endl;

            std::cout << "Choice: ";
            std::cin >> choice;
        }

        std::cin.ignore(100, '\n');
        std::cout << std::endl;

        // SHOP
        switch (choice)
        {
            case 0: // LEAVE
                shopping = false;
                break;

            case 1: // BUY
                std::cout << "--------------------------" << std::endl;
                std::cout << "***      BUY MENU      ***" << std::endl;
                std::cout << "--------------------------" << std::endl << std::endl;

                std::cout << "You Have " << character.getGold() << " GOLD" << std::endl << std::endl;

                inv.clear();

                for (size_t i = 0; i < merchantInv.size(); i++)
                {
                    inv += std::to_string(i) + ": " + merchantInv[i].toString() + "\n - PRICE: " +
                           std::to_string(merchantInv[i].getBuyValue()) + "\n";
                }
                std::cout << inv << std::endl;

                std::cout << "You Have " << character.getGold() << " GOLD" << std::endl << std::endl;
                std::cout << "Choice of item (-1 to cancel): ";
                std::cin >> choice;

                while (std::cin.fail() || choice > merchantInv.size() || choice < -1)
                {
                    std::cout << std::endl << "Faulty input!" << std::endl << std::endl;
                    // clear the stream
                    std::cin.clear();
                    // ignore 100 chars
                    std::cin.ignore(100, '\n');
                    // enter choice again

                    std::cout << "You Have " << character.getGold() << " GOLD" << std::endl << std::endl;
                    std::cout << "Choice of item (-1 to cancel): ";
                    std::cin >> choice;
                }

                std::cin.ignore(100, '\n');
                std::cout << std::endl;

                if (choice == -1)
                {
                    std::cout << "Cancelled..." << std::endl << std::endl;
                }
                else if (character.getGold() >= merchantInv[choice].getBuyValue())
                {
                    character.payGold(merchantInv[choice].getBuyValue());
                    character.addItem(merchantInv[choice]);

                    std::cout << "Bought item: " << merchantInv[choice].getName() << " -" << merchantInv[choice].getBuyValue() << std::endl;

                    merchantInv.removeItem(choice);
                }
                else
                {
                    std::cout << "Not enough GOLD!!!" << std::endl;
                }

                break;

            case 2: // SELL
                // if it is in shop (true) -> print sell value
                std::cout << character.getInvAsString(true) << std::endl;

                std::cout << "--------------------------" << std::endl;
                std::cout << "***      SELL MENU     ***" << std::endl;
                std::cout << "--------------------------" << std::endl << std::endl;

                std::cout << "You Have " << character.getGold() << " GOLD" << std::endl << std::endl;
                std::cout << "Choice of item (-1 to cancel): ";

                if (character.getInventorySize() > 0) // inventory is not empty
                {
                    std::cin >> choice;

                    while (std::cin.fail() || choice > character.getInventorySize() || choice < -1)
                    {
                        std::cout << std::endl << "Faulty input!" << std::endl << std::endl;
                        // clear the stream
                        std::cin.clear();
                        // ignore 100 chars
                        std::cin.ignore(100, '\n');
                        // enter choice again

                        std::cout << "You Have " << character.getGold() << " GOLD" << std::endl << std::endl;
                        std::cout << "Choice of item (-1 to cancel): ";
                        std::cin >> choice;
                    }

                    std::cin.ignore(100, '\n');
                    std::cout << std::endl;

                    if (choice == -1)
                    {
                        std::cout << "Cancelled..." << std::endl << std::endl;
                    }
                    else
                    {
                        character.gainGold(character.getItem(choice).getSellValue());
                        std::cout << " - Item sold!" << std::endl;
                        std::cout << " - Gold earned: " << character.getItem(choice).getSellValue() << std::endl << std::endl;;
                        character.removeItem(choice);
                    }
                }
                else
                {
                    std::cout << "The Inventory is EMPTY!" << std::endl << std::endl;
                }

                break;

            default:
                break;
        }
    }

    std::cout << " - You left the shop..." << std::endl << std::endl;
    std::cout << " ENTER to continue..." << "\n";
    // Wait for a character
    std::cin.get();
}

// BATTLE
void Event::enemyEncounter(Character &character, dArr<Enemy>& enemies)
{
    bool playerTurn = false;
    int choice = 0;

    // Coin toss for turn
    int coinToss = rand() % 2 + 1; // from 1 to 2
    // Check who's turn is
    if (coinToss == 1)
        playerTurn = true;
    else
        playerTurn = false;

    // End Conditions
    bool escape = false;
    bool playerDefeated = false;
    bool enemiesDefeated = false;

    enemies.clear(); // Clear old enemies

    int nrOfEnemies = rand() % 3 + 1; // 1 - 3 enemies

    // CREATE ENEMIES
    for (size_t i = 0; i < nrOfEnemies; i++)
    {
        enemies.push(Enemy(character.getLevel() + rand() % 3));
    }

    // Batte variables
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
        if (playerTurn && !playerDefeated)
        {
            // MENU
            system("clear"); // clear the console

            std::stringstream menu_str;

            std::cout << GuiDisplay::menuTitle("BATTLE MENU", '*');
            std::cin.get();

            menu_str << " - Player Turn " << std::endl << std::endl;

            menu_str << character.getMenuBar() << std::endl;

            menu_str << GuiDisplay::menuItem(0, "Escape");
            menu_str << GuiDisplay::menuItem(1, "Attack");
            menu_str << GuiDisplay::menuItem(2, "Defend");
            menu_str << GuiDisplay::menuItem(3, "Use Item") << std::endl;

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

                    // Attack Roll
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
                                rarity = 0; // Common item
                                // roll again
                                roll = rand() % 100 + 1; // 1 to 100
                                if (roll > 30)
                                {
                                    rarity = 1; // Uncommon item

                                    roll = rand() % 100 + 1; // 1 to 100
                                    if (roll > 50)
                                    {
                                        rarity = 2; // Rare

                                        roll = rand() % 100 + 1; // 1 to 100
                                        if (roll > 70)
                                        {
                                            rarity = 3; // Legendary item

                                            roll = rand() % 100 + 1; // 1 to 100
                                            if (roll > 90)
                                            {
                                                rarity = 4; // EPIC item
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

                case 2: // DEFEND

                    break;

                case 3: // USE ITEM
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
            //std::cin.get();

            // Choose a random enemy to attack
            int enemyIndex = rand() % enemies.size();
            Enemy* enemy = &enemies[enemyIndex];

            // Enemy attack
            std::cout << "Enemy: " << enemyIndex << std::endl << std::endl;

            // Attack Roll
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
        if (!character.isAlive())
        {
            playerDefeated = true;
        }
        else if (enemies.size() <= 0)
        {
            enemiesDefeated = true;
        }
    }
}

// PUZZLES
void Event::puzzleEncounter(Character &character)
{
    bool completed = false;
    int userAns = 0;
    int chances = 3;
    // EXPE BETWEEN 1 and 10
    int gainExp = (chances * character.getLevel() * (rand() % 10 + 1));
    int gainGold = (chances * character.getLevel() * (rand() % 10 + 1));

    std::cout << "Travel " << std::endl;

    Puzzle puzzle("Puzzles/2.txt");

    while (!completed && chances > 0)
    {
        std::cout << " - Chances: " << chances << std::endl;
        // Decrement the chance
        chances--;

        // Display Question
        std::cout << puzzle.getAsString() << std::endl;

        std::cout << "\n - Your ANSWER: ";
        std::cin >> userAns;
        std::cout << std::endl;

        // Error checking for input
        // loop until the input is valid/correct
        // numerical value, NOT string or char
        while (std::cin.fail())
        {
            std::cout << " - Faulty input!" << "\n";
            // clear the stream
            std::cin.clear();
            // ignore 100 chars
            std::cin.ignore(100, '\n');
            // enter chice again
            std::cout << "\n - Your ANSWER: ";
            std::cin >> userAns;
        }

        std::cin.ignore(100, '\n');
        std::cout << "\n";

        if (puzzle.getCorrectAns() == userAns)
        {
            completed = true;
            // Get addiction la exp for correct answer
            character.gainExp(gainExp);
            character.gainGold(gainGold);
            std::cout << "YOU GAINED " << gainExp << " EXP!" << std::endl << std::endl;
            std::cout << "YOU GAINED " << gainGold << " GOLD!" << std::endl << std::endl;

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

/*
// BOSS
void Event::bossEncounter(Character &character, Boss &boss)
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

    // CREATE ENEMIES
    int nrOfEnemies = rand() % 3 + 1; // prevent 0 enemies

    for (size_t i = 0; i < nrOfEnemies; i++)
    {
        // Create enemies
        enemies.push(Enemy(character.getLevel() + rand() % 3));
    }

    // Batte variables
    int damage = 0;
    int gainExp = 0;
    int gainGold = 0;

    int playerTotal = 0;

    int enemyTotal = 0;
    int combatTotal = 0;
    int combatRollPlayer = 0;
    int combatRollEnemy = 0;

    while (!escape & !playerDefeated && !enemieDefeated)
    {
        if (playerTurn && !playerDefeated)
        {
            // MENU
            // force to clear stream
            std::cout << std::flush;

            std::cout << "-----------------------------" << std::endl;
            std::cout << "***      PLAYER TURN      ***" << std::endl;
            std::cout << "-----------------------------" << std::endl << std::endl;
            std::cout << "Continue..." << std::endl;
            std::cin.get();

            std::cout << "* BATTLE MENU *" << std::endl << std::endl;
            std::cout << "HP: " << character.getHp() << " / " << character.getHpMax() << std::endl;

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
                    std::cout << "* SELECT ENEMY: *" << std::endl << std::endl;

                    for (size_t i = 0; i < enemies.size(); i++)
                    {
                        std::cout << i << ": "
                            << "Level: " << enemies[i].getLevel() << " - "
                            << "HP: " << enemies[i].getHp() << "/" << enemies[i].getHpMax() << " - "
                            << "Defence: " << enemies[i].getDefence() << " - "
                            << "Accuracy: " << enemies[i].getAccuracy() << " - "
                            << "Damage: " << enemies[i].getDamageMin() << " - " << enemies[i].getDamageMax() << std::endl;
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

                    // Attack Roll
                    combatTotal = enemies[choice].getAccuracy() + (character.getDefence() + character.getAddedDefence());
                    // calculate procentage
                    enemyTotal = enemies[choice].getAccuracy() / static_cast<double>(combatTotal) * 100;
                    playerTotal = (character.getDefence() + character.getAddedDefence()) / static_cast<double>(combatTotal) * 100;
                    combatRollPlayer = rand() % playerTotal + 1;
                    combatRollEnemy = rand() % enemyTotal + 1;

                    std::cout << "Combat total: " << combatTotal << std::endl;
                    std::cout << "Enemy percent: " << enemyTotal << std::endl;
                    std::cout << "Player percent: " << playerTotal << std::endl << std::endl;

                    std::cout << "Player roll: " << combatRollPlayer << std::endl;
                    std::cout << "Enemy roll: " << combatRollEnemy << std::endl << std::endl;

                    std::cout << "-----------------------------" << std::endl;
                    std::cout << "***     PLAYER ATTACK     ***" << std::endl;
                    std::cout << "-----------------------------" << std::endl << std::endl;

                    if (combatRollPlayer > combatRollEnemy) // HIT
                    {
                        std::cout << "HIT! " << std::endl << std::endl;

                        damage = character.getDamage();
                        enemies[choice].takeDamage(damage);

                        std::cout << "Damage: " << damage << "!" << std::endl << std::endl;
                        std::cout << "HP: " << character.getHp() << " / " << character.getHpMax() << std::endl;

                        if (!enemies[choice].isAlive())
                        {
                            std::cout << "ENEMY DEFEATED!" << std::endl << std::endl;
                            gainExp = enemies[choice].getExp();
                            character.gainExp(gainExp);

                            gainGold = rand() % enemies[choice].getLevel() * 10 + 1;
                            character.gainGold(gainGold);

                            std::cout << "EXP GAINED: " << gainExp << std::endl << std::endl;
                            std::cout << "GOLD GAINED: " << gainGold << std::endl << std::endl;

                            // Item roll
                            int roll = rand() % 100 + 1; // 1 tp 100
                            int rarity = -1;

                            if (roll > 20)
                            {
                                rarity = 0; // Common item
                                // roll again
                                roll = rand() % 100 + 1; // 1 to 100
                                if (roll > 30)
                                {
                                    rarity = 1; // Uncommon item

                                    roll = rand() % 100 + 1; // 1 to 100
                                    if (roll > 50)
                                    {
                                        rarity = 2; // Rare

                                        roll = rand() % 100 + 1; // 1 to 100
                                        if (roll > 70)
                                        {
                                            rarity = 3; // Legendary item

                                            roll = rand() % 100 + 1; // 1 to 100
                                            if (roll > 80)
                                            {
                                                rarity = 4; // EPIC item
                                            }
                                        }
                                    }
                                }

                            }

                            if (rarity >= 0)
                            {
                                // GET RANDOM ARMOR OR WEAPON
                                roll = rand() % 100 + 1;
                                if (roll > 50)
                                {
                                    Weapon tempW(character.getLevel(), rarity);
                                    character.addItem(tempW);
                                    std::cout << "WEAPON DROP!" << std::endl;
                                }
                                else
                                {
                                    Armor tempA(character.getLevel(), rarity);
                                    character.addItem(tempA);
                                    std::cout << "ARMOR DROP!" << std::endl;
                                }
                            }
                            enemies.remove(choice);
                        }
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
        else if (!playerTurn && !playerDefeated && !escape && !enemieDefeated) // ENEMIES TURN
        {
            std::cout << "-----------XXXXX-------------" << std::endl;
            std::cout << "xxx     ENEMY TURN      xxx" << std::endl;
            std::cout << "-----------XXXXX-------------" << std::endl << std::endl;

            // Enemy attack
            for (size_t i = 0; i < enemies.size(); i++)
            {
                std::cout << "Continue..." << std::endl << std::endl;
                std::cin.get();

                std::cout << "Enemy: " << i << std::endl << std::endl;

                // Attack Roll
                combatTotal = enemies[i].getDefence() + character.getAccuracy();
                // calculate procentage
                enemyTotal = enemies[i].getDefence() / static_cast<double>(combatTotal) * 100;
                playerTotal = character.getAccuracy() / static_cast<double>(combatTotal) * 100;
                combatRollPlayer = rand() % playerTotal + 1;
                combatRollEnemy = rand() % enemyTotal + 1;

                std::cout << "Combat total: " << combatTotal << std::endl;
                std::cout << "Enemy percent: " << enemyTotal << std::endl;
                std::cout << "Player percent: " << playerTotal << std::endl << std::endl;

                std::cout << "Player roll: " << combatRollPlayer << std::endl;
                std::cout << "Enemy roll: " << combatRollEnemy << std::endl << std::endl;

                if (combatRollPlayer > combatRollEnemy) // HIT
                {
                    std::cout << "HIT! " << std::endl << std::endl;

                    damage = enemies[i].getDamage();
                    character.takeDamage(damage);

                    std::cout << "Damage: " << damage << "!" << std::endl << std::endl;

                    if (!character.isAlive())
                    {
                        std::cout << "You are DEFEATED!" << std::endl << std::endl;
                        playerDefeated = true;
                    }
                }
                else // MISS
                {
                    std::cout << "MISSED!" << std::endl << std::endl;
                }
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

*/
