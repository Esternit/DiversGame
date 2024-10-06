#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include "FrameAnimation.h"
#include "TextureHolder.h"
#include "Gun.h"



class Player {
public:
	Player(const sf::Texture& textures, float Speed, float SpeedIncreaser, const sf::Texture& texturesGun);
	void move(sf::Vector2f direction, bool speedIncrease);
	void animateMovement(sf::Vector2f direction);
	bool animateAttack(sf::Vector2f direction, int attackFrame);

	bool animateAttackSword1(sf::Vector2f direction, int posY, int posX);
	bool animateAttackSword2(sf::Vector2f direction, int posX, int posY, int posXend, int posYend);

	sf::Sprite getSprite();

	void setGunRotation(sf::Vector2f enemyPos);

	Gun getGun() { return gun; }	
	float getSpeed() { return speed; }
	float getSpeedIncreaser() { return speedIncreaser; }
private:
	sf::Sprite player;
	FrameAnimation animation;
	float speed;
	float speedIncreaser;
	Gun gun;
};

#endif