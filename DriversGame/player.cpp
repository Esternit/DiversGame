#include "player.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

Player::Player(std::string Path,float Speed, float SpeedIncreaser) :speed(Speed), speedIncreaser(SpeedIncreaser) {
	// Load player texture
	if (!playerTexture.loadFromFile(Path)) {
		std::cerr << "Failed to load player image!" << std::endl;
	}

	player.setTexture(playerTexture);
	player.setTextureRect(IntRect(animation.FrameX, animation.FrameY, 40, 40));
	player.scale(2, 2);
	player.setPosition(Vector2f(1280, 720));
}

Player& Player::operator=(const Player& other) {
	if (this != &other) {
		playerTexture = other.playerTexture;
		player.setTexture(playerTexture);
		player.setPosition(other.player.getPosition());
	}
	return *this;
}

void Player::move(Vector2f direction, bool speedIncrease) {

	player.move(direction * (speedIncrease ? speedIncreaser : 1));
}

void Player::animateMovement(Vector2f direction) {
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
		player.setTextureRect(IntRect(animation.FrameX + animation.StepX, animation.FrameY, -40, 35));
	}

	else {
		player.setTextureRect(IntRect(animation.FrameX, animation.FrameY, 40, 35));
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