#include "Rock.h"
#include <iostream>

using namespace sf;

Rock::Rock(const Texture& textures, float posX, float posY, std::string name, int health, int givesGold, int givesRed) : name(name), health(health), givesGold(givesGold), givesRed(givesRed){
	rock.setTexture(textures);
	rock.setPosition(posX, posY);
	//rock.setScale(1.f, 1.f);
}

void Rock::updateTexture() {
	imagePos += 1;

	rock.setTexture(TextureHolder::GetTexture("Assets/Mining/64x64/" + name + std::to_string(imagePos) + ".png"));
}

bool Rock::takeDamage(int damage) {
	health -= damage;

	if ((health < 30.0f && imagePos == 1) || (health < 15.0f && imagePos == 2)) {
		updateTexture();
	}
	return health <= 0;
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