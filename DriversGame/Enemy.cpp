#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Enemy::Enemy(const std::string& Path, float posX, float posY, FrameAnimation anim, float width,  float height) : animation(anim) {
	if (!enemyTexture.loadFromFile(Path)) {
		std::cerr << "Failed to load enemy image!" << std::endl;
	}

	enemy.setTexture(enemyTexture);
	enemy.setTextureRect(IntRect(animation.FrameX, animation.FrameY, width, height));
	enemy.scale(2, 2);
	enemy.setPosition(posX, posY);

}

Sprite Enemy::getSprite() {
	return enemy;
}

void Enemy::move(Vector2f direction) {
	enemy.move(direction);
}