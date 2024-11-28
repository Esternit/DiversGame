#pragma once

struct Spawner {
	int posX;
	int posY;

	Spawner(int posX, int posY) {
		this->posX = posX;
		this->posY = posY;
	}

	void setPos(int posX, int posY) {
		this->posX = posX;
		this->posY = posY;
	}
};