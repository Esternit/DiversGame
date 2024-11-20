#pragma once
#include <SFML/Graphics.hpp>
#include "FrameAnimation.h"
#include "TextureHolder.h"
#include "Gun.h"



class Player {
public:
	Player(const sf::Texture& textures, float Speed, float SpeedIncreaser, const sf::Texture& texturesGun);
	void move(sf::Vector2f direction, bool speedIncrease, float mapWidth, float mapHeight);
	void animateMovement(sf::Vector2f direction);
	bool animateAttack(sf::Vector2f direction, int attackFrame);

	bool animateAttackSword1(sf::Vector2f direction, int posY, int posX);
	bool animateAttackSword2(sf::Vector2f direction, int posX, int posY, int posXend, int posYend);

	sf::Sprite getSprite();

	void setGunRotation(sf::Vector2f enemyPos);

	Gun getGun() { return gun; }	
	float getSpeed() { return speed; }
	float getSpeedIncreaser() { return speedIncreaser; }

	void updateExperience(float experience) { this->experience += experience; }

	float getExperience() { return experience; }

	void setExperience(float experience) { this->experience = experience; }

	float getHealth() { return health; }
	float getMaxHealth() { return maxHealth; }

	float getLevel() { return level; }

	void setLevel(float level) { this->level = level; }

	void setSpeed(float speed) { this->speed = speed; }

	void moveAlone(float offsetX, float offsetY) {
		player.move(offsetX, offsetY);
	}

	void setHealth(float health) { this->health = health; }
	void setMaxHealth(float maxHealth) { this->maxHealth = maxHealth; }

	int getMeleeAttack() {
		return meleeAttack;
	}

	void setMeleeAttack(int meleeAttack) {
		this->meleeAttack = meleeAttack;
	}

	void setGold(int gold) {
		this->gold = gold;
	}

	int getGold() {
		return gold;
	}

	void setRed(int red) {
		this->red = red;
	}

	int getRed() {
		return red;
	}
private:
	sf::Sprite player;
	FrameAnimation animation;
	float speed;
	float experience, level;
	float speedIncreaser;
	float health, maxHealth;
	int meleeAttack = 20;
	int gold = 0;
	int red = 0;
	Gun gun;
};