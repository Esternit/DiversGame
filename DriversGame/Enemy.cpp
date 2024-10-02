#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Enemy::Enemy(const std::string& Path, float posX, float posY, FrameAnimation anim, float width,  float height) : animation(anim), width(width), height(height), attack(false) {
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

void Enemy::animateMovement(Vector2f direction) {
	if (direction.x == 0 && direction.y == 0) {
		animation.FrameX += animation.StepX;
		animation.FrameY = 0;
		if (animation.FrameX < animation.StepX || animation.FrameX >180) {
			animation.FrameX = animation.StepX;
		}
	}
	else {
		animation.FrameY = animation.StepY;
		animation.FrameX += animation.StepX;
		if (animation.FrameX < animation.StepX || animation.FrameX > 340) {
			animation.FrameX = animation.StepX;
		}
	}
	if (direction.x < 0) {
		enemy.setTextureRect(IntRect(animation.FrameX + animation.StepX, animation.FrameY, -width, height));
	}

	else {
		enemy.setTextureRect(IntRect(animation.FrameX, animation.FrameY, width, height));
	}
}