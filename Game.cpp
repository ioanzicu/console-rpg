#include "Game.h"

Game::Game()
{
    choice = 0;
    playing = true;
    activeCharacter = 0;
    // .txt - ensure the file will be open by
    // default with text editor
    fileName = "characters.txt";
}

Game::~Game()
{
    //dtor
}

// Functions
void Game::initGame()
{
    std::ifstream in;
    in.open("characters.txt");

    Weapon::initNames();
    Armor::initNames();

    if (in.is_open())
        this->loadCharacters();
    else
    {
        createCharacter();
        this->saveCharacters();
    }

    in.close();
}

void Game::mainMenu()
{
    std::cout << "ENTER to continue..." << "\n";
    // Wait for a character
    std::cin.get();
    // Force to clear the iostream before it will be filled
    std::cout << std::flush;

    if (this->characters[activeCharacter].isAlive())
    {
        if (this->characters[activeCharacter].getExp() >=
            this->characters[activeCharacter].getExpNext())
        {
            std::cout << std::endl
                      << "+++++++++++++++++++++++++++" << std::endl;
            std::cout << "+++ LEVEL UP AVAILABLE! +++" << std::endl;
            std::cout << "+++++++++++++++++++++++++++" << std::endl << std::endl;
        }

        std::cout << "*** MAIN MENU ***" << std::endl << std::endl;

        std::cout << "* Active Character: " <<
            this->characters[activeCharacter].getName() << " Nr: " <<
            this->activeCharacter + 1 << " / " << this->characters.size() << " *" <<
            std::endl << std::endl;

        std::cout << "0: Quit" << std::endl;
        std::cout << "1: Travel" << std::endl;
        std::cout << "2: Shop" << std::endl;
        std::cout << "3: Level Up" << std::endl;
        std::cout << "4: Rest" << std::endl;
        std::cout << "5: Character sheet" << std::endl;
        std::cout << "6: Create new character" << std::endl;
        std::cout << "7: Select Characterw" << std::endl;
        std::cout << "8: Save Character" << std::endl;
        std::cout << "9: Load Character" << std::endl << std::endl;

        std::cout << std::endl << "Choice: ";
        std::cin >> this->choice;

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
            std::cout << std::endl << "Choice: ";
            std::cin >> this->choice;
        }

        std::cin.ignore(100, '\n');
        std::cout << std::endl;

        switch (this->choice)
        {
            case 0: // QUIT
                playing = false;
                this->saveCharacters();
                break;

            case 1: // TRAVEL
                travel();
                break;

            case 3: // LEVEL UP
                this->levelUpCharacter();
                break;

            case 4: // REST
                rest();
                break;

            case 5: // DISPLYA CHARACTER SHEET
                this->characterMenu();
                break;

            case 6: // CREATE NEW CHARACTER
                createCharacter();
                saveCharacters();
                break;

            case 7:
                selectCharacters();
                break;

            case 8: // SAVE
                saveCharacters();
                break;

            case 9: // LOAD
                loadCharacters();
                break;


            default:
                break;
        }
    }
    else
    {
        std::cout << "*** YOU ARE DEAD, LOAD? ***" << std::endl << std::endl;
        std::cout << "(0) YES, (1) NO" << std::endl << std::endl;
        std::cin >> this->choice;

        // Error checking for input
        while (std::cin.fail() || this->choice < 0 || this->choice > 1)
        {
            std::cout << "Faulty input!" << "\n";
            // clear the stream
            std::cin.clear();
            // ignore 100 chars
            std::cin.ignore(100, '\n');
            // enter chice again
            std::cout << "(0) YES, (1) NO" << std::endl << std::endl;
            std::cin >> this->choice;
        }

        std::cin.ignore(100, '\n');
        std::cout << std::endl;

        if (this->choice == 0)
            this->loadCharacters();
        else
            this->playing = false;
    }
}

void Game::createCharacter()
{
    std::string name = "";
    std::cout << "Character name: ";
    // clear new line form the previous cin
    std::getline(std::cin, name);

    for (size_t i = 0; i < this->characters.size(); i++)
    {
        while (name == this->characters[i].getName())
        {
            std::cout << "CANNOT CREATE CHARACTER!" <<
            std::endl << "The Name Already Exists!!!" << std::endl;

            std::cout << "Character name: ";
            std::getline(std::cin, name);
        }
    }

    // activeCharacter is the last element in the vector
    characters.push_back(Character());
    activeCharacter = characters.size() - 1;
    characters[activeCharacter].initialize(name);
}

