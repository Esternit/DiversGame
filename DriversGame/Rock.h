#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"

class Rock {
private:
	sf::Sprite rock;
	int imagePos = 1;
	std::string name;
	int health;
	int givesGold;
	int givesRed;

public:
	Rock(const sf::Texture& textures, float x, float y, std::string name, int health, int givesGold, int givesRed);

	void updateTexture();

	void setPosition(float x, float y);

	int getImagePos() const;

	void setImagePos(int imagePos);

	bool takeDamage(int damage);

	int getGivesGold() {
		return givesGold;
	}

	int getGivesRed() {
		return givesRed;
	}

	int getHealth(){
		return health;
	}

	std::string getName() {
		return name;
	}

	sf::Sprite getSprite() const;
};