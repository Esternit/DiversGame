#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>


class Player {
public:
	Player(std::string Path);
	Player &operator=(const Player &other);
	void move(sf::Vector2f direction);

	sf::Sprite getSprite();
private:
	sf::Sprite player;
	sf::Texture playerTexture;  // Store the texture
};

#endif