void Game::levelUpCharacter()
{
    this->characters[activeCharacter].levelUp();

    if (this->characters[activeCharacter].getStatPoints() > 0)
    {
        std::cout << "You have statpoints to allocate!" << std::endl << std::endl;

        std::cout << "Stat to upgrade: " << std::endl;
        std::cout << "0: Stength " << std::endl;
        std::cout << "1: Vitality" << std::endl;
        std::cout << "2: Dexterity " << std::endl;
        std::cout << "3: Intelligence " << std::endl;

        std::cout << std::endl << "Stat to upgrade: ";
        std::cin >> this->choice;

        // Error checking for input
        // loop until the input is valid/correct
        // numerical value, NOT string or char
        while (std::cin.fail() || this->choice > 3)
        {
            std::cout << std::endl << "Faulty input!" << std::endl << std::endl;
            // clear the stream
            std::cin.clear();
            // ignore 100 chars
            std::cin.ignore(100, '\n');
            // enter chice again
            std::cout << "Stat to upgrade: " << std::endl;
            std::cin >> this->choice;
        }

        std::cin.ignore(100, '\n');
        std::cout << std::endl;

        switch (this->choice)
        {
            case 0: // STRENGTH
                this->characters[activeCharacter].addToStat(0, 1);
                break;

            case 1: // VITALITY
                this->characters[activeCharacter].addToStat(1, 1);
                break;

            case 2: // DEXTERITY
                this->characters[activeCharacter].addToStat(2, 1);
                break;

            case 3: // INTELLIGENCE
                this->characters[activeCharacter].addToStat(3, 1);
                break;

            default:
                std::cout << "UNDEFINED STAT" << std::endl;
                break;
        }
    }
}

void Game::saveCharacters()
{
    std::ofstream outFile(fileName);
    // if file doesn't exist, it will be created
    if (outFile.is_open())
    {
        // loop throught characet vector and append to file
       for (size_t i = 0; i < this->characters.size(); i++)
       {
            // save character
            outFile << this->characters[i].getAsString() << std::endl; // new line
            // save inventory
            outFile << this->characters[i].getInvAsStringSave() << std::endl;
       }
    }

    outFile.close();
}

void Game::characterMenu()
{
    do
    {
        // Force to clear the iostream before it will be filled
        std::cout << std::flush;

        std::cout << std::endl
                  << "+++++++++++++++++++++++++++" << std::endl;
        std::cout << "+++    CHARACTER MENU   +++" << std::endl;
        std::cout << "+++++++++++++++++++++++++++" << std::endl << std::endl;

        characters[activeCharacter].displayCharacter();

        std::cout << "* MENU *" << std::endl << std::endl;;
        std::cout << "0: Back to Main Menu" << std::endl;
        std::cout << "1: Display Inventory" << std::endl;
        std::cout << "2: Equip Item" << std::endl << std::endl;
        std::cout << "Choice: ";
        std::cin >> this->choice;

        while (std::cin.fail() || this->choice < 0 || this->choice > 2)
        {
            std::cout << "Faulty input!" << "\n";
            // clear the stream
            std::cin.clear();
            // ignore 100 chars
            std::cin.ignore(100, '\n');
            // enter chice again
            std::cout << "* MENU *" << std::endl << std::endl;;
            std::cout << "0: Back to Main Menu" << std::endl;
            std::cout << "1: Display Inventory" << std::endl;
            std::cout << "2: Equip Item" << std::endl << std::endl ;
            std::cout << "Choice: ";
            std::cin >> this->choice;
        }

        std::cin.ignore(100, '\n');
        std::cout << std::endl;

        switch (this->choice)
        {
            case 1:
                std::cout << this->characters[this->activeCharacter].getInvAsString();

                break;

            case 2:
                std::cout << this->characters[this->activeCharacter].getInvAsString();

                std::cout << "Item index: ";
                std::cin >> this->choice;

                while (std::cin.fail() || this->choice < 0 ||
                       this->choice >= this->characters[this->activeCharacter].getInventorySize())
                {
                    std::cout << "Faulty input!" << "\n";
                    // clear the stream
                    std::cin.clear();
                    // ignore 100 chars
                    std::cin.ignore(100, '\n');
                    // enter chice again
                    std::cout << "Item index: ";
                    std::cin >> this->choice;
                }

                std::cin.ignore(100, '\n');
                std::cout << std::endl;

                this->characters[activeCharacter].equipItem(this->choice);
                break;

            default:
                break;
        }

        if (this->choice > 0)
        {
            std::cout << "ENTER to continue..." << "\n";
            // Wait for a character
            std::cin.get();
        }
    } while (this->choice > 0);
}

