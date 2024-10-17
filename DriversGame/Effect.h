#pragma once
#ifndef EFFECT_H
#define EFFECT_H

#include <SFML/Graphics.hpp>
#include <string>
#include "FrameAnimation.h"

class Effect {
public:

	Effect(const sf::Texture& textures, float posX, float posY, FrameAnimation anim);
	bool proceedAnimation();

private:

	sf::Sprite effect;
	FrameAnimation animation;

};

#endif