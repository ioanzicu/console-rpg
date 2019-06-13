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
        static const std::string menuTitle(const std::string title);
        static const std::string menuTitle(const std::string title, const char symbol);
        static const std::string divider(const unsigned amount = 40, const char symbol = '-');
        static const std::string menuItem(const unsigned index, const std::string text);
        static const std::string progresBar(const int valueMin, const int valueMax, const int maxLength,
                                            const char symbolEmpty, const char symbolFull);
        static const std::string alert(const std::string text);
        static const std::string error(const std::string text);


    protected:

    private:
};

#endif // GUIDISPLAY_H