void Game::loadCharacters()
{
    std::ifstream inFile(fileName);

    // clean/delete old character
    this->characters.clear();

    // CHARACTER DATA
    std::string name = "";
    int distanceTraveled = 0;
    int gold = 0;
    int level = 0;
    int exp = 0;
    int strength = 0;
    int vitality = 0;
    int dexterity = 0;
    int intelligence = 0;
    int hp = 0;
    int stamina = 0;
    int statPoints = 0;
    int skillPoints = 0;

    // ITEM DATA
    int itemType = 0;
    int defence = 0;
    int type = 0;
    int damageMin = 0;
    int damageMax = 0;
    // name
    // level
    int buyValue = 0;
    int sellValue = 0;
    int rarity = 0;

    Inventory tempItems;

    std::string line = "";
    std::stringstream str;

    // if file exist, open
    if (inFile.is_open())
    {
        while (getline(inFile, line))
        {
            str.str(line);

            str >> name;
            str >> distanceTraveled;
            str >> gold;
            str >> level;
            str >> exp;
            str >> strength;
            str >> vitality;
            str >> dexterity;
            str >> intelligence;
            str >> hp;
            str >> stamina;
            str >> statPoints;
            str >> skillPoints;

            // Create a character with data loaded from the file
            Character temp(name, distanceTraveled, gold,
                      level, exp, strength, vitality,
                      dexterity, intelligence, hp,
                      stamina, statPoints);
            str.clear();
            line.clear();
            getline(inFile, line);

            str.str(line);

            // READ WEAPONS
            while (str >> itemType >> name >>
                   level >> rarity >> buyValue >>
                   sellValue >> damageMin >> damageMax)
            {
                temp.addItem(
                    Weapon
                    (
                        damageMin,
                        damageMax,
                        name,
                        level,
                        buyValue,
                        sellValue,
                        rarity
                    )
                );
            }

            str.clear();
            line.clear();
            getline(inFile, line);

            str.str(line);

            // READ ARMORS
            while (str >> itemType >> name >>
                   level >> rarity >> buyValue >>
                   sellValue >> defence >> type)
            {
                temp.addItem(
                    Armor
                    (
                        type,
                        defence,
                        name,
                        level,
                        buyValue,
                        sellValue,
                        rarity
                    )
                );
            }

            this->characters.push_back(Character(temp));

            std::cout << "Character " << temp.getName() << " Loaded!" << std::endl;
            // Creal string input for the next stream
            str.clear();
        }
    }

    inFile.close();

    if (this->characters.size() <= 0)
    {
        throw "ERROR! NO CHARACTERS LOADED OR EMPTY FILE!";
    }
}

void Game::selectCharacters()
{
    std::cout << "Select character: " << std::endl << std::endl;

    for (size_t i = 0; i < this->characters.size(); i++)
    {
        std::cout << "Index: " << i << " = " << this->characters[i].getName() << " Level: " << this->characters[i].getLevel() << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Choice: " << std::endl;
    std::cin >> this->choice;

    while (std::cin.fail() || this->choice >= this->characters.size() || this->choice < 0)
    {
        std::cout << std::endl << "Faulty input!" << std::endl << std::endl;
        // clear the stream
        std::cin.clear();
        // ignore 100 chars
        std::cin.ignore(100, '\n');
        // enter chice again
        std::cout << "Select character " << std::endl;
        std::cin >> this->choice;
    }

    std::cin.ignore(100, '\n');
    std::cout << std::endl;

    this->activeCharacter = this->choice;

    std::cout << this->characters[this->activeCharacter] .getName() << " is SELECTED" << std::endl << std::endl;
}

void Game::travel()
{
    this->characters[activeCharacter].travel();

    Event ev;

    ev.generateEvent(this->characters[activeCharacter], this->enemies);
}

void Game::rest()
{
    int restCost = this->characters[this->activeCharacter].getHpMax() - this->characters[this->activeCharacter].getHp();
    std::cout << "-------------------------------" << std::endl;
    std::cout << "***   REST - FILL YOUR HP   ***" << std::endl;
    std::cout << "-------------------------------" << std::endl << std::endl;

    std::cout << "Resting costs you: " << restCost << std::endl << std::endl;
    std::cout << "Your gold: " << this->characters[this->activeCharacter].getGold() << std::endl << std::endl;
    std::cout << "HP: " << this->characters[this->activeCharacter].getHp() << " / " << this->characters[this->activeCharacter].getHpMax() << std::endl << std::endl;

    if (this->characters[this->activeCharacter].getGold() < restCost)
    {
        std::cout << "Not Enough Money, Sorry!!!..." << std::endl << std::endl;
    }
    else if(this->characters[this->activeCharacter].getHp() >= this->characters[this->activeCharacter].getHpMax())
    {
         std::cout << "Your HEALTH is already FULL!!!" << std::endl << std::endl;
    }
    else
    {
        std::cout << "Rest? (0) Yes, (1) No..." << std::endl << std::endl;

        std::cin >> this->choice;

        // Error checking for input
        while (std::cin.fail() || this->choice < 0 || this->choice > 1)
        {
            std::cout << "Faulty input!" << "\n";
            // clear the stream
            std::cin.clear();
            // ignore 100 chars
            std::cin.ignore(100, '\n');
            // enter chice again
            std::cout << "Rest? (1) Yes, (0) No..." << std::endl << std::endl;
            std::cin >> this->choice;
        }

        std::cin.ignore(100, '\n');
        std::cout << std::endl;

        if (this->choice == 0)
        {
            this->characters[this->activeCharacter].resetHp();
            this->characters[this->activeCharacter].payGold(restCost);
            std::cout << "RESTED!" << std::endl << std::endl;
        }
        else
        {
             std::cout << "MAYBE NEXT TIME..." << std::endl;
        }
    }
}
