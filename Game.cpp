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
    Inventory inv;

    inv.addItem(Weapon(0,0,"wep1"));
    inv.addItem(Weapon(0,0,"wep2"));
    inv.addItem(Weapon(0,0,"wep3"));
    inv.addItem(Armor(0,0,"arm1"));
    inv.addItem(Armor(0,0,"arm2"));
    inv.addItem(Armor(0,0,"arm3"));

    for (size_t i = 0; i < inv.size(); i++)
    {
        std::cout << inv[i].debugPrint() << std::endl;
    }

    createCharacter();
}

void Game::mainMenu()
{
    std::cout << "* MAIN MENU *" << std::endl << std::endl;

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
    std::cin >> choice;
    std::cout << std::endl;

    switch (choice)
    {
        case 0:
            playing = false;
            break;

        case 5:
            characters[activeCharacter].displayCharacter();
            break;

        case 6:
            std::cin.ignore();
            createCharacter();
            saveCharacters();
            break;

        case 7:
            saveCharacters();
            break;

        case 8:
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

void Game::loadCharacters()
{

}

void Game::saveCharacters()
{
    std::ofstream outFile(this->fileName);
    // if file doesn't exist, it will be created
    if (outFile.is_open())
    {
        // loop throught characet vector and append to file
       for (size_t i = 0; i < characters.size();
        i++)
       {
           outFile << characters[i].getAsString() << "\n"; // new line
       }
    }

    outFile.close();
}
