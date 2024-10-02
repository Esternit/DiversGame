#include "Minotaur.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

const std::vector<int> animsXMove = { 24, 120, 212, 310, 404 };
const std::vector<int> animsXStay = { 25, 120, 219, 315, 410 };
const std::vector<int> animsXAttack = { 4, 126, 220, 314, 410, 505, 602, 700, 794 };

Minotaur::Minotaur(const std::string& Path, float posX, float posY) : Enemy(Path, posX, posY, FrameAnimation(0, 90, 0, 100), 60,60) {

}

void Minotaur::animateMovement(Vector2f direction) {
	bool check = direction.x == 0 && direction.y == 0;
	std::vector <int> animsX = check ? animsXStay : animsXMove;
	if (direction.x == 0 && direction.y == 0) {
		animation.FrameY = 0;
	}
	else {
		
		animation.FrameY = animation.StepY * 2;

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

void Minotaur::animateAttack(Vector2f direction) {
	if (animation.FrameY != animation.StepY * 3) {
		animation.FrameX = 0;
	}
	animation.FrameY = animation.StepY * 3;
	animation.FrameX += 1;

	if (animation.FrameX >= animsXAttack.size()) {
		animation.FrameX = 0;
		attack = false;
	}

	if (direction.x < 0) {
		enemy.setTextureRect(IntRect(animsXAttack[animation.FrameX] + width, animation.FrameY, -width, height));
	}

	else {
		enemy.setTextureRect(IntRect(animsXAttack[animation.FrameX], animation.FrameY, width, height));
	}
}

