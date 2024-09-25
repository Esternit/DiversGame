#pragma once
#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "player.h"

class Game {
public:
	Game(std::string BGpath, std::string playerPath);
	void processer();
private:
	sf::RectangleShape GameBackground;
	sf::Texture backgroundTexture; // Store the texture
	Player player;
};
#endif // !GAME_H
