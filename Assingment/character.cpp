#include "character.hpp"
#include <stdlib.h>  

#include <algorithm>

Character::Character(std::string name, std::string spriteFile, int hp, int attack, int defense) :
    name(name), spriteFile(spriteFile), maxhp(hp), attack(attack), defense(defense),activeAttack(attack), activeDefence(defense), activeHP(hp)
{ }
Character::Character(std::string name, std::string spriteFile) :
    name(name), spriteFile(spriteFile)
{
    //this->perks.push_back("GetHealthEveryFight");
    //this->perks.push_back("LowerEnemyHealthEveryFight");
    //this->perks.push_back("LoweEnemyAttackEveryFight");
    //this->perks.push_back("LowerEnemyDefenseEveryFight");
    //this->currentPerks.push_back("LowerEnemyHealthEveryFight");
    //printf("%s\n", this->currentPerks[0]);
    //printf("%s\n", this->perks[0]);
    //printf("%s\n", this->perks[1]);
    //printf("%s\n", this->perks[2]);
    //printf("%s\n", this->perks[3]);
}
Character::~Character() { }

void Character::attackCharacter(Character& character) const {

    int defensePower = character.getDefense();

    character.takeDamage(std::max(activeAttack - defensePower, 10));
}


void Character::takeDamage(int damage) {
    this->activeHP -= damage;
    if (this->activeHP <= 0) this->activeHP = 0;
}

void Character::heal() {
    this->activeHP += 10;
}

void Character::defend() {
    this->activeDefence *= 2;
}

int Character::getAttack() const {
    return this->activeAttack;
}

int Character::getMaxAttack() const {
    return this->attack;
}
void Character::setAttack(int attack) {
    this->attack = attack;
    this->activeAttack = this->attack;
}

int Character::getDefense() const {
    return this->activeDefence;
}

int Character::getMaxDefense() const {
    return this->defense;
}

int Character::getHP() const {
    return this->activeHP;
}
int Character::geMaxHP() const {
    return this->maxhp;
}
std::string Character::getName() const {
    return this->name;
}

std::string Character::getSpriteFile() const {
    return this->spriteFile;
}

void Character::setDefense(int defense) {
    this->defense = defense;
    this->activeDefence = this->defense;
}

void Character::setHP(int hp) {
    this->maxhp = (hp > 0) ? hp : 0;
    this->activeHP = this->maxhp;
}

void Character::setName(std::string name) {
    this->name = name;
}

void Character::randomizeStats() {
    this->attack = (rand() % 40)+10;
    this->defense = (rand() % 20)+5;
    this->maxhp = (rand() % 100)+20;
    this->activeAttack = this->attack;
    this->activeDefence = this->defense;
    this->activeHP= this->maxhp;
}

void Character::doAction(Character &character, TextObject& hptext, TextObject& attackText, TextObject& defenseText, TextObject &characterHpText) {
    int a = rand() % 100;
    if (a < chanceForHealing) {
        this->heal();
        hptext.setText("Hp: " + std::to_string(getHP()));
    }
    else if (a < chanceForDefence) {
        
        this->defend();
        defenseText.setText("Defense: " + std::to_string(getDefense()));
    }
    else if (a < chanceForAttack) {
       
        this->attackCharacter(character);
        characterHpText.setText("Hp: " + std::to_string(character.getHP()));
    }
}

void Character::resetDefense() {
    this->activeDefence = this->defense;
}

void Character::resetAttack() {
    this->activeAttack = this->attack;
}

void Character::setChance(int chanceForHealing, int chanceForDefence, int chanceForAttack) {
    this->chanceForHealing = chanceForHealing;
    this->chanceForDefence = chanceForDefence;
    this->chanceForAttack = chanceForAttack;
}

//void Character::getHealthPerk() {
//    this->heal();
//    this->heal();
//}
//void Character::lowerEnemyHealthPerk(Character character) {
//    attackCharacter(character);
//
//}
//void Character::lowerEnemyAttackPerk(Character character) {
//    character.setAttack(character.getMaxAttack() / 2);
//}
//void Character::lowerEnemyDefensePerk(Character character) {
//    character.setDefense(character.getMaxDefense() / 2);
//}
//void Character::getPerk() {
//    if (this->maxNumberOfPerks < 4) {
//        int chance = rand() % 100;
//        if (chance < 25) {
//            int randomPerk = rand() % perks.size();
//            if (!currentPerks.empty()) {
//                if (!(std::find(currentPerks.begin(), currentPerks.end(), perks[randomPerk]) != currentPerks.end())) {
//                    currentPerks.push_back(perks[randomPerk]);
//                    maxNumberOfPerks++;
//                }
//            }
//        }
//    }
//}
//
//void Character::usePerks(Character &character) {
//   // std::vector<std::string>::iterator perksIterator = currentPerks.begin();
//    //while (perksIterator!=currentPerks.end())
//    for (int i = 0; i < this->currentPerks.size(); i++)
//
//    {
//       //std::string p= *perksIterator;
//       // printf("%s\n", *perksIterator);
//        printf("%s\n", currentPerks[i]);
//        if (this->currentPerks[i] == "GetHealthEveryFight") {
//            this->getHealthPerk();
//        }
//        if (this->currentPerks[i] == "LowerEnemyHealthEveryFight") {
//            this->lowerEnemyHealthPerk(character);
//        }
//        if (this->currentPerks[i] == "LoweEnemyAttackEveryFight") {
//            this->lowerEnemyAttackPerk(character);
//        }
//        if (this->currentPerks[i] == "LowerEnemyDefenseEveryFight") {
//            this->lowerEnemyDefensePerk(character);
//        }
//
//       // perksIterator++;
//    }
//}

