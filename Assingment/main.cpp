#include <SFML/Graphics.hpp>

#include <fstream>
#include <iostream>

#include "scene.hpp"
#include "textObject.hpp"
#include "sprite.hpp"
#include "character.hpp"
#include "button.hpp"
#include "sceneHandler.hpp"

#include <functional>

int main() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "My assighnment");


	sf::Font font;
	font.loadFromFile("Lato-Regular.ttf");
	sf::Color darkColor = sf::Color(71, 82, 94, 255);
	sf::Color darkGreyColor = sf::Color(132, 146, 166, 255);
	sf::Color lightGreyColor = sf::Color(129, 144, 165, 255);

	SceneHandler handler;
	int actionOrder = 0;
	bool isFight = false;;


	Button backAScreen("backAScreen", font, "BACK", sf::Vector2f(192.5f, 50.0f), darkColor);
	backAScreen.setPosition(sf::Vector2f(108.0f, 540.0f));

	backAScreen.setButtonAction([&window]() {
		window.close();
		});
	//---------------------------------------
	Scene mainMenu("mainMenu");

	Button playButton("playButton", font, "PLAY", sf::Vector2f(192.5f, 50.0f), darkColor);
	playButton.setPosition(sf::Vector2f(508.0f, 540.0f));

	playButton.setButtonAction([&handler, &isFight]() {
		handler.stackScene("fightScreen");
		isFight = true;
		});

	Button scoreButton("scoreButton", font, "SCORE", sf::Vector2f(192.5f, 50.0f), darkColor);
	scoreButton.setPosition(sf::Vector2f(308.0f, 540.0f));

	scoreButton.setButtonAction([&handler]() {
		handler.stackScene("fightScreen");
		});

	Button quitButton("quitButton", font, "QUIT", sf::Vector2f(192.5f, 50.0f), darkColor);
	quitButton.setPosition(sf::Vector2f(108.0f, 540.0f));

	quitButton.setButtonAction([&window]() {
		std::cout << "quit";
		window.close();
		});

	mainMenu.addGameObject(playButton);
	mainMenu.addGameObject(scoreButton);
	mainMenu.addGameObject(quitButton);


	//------------------------------------------
	Scene scoreScreen("scoreScreen");



	std::vector<std::string> scores;
	std::string score;
	std::ifstream scoresFile("scores.txt");
	if (!scoresFile.fail()) {
		while (std::getline(scoresFile, score))
		{
			scores.push_back(score.c_str());
		}
	}
	score = "";
	for (int i = 0; i < scores.size(); i++)
	{
		score += scores[i] + '\n';
	}
	TextObject scoreText("scores", font, score);
	scoreText.setPosition(sf::Vector2f(109.0f, 34.0f));
	scoreText.setCharacterSize(26);
	scoreText.setFillColor(darkColor);

	Button eraseData("eraseData", font, "ERASE DATA", sf::Vector2f(192.5f, 50.0f), darkColor);
	eraseData.setPosition(sf::Vector2f(108.0f, 540.0f));

	eraseData.setButtonAction([&score]() {
		score = "";
		});
	scoreScreen.addGameObject(eraseData);
	scoreScreen.addGameObject(scoreText);
	//------------------------------------------
	/*Scene characterSelectionScreen("characterSelectionScreen");
	Button play("play", font, "PLAY", sf::Vector2f(192.5f, 50.0f), darkColor);
	play.setPosition(sf::Vector2f(108.0f, 540.0f));

	play.setButtonAction([&handler]() {
		handler.stackScene("fightScreen");
		});*/
		//-----------------------------------------------------------------------------
	Scene fightScreen("fightScreen");

	Character player("Player", "head.png", 10, 2, 2, false);
	SpriteObj playerAvatar("soldierSprite", player.getSpriteFile());
	playerAvatar.setPosition(sf::Vector2f(835.0f, 90.0f));
	playerAvatar.setScale(sf::Vector2f(2.5f, 2.5f));

	Character enemy("Enemy", "head.png", 10, 2, 2, true);
	SpriteObj enemyAvatar("soldierSprite", enemy.getSpriteFile());
	enemyAvatar.setPosition(sf::Vector2f(135.0f, 90.0f));
	enemyAvatar.setScale(sf::Vector2f(2.5f, 2.5f));



	TextObject playerName("characterNameText", font, player.getName());
	playerName.setPosition(sf::Vector2f(809.0f, 34.0f));
	playerName.setCharacterSize(26);
	playerName.setFillColor(darkColor);

	TextObject playerhpText("hpText", font, "HP: " + std::to_string(player.getHP()));
	playerhpText.setPosition(sf::Vector2f(861.0f, 238.0f));
	playerhpText.setCharacterSize(26);
	playerhpText.setFillColor(darkColor);

	TextObject playerattackText("attackText", font, "ATTACK: " + std::to_string(player.getAttack()));
	playerattackText.setPosition(sf::Vector2f(848.0f, 290.0f));
	playerattackText.setCharacterSize(26);
	playerattackText.setFillColor(darkColor);

	TextObject playerdefenseText("defenseText", font, "DEFENSE: " + std::to_string(player.getDefense()));
	playerdefenseText.setPosition(sf::Vector2f(840.0f, 345.0f));
	playerdefenseText.setCharacterSize(26);
	playerdefenseText.setFillColor(darkColor);



	TextObject enemyName("characterNameText", font, enemy.getName());
	enemyName.setPosition(sf::Vector2f(109.0f, 34.0f));
	enemyName.setCharacterSize(26);
	enemyName.setFillColor(darkColor);

	TextObject enemyhpText("hpText", font, "HP: " + std::to_string(enemy.getHP()));
	enemyhpText.setPosition(sf::Vector2f(161.0f, 238.0f));
	enemyhpText.setCharacterSize(26);
	enemyhpText.setFillColor(darkColor);

	TextObject enemyattackText("attackText", font, "ATTACK: " + std::to_string(enemy.getAttack()));
	enemyattackText.setPosition(sf::Vector2f(148.0f, 290.0f));
	enemyattackText.setCharacterSize(26);
	enemyattackText.setFillColor(darkColor);

	TextObject enemydefenseText("defenseText", font, "DEFENSE: " + std::to_string(enemy.getDefense()));
	enemydefenseText.setPosition(sf::Vector2f(140.0f, 345.0f));
	enemydefenseText.setCharacterSize(26);
	enemydefenseText.setFillColor(darkColor);

	Button attack("attack", font, "attack", sf::Vector2f(192.5f, 50.0f), darkColor);
	attack.setPosition(sf::Vector2f(808.0f, 400.0f));
	attack.setButtonAction([&player, &enemy,&enemyhpText, &actionOrder]() {
		player.attackCharacter(enemy);
		enemyhpText.setText("Hp: " + std::to_string(enemy.getHP()));
		actionOrder = 1;

		});


	Button heal("heal", font, "heal", sf::Vector2f(192.5f, 50.0f), darkColor);
	heal.setPosition(sf::Vector2f(808.0f, 450.0f));

	heal.setButtonAction([&player,&playerhpText, &actionOrder]() {
		player.heal();
		playerhpText.setText("Hp: " + std::to_string(player.getHP()));
		actionOrder = 1;

		});


	Button defend("defend", font, "defend", sf::Vector2f(192.5f, 50.0f), darkColor);
	defend.setPosition(sf::Vector2f(808.0f, 500.0f));

	defend.setButtonAction([&player,&playerdefenseText, &actionOrder]() {
		player.setDefense(player.getDefense() * 2);
		playerdefenseText.setText("DEFENSE: " + std::to_string(player.getDefense()));
		actionOrder = 1;

		});

	Button prepare("prepare", font, "prepare", sf::Vector2f(192.5f, 50.0f), darkColor);
	prepare.setPosition(sf::Vector2f(808.0f, 550.0f));

	prepare.setButtonAction([&player,&playerattackText, &actionOrder]() {
		player.setAttack(player.getAttack() * 3);
		playerattackText.setText("Attack: " + std::to_string(player.getAttack()));
		actionOrder = 1;
		});

	fightScreen.addGameObject(playerAvatar);
	fightScreen.addGameObject(enemyAvatar);

	fightScreen.addGameObject(attack);
	fightScreen.addGameObject(heal);
	fightScreen.addGameObject(defend);
	fightScreen.addGameObject(prepare);

	fightScreen.addGameObject(playerName);
	fightScreen.addGameObject(playerhpText);
	fightScreen.addGameObject(playerattackText);
	fightScreen.addGameObject(playerdefenseText);

	fightScreen.addGameObject(enemyName);
	fightScreen.addGameObject(enemyhpText);
	fightScreen.addGameObject(enemyattackText);
	fightScreen.addGameObject(enemydefenseText);
	//----------------------------------------------------------------------------
	//Scene characterScreen("characterScreen");
	//Character character("Dude", "head.png", 10, 2, 2,false);
	//std::vector<std::string> characterTextFilesNames;
	//std::string playableCharacters;
	//int counterForCharacters = 0;
	//std::ifstream characterNameFile("characters.txt");
	//if (!characterNameFile.fail()) {
	//	while (std::getline(characterNameFile, playableCharacters))
	//	{
	//		characterTextFilesNames.push_back(playableCharacters.c_str());
	//		counterForCharacters++;
	//	}
	//}

	//std::ifstream myfileRead(characterTextFilesNames[0]);

	//if (!myfileRead.fail()) {
	//	std::string line;

	//	std::getline(myfileRead, line);
	//	player.setName(line);
	//	// player.setText(line);

	//	std::getline(myfileRead, line);
	//	character.setHP(std::stoi(line));
	//	// hpText.setText("HP: " + std::to_string(character.getHP()));

	//	std::getline(myfileRead, line);
	//	player.setAttack(std::stoi(line));
	//	// attackText.setText("ATTACK: " + std::to_string(character.getAttack()));

	//	std::getline(myfileRead, line);
	//	player.setDefense(std::stoi(line));
	//	// defenseText.setText("DEFENSE: " + std::to_string(character.getDefense()));
	//	myfileRead.close();
	//}


	handler.addScene(mainMenu);
	handler.addScene(scoreScreen);
	handler.addScene(fightScreen);

	//TextObject characterName("characterNameText", font, character.getName());
	//characterName.setPosition(sf::Vector2f(109.0f, 34.0f));
	//characterName.setCharacterSize(26);
	//characterName.setFillColor(darkColor);

	//SpriteObj characterAvatar("soldierSprite", character.getSpriteFile());
	//characterAvatar.setPosition(sf::Vector2f(135.0f, 90.0f));
	//characterAvatar.setScale(sf::Vector2f(2.5f, 2.5f));

	//TextObject hpText("hpText", font, "HP: " + std::to_string(character.getHP()));
	//hpText.setPosition(sf::Vector2f(161.0f, 238.0f));
	//hpText.setCharacterSize(26);
	//hpText.setFillColor(darkColor);

	//TextObject attackText("attackText", font, "ATTACK: " + std::to_string(character.getAttack()));
	//attackText.setPosition(sf::Vector2f(148.0f, 290.0f));
	//attackText.setCharacterSize(26);
	//attackText.setFillColor(darkColor);

	//TextObject defenseText("defenseText", font, "DEFENSE: " + std::to_string(character.getDefense()));
	//defenseText.setPosition(sf::Vector2f(140.0f, 345.0f));
	//defenseText.setCharacterSize(26);
	//defenseText.setFillColor(darkColor);

	//Button attackItselfButton("attackItselfButton", font, "ATTACK ITSELF",
	//	sf::Vector2f(192.5f, 50.0f), darkColor);
	//attackItselfButton.setPosition(sf::Vector2f(108.0f, 400.0f));

	//attackItselfButton.setButtonAction([&character, &hpText]() {
	//	//int damage = character.attackCharacter(character);
	//	//character.takeDamage(character.attackCharacter(character));
	//	hpText.setText("HP: " + std::to_string(character.getHP()));
	//	});

	//Button loadButton("loadButton", font, "LOAD", sf::Vector2f(96.25f, 50.0f), darkColor);
	//loadButton.setPosition(sf::Vector2f(60.0f, 470.0f));
	//loadButton.setButtonAction([&character, &characterName, &hpText, &attackText, &defenseText]() {
	//	std::ifstream myfileRead("character.txt");
	//	if (!myfileRead.fail()) {
	//		std::string line;

	//		std::getline(myfileRead, line);
	//		character.setName(line);
	//		characterName.setText(line);

	//		std::getline(myfileRead, line);
	//		character.setHP(std::stoi(line));
	//		hpText.setText("HP: " + std::to_string(character.getHP()));

	//		std::getline(myfileRead, line);
	//		character.setAttack(std::stoi(line));
	//		attackText.setText("ATTACK: " + std::to_string(character.getAttack()));

	//		std::getline(myfileRead, line);
	//		character.setDefense(std::stoi(line));
	//		defenseText.setText("DEFENSE: " + std::to_string(character.getDefense()));
	//		myfileRead.close();
	//	}
	//	});

	//Button exportButton("exportButton", font, "EXPORT", sf::Vector2f(96.25f, 50.0f), darkColor);
	//exportButton.setPosition(sf::Vector2f(216.25f, 470.0f));
	//exportButton.setButtonAction([&character]() {
	//	std::ofstream myfileWrite("character.txt", std::ios::trunc);
	//	myfileWrite << character.getName() << std::endl;
	//	myfileWrite << character.getHP() << std::endl;
	//	myfileWrite << character.getAttack() << std::endl;
	//	myfileWrite << character.getDefense() << std::endl;

	//	myfileWrite.close();
	//	});



	//characterScreen.addGameObject(characterName);
	//characterScreen.addGameObject(characterAvatar);
	//characterScreen.addGameObject(hpText);
	//characterScreen.addGameObject(attackText);
	//characterScreen.addGameObject(defenseText);
	//characterScreen.addGameObject(attackItselfButton);
	//characterScreen.addGameObject(loadButton);
	//characterScreen.addGameObject(exportButton);
	//characterScreen.addGameObject(quitButton);

	//Button pAttack("plusAttack", font, "+", sf::Vector2f(30.0f, 30.0f), darkColor);
	//pAttack.setPosition(sf::Vector2f(40.0f, 290.0f));
	//pAttack.setButtonAction([&character, &attackText]() {
	//	character.setAttack(character.getAttack() + 1);
	//	attackText.setText("ATTACK: " + std::to_string(character.getAttack()));
	//	});
	//characterScreen.addGameObject(pAttack);

	//Button rAttack("reduceAttack", font, "-", sf::Vector2f(30.0f, 30.0f), darkColor);
	//rAttack.setPosition(sf::Vector2f(340.0f, 290.0f));
	//rAttack.setButtonAction([&character, &attackText]() {
	//	character.setAttack(character.getAttack() - 1);
	//	attackText.setText("ATTACK: " + std::to_string(character.getAttack()));
	//	});
	//characterScreen.addGameObject(rAttack);

	//Button pDefense("plusDefense", font, "+", sf::Vector2f(30.0f, 30.0f), darkColor);
	//pDefense.setPosition(sf::Vector2f(40.0f, 345.0f));
	//pDefense.setButtonAction([&character, &defenseText]() {
	//	character.setDefense(character.getDefense() + 1);
	//	defenseText.setText("DEFENSE: " + std::to_string(character.getDefense()));
	//	});
	//characterScreen.addGameObject(pDefense);

	//Button rDefense("reduceDefense", font, "-", sf::Vector2f(30.0f, 30.0f), darkColor);
	//rDefense.setPosition(sf::Vector2f(340.0f, 345.0f));
	//rDefense.setButtonAction([&character, &defenseText]() {
	//	character.setDefense(character.getDefense() - 1);
	//	defenseText.setText("DEFENSE: " + std::to_string(character.getDefense()));
	//	});
	//characterScreen.addGameObject(rDefense);

	//Button pHp("plusHP", font, "+", sf::Vector2f(30.0f, 30.0f), darkColor);
	//pHp.setPosition(sf::Vector2f(40.0f, 238.0f));
	//pHp.setButtonAction([&character, &hpText]() {
	//	character.setHP(character.getHP() + 10);
	//	hpText.setText("HP: " + std::to_string(character.getHP()));
	//	});
	//characterScreen.addGameObject(pHp);

	//Button rHp("reduceHp", font, "-", sf::Vector2f(30.0f, 30.0f), darkColor);
	//rHp.setPosition(sf::Vector2f(340.0f, 238.0f));
	//rHp.setButtonAction([&character, &hpText]() {
	//	character.setHP(character.getHP() - 10);
	//	hpText.setText("HP: " + std::to_string(character.getHP()));
	//	});
	//characterScreen.addGameObject(rHp);

	//while (window.isOpen()) {

	//	sf::Event event;
	//	while (window.pollEvent(event)) {
	//		if (event.type == sf::Event::Closed) {
	//			window.close();
	//		}
	//		else {
	//			characterScreen.handleEvent(event, window);
	//		}
	//	}

	//	window.clear(sf::Color::White);
	//	characterScreen.update();
	//	characterScreen.render(window);
	//	window.display();
	//}
	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else {
				if (isFight) {
					if (actionOrder == 0) {
						handler.lastSceneHandleEvent(event, window);
						//actionOrder = 1;
					}
					else {
						if (isFight) {
							enemy.doAction(player, enemyhpText,enemyattackText,enemydefenseText, playerhpText);
							actionOrder = 0;
						}

					}
				}
				else {
					handler.lastSceneHandleEvent(event, window);
				}
			}
		}

		window.clear(sf::Color::White);
		handler.update();
		handler.render(window);
		window.display();
	}

	return 0;
}