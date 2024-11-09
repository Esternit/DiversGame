#pragma once
#ifndef GUN_H
#define GUN_H

#include <SFML/Graphics.hpp>
#include <string>
#include "FrameAnimation.h"

class Gun{
public:
	Gun(const sf::Texture& textures, float posX, float posY, float width, float height, float attackGamage, FrameAnimation anim, float fireRate, float range);
	Gun() = default;

	sf::Sprite getGun() { return gun; }

	void setPosition(float x, float y) { gun.setPosition(x, y); }

	void setRotation(sf::Vector2f enemyPos);

	float getFireRate() { return fireRate; }

	float getAttackGamage() { return attackGamage; }

	float getRange() { return range; }

	void setRange(float range) { this->range = range; }

	void setFireRate(float fireRate) { this->fireRate = fireRate; }
private:
	sf::Sprite gun;
	float attackGamage;
	float fireRate;
	float range;
};

#endif // !

