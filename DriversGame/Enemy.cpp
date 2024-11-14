#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <iostream>

const std::vector<int> yPosesMinotaur = {0, 200, 300 }; //stay/move/attack
const std::vector<int> animsXMoveMinotaur = { 24, 120, 212, 310, 404 };
const std::vector<int> animsXStayMinotaur = { 25, 120, 219, 315, 410 };
const std::vector<int> animsXAttackMinotaur = { 4, 126, 220, 314, 410, 505, 602, 700, 794 };

const std::vector<int> yPosesFirebug = { 524, 330, 524 };
const std::vector<int> animsXMoveFirebug = { 35, 162, 290, 420, 545, 673, 802, 930 }; //65 - width
const std::vector<int> animsXStayFirebug = { 35, 162, 290, 420, 545, 673, 802, 930, 1053, 1180, 1310};
Enemy::Enemy(const sf::Texture& textures, float posX, float posY, FrameAnimation anim, float width,  float height, float health, float givesXp, float damage, std::string name) : animation(anim), width(width), height(height), attack(false), health(health), givesXp(givesXp), damage(damage), name(name) {

	enemy.setTexture(textures);
	enemy.setTextureRect(IntRect(animation.FrameX, animation.FrameY, width, height));
	if (name == "Minotaur") {
		enemy.scale(2, 2);
	}
	enemy.setPosition(posX, posY);

	amountXp = rand() % 5 + 1;

}

Sprite Enemy::getSprite() {
	return enemy;
}

void Enemy::move(Vector2f direction) {
	enemy.move(direction);
}

void Enemy::animateMovement(Vector2f direction) {
	bool check = direction.x == 0 && direction.y == 0;
	std::vector <int> animsX;
	int yPosStay = 0, yPosMove = 0;
	if (name == "Minotaur") {
		animsX = check ? animsXStayMinotaur : animsXMoveMinotaur;
		yPosStay = yPosesMinotaur[0];
		yPosMove = yPosesMinotaur[1];
	}
	else if(name == "Firebug") {
		animsX = check ? animsXStayFirebug : animsXMoveFirebug;
		yPosStay = yPosesFirebug[0];
		yPosMove = yPosesFirebug[1];
	}

	if (direction.x == 0 && direction.y == 0) {
		animation.FrameY = yPosStay;
	}
	else {

		animation.FrameY = yPosMove;

	}
	animation.FrameX += 1;
	if (animation.FrameX >= animsX.size()) {
		animation.FrameX = 0;
	}
	if (direction.x < 0) {
		enemy.setTextureRect(IntRect(animsX[animation.FrameX] + width, animation.FrameY, -width, height));
	}

	else {
		enemy.setTextureRect(IntRect(animsX[animation.FrameX], animation.FrameY, width, height));
	}
}

void Enemy::animateAttack(Vector2f direction) {
	std::vector <int> animsX;
	int yPosAttack = 0;
	if (name == "Minotaur") {
		animsX = animsXAttackMinotaur;
		yPosAttack = yPosesMinotaur[2];
	}
	else if (name == "Firebug") {
		animsX = animsXStayFirebug;
		yPosAttack = yPosesFirebug[2];
	}

	if (animation.FrameY != yPosAttack) {
		animation.FrameX = 0;
	}
	animation.FrameY = yPosAttack;
	animation.FrameX += 1;

	if (animation.FrameX >= animsX.size()) {
		animation.FrameX = 0;
		attack = false;
	}

	if (direction.x < 0) {
		enemy.setTextureRect(IntRect(animsX[animation.FrameX] + width, animation.FrameY, -width, height));
	}

	else {
		enemy.setTextureRect(IntRect(animsX[animation.FrameX], animation.FrameY, width, height));
	}
}