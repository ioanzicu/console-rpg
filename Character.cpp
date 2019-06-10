#include "Character.h"

Character::Character()
{
    this->distanceTraveled = 0;

    this->gold = 0;

    this->name = "";
    this->level = 0;
    this->exp = 0;
    this->expNext = 0;

    this->strength = 0;
    this->vitality = 0;
    this->dexterity = 0;
    this->intelligence = 0;

    this->hp = 0;
    this->hpMax = 0;
    this->stamina = 0;
    this->staminaMax = 0;
    this->damageMin = 0;
    this->damageMax = 0;
    this->defence = 0;
    this->accuracy = 0;
    this->luck = 0;

    this->statPoints = 0;
}

Character::Character(std::string name, int distanceTraveled,
                     int gold, int level, int exp, int strength,int vitality, int dexterity,
                     int intelligence, int stamina, int hp,
                     int statPoints)
{
    this->name = name;
    this->distanceTraveled = distanceTraveled;
    this->gold = gold;
    this->level = level;
    this->exp = exp;
    this->expNext = 0;

    this->strength = strength;
    this->vitality = vitality;
    this->dexterity = dexterity;
    this->intelligence = intelligence;

    this->hp = hp;
    this->hpMax = 0;
    this->stamina = stamina;
    this->staminaMax = 0;
    this->damageMin = 0;
    this->damageMax = 0;
    this->defence = 0;
    this->accuracy = 0;
    this->luck = 0;

    this->statPoints = statPoints;

    this->updateStats();
}


Character::~Character()
{
    //dtor
}

// Functions
void Character::initialize(const std::string name)
{
    this->distanceTraveled = 0;

    this->gold = 100;

    this->name = name;
    this->level = 1;
    this->exp = 0;

    this->strength = 5;
    this->vitality = 5;
    this->dexterity = 5;
    this->intelligence = 5;

    this->statPoints = 0;

    this->updateStats();

    this->hp = this->hpMax;
}

void Character::displayCharacter() const
{
    std::cout << std::endl;
    std::cout << "-------------------------------" << std::endl;
    std::cout << "***     CHARACTER SHEET     ***" << std::endl;
    std::cout << "-------------------------------" << std::endl << std::endl;

    std::cout << "= Name: " << this->name << std::endl;
    std::cout << "= Level: " << this->level << std::endl;
    std::cout << "= Exp: " << this->exp << std::endl;
    std::cout << "= Exp to next level: " << this->expNext << std::endl;
    std::cout << "= Statpoints: " << this->expNext << std::endl;
    std::cout << std::endl;

    std::cout << "= Strenght: " << this->strength << std::endl;
    std::cout << "= Vitality: " << this->vitality << std::endl;
    std::cout << "= Dexterity: " << this->dexterity << std::endl;
    std::cout << "= Intelligence: " << this->intelligence << std::endl;
    std::cout << std::endl;

    std::cout << "= HP: " << this->hp << "/" << this->hpMax << std::endl;
    std::cout << "= Stamina: " << this->stamina << "/" << this->staminaMax << std::endl;
    std::cout << "= Damage: " << this->damageMin << " - " << this->damageMax << std::endl;
    std::cout << "= Defence: " << this->defence << std::endl;
    std::cout << "= Accuracy: " << this->accuracy << std::endl;
    std::cout << "= Luck: " << this->luck << std::endl;
    std::cout << "= Distance Travelled: " << this->distanceTraveled << std::endl;
    std::cout << "= Gold: " << this->gold << std::endl;
    std::cout << "= Luck: " << this->luck << std::endl << std::endl;

    std::cout << "----------------------------------" << std::endl;
    std::cout << "***     WEAPONS AND ARMORY     ***" << std::endl;
    std::cout << "----------------------------------" << std::endl << std::endl;

    std::cout << "= Weapon: " << this->weapon.getName()
              << " Level: " << this->weapon.getLevel()
              << " Damage: " << this->weapon.getDamageMin() << "/" << this->weapon.getDamageMax() << std::endl;
    std::cout << "= Armor Head: " << this->armor_head.getName()
              << " Level: " << this->armor_head.getLevel()
              << " Defence: " << this->armor_head.getDefence() << std::endl;
    std::cout << "= Armor Chest: " << this->armor_chest.getName()
              << " Level: " << this->armor_chest.getLevel()
              << " Defence: " << this->armor_chest.getDefence() << std::endl;
    std::cout << "=  Armor Arms: " << this->armor_arms.getName()
              << " Level: " << this->armor_arms.getLevel()
              << " Defence: " << this->armor_arms.getDefence() << std::endl;
    std::cout << "=  Armor Legs: " << this->armor_chest.getName()
              << " Level: " << this->armor_chest.getLevel()
              << " Defence: " << this->armor_chest.getDefence() << std::endl;

    std::cout << std::endl;
}

