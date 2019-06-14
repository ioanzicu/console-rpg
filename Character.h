#ifndef CHARACTER_H
#define CHARACTER_H

#include "STLINCLUDE.h"
#include "Entity.h"
#include "Inventory.h"


class Character : public Entity
{
    public:
        Character();
        Character(std::string name, int distanceTraveled, int gold,
                int level, int exp, int flasks, int flasksMax, int flaskShards,
                int strength, int vitality, int dexterity,
                int intelligence, int stamina, int hp, int statPoints);
        virtual ~Character();

        /* VIRTUAL */
        virtual void takeDamage(const int damage);
        virtual std::string getAsString() const;

        // Functions
        void initialize(const std::string name);
        void displayCharacter() const;

        std::string getInvAsString(bool shop = false);
        std::string getInvAsStringSaveWeapon();
        std::string getInvAsStringSave();
        void levelUp();
        void updateStats();
        void addToStat(int stat, int value);
        void equipItem(unsigned index);
        inline void resetHp() { this->setHp(this->getHpMax()); };
        void addItem(const Item &item) { this->inventory.addItem(item); }
        void removeItem(const int index);
        const Item& getItem(const int index);
        const std::string getMenuBar() const;
        const bool consumeFlask();
        const bool upgradeFlask();
        void resetFlasks();

        // Accessors
        inline const int& getDistanceTraveled() const { return this->distanceTraveled; }
        inline const std::string& getName() const { return this->name; }
        inline const int& getExp() const { return this->exp; }
        inline const int& getExpNext() const { return this->expNext; }
        inline const int& getStatPoints() const { return this->statPoints; };
        inline const int& getStamin() const { return this->stamina; }
        inline const int  getDamage() const { return rand() % (this->getDamageMax()
                                                        + this->weapon.getDamageMax())
                                                        + (this->getDamageMin() + this->weapon.getDamageMin()); }

        inline const int  getAddedDefence() const { return this->armor_arms.getDefence()
                                                         + this->armor_chest.getDefence()
                                                         + this->armor_head.getDefence()
                                                         + this->armor_legs.getDefence(); }

        inline const int& getGold() const { return this->gold; }
        inline const int  getInventorySize() const { return this->inventory.size(); }

        // Modifier
        inline void setDistanceTraveled(const int& distance) { this->distanceTraveled = distance; }
        inline void travel() { this->distanceTraveled++; }
        inline void gainExp(const int exp) { this->exp += exp; }
        inline void gainGold(const int gold) { this->gold += gold; }
        inline void payGold(const int gold) { this->gold -= gold; }
        inline void setWeapon(Weapon weapon) { this->weapon = weapon; }
        inline void setArmorHead(Armor armor_head) { this->armor_head = armor_head; }
        inline void setArmorChest(Armor armor_chest) { this->armor_chest = armor_chest; }
        inline void setArmorArms(Armor armor_arms) { this->armor_arms = armor_arms; }
        inline void setArmorLegs(Armor armor_legs) { this->armor_legs = armor_legs; }

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
        int exp;
        int expNext;

        int strength;
        int vitality;
        int dexterity;
        int intelligence;
        int stamina;
        int staminaMax;
        int luck;

        int statPoints;

        int flasks; // For Healing Bonuses when you have 10
        int flasksMax;
        int flaskShards;
        int flaskShardsMax;
};

#endif // CHARACTER_H
