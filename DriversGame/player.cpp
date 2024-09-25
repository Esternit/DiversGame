#include "player.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

Player::Player(std::string Path) {
	// Load player texture
	if (!playerTexture.loadFromFile(Path)) {
		std::cerr << "Failed to load player image!" << std::endl;
	}

	player.setTexture(playerTexture);
	player.setPosition(Vector2f(80, 80));
}

Player& Player::operator=(const Player& other) {
	if (this != &other) {
		playerTexture = other.playerTexture;
		player.setTexture(playerTexture);
		player.setPosition(other.player.getPosition());
	}
	return *this;
}

void Player::move(Vector2f direction) {
	player.move(direction);
}

Sprite Player::getSprite() {
	return player;
}