void Character::updateStats() // after save or loading
{
    // Level formula
    this->expNext = static_cast<int>((50 / 3)*(pow(level, 3) -
                        6 * pow(level, 2) +
                        (17 * level) - 12) + 100);

    this->hpMax = (this->vitality * 2) + (this->strength/2) + this->level * 5;
    this->hp = hpMax;
    this->staminaMax = this->vitality + (this->strength/2) + (this->dexterity/3);
    this->stamina = this->staminaMax;
    this->damageMin = this->strength;
    this->damageMax = this->strength + 2;
    this->defence = this->dexterity + (this->intelligence/2);
    this->accuracy = (this->dexterity / 2) + intelligence + 1;
    this->luck = this->intelligence;
}

void Character::addToStat(int stat, int value)
{
    // Check if there are statPoints
    if(this->statPoints < value)
        std::cout << "ERROR! NOT ENOUGH STATPOINTS!" << std::endl;
    else
    {
        std::cout << "#######################################" << std::endl;
        switch (stat)
        {
            case 0:
                std::cout << "Strnength was UPGRADED from: " << this->strength;
                this->strength += value;
                std:: cout << " to -> " << this->strength << std::endl;
                break;

            case 1:
                std::cout << "Vitality was UPGRADED from: " << this->vitality;
                this->vitality +=value;
                std:: cout << " to -> " << this->vitality << std::endl;
                break;

            case 2:
                std::cout << "Dexterity was UPGRADED from: " << this->dexterity;
                this->dexterity += value;
                std:: cout << " to -> " << this->dexterity << std::endl;
                break;

            case 3:
                std::cout << "Intelligence was UPGRADED from: " << this->intelligence;
                this->intelligence += value;
                std:: cout << " to -> " << this->intelligence << std::endl;
                break;

            default:
                std::cout << "UNDEFINED STAT" << std::endl;
                break;
        }
        std::cout << "#######################################" << std::endl << std::endl;

        // update stat points
        this->statPoints -= value;

        this->updateStats();
    }
}

void Character::levelUp()
{
    if (exp >= this->expNext)
    {
        this->exp -= this->expNext;
        this->level++;
        this->expNext = static_cast<int>((50 / 3)*(pow(level, 3) -
                        6 * pow(level, 2) +
                        (17 * level) - 12));

        this->statPoints++;

        this->updateStats();

        this->hp = this->hpMax;

        std::cout << "YOU ARE NOW LEVEL " << this->level << " !!!" << std::endl << std::endl;

    }
    else
    {
        std::cout << "NOT ENOUGH EXP!" << std::endl << std::endl;
    }
}

// For Saving in File
std::string Character::getAsString() const
{
         return name + " "
            + std::to_string(distanceTraveled) + " "
            + std::to_string(gold) + " "
            + std::to_string(level) + " "
            + std::to_string(exp) + " "
            + std::to_string(strength) + " "
            + std::to_string(vitality) + " "
            + std::to_string(dexterity) + " "
            + std::to_string(intelligence) + " "
            + std::to_string(hp) + " "
            + std::to_string(stamina) + " "
            + std::to_string(statPoints);
}

void Character::takeDamage(const int damage)
{
    this->hp -= damage;

    if (this->hp <= 0)
    {
        this->hp = 0;
    }
}
