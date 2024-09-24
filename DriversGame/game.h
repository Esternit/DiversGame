#pragma once
#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>

class Game {
public:
	Game(std::string BGpath);
	void processer();
private:
	sf::RectangleShape GameBackgorund;
};
#endif // !GAME_H
