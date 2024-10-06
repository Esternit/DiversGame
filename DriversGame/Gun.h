#pragma once
#ifndef GUN_H
#define GUN_H

#include <SFML/Graphics.hpp>
#include <string>
#include "FrameAnimation.h"

class Gun{
public:
	Gun(const sf::Texture& textures, float posX, float posY, float width, float height, float attackGamage, FrameAnimation anim);
	Gun() = default;

	sf::Sprite getGun() { return gun; }

	void setPosition(float x, float y) { gun.setPosition(x, y); }

	void setRotation(sf::Vector2f enemyPos);
private:
	sf::Sprite gun;
	float attackGamage;
};

#endif // !

