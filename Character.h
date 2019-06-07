#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

class Character
{
    public:
        Character();
        virtual ~Character();

    // Functions
    void initialize(int level, std::string name);

    // Accessors
    inline const double& getxPos() const { return this->xPos; }
    inline const double& getyPos() const { return this->yPos; }
    inline const std::string& getName() const { return this->name; }
    inline const int getLevel() const { return this->level; }
    inline const int& getExp() const { return this->exp; }
    inline const int& getExpNext() const { return this->expNext; }
    inline const int& getHp() const { return this->hp; }
    inline const int& getHpMax() const { return this->hpMax; }
    inline const int& getStamin() const { return this->stamina; }
    inline const int& getDamageMin() const { return this->damageMin; }
    inline const int& getDamageMax() const { return this->damageMax; }
    inline const int& getDefence() const { return this->defence; }

    // Modifier


    protected:

    private:
        double xPos;
        double yPos;

        std::string name;
        int level;
        int exp;
        int expNext;
        int hp;
        int hpMax;
        int stamina;
        int damageMin;
        int damageMax;
        int defence;
};

#endif // CHARACTER_H
