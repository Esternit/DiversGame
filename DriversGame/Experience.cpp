#include "Experience.h"

using namespace sf;

Experience::Experience(const sf::Texture& textures, float xpGiven, float posX, float posY, float width, float height, FrameAnimation anim) : xpGiven(xpGiven) {
	xp.setTexture(textures);
	xp.setTextureRect(IntRect(anim.FrameX, anim.FrameY, width, height));
	xp.setPosition(posX, posY);
	xp.setScale(2.f, 2.f);
}