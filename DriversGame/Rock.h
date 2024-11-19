#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"

class Rock {
private:
	sf::Sprite rock;
	int imagePos = 1;
	std::string name;

public:
	Rock(const sf::Texture& textures, float x, float y, std::string name);

	void updateTexture();

	void setPosition(float x, float y);

	int getImagePos() const;

	void setImagePos(int imagePos);

	sf::Sprite getSprite() const;
};