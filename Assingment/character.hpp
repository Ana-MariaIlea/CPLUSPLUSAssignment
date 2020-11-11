#pragma once

#include <string>
#include "textObject.hpp"

class Character {
private:
    std::string name;
    std::string spriteFile;
    int hp;
    int attack;
    int defense;
    bool actItself;
    int activeAttack;
    int activeDefence;

public:
    Character(std::string name, std::string spriteFile,
        int hp, int attack, int defense, bool isAware);
    ~Character();

    void attackCharacter(Character& character) const;
   // bool takeDamage(int damage);
    void takeDamage(int damage);

    int getAttack() const;
    void setAttack(int attack);

    int getDefense() const;
    void setDefense(int defense);

    int getHP() const;
    void setHP(int hp);

    std::string getName() const;
    void setName(std::string name);

    void randomizeStats();

    void setActivity(bool IsActingByItself);

    void doAction(Character &character,TextObject &hptext, TextObject &attackText, TextObject &defenseText, TextObject& characterHpText);

    void heal();

    void resetStats();

    std::string getSpriteFile() const;
};
