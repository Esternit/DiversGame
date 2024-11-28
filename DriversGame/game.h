#pragma once
#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "player.h"
#include <map>
#include <string>
#include "TextureHolder.h"
#include "Enemy.h"
#include "Experience.h"
#include <vector>
#include "IniFile.h"
#include "Buff.h"
#include "GameMenu.h"
#include "Rock.h"
#include "MobController.h"

class Game {
public:
	Game(std::string BGpath, std::string playerPath);
	void processer();

	void processerMenu();

	sf::Vector2f normalize(const sf::Vector2f& source);

	bool checkCollision(const sf::Sprite& rect1, const sf::Sprite& rect2);
	void spawnEnemies(int amount);

	Enemy* findClosestEnemy(sf::Sprite sprite, float range);

	void spawnExperience(std::vector<Experience>& experience, Enemy enemy);
	void calculateBuffs(IniFile& ini, std::vector<Buff>& availableBuffs);

	void giveBuff(Player& player, Buff buff);

	void spawnRocks(std::vector<Rock>& rocks, int numRocks, IniFile& ini);

	void handlePlayerCollisions(Player& player, const std::vector<Rock>& rocks);

	Rock chooseRock(IniFile& ini);
	sf::Vector2f rotateVector(const sf::Vector2f& vec, float angle);

private:
	sf::RectangleShape GameBackground;
	Player player;
	std::vector<Enemy> enemies;
	sf::RenderWindow window;

};
#endif // !GAME_H
