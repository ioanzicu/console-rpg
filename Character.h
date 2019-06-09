#ifndef CHARACTER_H
#define CHARACTER_H

#include "Inventory.h"
#include "Enemy.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>

class Character
{
    public:
        Character();
        Character(std::string name, int distanceTraveled,
                     int gold, int level, int exp, int strength, int vitality, int dexterity,
                     int intelligence, int stamina, int hp,
                     int statPoints, int skillPoints);
        virtual ~Character();

        // Functions
        void initialize(const std::string name);
        void displayCharacter() const;
        std::string getAsString() const;
        void levelUp();
        void updateStats();
        void addToStat(int stat, int value);

        // Accessors
        inline const int& getDistanceTraveled() const { return this->distanceTraveled; }
        inline const std::string& getName() const { return this->name; }
        inline const int getLevel() const { return this->level; }
        inline const int& getExp() const { return this->exp; }
        inline const int& getExpNext() const { return this->expNext; }
        inline const int& getStatPoints() const { return this->statPoints; };
        inline const int& getHp() const { return this->hp; }
        inline const int& getHpMax() const { return this->hpMax; }
        inline const bool isAlive() { return this->hp > 0; }
        inline const int& getStamin() const { return this->stamina; }
        inline const int& getDamageMin() const { return this->damageMin; }
        inline const int& getDamageMax() const { return this->damageMax; }
        inline const int getDamage() const { return rand() % this->damageMax + this->damageMin; }
        inline const int& getDefence() const { return this->defence; }
        inline const int& getAccuracy() const { return this->accuracy; }

        // Modifier
        inline void setDistanceTraveled(const int& distance) { this->distanceTraveled = distance; }
        inline void travel() { this->distanceTraveled++; }
        inline void gainExp(const int exp) { this->exp += exp; };
        void takeDamage(const int damage);

    protected:

    private:
        int distanceTraveled;

        Inventory inventory;
        Weapon weapon;

        Armor armor_head;
        Armor armor_chest;
        Armor armor_arms;
        Armor armor_legs;
        int gold;

        std::string name;
        int level;
        int exp;
        int expNext;

        int strength;
        int vitality;
        int dexterity;
        int intelligence;

        int hpMax;
        int hp;
        int stamina;
        int staminaMax;
        int damageMin;
        int damageMax;
        int defence;
        int accuracy;
        int luck;

        int statPoints;
        int skillPoints;
};

#endif // CHARACTER_H
