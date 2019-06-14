#ifndef ENTITY_H
#define ENTITY_H

#include "STLINCLUDE.h"

class Entity
{
    public:
        Entity();
        Entity(int level);
        Entity(int hp, int level);
        virtual ~Entity();

        /* VIRTUAL */
        virtual void takeDamage(const int damage) = 0;
        virtual std::string getAsString() const = 0;

        // Accessors
        inline const int& getLevel() const { return this->level; }
        inline const int& getHp() const { return this->hp; }
        inline const int& getHpMax() const { return this->hpMax; }
        inline const int& getDamageMin() const { return this->damageMin; }
        inline const int& getDamageMax() const { return this->damageMax; }
        inline const int& getDefence() const { return this->defence; }
        inline const int& getAccuracy() const { return this->accuracy; }

        // Functions
        inline const bool isAlive() { return this->hp > 0; }

        // Modifier
        inline void setHp(const int hp) { this->hp = hp; }
        inline void setHpMax(const int hpMax) { this->hpMax = hpMax; }
        inline void setDamageMin(const int damageMin) { this->damageMin = damageMin; }
        inline void setDamageMax(const int damageMax) { this->damageMax = damageMax; }
        inline void setDefence(int defence) { this->defence = defence; }
        inline void setLevel(const int level) { this->level = level; }
        inline void setAccuracy(int accuracy) { this->accuracy = accuracy; }
/*
    protected:
        int hpMax;
        int hp;
        int damageMin;
        int damageMax;
        int defence;
        int accuracy;
        int level;
*/

    private:
        int hpMax;
        int hp;
        int level;
        int damageMin;
        int damageMax;
        int defence;
        int accuracy;
};

#endif // ENTITY_H
