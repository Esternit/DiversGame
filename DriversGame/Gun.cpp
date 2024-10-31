#include "Gun.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath> 


using namespace sf;

Gun::Gun(const Texture& textures, float posX, float posY, float width, float height, float attackGamage, FrameAnimation anim, float fireRate,float range) : attackGamage(attackGamage), fireRate(fireRate), range(range) {
	gun.setTexture(textures);
	gun.setTextureRect(IntRect(anim.FrameX, anim.FrameY, width, height));
	gun.setPosition(posX, posY);
    gun.setScale(1.f, 1.f);
}

void Gun::setRotation(Vector2f enemyPos) {
    sf::Vector2f gunPos = gun.getPosition();

    sf::Vector2f direction = enemyPos - gunPos;

    float angle = std::atan2(direction.y, direction.x) * 180 / 3.14159f;

    gun.setRotation(angle);

    if (angle < -90 || angle > 90)
    {
        gun.setScale(1.f, -1.f);
    }
    else
    {
        gun.setScale(1.f, 1.f);
    }
}