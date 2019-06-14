#include "Character.h"

Character::Character() : Entity()
{
    this->distanceTraveled = 0;

    this->gold = 0;

    this->name = "";
    this->exp = 0;
    this->expNext = 0;

    this->strength = 0;
    this->vitality = 0;
    this->dexterity = 0;
    this->intelligence = 0;

    this->stamina = 0;
    this->staminaMax = 0;
    this->luck = 0;

    this->statPoints = 0;

    this->flasksMax = 1;
    this->flasks = this->flasksMax;
    this->flaskShards = 0;
    this->flaskShardsMax = 10;
}

Character::Character(std::string name, int distanceTraveled, int gold,
            int level, int exp, int flasks, int flasksMax, int flaskShards,
            int strength, int vitality, int dexterity, int intelligence,
            int stamina, int hp, int statPoints)
            : Entity(hp, level)
{
    this->name = name;
    this->distanceTraveled = distanceTraveled;
    this->gold = gold;
    this->exp = exp;
    this->expNext = 0;

    this->strength = strength;
    this->vitality = vitality;
    this->dexterity = dexterity;
    this->intelligence = intelligence;

    this->stamina = stamina;
    this->staminaMax = 0;
    this->luck = 0;

    this->statPoints = statPoints;

    this->flasksMax = flasksMax;
    this->flasks = flasks;
    this->flaskShards = flaskShards;
    this->flaskShardsMax = 10;

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

    this->gold = 30;

    this->name = name;
    this->setLevel(1);
    this->exp = 0;

    this->strength = 5;
    this->vitality = 5;
    this->dexterity = 5;
    this->intelligence = 5;

    this->statPoints = 0;

    // Add a weapon to inventory
    Inventory inv;
    inv.addItem(Weapon(1, 3));

    this->flasksMax = 1;
    this->flasks = this->flasksMax;
    this->flaskShards = 0;
    this->flaskShardsMax = 10;

    this->updateStats();
}

