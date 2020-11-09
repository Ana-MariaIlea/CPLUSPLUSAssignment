#include <SFML/Graphics.hpp>

#include <fstream>
#include <iostream>

#include "scene.hpp"
#include "textObject.hpp"
#include "sprite.hpp"
#include "character.hpp"
#include "button.hpp"
#include <functional>

void characterAttackItself() {
    // GameObject& character = scene.getGameObjectByName("character");
    //Make the character attack it self
    printf("Hello world!\n");
}

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 600), "SFML with Scenes!");

    Scene characterScreen("characterScreen");
    Character character("Dude", "head.png", 10, 2, 2);

    sf::Font font;
    font.loadFromFile("Lato-Regular.ttf");
    sf::Color darkColor = sf::Color(71, 82, 94, 255);
    sf::Color darkGreyColor = sf::Color(132, 146, 166, 255);
    sf::Color lightGreyColor = sf::Color(129, 144, 165, 255);

    TextObject characterName("characterNameText", font, character.getName());
    characterName.setPosition(sf::Vector2f(109.0f, 34.0f));
    characterName.setCharacterSize(26);
    characterName.setFillColor(darkColor);

    SpriteObj characterAvatar("soldierSprite", character.getSpriteFile());
    characterAvatar.setPosition(sf::Vector2f(135.0f, 90.0f));
    characterAvatar.setScale(sf::Vector2f(2.5f, 2.5f));

    TextObject hpText("hpText", font, "HP: " + std::to_string(character.getHP()));
    hpText.setPosition(sf::Vector2f(161.0f, 238.0f));
    hpText.setCharacterSize(26);
    hpText.setFillColor(darkColor);

    TextObject attackText("attackText", font, "ATTACK: " + std::to_string(character.getAttack()));
    attackText.setPosition(sf::Vector2f(148.0f, 290.0f));
    attackText.setCharacterSize(26);
    attackText.setFillColor(darkColor);

    TextObject defenseText("defenseText", font, "DEFENSE: " + std::to_string(character.getDefense()));
    defenseText.setPosition(sf::Vector2f(140.0f, 345.0f));
    defenseText.setCharacterSize(26);
    defenseText.setFillColor(darkColor);

    Button attackItselfButton("attackItselfButton", font, "ATTACK ITSELF",
        sf::Vector2f(192.5f, 50.0f), darkColor);
    attackItselfButton.setPosition(sf::Vector2f(108.0f, 400.0f));

    attackItselfButton.setButtonAction([&character, &hpText]() {
        int damage = character.attackCharacter(character);
        character.takeDamage(damage);
        hpText.setText("HP: " + std::to_string(character.getHP()));
        });

    Button loadButton("loadButton", font, "LOAD", sf::Vector2f(96.25f, 50.0f), darkColor);
    loadButton.setPosition(sf::Vector2f(60.0f, 470.0f));
    loadButton.setButtonAction([&character, &characterName, &hpText, &attackText, &defenseText]() {
        std::ifstream myfileRead("character.txt");
        if (!myfileRead.fail()) {
            std::string line;

            std::getline(myfileRead, line);
            character.setName(line);
            characterName.setText(line);

            std::getline(myfileRead, line);
            character.setHP(std::stoi(line));
            hpText.setText("HP: " + std::to_string(character.getHP()));

            std::getline(myfileRead, line);
            character.setAttack(std::stoi(line));
            attackText.setText("ATTACK: " + std::to_string(character.getAttack()));

            std::getline(myfileRead, line);
            character.setDefense(std::stoi(line));
            defenseText.setText("DEFENSE: " + std::to_string(character.getDefense()));
            myfileRead.close();
        }
        });

    Button exportButton("exportButton", font, "EXPORT", sf::Vector2f(96.25f, 50.0f), darkColor);
    exportButton.setPosition(sf::Vector2f(216.25f, 470.0f));
    exportButton.setButtonAction([&character]() {
        std::ofstream myfileWrite("character.txt", std::ios::trunc);
        myfileWrite << character.getName() << std::endl;
        myfileWrite << character.getHP() << std::endl;
        myfileWrite << character.getAttack() << std::endl;
        myfileWrite << character.getDefense() << std::endl;

        myfileWrite.close();
        });

    Button quitButton("quitButton", font, "QUIT", sf::Vector2f(192.5f, 50.0f), darkColor);
    quitButton.setPosition(sf::Vector2f(108.0f, 540.0f));

    quitButton.setButtonAction([&window]() {
        window.close();
        });

    characterScreen.addGameObject(characterName);
    characterScreen.addGameObject(characterAvatar);
    characterScreen.addGameObject(hpText);
    characterScreen.addGameObject(attackText);
    characterScreen.addGameObject(defenseText);
    characterScreen.addGameObject(attackItselfButton);
    characterScreen.addGameObject(loadButton);
    characterScreen.addGameObject(exportButton);
    characterScreen.addGameObject(quitButton);

    Button pAttack("plusAttack", font, "+", sf::Vector2f(30.0f, 30.0f), darkColor);
    pAttack.setPosition(sf::Vector2f(40.0f, 290.0f));
    pAttack.setButtonAction([&character, &attackText]() {
        character.setAttack(character.getAttack() + 1);
        attackText.setText("ATTACK: " + std::to_string(character.getAttack()));
        });
    characterScreen.addGameObject(pAttack);

    Button rAttack("reduceAttack", font, "-", sf::Vector2f(30.0f, 30.0f), darkColor);
    rAttack.setPosition(sf::Vector2f(340.0f, 290.0f));
    rAttack.setButtonAction([&character, &attackText]() {
        character.setAttack(character.getAttack() - 1);
        attackText.setText("ATTACK: " + std::to_string(character.getAttack()));
        });
    characterScreen.addGameObject(rAttack);

    Button pDefense("plusDefense", font, "+", sf::Vector2f(30.0f, 30.0f), darkColor);
    pDefense.setPosition(sf::Vector2f(40.0f, 345.0f));
    pDefense.setButtonAction([&character, &defenseText]() {
        character.setDefense(character.getDefense() + 1);
        defenseText.setText("DEFENSE: " + std::to_string(character.getDefense()));
        });
    characterScreen.addGameObject(pDefense);

    Button rDefense("reduceDefense", font, "-", sf::Vector2f(30.0f, 30.0f), darkColor);
    rDefense.setPosition(sf::Vector2f(340.0f, 345.0f));
    rDefense.setButtonAction([&character, &defenseText]() {
        character.setDefense(character.getDefense() - 1);
        defenseText.setText("DEFENSE: " + std::to_string(character.getDefense()));
        });
    characterScreen.addGameObject(rDefense);

    Button pHp("plusHP", font, "+", sf::Vector2f(30.0f, 30.0f), darkColor);
    pHp.setPosition(sf::Vector2f(40.0f, 238.0f));
    pHp.setButtonAction([&character, &hpText]() {
        character.setHP(character.getHP() + 10);
        hpText.setText("HP: " + std::to_string(character.getHP()));
        });
    characterScreen.addGameObject(pHp);

    Button rHp("reduceHp", font, "-", sf::Vector2f(30.0f, 30.0f), darkColor);
    rHp.setPosition(sf::Vector2f(340.0f, 238.0f));
    rHp.setButtonAction([&character, &hpText]() {
        character.setHP(character.getHP() - 10);
        hpText.setText("HP: " + std::to_string(character.getHP()));
        });
    characterScreen.addGameObject(rHp);

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else {
                characterScreen.handleEvent(event, window);
            }
        }

        window.clear(sf::Color::White);
        characterScreen.update();
        characterScreen.render(window);
        window.display();
    }

    return 0;
}