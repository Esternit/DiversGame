#pragma once
#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "player.h"
#include <map>
#include <string>
#include "TextureHolder.h"

class Game {
public:
	Game(std::string BGpath, std::string playerPath);
	void processer();

	sf::Vector2f normalize(const sf::Vector2f& source);


private:
	sf::RectangleShape GameBackground;
	Player player;

};
#endif // !GAME_H
