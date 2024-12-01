#pragma once

#include <SFML/Graphics.hpp>
#include "FrameAnimation.h"
#include <string>

using namespace sf;

class Enemy {
public:

    Enemy(const sf::Texture& textures, float posX, float posY, FrameAnimation animation, float width, float height, float health, float givesXp, float damage, std::string name, int givesRed, int givesGold, int id);

    Sprite getSprite();

    void move(sf::Vector2f direction, std::vector<Enemy>& enemies);

    void animateMovement(sf::Vector2f direction);

    void animateAttack(sf::Vector2f direction);

    bool getAttack() {
        return attack;
    };

	float getHealth() {
		return health;
	}

	void setAttack(bool attack) {
		this->attack = attack;
	};

    void setHealth(float health) {
		this->health = health;
	}

    bool updateHealth(float damage) {
		health -= damage;
		return health <= 0;
    }

    Clock getAnimateMovementClock() {
		return animateMovementClock;
	}

	Clock getAnimateAttackClock() {
		return animateAttackClock;
	}

    void resetAnimateAttackClock() {
		animateAttackClock.restart();
    }

	void resetAnimateMovementClock() {
		animateMovementClock.restart();
	}

    float getGivesXp() {
		return givesXp;
	}

    float getDamage() {
		return damage;
	}

    void setDamage(float damage) {
		this->damage = damage;
	}

	int getAmountXp() {
		return amountXp;
	}

	int getGivesRed() {
		return givesRed;
	}

	int getGivesGold() {
		return givesGold;
	}
	int getId() {
		return id;
	}
protected:
    Sprite enemy;
    Texture enemyTexture;
    FrameAnimation animation;
    float width;
    bool attack;
	float height;
    float health;
    float givesXp;
	int amountXp;
    float damage;
	int givesRed;
	int givesGold;
	int id;
	std::string name;
    Clock animateMovementClock, animateAttackClock;
};
