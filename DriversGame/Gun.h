#pragma once

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

	float getCriticalChance() { return criticalChance; }

	int getRayCastsAmount() { return rayCastsAmount; }

	void setRayCastsAmount(int rayCastsAmount) { this->rayCastsAmount = rayCastsAmount; }

	int getTransferthrough() { return transferthrough; }

	void setTransferthrough(int transferthrough) { this->transferthrough = transferthrough; }
private:
	sf::Sprite gun;
	float attackGamage;
	float fireRate;
	float range;
	float criticalChance = 0.1f;
	int transferthrough = 1;
	int rayCastsAmount = 1;
};

