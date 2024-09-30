#pragma once
#ifndef MINOTAUR_H
#define MINOTAUR_H
#include <SFML/Graphics.hpp>

#include "Enemy.h"



using namespace sf;

class Minotaur : public Enemy {
public:
    Minotaur(const std::string& Path, float posX, float posY);

    Sprite getSprite() { return enemy; }

    //void update(float deltaTime) override;
    //void draw(RenderWindow& window) override;
};

#endif