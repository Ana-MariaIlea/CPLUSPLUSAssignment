#pragma once

#include <string>
#include "textObject.hpp"

class Character {
private:
    std::string name;
    std::string spriteFile;
    int maxhp=0;
    int attack=0;
    int defense=0;
    int activeAttack=0;
    int activeDefence=0;
    int activeHP=0;
    int chanceForAttack=0;
    int chanceForHealing=0;
    int chanceForDefence=0;

public:
    Character(std::string name, std::string spriteFile,
        int hp, int attack, int defense);
    Character(std::string name, std::string spriteFile);
    ~Character();

    void attackCharacter(Character& character) const;
   // bool takeDamage(int damage);
    void takeDamage(int damage);

    int getAttack() const;
    int getMaxAttack() const;
    void setAttack(int attack);

    int getDefense() const;
    int getMaxDefense() const;
    void setDefense(int defense);

    int getHP() const;
    int geMaxHP() const;
    void setHP(int hp);

    std::string getName() const;
    void setName(std::string name);

    void randomizeStats();


    void doAction(Character &character,TextObject &hptext, TextObject &attackText, TextObject &defenseText, TextObject& characterHpText);

    void heal();
    void defend();

    void resetDefense();
    void resetAttack();
    void setChance(int chanceForHealing, int chanceForDefence, int chanceForAttack);

    std::string getSpriteFile() const;
};
