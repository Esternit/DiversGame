#include "Effect.h"


using namespace sf;
 // y =97

const std::vector<int> animsX = { 165, 177, 192};

Effect::Effect(const Texture& textures, float posX, float posY, FrameAnimation anim) : animation(anim) {
	effect.setTexture(textures);
	effect.setTextureRect(IntRect(animation.FrameX, animation.FrameY, 20, 20));
	effect.scale(2, 2);
	effect.setPosition(posX, posY);
}


bool Effect::proceedAnimation() {

	animation.FrameY = 97;

	if (animation.FrameX >= animsX.size()) {
		return false;
	}

	effect.setTextureRect(IntRect(animsX[animation.FrameX], animation.FrameY, 20, 20));

	animation.FrameX += 1;
	return true;
}