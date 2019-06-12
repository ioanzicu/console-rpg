#ifndef GUIDISPLAY_H
#define GUIDISPLAY_H

#include <string>
#include <sstream>

class GuiDisplay
{
    public:
        GuiDisplay();
        virtual ~GuiDisplay();

        // static
        static const std::string menuTitle(const std::string title, const char symbol = '-');
        static const std::string divider(const unsigned amount = 30, const char symbol = '-');
        static const std::string menuItem(const unsigned index, const std::string text);

    protected:

    private:
};

#endif // GUIDISPLAY_H
