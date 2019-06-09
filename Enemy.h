#ifndef ENEMY_H
#define ENEMY_H

#include <stdlib.h>
#include <string>

class Enemy
{
    public:
        Enemy(int level = 0);
        virtual ~Enemy();

        inline bool isAlive() { return this->hp > 0; }
        std::string getAsString() const;
        void takeDamage(int damage);

        inline int getLevel() const { return this->level; }
        inline int getDamage() const { return rand() % this->damageMax + this->damageMin; };
        inline int getExp() const { return this->level * 100; };
        inline int getHp() const { return this->hp; }
        inline int getHpMax() const { return this->hpMax; }
        inline int getDefence() const { return this->defence; }
        inline int getAccuracy() const { return this->accuracy; }

    protected:

    private:
        int hp;
        int hpMax;
        int level;
        int damageMin;
        int damageMax;
        float dropChance;
        int defence;
        int accuracy;
};

#endif // ENEMY_H
