#include "Rock.h"

using namespace sf;

Rock::Rock(const Texture& textures, float posX, float posY, std::string name) : name(name) {
	rock.setTexture(textures);
	rock.setPosition(posX, posY);
	//rock.setScale(1.f, 1.f);
}

void Rock::updateTexture() {
	imagePos += 1;
	rock.setTexture(TextureHolder::GetTexture("Assets/Mining/64x64/" + name + std::to_string(imagePos) + ".png"));
}

void Rock::setPosition(float posX, float posY) {
	rock.setPosition(posX, posY);
}

Sprite Rock::getSprite() const{
	return rock;
}

int Rock::getImagePos() const {
	return imagePos;
}

void Rock::setImagePos(int pos) {
	imagePos = pos;
}