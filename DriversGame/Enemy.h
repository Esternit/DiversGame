#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "FrameAnimation.h"
#include <string>

using namespace sf;

class Enemy {
public:

    Enemy(const std::string& Path, float posX, float posY, FrameAnimation animation, float width, float height);

    Sprite getSprite();

    void move(sf::Vector2f direction);

    void animateMovement(sf::Vector2f direction);
protected:
    Sprite enemy;
    Texture enemyTexture;
    FrameAnimation animation;
    float width;
	float height;
};

#endif
