#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Spawner.h"
#include "player.h"

class MobController {
public:
	MobController(float delay, float delayWave);

	bool startWave();
	void spawnEnemies(std::vector<Enemy>& enemies, std::vector<Spawner>& spawners, sf::View& view, int& currentId);
	std::vector<Spawner> calculateSpawners(std::vector<Spawner>& spawners, sf::View& view);
private:
	sf::Clock timer;
	float delay;
	Spawner currentSpawner;
	sf::Clock timerWave;
	float delayWave;
	int waveCount = 0;
	int increaserPerWave = 10;
	bool isBoss = false;
};