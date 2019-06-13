#include "GuiDisplay.h"

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

const std::string GuiDisplay::alert(const std::string text)
{
    std::stringstream ss;

    ss  << " - (!) " << text
        << std::endl;

    return ss.str();
}

const std::string GuiDisplay::error(const std::string text)
{
    std::stringstream ss;

    ss  << " - (ERR) " << text
        << std::endl;

    return ss.str();
}

