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

    // If File isn't Empty Load Characters
    if (in.peek() != std::ifstream::traits_type::eof())
    {
        std::cout << "Try to load character..." << std::endl;
        this->loadCharacters();
    }
    else
    {
        createCharacter();
        this->saveCharacters();
    }

    in.close();
}

void Game::mainMenu()
{
    std::cin.get();       // pause the system
    std::system("clear"); // clear the console

    std::cout << "ENTER to continue..." << "\n";
    std::cin.get();

    if (this->characters[activeCharacter].isAlive())
    {
        std::stringstream menu_str;

        menu_str << GuiDisplay::menuTitle("MAIN MENU", '-');

        if (this->characters[activeCharacter].getExp() >=
            this->characters[activeCharacter].getExpNext())
        {
            menu_str << GuiDisplay::alert("LEVEL UP AVAILABLE") << std::endl;
        }

        menu_str << this->characters[activeCharacter].getMenuBar() << std::endl;

        menu_str << GuiDisplay::menuItem(0, "Quit");
        menu_str << GuiDisplay::menuItem(1, "Travel");
        menu_str << GuiDisplay::menuItem(2, "Level Up");
        menu_str << GuiDisplay::menuItem(3, "Rest");
        menu_str << GuiDisplay::menuItem(4, "Character Sheet");
        menu_str << GuiDisplay::menuItem(5, "Create New Character");
        menu_str << GuiDisplay::menuItem(6, "Select Character");
        menu_str << GuiDisplay::menuItem(7, "Save Character");
        menu_str << GuiDisplay::menuItem(8, "Load Character") << std::endl;

        UserInput::getChoice(this->choice, menu_str.str(), 1);

        switch (this->choice)
        {
            case 0: // QUIT
                playing = false;
                this->saveCharacters();
                break;

            case 1: // TRAVEL
                travel();
                break;

            case 2: // LEVEL UP
                this->levelUpCharacter();
                break;

            case 3: // REST
                rest();
                break;

            case 4: // DISPLYA CHARACTER SHEET
                this->characterMenu();
                break;

            case 5: // CREATE NEW CHARACTER
                createCharacter();
                saveCharacters();
                break;

            case 6:
                selectCharacters();
                break;

            case 7: // SAVE
                saveCharacters();
                break;

            case 8: // LOAD
                loadCharacters();
                break;

            default:
                std::cout << "ERROR, NO SUCH OPTION." << std::endl << std::endl;
                break;
        }
    }
    else
    {
        std::stringstream menu_str;

        menu_str << GuiDisplay::menuTitle("You are DEAD... LOAD???", 'X');
        menu_str << GuiDisplay::menuItem(0, "YES");
        menu_str << GuiDisplay::menuItem(1, "NO");

        UserInput::getChoice(this->choice, menu_str.str(), 1);

        if (this->choice == 0)
            this->loadCharacters();
        else
            playing = false;
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
            std::cout << GuiDisplay::error("CHARACTER ALREADY EXISTS!");
            std::cin.get();

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
        std::stringstream menu_str;

        menu_str << GuiDisplay::menuTitle("You have statpoints to allocate!", '-');

        menu_str << GuiDisplay::menuTitle("Stat to upgrade: ");
        menu_str << GuiDisplay::menuItem(0, "Stength");
        menu_str << GuiDisplay::menuItem(1, "Vitality");
        menu_str << GuiDisplay::menuItem(2, "Dexterity");
        menu_str << GuiDisplay::menuItem(3, "Intelligence") << std::endl;

        UserInput::getChoice(this->choice, menu_str.str(), 1);

        while (this->choice < 0 || this->choice > 3) // validate choice between 0 and 3
        {
            std::cout << GuiDisplay::error("UNKNOWN STAT");

            UserInput::getChoice(this->choice, menu_str.str(), 1);
        }

        this->characters[activeCharacter].addToStat(this->choice, 1);
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

        std::cout << GuiDisplay::menuTitle("CHARACTER MENU", '+');

        std::cout << GuiDisplay::divider();
        characters[activeCharacter].displayCharacter();
        std::cout << GuiDisplay::divider();

        std::cout << "* MENU *" << std::endl << std::endl;;
        std::cout << GuiDisplay::menuItem(0, "Back to Main Menu");
        std::cout << GuiDisplay::menuItem(1, "Display Inventory");
        std::cout << GuiDisplay::menuItem(2, "Equip Item");

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
    int flasks = 0;
    int flasksMax = 0;
    int flaskShards = 0;
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
            str >> flasks;
            str >> flasksMax;
            str >> flaskShards;
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
                      level, exp, flasks, flasksMax, flaskShards, strength, vitality,
                      dexterity, intelligence, hp,
                      stamina, statPoints);

            // Create object, and set object
            // Weapon
            str >> itemType >> name >>
                   level >> rarity >> buyValue >>
                   sellValue >> damageMin >> damageMax;

            Weapon weapon(damageMin, damageMax, name, level, buyValue, sellValue, rarity);

            // Armors
            // Head
            str >> itemType >> name >>
                   level >> rarity >> buyValue >>
                   sellValue >> defence >> type;

            Armor armor_head(type, defence, name, level, buyValue, sellValue, rarity);

            // Chest
            str >> itemType >> name >>
                   level >> rarity >> buyValue >>
                   sellValue >> defence >> type;

            Armor armor_chest(type, defence, name, level, buyValue, sellValue, rarity);

            // Arms
            str >> itemType >> name >>
                   level >> rarity >> buyValue >>
                   sellValue >> defence >> type;

            Armor armor_arms(type, defence, name, level, buyValue, sellValue, rarity);

            // Legs
            str >> itemType >> name >>
                   level >> rarity >> buyValue >>
                   sellValue >> defence >> type;

            Armor armor_legs(type, defence, name, level, buyValue, sellValue, rarity);

            temp.setWeapon(weapon);
            temp.setArmorHead(armor_head);
            temp.setArmorChest(armor_chest);
            temp.setArmorArms(armor_arms);
            temp.setArmorLegs(armor_legs);

            // Add inventory Items
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

