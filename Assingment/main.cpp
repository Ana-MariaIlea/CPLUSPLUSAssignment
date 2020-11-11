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

int main(int argc, char* argv[]) {

	printf("%s\n", argv[0]);
	int width = argc > 1 ? std::stoi(argv[1]) : 1280;
	int height = argc > 2 ? std::stoi(argv[2]) : 720;
	printf("%d\n", width);
	printf("%d\n", height);
	sf::RenderWindow window(sf::VideoMode(width, height), "My assighnment");

	sf::Font font;
	font.loadFromFile("Lato-Regular.ttf");
	sf::Color darkColor = sf::Color(71, 82, 94, 255);
	sf::Color darkGreyColor = sf::Color(132, 146, 166, 255);
	sf::Color lightGreyColor = sf::Color(129, 144, 165, 255);

	SceneHandler handler;
	int actionOrder = 0;
	bool isFight = false;;
	int score = 0;
	int fightsWon = 0;

	Character player("Player", "head.png");
	SpriteObj playerAvatar("soldierSprite", player.getSpriteFile());
	playerAvatar.setPosition(sf::Vector2f(835.0f, 90.0f));
	playerAvatar.setScale(sf::Vector2f(2.5f, 2.5f));

	Character enemy("Enemy", "head.png");
	SpriteObj enemyAvatar("soldierSprite", enemy.getSpriteFile());
	enemyAvatar.setPosition(sf::Vector2f(135.0f, 90.0f));
	enemyAvatar.setScale(sf::Vector2f(2.5f, 2.5f));

	std::ifstream getDifficulty("NormalDifficulty.txt");
	if (!getDifficulty.fail()) {
		std::string line;

		std::getline(getDifficulty, line);
		int chanceForHealing = std::stoi(line);

		std::getline(getDifficulty, line);
		int chanceForDefense = std::stoi(line);

		std::getline(getDifficulty, line);
		int chanceForAttack = std::stoi(line);

		enemy.setChance(chanceForHealing, chanceForDefense, chanceForAttack);

		getDifficulty.close();
	}
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

	//---------------------------------------
	Scene mainMenu("mainMenu");

	Button playButton("playButton", font, "PLAY", sf::Vector2f(192.5f, 50.0f), darkColor);
	playButton.setPosition(sf::Vector2f(508.0f, 540.0f));

	playButton.setButtonAction([&handler, &isFight, &actionOrder, &player, &enemy,
		&playerhpText, &playerattackText, &playerdefenseText, &enemyhpText, &enemyattackText, &enemydefenseText, &score, &fightsWon]() {
			handler.stackScene("fightScreen");
			isFight = true;
			actionOrder = 0;
			player.randomizeStats();
			enemy.randomizeStats();
			playerhpText.setText("Hp: " + std::to_string(player.getHP()));
			playerattackText.setText("Attack: " + std::to_string(player.getAttack()));
			playerdefenseText.setText("Defence: " + std::to_string(player.getDefense()));
			enemyhpText.setText("Hp: " + std::to_string(enemy.getHP()));
			enemyattackText.setText("Attack: " + std::to_string(enemy.getAttack()));
			enemydefenseText.setText("Defense: " + std::to_string(enemy.getDefense()));
			score = 0;
			fightsWon = 0;
		});

	Button scoreButton("scoreButton", font, "SCORE", sf::Vector2f(192.5f, 50.0f), darkColor);
	scoreButton.setPosition(sf::Vector2f(308.0f, 540.0f));

	scoreButton.setButtonAction([&handler]() {
		handler.stackScene("scoreScreen");
		});

	Button setDifficultyEasy("setDifficultyEasy", font, "EASY", sf::Vector2f(192.5f, 50.0f), darkColor);
	setDifficultyEasy.setPosition(sf::Vector2f(700.0f, 200.0f));

	setDifficultyEasy.setButtonAction([&enemy]() {
		std::ifstream getDifficulty("EasyDifficulty.txt");
		if (!getDifficulty.fail()) {
			std::string line;

			std::getline(getDifficulty, line);
			int chanceForHealing = std::stoi(line);

			std::getline(getDifficulty, line);
			int chanceForDefense = std::stoi(line);

			std::getline(getDifficulty, line);
			int chanceForAttack = std::stoi(line);

			enemy.setChance(chanceForHealing, chanceForDefense, chanceForAttack);

			getDifficulty.close();
		}
		});
	Button setDifficultyNormal("setDifficultyNormal", font, "NORMAL", sf::Vector2f(192.5f, 50.0f), darkColor);
	setDifficultyNormal.setPosition(sf::Vector2f(700.0f, 300.0f));

	setDifficultyNormal.setButtonAction([&enemy]() {
		std::ifstream getDifficulty("NormalDifficulty.txt");
		if (!getDifficulty.fail()) {
			std::string line;

			std::getline(getDifficulty, line);
			int chanceForHealing = std::stoi(line);

			std::getline(getDifficulty, line);
			int chanceForDefense = std::stoi(line);

			std::getline(getDifficulty, line);
			int chanceForAttack = std::stoi(line);

			enemy.setChance(chanceForHealing, chanceForDefense, chanceForAttack);

			getDifficulty.close();
		}
		});
	Button setDifficultyHard("setDifficultyHard", font, "HARD", sf::Vector2f(192.5f, 50.0f), darkColor);
	setDifficultyHard.setPosition(sf::Vector2f(700.0f, 400.0f));

	setDifficultyHard.setButtonAction([&enemy]() {
		std::ifstream getDifficulty("HardDifficulty.txt");
		if (!getDifficulty.fail()) {
			std::string line;

			std::getline(getDifficulty, line);
			int chanceForHealing = std::stoi(line);

			std::getline(getDifficulty, line);
			int chanceForDefense = std::stoi(line);

			std::getline(getDifficulty, line);
			int chanceForAttack = std::stoi(line);

			enemy.setChance(chanceForHealing, chanceForDefense, chanceForAttack);

			getDifficulty.close();
		}
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
	mainMenu.addGameObject(setDifficultyEasy);
	mainMenu.addGameObject(setDifficultyNormal);
	mainMenu.addGameObject(setDifficultyHard);

	int scoresInInt[5];
	TextObject scoreText1("score1", font, "");
	scoreText1.setPosition(sf::Vector2f(109.0f, 50.0f));
	scoreText1.setCharacterSize(26);
	scoreText1.setFillColor(darkColor);

	TextObject scoreText2("score2", font, "");
	scoreText2.setPosition(sf::Vector2f(109.0f, 100.0f));
	scoreText2.setCharacterSize(26);
	scoreText2.setFillColor(darkColor);

	TextObject scoreText3("score3", font, "");
	scoreText3.setPosition(sf::Vector2f(109.0f, 150.0f));
	scoreText3.setCharacterSize(26);
	scoreText3.setFillColor(darkColor);

	TextObject scoreText4("score4", font, "");
	scoreText4.setPosition(sf::Vector2f(109.0f, 200.0f));
	scoreText4.setCharacterSize(26);
	scoreText4.setFillColor(darkColor);

	TextObject scoreText5("score5", font, "");
	scoreText5.setPosition(sf::Vector2f(109.0f, 250.0f));
	scoreText5.setCharacterSize(26);
	scoreText5.setFillColor(darkColor);

	//------------------------------------------

	Button backAScreen("backAScreen", font, "Main Menu", sf::Vector2f(192.5f, 50.0f), darkColor);
	backAScreen.setPosition(sf::Vector2f(1000.0f, 600.0f));

	backAScreen.setButtonAction([&handler, &isFight,&score,&scoresInInt,&scoreText1, &scoreText2, &scoreText3, &scoreText4, &scoreText5]() {
		handler.popAllScenes();
		handler.stackScene("mainMenu");
		isFight = false;
		if (score != 0) {
			for (int i = 5; i >= 0; i--)
			{
				if (scoresInInt[i] < score) {
					scoresInInt[4] = score;
					int ok = 1;
					int aux = 0;
					do {
						ok = 1;
						for (i = 0; i < 5; i++)
						{
							if (scoresInInt[i] < scoresInInt[i + 1]) {
								aux = scoresInInt[i];
								scoresInInt[i] = scoresInInt[i + 1];
								scoresInInt[i + 1] = aux;
								ok = 0;
							}

						}
					} while (ok != 1);
					std::ofstream myfileWrite("scores.cmgt", std::ios::trunc);
					myfileWrite << scoresInInt[0] << std::endl;
					myfileWrite << scoresInInt[1] << std::endl;
					myfileWrite << scoresInInt[2] << std::endl;
					myfileWrite << scoresInInt[3] << std::endl;
					myfileWrite << scoresInInt[4] << std::endl;

					scoreText1.setText(std::to_string(scoresInInt[0]));
					scoreText2.setText(std::to_string(scoresInInt[1]));
					scoreText3.setText(std::to_string(scoresInInt[2]));
					scoreText4.setText(std::to_string(scoresInInt[3]));
					scoreText5.setText(std::to_string(scoresInInt[4]));

					myfileWrite.close();

					break;
				}

			}
		}
		});


	Scene scoreScreen("scoreScreen");

	


	std::ifstream getScores("scores.cmgt");
	if (!getScores.fail()) {
		std::string line;

		std::getline(getScores, line);
		scoreText1.setText(line);
		scoresInInt[0] = std::stoi(line);

		std::getline(getScores, line);
		scoreText2.setText(line);
		scoresInInt[1] = std::stoi(line);

		std::getline(getScores, line);
		scoreText3.setText(line);
		scoresInInt[2] = std::stoi(line);

		std::getline(getScores, line);
		scoreText4.setText(line);
		scoresInInt[3] = std::stoi(line);

		std::getline(getScores, line);
		scoreText5.setText(line);
		scoresInInt[4] = std::stoi(line);

		getScores.close();
	}

	Button eraseData("eraseData", font, "ERASE DATA", sf::Vector2f(192.5f, 50.0f), darkColor);
	eraseData.setPosition(sf::Vector2f(108.0f, 540.0f));

	eraseData.setButtonAction([&scoreText1, &scoreText2, &scoreText3, &scoreText4, &scoreText5, &scoresInInt]() {
		std::ofstream myfileWrite("scores.cmgt", std::ios::trunc);
		myfileWrite << 0 << std::endl;
		myfileWrite << 0 << std::endl;
		myfileWrite << 0 << std::endl;
		myfileWrite << 0 << std::endl;
		myfileWrite << 0 << std::endl;

		scoreText1.setText("0");
		scoreText2.setText("0");
		scoreText3.setText("0");
		scoreText4.setText("0");
		scoreText5.setText("0");

		scoresInInt[0] = 0;
		scoresInInt[1] = 0;
		scoresInInt[2] = 0;
		scoresInInt[3] = 0;
		scoresInInt[4] = 0;

		myfileWrite.close();
		});
	scoreScreen.addGameObject(eraseData);
	scoreScreen.addGameObject(scoreText1);
	scoreScreen.addGameObject(scoreText2);
	scoreScreen.addGameObject(scoreText3);
	scoreScreen.addGameObject(scoreText4);
	scoreScreen.addGameObject(scoreText5);
	scoreScreen.addGameObject(backAScreen);

	Scene fightScreen("fightScreen");

	Button attack("attack", font, "attack", sf::Vector2f(192.5f, 50.0f), darkColor);
	attack.setPosition(sf::Vector2f(808.0f, 400.0f));
	attack.setButtonAction([&player, &enemy, &enemyhpText, &actionOrder]() {
		player.attackCharacter(enemy);
		enemyhpText.setText("Hp: " + std::to_string(enemy.getHP()));
		actionOrder = 1;

		});


	Button heal("heal", font, "Heal", sf::Vector2f(192.5f, 50.0f), darkColor);
	heal.setPosition(sf::Vector2f(808.0f, 450.0f));

	heal.setButtonAction([&player, &playerhpText, &actionOrder]() {
		player.heal();
		playerhpText.setText("Hp: " + std::to_string(player.getHP()));
		actionOrder = 1;

		});


	Button defend("defend", font, "defend", sf::Vector2f(192.5f, 50.0f), darkColor);
	defend.setPosition(sf::Vector2f(808.0f, 500.0f));

	defend.setButtonAction([&player, &playerdefenseText, &actionOrder]() {
		player.defend();
		playerdefenseText.setText("Defese: " + std::to_string(player.getDefense()));
		actionOrder = 1;

		});



	fightScreen.addGameObject(playerAvatar);
	fightScreen.addGameObject(enemyAvatar);

	fightScreen.addGameObject(attack);
	fightScreen.addGameObject(heal);
	fightScreen.addGameObject(defend);

	fightScreen.addGameObject(playerName);
	fightScreen.addGameObject(playerhpText);
	fightScreen.addGameObject(playerattackText);
	fightScreen.addGameObject(playerdefenseText);

	fightScreen.addGameObject(enemyName);
	fightScreen.addGameObject(enemyhpText);
	fightScreen.addGameObject(enemyattackText);
	fightScreen.addGameObject(enemydefenseText);

	fightScreen.addGameObject(backAScreen);

	handler.addScene(mainMenu);
	handler.addScene(scoreScreen);
	handler.addScene(fightScreen);



	TextObject currentScoreText("attackText", font, "Score: " + std::to_string(score));
	currentScoreText.setPosition(sf::Vector2f(848.0f, 290.0f));
	currentScoreText.setCharacterSize(26);
	currentScoreText.setFillColor(darkColor);

	Scene gameOverScreen("gameOverScreen");
	gameOverScreen.addGameObject(backAScreen);
	gameOverScreen.addGameObject(currentScoreText);

	Scene winFightScreen("winFightScreen");
	Scene progressScreen("progressScreen");

	Button nextFight("attack", font, "Next Fight", sf::Vector2f(192.5f, 50.0f), darkColor);
	nextFight.setPosition(sf::Vector2f(808.0f, 400.0f));
	nextFight.setButtonAction([&player, &enemy, &handler, &actionOrder, &enemyhpText, &enemyattackText, &enemydefenseText, &isFight]() {
		enemy.randomizeStats();

		//player.getPerk();
		//player.usePerks(enemy);
		enemyhpText.setText("Hp: " + std::to_string(enemy.getHP()));
		enemyattackText.setText("Attack: " + std::to_string(enemy.getAttack()));
		enemydefenseText.setText("Defense: " + std::to_string(enemy.getDefense()));
		actionOrder = 0;
		isFight = true;
		handler.popScene();
		});

	Button increaseHealth("attack", font, "Increase Health +50", sf::Vector2f(250.5f, 50.0f), darkColor);
	increaseHealth.setPosition(sf::Vector2f(100.0f, 200.0f));
	increaseHealth.setButtonAction([&player, &handler, &actionOrder, &playerhpText, &playerattackText, &playerdefenseText, &isFight,
		&enemyhpText, &enemyattackText, &enemydefenseText, &enemy]() {
			enemy.randomizeStats();

			player.setHP(player.geMaxHP() + 50);
			playerhpText.setText("Hp: " + std::to_string(player.getHP()));
			//player.getPerk();
			//player.usePerks(enemy);
			enemyhpText.setText("Hp: " + std::to_string(enemy.getHP()));
			enemyattackText.setText("Attack: " + std::to_string(enemy.getAttack()));
			enemydefenseText.setText("Defense: " + std::to_string(enemy.getDefense()));
			actionOrder = 0;
			isFight = true;
			handler.popScene();
		});
	Button increaseAttack("attack", font, "Increase Attack +10", sf::Vector2f(250.5f, 50.0f), darkColor);
	increaseAttack.setPosition(sf::Vector2f(400.0f, 200.0f));
	increaseAttack.setButtonAction([&player, &handler, &actionOrder, &playerhpText, &playerattackText, &playerdefenseText, &isFight,
		&enemyhpText, &enemyattackText, &enemydefenseText, &enemy]() {
			enemy.randomizeStats();
			player.setAttack(player.getMaxAttack() + 10);
			playerattackText.setText("Attack: " + std::to_string(player.getAttack()));
			//player.getPerk();
			//player.usePerks(enemy);
			enemyhpText.setText("Hp: " + std::to_string(enemy.getHP()));
			enemyattackText.setText("Attack: " + std::to_string(enemy.getAttack()));
			enemydefenseText.setText("Defense: " + std::to_string(enemy.getDefense()));
			actionOrder = 0;
			isFight = true;
			handler.popScene();
		});
	Button increaseDefense("attack", font, "Increase Defense +5", sf::Vector2f(250.5f, 50.0f), darkColor);
	increaseDefense.setPosition(sf::Vector2f(700.0f, 200.0f));
	increaseDefense.setButtonAction([&player, &handler, &actionOrder, &playerhpText, &playerattackText, &playerdefenseText, &isFight,
		&enemyhpText, &enemyattackText, &enemydefenseText, &enemy]() {
			enemy.randomizeStats();
			enemyhpText.setText("Hp: " + std::to_string(enemy.getHP()));
			enemyattackText.setText("Attack: " + std::to_string(enemy.getAttack()));
			enemydefenseText.setText("Defense: " + std::to_string(enemy.getDefense()));
			player.setDefense(player.getMaxDefense() + 5);
			//player.getPerk();
			//player.usePerks(enemy);
			playerdefenseText.setText("Defense: " + std::to_string(player.getDefense()));
			actionOrder = 0;
			isFight = true;
			handler.popScene();
		});

	progressScreen.addGameObject(increaseHealth);
	progressScreen.addGameObject(increaseAttack);
	progressScreen.addGameObject(increaseDefense);
	progressScreen.addGameObject(backAScreen);
	progressScreen.addGameObject(currentScoreText);

	winFightScreen.addGameObject(backAScreen);
	winFightScreen.addGameObject(nextFight);
	winFightScreen.addGameObject(currentScoreText);


	handler.addScene(gameOverScreen);
	handler.addScene(winFightScreen);
	handler.addScene(progressScreen);

	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else {
				if (isFight) {
					if (actionOrder == 0) {
						player.resetDefense();// The defense button works but because off the framerate you don't see it;
						handler.lastSceneHandleEvent(event, window);
						enemy.resetDefense();
					}
					else {
						if (isFight) {
							if (enemy.getHP() > 0) {
								enemy.doAction(player, enemyhpText, enemyattackText, enemydefenseText, playerhpText);
								actionOrder = 0;
								if (player.getHP() <= 0) {
									// Game Over
									isFight = false;
									for (int i = 5; i >= 0; i--)
									{
										if (scoresInInt[i] < score) {
											scoresInInt[4] = score;
											int ok = 1;
											int aux = 0;
											do {
												ok = 1;
												for (i = 0; i < 5; i++)
												{
													if (scoresInInt[i] < scoresInInt[i + 1]) {
														aux = scoresInInt[i];
														scoresInInt[i] = scoresInInt[i + 1];
														scoresInInt[i + 1] = aux;
														ok = 0;
													}

												}
											} while (ok != 1);
											std::ofstream myfileWrite("scores.cmgt", std::ios::trunc);
											myfileWrite << scoresInInt[0] << std::endl;
											myfileWrite << scoresInInt[1] << std::endl;
											myfileWrite << scoresInInt[2] << std::endl;
											myfileWrite << scoresInInt[3] << std::endl;
											myfileWrite << scoresInInt[4] << std::endl;

											scoreText1.setText(std::to_string(scoresInInt[0]));
											scoreText2.setText(std::to_string(scoresInInt[1]));
											scoreText3.setText(std::to_string(scoresInInt[2]));
											scoreText4.setText(std::to_string(scoresInInt[3]));
											scoreText5.setText(std::to_string(scoresInInt[4]));

											myfileWrite.close();

											break;
										}

									}
									handler.stackScene("gameOverScreen");
								}

							}
							else {
								score += 50;
								currentScoreText.setText("Score: " + std::to_string(score));
								isFight = false;
								fightsWon++;
								if (fightsWon % 2 == 0) {
									handler.stackScene("progressScreen");
								}
								else {
									handler.stackScene("winFightScreen");
								}
								//New Fight
							}

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