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
    createCharacter();
}

void Game::mainMenu()
{
    std::cout << "ENTER to continue..." << "\n";
    // Wait for a character
    std::cin.get();
    // CLEAR THE SCREEN
    //system("CLS");
    // Force to clear the iostream before it will be filled
    std::cout << std::flush;


    if (this->characters[activeCharacter].getExp() >=
        this->characters[activeCharacter].getExpNext())
    {
        std::cout << std::endl << "+++++++++++++++++++++++++++" << std::endl;
        std::cout << "+++ LEVEL UP AVAILABLE! +++" << std::endl;
        std::cout << "+++++++++++++++++++++++++++" << std::endl << std::endl;
    }

    std::cout << "*** MAIN MENU ***" << std::endl << std::endl;

    std::cout << "0: Quit" << std::endl;
    std::cout << "1: Travel" << std::endl;
    std::cout << "2: Shop" << std::endl;
    std::cout << "3: Level Up" << std::endl;
    std::cout << "4: Rest" << std::endl;
    std::cout << "5: Character sheet" << std::endl;
    std::cout << "6: Create new character" << std::endl;
    std::cout << "7: Save Character" << std::endl;
    std::cout << "8: Load Character" << std::endl;
    std::cout << std::endl;

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
            break;

        case 1: // TRAVEL

            Travel();

            break;

        case 3: // LEVEL UP
            this->levelUpCharacter();
            break;

        case 5: // DISPLYA CHARACTER SHEET
            // std::cout << std::flush;
            characters[activeCharacter].displayCharacter();
            break;

        case 6: // CREATE CHARACTER
            // std::cout << std::flush;
            std::cin.ignore();
            createCharacter();
            saveCharacters();
            break;

        case 7: // SAVE
            saveCharacters();
            break;

        case 8: // LOAD
            loadCharacters();
            break;


        default:
            break;
    }
}

void Game::createCharacter()
{
    std::string name = "";
    std::cout << "Character name: ";
    // clear new line form the previous cin
    std::getline(std::cin, name);

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
            std::cout << "Faulty input!" << std::endl;
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
       for (size_t i = 0; i < characters.size(); i++)
       {
           outFile << characters[i].getAsString() << std::endl; // new line
       }
    }

    outFile.close();
}

void Game::loadCharacters()
{
    std::ifstream inFile(fileName);

    // clean/delete old character
    this->characters.clear();

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
                      stamina, statPoints, skillPoints);

            this->characters.push_back(Character(temp));

            std::cout << "Character " << name << " Loaded!" << std::endl;
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

void Game::Travel()
{
    this->characters[activeCharacter].travel();

    Event ev;

    ev.generateEvent(this->characters[activeCharacter]);
}
