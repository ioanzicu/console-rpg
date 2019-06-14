#include "GuiDisplay.h"
#include <iostream>
GuiDisplay::GuiDisplay()
{
    //ctor
}

GuiDisplay::~GuiDisplay()
{
    //dtor
}

const std::string GuiDisplay::menuTitle(const std::string title)
{
    std::stringstream ss;
    ss  << std::endl
        << " ===  " << title << "  ===" << std::endl << std::endl;

    return ss.str();
}

const std::string GuiDisplay::menuTitle(const std::string title, const char symbol)
{
    /*
        Draw MENU EXAMPLE
    --------------------------
    ***   CHARACTER MENU   ***
    --------------------------
    */

    int lineSize = title.length() + 16; // nr of stars + empty spaces
    std::stringstream ss;
    // Repeat N times the given symbol
    ss  << " " << std::string(lineSize, symbol) << std::endl
        << " ***     " << title << "     ***" << std::endl
        << " " << std::string(lineSize, symbol) << std::endl <<std::endl;

    return ss.str();
}

const std::string GuiDisplay::divider(const unsigned amount, const char symbol)
{
    std::stringstream ss;
    ss  << " " << std::string(amount, symbol)
        << std::endl;

    return ss.str();
}


const std::string GuiDisplay::menuItem(const unsigned index, const std::string text)
{
    std::stringstream ss;
    // Repeat N times the given symbol
    ss  << " - (" << index << ") " << text
        << std::endl;

    return ss.str();
}

const std::string GuiDisplay::progresBar(const int valueMin, const int valueMax,const int maxLength,
                             const char symbolEmpty, const char symbolFull)
{
    std::stringstream ss;

    if (valueMin > valueMax) // prevent from crashing when exp is grather than next level exp limit
    {
        ss << " Level UP Available";
    }
    else
    {
        double percent = static_cast<double>(valueMin) / valueMax; // Calculate the porcentage - result in float
        int symbolsFull = maxLength * percent;      // Number of symbols in the bar
        int symbolsEmpty = maxLength - symbolsFull;  // Number of empty symbols in the bar

        //  DEBUG PRINT
        //ss << valueMin << " " << valueMax << " " << maxLength << " " << symbolEmpty << " " << symbolFull << std::endl;
        ss << " |" << std::string(symbolsFull, symbolFull) << std::string(symbolsEmpty, symbolEmpty) << "| ";
    }

    return ss.str();
}

const std::string GuiDisplay::alert(const std::string text)
{
    std::stringstream ss;

    ss  << std::endl
        << " - (!) " << text
        << std::endl << std::endl;

    return ss.str();
}

const std::string GuiDisplay::error(const std::string text)
{
    std::stringstream ss;

    ss  << std::endl
        << " - (ERR) " << text
        << std::endl << std::endl;

    return ss.str();
}

// Show Game Intro Story
const std::string GuiDisplay::gameIntro()
{
    std::stringstream ss;

    ss << "Thankfully Ilon's Musk experiment with car in the open space," << std::endl
        << "the humanity  realized that they can also go in the space: " << std::endl
        << " - Hey man, that car was so brave, why we humans are not, to do so??? " << std::endl
        << "And it started, the humans started their colonisation on the other planets." << std::endl
        << "The most popular colony with the original name is Marsian Colony, because of Mars." << std::endl
        << "So, the humans started great, but they are humans, and with peoples, comes " << std::endl
        << "their problems. For this reason the was founded the Marsian Police, a hardcore" << std::endl
        << "service for fighting with the danger entities." << std::endl << std::endl

        << "Here is starting your job, to fight, to improve yourself and to maintain " << std::endl
        << "order with the best armory in the galaxy. So, good luck in your advanture..." << std::endl;

    return ss.str();
}
