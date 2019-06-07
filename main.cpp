#include <iostream>
#include <cstring>
#include <iomanip>
#include <ctime>
#include "functions.h"
#include "Game.h"

int main()
{
    srand(time(NULL));

    Game game;

    while(game.getPlaying())
    {
        game.mainMenu();
    }

    return 0;
}