void Character::displayCharacter() const
{
    std::cout << std::endl;

    GuiDisplay::menuTitle("CHARACTER SHEET", '-');

    std::cout << "= Name: " << this->name << std::endl;
    std::cout << "= Level: " << this->getLevel() << std::endl;
    std::cout << "= Exp: " << this->exp << std::endl;
    std::cout << "= Exp to next level: " << this->expNext << std::endl;
    std::cout << "= Statpoints: " << this->expNext << std::endl;
    std::cout << "= Flasks: " << this->flasks << "/" << this->flasksMax << std::endl;
    std::cout << "= Flask Shards: " << this->flaskShards << " / " << this->flaskShardsMax << std::endl;
    std::cout << std::endl;

    GuiDisplay::menuTitle("PASSIVE SKILLS");
    std::cout << "------------------------------" << std::endl << std::endl;
    std::cout << "= Strenght: " << this->strength << std::endl;
    std::cout << "= Vitality: " << this->vitality << std::endl;
    std::cout << "= Dexterity: " << this->dexterity << std::endl;
    std::cout << "= Intelligence: " << this->intelligence << std::endl;
    std::cout << std::endl;

    std::cout << "= HP: " << this->getHp() << "/" << this->getHpMax() << std::endl;
    std::cout << "= Stamina: " << this->stamina << "/" << this->staminaMax << std::endl;
    std::cout << "= Damage: " << this->getDamageMin() << " - " << this->getDamageMax() << std::endl;
    std::cout << "= Defence: " << this->getDefence() << "  (+"
              << std::to_string(this->getAddedDefence()) << ")" << std::endl;
    std::cout << "= Accuracy: " << this->getAccuracy() << std::endl;
    std::cout << "= Luck: " << this->luck << std::endl;
    std::cout << "= Distance Travelled: " << this->distanceTraveled << std::endl;
    std::cout << "= Gold: " << this->gold << std::endl;
    std::cout << "= Luck: " << this->luck << std::endl << std::endl;

    GuiDisplay::menuTitle("WEAPONS AND ARMORY");

    std::cout << "= Weapon: " << this->weapon.getName()
              << " Level: " << this->weapon.getLevel()
              << " Damage: " << this->getDamageMin()
              << " (+" << this->weapon.getDamageMin() << ") "
              << "/ " << this->getDamageMax()
              << " (+" << this->weapon.getDamageMax() << ") "
              << std::endl;
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

// For Saving in File
std::string Character::getAsString() const
{
         return name + " "
            + std::to_string(distanceTraveled) + " "
            + std::to_string(gold) + " "
            + std::to_string(this->getLevel()) + " "
            + std::to_string(exp) + " "
            + std::to_string(flasks) + " "
            + std::to_string(flasksMax) + " "
            + std::to_string(flaskShards) + " "
            + std::to_string(strength) + " "
            + std::to_string(vitality) + " "
            + std::to_string(dexterity) + " "
            + std::to_string(intelligence) + " "
            + std::to_string(this->getHp()) + " "
            + std::to_string(stamina) + " "
            + std::to_string(statPoints) + " "
            + this->weapon.toStringSave()
            + this->armor_head.toStringSave()
            + this->armor_chest.toStringSave()
            + this->armor_arms.toStringSave()
            + this->armor_legs.toStringSave();
}

std::string Character::getInvAsString(bool shop)
{
    std::string inv;

    for (size_t i = 0; i < this->inventory.size(); i++)
    {
        if (shop)
        {   // SHOPE VERSION
            inv += std::to_string(i) + ": " + this->inventory[i].toString() + "\n" +
                + " | Sell Value: " + std::to_string(this->inventory[i].getSellValue()) + "\n";
        }
        else
        {
            inv += std::to_string(i) + ": " + this->inventory[i].toString() + "\n";
        }
    }

    return inv;
}

// For Saving Inventory in the File
std::string Character::getInvAsStringSave()
{
    std::string inv;

    // Save WEAPONS
    for (size_t i = 0; i < this->inventory.size(); i++)
    {
        if (this->inventory[i].getItemType() == itemType::WEAPON)
            inv += this->inventory[i].toStringSave();
    }

    inv += "\n";

    // Save ARMOR
    for (size_t i = 0; i < this->inventory.size(); i++)
    {
        if (this->inventory[i].getItemType() == itemType::ARMOR)
            inv += this->inventory[i].toStringSave();
    }

    return inv;
}

void Character::levelUp()
{
    system("clear");
    if (exp >= this->expNext)
    {
        this->exp -= this->expNext;
        this->setLevel(this->getLevel() + 1);
        this->expNext = static_cast<int>((50 / 3)*(pow(this->getLevel(), 3) -
                        6 * pow(this->getLevel(), 2) +
                        (17 * this->getLevel()) - 12));

        this->statPoints++;

        this->updateStats();

        std::cout << "YOU ARE NOW LEVEL " << this->getLevel() << " !!!" << std::endl << std::endl;

    }
    else
    {
        std::cout << "NOT ENOUGH EXP!" << std::endl << std::endl;
    }
}

void Character::updateStats() // after save or loading
{
    // Level formula
    this->expNext = static_cast<int>((50 / 3) * (pow(this->getLevel(), 3) -
                        6 * pow(this->getLevel(), 2) + (17 * this->getLevel()) - 12) + 100);

    this->setHpMax((this->vitality * 5) + (this->strength) + this->getLevel() * 5);
    this->setHp(this->getHpMax());
    this->staminaMax = this->vitality + (this->strength/2) + (this->dexterity/3);
    this->stamina = this->staminaMax;
    this->setDamageMin(this->strength);
    this->setDamageMax(this->strength + 2);
    this->setDefence(this->dexterity + (this->intelligence/2));
    this->setAccuracy((this->dexterity / 2) + intelligence + 1);
    this->luck = this->intelligence;

    this->setHp(this->getHpMax());
}

void Character::addToStat(int stat, int value)
{
    // Check if there are statPoints
    if(this->statPoints < value)
        std::cout << "ERROR! NOT ENOUGH STATPOINTS!" << std::endl;
    else
    {
        std::cout << " #######################################" << std::endl;
        switch (stat)
        {
            case 0:
                std::cout << " - Strength was UPGRADED from: " << this->strength;
                this->strength += value;
                std:: cout << " to -> " << this->strength << std::endl;
                break;

            case 1:
                std::cout << " - Vitality was UPGRADED from: " << this->vitality;
                this->vitality +=value;
                std:: cout << " to -> " << this->vitality << std::endl;
                break;

            case 2:
                std::cout << " - Dexterity was UPGRADED from: " << this->dexterity;
                this->dexterity += value;
                std:: cout << " to -> " << this->dexterity << std::endl;
                break;

            case 3:
                std::cout << " - Intelligence was UPGRADED from: " << this->intelligence;
                this->intelligence += value;
                std:: cout << " to -> " << this->intelligence << std::endl;
                break;

            default:
                std::cout << GuiDisplay::error("UNDEFINED STAT");
                break;
        }
        std::cout << " #######################################" << std::endl << std::endl;

        // Update Stat Points
        this->statPoints -= value;

        this->updateStats();
    }
}

void Character::equipItem(unsigned index)
{
    if (index < 0 || index >= this->inventory.size())
    {
        std::cout << "No Valid ITEM SELECTED!" << std::endl << std::endl;
    }
    else
    {
        Weapon *w = nullptr;
        w = dynamic_cast<Weapon*>(&this->inventory[index]);

        Armor *a = nullptr;
        a = dynamic_cast<Armor*>(&this->inventory[index]);

        // Is weapon
        if (w != nullptr)
        {
            if (this->weapon.getRarity() >= 0)
            {
                this->inventory.addItem(this->weapon);
            }
            this->weapon = *w;
            this->inventory.removeItem(index);
        }
        else if (a != nullptr)
        {
            switch (a->getType())
            {
                case armorType::HEAD:
                    if (this->armor_head.getRarity() >= 0)
                    {
                        this->inventory.addItem(this->armor_head);
                    }
                    this->armor_head = *a;
                    this->inventory.removeItem(index);
                    break;

                case armorType::CHEST:
                    if (this->armor_chest.getRarity() >= 0)
                    {
                        this->inventory.addItem(this->armor_chest);
                    }
                    this->armor_chest = *a;
                    this->inventory.removeItem(index);
                    break;

                case armorType::ARMS:
                    if (this->armor_arms.getRarity() >= 0)
                    {
                        this->inventory.addItem(this->armor_arms);
                    }
                    this->armor_arms = *a;
                    this->inventory.removeItem(index);
                    break;

                case armorType::LEGS:
                    if (this->armor_legs.getRarity() >= 0)
                    {
                        this->inventory.addItem(this->armor_legs);
                    }
                    this->armor_legs = *a;
                    this->inventory.removeItem(index);
                    break;

                default:
                    std::cout << "ERROR ARMOR TYPE INVALID!" << std::endl;
                    break;
            }
        }
        else
        {
            std::cout << "ERROR EQUIP ITEM IS NOT ARMOR OR WEAPON!" << std::endl;
        }
    }
}

void Character::removeItem(const int index)
{
    if (index < 0 || index >= this->inventory.size())
    {
        std::cout << "ERROR, NOT POSSIBLE TO REMOVE ITEM, removeItem Character" << std::endl << std::endl;
    }
    else
    {
        this->inventory.removeItem(index);
    }
}

const Item& Character::getItem(const int index)
{
    if (index < 0 || index >= this->inventory.size())
    {
        std::cout << GuiDisplay::error("ERROR, NOT POSSIBLE TO REMOVE ITEM, getItem Character") << std::endl;
        throw("ERROR, OUT OF BOUNDS, GET ITEM CHARACTERS");
    }

    return this->inventory[index];
}

const std::string Character::getMenuBar() const
{
    std::stringstream ss;

    ss << std::string(35, '-') << std::endl;

    ss << " | Name: " << this->name << std::endl;
    ss << " | Level: " << this->getLevel();

    ss << GuiDisplay::progresBar(this->exp, this->expNext, 15, '-', '=');
    ss << " [" << this->exp << "/" << this->expNext << "] " << std::endl;
    ss << " | Statpoints: " << this->expNext << std::endl;
    ss << " | HP: " << GuiDisplay::progresBar(this->getHp(), this->getHpMax(), 15, '-', '=') << this->getHp() << "/" << this->getHpMax() << std::endl;
    ss << " | Flasks: " << this->flasks << "/" << this->flasksMax << " (Shards: " << this->flaskShards << "/" << this->flaskShardsMax << ")" << std::endl;

    ss << std::string(35, '-') << std::endl;

    return ss.str();
}

// Use Flask for Fill HP
const bool Character::consumeFlask()
{
    bool consumed = false;

    if (this->flasks > 0)
    {
        this->setHp(this->getHpMax()); // Reset HP
        this->flasks--;         // Decrement flask
        consumed = true;
    }

    return consumed;
}

// Increase the Number of total Flasks and reset Flasks Shard
const bool Character::upgradeFlask()
{
    bool upgraded = false;
    if (this->flaskShards >= this->flaskShardsMax)
    {
        this->flaskShards -= this->flaskShardsMax; // Ex: 13 - 10 = 3
        this->flasksMax++;                         // FlaskMax +1
        this->flasks++;                            // Flasks   +1

        upgraded = true;
    }

    return upgraded;
}

// Reset Fasks
void Character::resetFlasks()
{
    this->flasks = this->flasksMax;
}

// Take Damage
void Character::takeDamage(const int damage)
{
    this->setHp(this->getHp() - damage);

    if (this->getHp() <= 0)
    {
        this->setHp(0);
    }
}
