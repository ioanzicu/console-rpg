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
        inline void takeDamage(int damage) { this->hp -= damage; };
        inline int getDamage() const { return rand() % this->damageMax - this->damageMin; };
        inline int getExp() const { return this->level * 100; };

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
