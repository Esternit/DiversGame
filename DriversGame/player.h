#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>

struct FrameAnimation {
	int FrameX = 0;
	int StepX = 50;
	int FrameY = 0;
	int StepY = 40;
};

class Player {
public:
	Player(std::string Path, float Speed, float SpeedIncreaser);
	Player &operator=(const Player &other);
	void move(sf::Vector2f direction, bool speedIncrease);
	void animateMovement(sf::Vector2f direction);
	bool animateAttack(sf::Vector2f direction, int attackFrame);

	bool animateAttackSword1(sf::Vector2f direction, int posY, int posX);
	bool animateAttackSword2(sf::Vector2f direction, int posX, int posY, int posXend, int posYend);

	sf::Sprite getSprite();
	float getSpeed() { return speed; }
	float getSpeedIncreaser() { return speedIncreaser; }
private:
	sf::Sprite player;
	sf::Texture playerTexture;  // Store the texture
	FrameAnimation animation;
	float speed;
	float speedIncreaser;
};

#endif