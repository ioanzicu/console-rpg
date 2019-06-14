#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "STLINCLUDE.h"

class Enemy : public Entity
{
    public:
        Enemy(int level = 0);
        virtual ~Enemy();

        /* VIRTUAL */
        virtual void takeDamage(int damage);
        virtual std::string getAsString() const;

        // Functions
        std::string getAsStringEvent() const;

        // Accessors
        /* Move to  Parent */

        inline int getDamage() const { return rand() % this->getDamageMax() + this->getDamageMin(); };
        inline int getExp() const { return this->getLevel() * 100; };

    private:
        float dropChance;
};

#endif // ENEMY_H
