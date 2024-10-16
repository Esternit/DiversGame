#pragma once
#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include <string>
#include "FrameAnimation.h"


class Bullet
{
public:
	Bullet(const sf::Texture& textures, float posX, float posY, float width, float height, float attackGamage, FrameAnimation anim, sf::Vector2f direction);
	Bullet() = default;

	void animateMovement();

	const sf::Sprite& getSprite() const {
		return bullet;
	};

	void move(float seconds);

	float getAttackGamage() const {
		return attackGamage;
	}
private:
	sf::Sprite bullet;
	float attackGamage;
	FrameAnimation animation;
	float width, height;
	sf::Vector2f direction;
};

#endif // !
