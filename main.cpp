#include <iostream>

#include <cstring>
#include <iomanip>
#include <ctime>
#include "functions.h"
#include "Game.h"

int main()
{
    try
    {
        srand(time(NULL)); // Set The SEED

        Game game;
        game.initGame();

        while(game.getPlaying())
        {
            game.mainMenu();
        }
    }
    catch (std::exception const &exc)
    {
        std::cerr << "Exception caught " << exc.what() << std::endl;
    }
    catch(...)
    {
        std::cerr << "Unknown exception caught" << std::endl;
    }

    return 0;
}
