#ifndef CHARACTER_H
#define CHARACTER_H

#include "STLINCLUDE.h"
#include "Inventory.h"

class Character
{
    public:
        Character();
        Character(std::string name, int distanceTraveled, int gold,
            int level, int exp, int flasks, int flaskShards,
            int strength, int vitality, int dexterity,
            int intelligence, int stamina, int hp, int statPoints);
        virtual ~Character();

        // Functions
        void initialize(const std::string name);
        void displayCharacter() const;
        std::string getAsString() const;
        std::string getInvAsString(bool shop = false);
        std::string getInvAsStringSaveWeapon();
        std::string getInvAsStringSave();
        void levelUp();
        void updateStats();
        void addToStat(int stat, int value);
        void equipItem(unsigned index);
        inline void resetHp() { this->hp = this->hpMax; };
        void addItem(const Item &item) { this->inventory.addItem(item); }
        void removeItem(const int index);
        const Item& getItem(const int index);
        const std::string getMenuBar() const;

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
        inline const int  getDamage() const { return rand() % (this->damageMax
                                                        + this->weapon.getDamageMax())
                                                        + (this->damageMin
                                                        + this->weapon.getDamageMin()); }
        inline const int& getDefence() const { return this->defence; }
        inline const int  getAddedDefence() const { return this->armor_arms.getDefence()
                                                         + this->armor_chest.getDefence()
                                                         + this->armor_head.getDefence()
                                                         + this->armor_legs.getDefence(); }
        inline const int& getAccuracy() const { return this->accuracy; }
        inline const int& getGold() const { return this->gold; }
        inline const int  getInventorySize() const { return this->inventory.size(); }


        // Modifier
        inline void setDistanceTraveled(const int& distance) { this->distanceTraveled = distance; }
        inline void travel() { this->distanceTraveled++; }
        inline void gainExp(const int exp) { this->exp += exp; }
        inline void gainGold(const int gold) { this->gold += gold; }
        inline void payGold(const int gold) { this->gold -= gold; }
        void takeDamage(const int damage);
        inline void setWeapon(Weapon weapon) { this->weapon = weapon; }
        inline void setArmorHead(Armor armor_head) { this->armor_head = armor_head; }
        inline void setArmorChest(Armor armor_chest) { this->armor_chest = armor_chest; }
        inline void setArmorArms(Armor armor_arms) { this->armor_arms = armor_arms; }
        inline void setArmorLegs(Armor armor_legs) { this->armor_legs = armor_legs; }

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

        int flasks;
        int flaskShards;
        int flaskShardsMax;
};

#endif // CHARACTER_H
