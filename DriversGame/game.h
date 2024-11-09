#pragma once
#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "player.h"
#include <map>
#include <string>
#include "TextureHolder.h"
#include "Minotaur.h"
#include "Experience.h"
#include <vector>
#include "IniFile.h"

class Game {
public:
	Game(std::string BGpath, std::string playerPath);
	void processer();

	sf::Vector2f normalize(const sf::Vector2f& source);

	bool checkCollision(const sf::Sprite& rect1, const sf::Sprite& rect2);
	void spawnEnemies(int amount);

	Enemy* findClosestEnemy(sf::Sprite sprite, float range);

	void spawnExperience(std::vector<Experience>& experience, Enemy enemy);
	void calculateBuffs(IniFile ini, std::vector<std::pair<std::string, float>>& availableBuffs);

	void giveBuff(Player& player, std::pair<std::string, float> buff);
private:
	sf::RectangleShape GameBackground;
	Player player;
	std::vector<Enemy> enemies;

};
#endif // !GAME_H
