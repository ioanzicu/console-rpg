#ifndef PUZZLE_H
#define PUZZLE_H

#include "STLINCLUDE.h"

class Puzzle
{
    public:
        Puzzle(std::string fileName);
        virtual ~Puzzle();
        std::string getAsString();

        inline const int& getCorrectAns() const { return this->correctAnswer; };

    protected:

    private:
        std::string question;
        std::vector<std::string> answers;
        int correctAnswer;
};

#endif // PUZZLE_H
