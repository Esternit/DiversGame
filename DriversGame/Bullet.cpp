#include "Bullet.h"
#include <vector>
#include <iostream>

const std::vector<int> animsXMove = { 180, 194, 211, 226 };

using namespace sf;

Bullet::Bullet(const Texture& textures, float posX, float posY, float width, float height, float attackGamage, FrameAnimation anim, Vector2f direction) : attackGamage(attackGamage), animation(anim), width(width), height(height), direction(direction) {
	bullet.setTexture(textures);
	bullet.setTextureRect(IntRect(anim.FrameX, anim.FrameY, width, height));
	bullet.setPosition(posX, posY);
	bullet.setScale(2.f, 2.f);
}


void Bullet::animateMovement() {
	std::vector <int> animsX =  animsXMove;
	animation.FrameY = 110;
	animation.FrameX += 1;
	if (animation.FrameX >= animsX.size()) {
		animation.FrameX = 0;
	}
	bullet.setTextureRect(IntRect(animsX[animation.FrameX] + 25, animation.FrameY, width, height));

}

void Bullet::move(float seconds) {
	bullet.setPosition(bullet.getPosition() + seconds * direction * 500.0f);
}