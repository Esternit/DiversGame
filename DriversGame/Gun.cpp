#include "Gun.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath> 


using namespace sf;

Gun::Gun(const Texture& textures, float posX, float posY, float width, float height, float attackGamage, FrameAnimation anim) : attackGamage(attackGamage) {
	gun.setTexture(textures);
	gun.setTextureRect(IntRect(anim.FrameX, anim.FrameY, width, height));
	gun.setPosition(posX, posY);
    gun.setScale(1.f, 1.f);
}

void Gun::setRotation(Vector2f enemyPos) {
    sf::Vector2f gunPos = gun.getPosition();

    // Calculate the direction vector (from gun to enemy)
    sf::Vector2f direction = enemyPos - gunPos;

    // Calculate the angle using atan2 (returns radians)
    float angle = std::atan2(direction.y, direction.x) * 180 / 3.14159f;

    gun.setRotation(angle);

    if (angle < -90 || angle > 90)
    {
        // Flip the sprite horizontally by setting a negative scale on the X axis
        gun.setScale(1.f, -1.f);
    }
    else
    {
        // Set normal scale when not mirrored
        gun.setScale(1.f, 1.f);
    }
}