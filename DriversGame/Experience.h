#pragma once
#ifndef EXPERIENCE_H
#define EXPERIENCE_H

#include <SFML/Graphics.hpp>
#include <string>
#include "FrameAnimation.h"

class Experience {
private:
	sf::Sprite xp;
	float xpGiven;
public:
	Experience(const sf::Texture& textures, float xpGiven, float posX, float posY, float width, float height, FrameAnimation anim);
	sf::Sprite getSprite() { return xp; }
	float getXpGiven() { return xpGiven; }
};

#endif // !
