#include "character.hpp"
//#include <stdlib.h>  

#include <algorithm>

Character::Character(std::string name, std::string spriteFile, int hp, int attack, int defense, bool isAware) :
    name(name), spriteFile(spriteFile), hp(hp), attack(attack), defense(defense),actItself(isAware),activeAttack(attack), activeDefence(defense)
{ }

Character::~Character() { }

void Character::attackCharacter(Character& character) const {

    int defensePower = character.getDefense();

    character.takeDamage(std::max(activeAttack - defensePower, 10));
}

//bool Character::takeDamage(int damage) {
//    hp = std::max(hp - damage, 0);
//    return hp == 0;
//}
void Character::takeDamage(int damage) {
    this->hp -= damage;
}

void Character::heal() {
    this->hp += 10;
}

int Character::getAttack() const {
    return this->activeAttack;
}

void Character::setAttack(int attack) {
    this->activeAttack = attack;
}

int Character::getDefense() const {
    return this->activeDefence;
}

int Character::getHP() const {
    return this->hp;
}

std::string Character::getName() const {
    return this->name;
}

std::string Character::getSpriteFile() const {
    return this->spriteFile;
}

void Character::setDefense(int defense) {
    this->activeDefence = defense;
}

void Character::setHP(int hp) {
    this->hp = (hp > 0) ? hp : 0;
}

void Character::setName(std::string name) {
    this->name = name;
}

void Character::randomizeStats() {
    this->attack = rand() % 90;
    this->defense = rand() % 50;
    this->activeAttack = this->attack;
    this->activeDefence = this->defense;
}

void Character::doAction(Character &character, TextObject& hptext, TextObject& attackText, TextObject& defenseText, TextObject &characterHpText) {
    int a = rand() % 100;
    if (a < 50) {
        attackCharacter(character);
        characterHpText.setText("Hp: " + std::to_string(character.getHP()));

    }
    else if (a < 70) {
        heal();
        hptext.setText("Hp: " + std::to_string(getHP()));
    }
    else if (a < 80) {
        setDefense(this->defense * 2);
        defenseText.setText("Defense: " + std::to_string(getDefense()));
    }
}

void Character::resetStats() {
    this->activeAttack = this->attack;
    this->activeDefence = this->defense;
}
void Character::setActivity(bool IsActingByItself) {
    this->actItself = IsActingByItself;
}
