#pragma once
#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include <string>
#include "FrameAnimation.h"
#include <vector>
#include "Enemy.h"
#include <iostream>

class Bullet
{
public:
	Bullet(const sf::Texture& textures, float posX, float posY, float width, float height, float attackGamage, FrameAnimation anim, sf::Vector2f direction, sf::Color color, int transferThrough);
	Bullet() = default;

	void animateMovement();

	const sf::Sprite& getSprite() const {
		return bullet;
	};

	void move(float seconds);

	float getAttackGamage() const {
		return attackGamage;
	}

	sf::Clock getClock() {
		return clock;
	}

	int getTransferThrough() {
		return transferThrough;
	}

	void setTransferThrough(int id) {
		if(lastTransferredId != id) {
			std::cout << id << " " <<  lastTransferredId << std::endl;
			transferThrough--;
			this->lastTransferredId = id;
		}
	}
private:
	sf::Sprite bullet;
	float attackGamage;
	FrameAnimation animation;
	float width, height;
	sf::Vector2f direction;
	sf::Clock clock;
	std::vector<Enemy> enemies;
	int transferThrough;
	int lastTransferredId = -1;
};

#endif // !
