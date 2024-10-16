#pragma once
#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "player.h"
#include <map>
#include <string>
#include "TextureHolder.h"
#include "Minotaur.h"

class Game {
public:
	Game(std::string BGpath, std::string playerPath);
	void processer();

	sf::Vector2f normalize(const sf::Vector2f& source);

	bool checkCollision(const sf::Sprite& rect1, const sf::Sprite& rect2);
	void spawnEnemies(int amount);

	Enemy* findClosestEnemy(sf::Sprite sprite);
private:
	sf::RectangleShape GameBackground;
	Player player;
	std::vector<Enemy> enemies;

};
#endif // !GAME_H
