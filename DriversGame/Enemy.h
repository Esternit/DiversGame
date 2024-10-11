#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "FrameAnimation.h"
#include <string>

using namespace sf;

class Enemy {
public:

    Enemy(const sf::Texture& textures, float posX, float posY, FrameAnimation animation, float width, float height, float health);

    Sprite getSprite();

    void move(sf::Vector2f direction);

    void animateMovement(sf::Vector2f direction);

    bool getAttack() {
        return attack;
    };

	void setAttack(bool attack) {
		this->attack = attack;
	};

    bool updateHealth(float damage) {
		health -= damage;
		return health <= 0;
    }
protected:
    Sprite enemy;
    Texture enemyTexture;
    FrameAnimation animation;
    float width;
    bool attack;
	float height;
    float health;
};

#endif
