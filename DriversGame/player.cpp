#include "player.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

const std::vector<int> animsXMoveMinotaur = { 65, 114, 164, 216, 264, 314 };
const std::vector<int> animsXStayMinotaur = { 13, 64, 114, 161};

using namespace sf;

Player::Player(const Texture &textures,float Speed, float SpeedIncreaser, const Texture& texturesGun) :speed(Speed), speedIncreaser(SpeedIncreaser), animation(0,50,0,40), experience(0), health(100), maxHealth(100), level(1) {

	player.setTexture(textures);
	player.setTextureRect(IntRect(animation.FrameX, animation.FrameY, 40, 40));
	player.scale(2, 2);
	player.setPosition(Vector2f(1280, 720));

	gun = Gun(texturesGun, player.getPosition().x + 10, player.getPosition().y + 38, 30, 15, 10, FrameAnimation(0, 0, 50, 0), 0.5f, 500);
}

void Player::move(Vector2f direction, bool speedIncrease, float mapWidth, float mapHeight) {
	
	player.move(direction * (speedIncrease ? speedIncreaser : 1));

	if (player.getPosition().x < 0) {
		player.setPosition(0, player.getPosition().y);
	}
	if (player.getPosition().x > mapWidth - 40) {
		player.setPosition(mapWidth - 40, player.getPosition().y);
	}
	if (player.getPosition().y < 0) {
		player.setPosition(player.getPosition().x, 0);
	}
	if (player.getPosition().y > mapHeight - 40) {
		player.setPosition(player.getPosition().x, mapHeight - 40);
	}

	if (gun.getGun().getScale().y < 0) {
		gun.setPosition(player.getPosition().x + 17.5, player.getPosition().y + 38);
	}
	else {
		gun.setPosition(player.getPosition().x + 10, player.getPosition().y + 38);
	}
}

void Player::animateMovement(Vector2f direction) {
	bool check = direction.x == 0 && direction.y == 0;
	std::vector <int> animsX = check ? animsXStayMinotaur : animsXMoveMinotaur;
	if (direction.x == 0 && direction.y == 0) {
		animation.FrameY = 0;
	}
	else {

		animation.FrameY = animation.StepY * 1;

	}
	animation.FrameX += 1;
	if (animation.FrameX >= animsX.size()) {
		animation.FrameX = 0;
	}
	if (direction.x < 0) {
		player.setTextureRect(IntRect(animsX[animation.FrameX] + 25, animation.FrameY, -25, 35));
	}

	else {
		player.setTextureRect(IntRect(animsX[animation.FrameX], animation.FrameY, 25, 35));
	}

}

bool Player::animateAttack(Vector2f direction, int attackFrame) {
	switch (attackFrame) {
		case 0:
			return animateAttackSword1(direction, 280, 222);
		case 1:
			return animateAttackSword1(direction, 180, 262);
		case 2:
			return animateAttackSword2(direction, 200, 262, 140, 302);
		default:
			return false;
	}
}

bool Player::animateAttackSword1(Vector2f direction, int posX, int posY) {
	if (animation.FrameY != posY) {
		animation.FrameY = posY;
		animation.FrameX = 0;
	}
	else {
		animation.FrameX += animation.StepX;
	}

	if (animation.FrameX > posX) {
		animation.FrameX = 0;
		animation.FrameY = 0;
		return false;
	}
	if (direction.x < 0) {
		player.setTextureRect(IntRect(animation.FrameX + animation.StepX, animation.FrameY, -50, 40));
	}
	else {
		player.setTextureRect(IntRect(animation.FrameX, animation.FrameY, 50, 40));
	}

	return true;
}

bool Player::animateAttackSword2(Vector2f direction, int posX, int posY, int posXend, int posYend) {
	if (animation.FrameY != posY && animation.FrameY != posYend) {
		animation.FrameY = posY;
		animation.FrameX = posX;
	}
	else {
		animation.FrameX += animation.StepX;
	}

	if (animation.FrameX > posXend && animation.FrameY == posYend) {
		animation.FrameX = 0;
		animation.FrameY = 0;
		return false;
	}
	if (animation.FrameX > 320) {
		animation.FrameX = 0;
		animation.FrameY = posYend;
	}
	if (direction.x < 0) {
		player.setTextureRect(IntRect(animation.FrameX + animation.StepX, animation.FrameY, -50, 40));
	}
	else {
		player.setTextureRect(IntRect(animation.FrameX, animation.FrameY, 50, 40));
	}

	return true;

}

Sprite Player::getSprite() {
	return player;
}

void Player::setGunRotation(Vector2f enemyPos) {
	gun.setRotation(enemyPos);
}