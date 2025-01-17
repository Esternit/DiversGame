#include "MobController.h"
#include <iostream>
#include <random>

MobController::MobController(float delay, float delayWave) : delay(delay), delayWave(delayWave) , currentSpawner(-1,-1) {
	timer.restart();
    timerWave.restart();
}

void MobController::spawnEnemies(std::vector<Enemy>& enemies, std::vector<Spawner>& spawners, sf::View& view, int& currentId) {
    if (timer.getElapsedTime().asSeconds() > delay && enemies.size() < 150 && !isBoss) {
        
		timer.restart();
        if (currentSpawner.posX == -1 && currentSpawner.posY == -1) {
            std::vector<Spawner> calculatedSpawners = calculateSpawners(spawners, view);
            int index = rand() % calculatedSpawners.size();
            currentSpawner = calculatedSpawners[index];
        }
        
        currentId++;
        if (waveCount % 5 == 0) {
            isBoss = true;
            enemies.push_back(Enemy(TextureHolder::GetTexture("Assets/Enemy/Minotaur.png"), currentSpawner.posX, currentSpawner.posY, FrameAnimation(0, 90, 0, 100), 60, 60, 100 + waveCount * increaserPerWave, 10, 20 + waveCount * increaserPerWave, "Minotaur", 100, 100, currentId));
        }
        else if (waveCount % 3 == 0) {
            enemies.push_back(Enemy(TextureHolder::GetTexture("Assets/Enemy/Firebug.png"), currentSpawner.posX, currentSpawner.posY, FrameAnimation(0, 90, 0, 100), 65, 40, 20 + waveCount * increaserPerWave / 2, 3, 2 + waveCount * increaserPerWave, "Firebug", 5, 5, currentId));
        }
        else {
            enemies.push_back(Enemy(TextureHolder::GetTexture("Assets/Enemy/leafbug.png"), currentSpawner.posX, currentSpawner.posY, FrameAnimation(0, 90, 0, 100), 50, 25, 20 + waveCount * increaserPerWave / 2 , 3, 2 + waveCount * increaserPerWave, "Leafbug", 5, 5, currentId));
        }
        
    }
}

std::vector<Spawner> MobController::calculateSpawners(std::vector<Spawner>& spawners, sf::View& view) {
    sf::FloatRect viewBounds(
        view.getCenter().x - view.getSize().x / 2,
        view.getCenter().y - view.getSize().y / 2,
        view.getSize().x,                         
        view.getSize().y
    );

    std::vector<Spawner> outsideViewSpawners;

    for (const auto& spawner : spawners) {
        if (!viewBounds.contains(spawner.posX, spawner.posY)) {
            outsideViewSpawners.push_back(spawner);
        }
    }

    return outsideViewSpawners;
}

bool MobController::startWave() {
	if (timerWave.getElapsedTime().asSeconds() > delayWave * 2) {
        isBoss = false;
        waveCount++;
        timerWave.restart();
		return true;
	}
    if(timerWave.getElapsedTime().asSeconds() > delayWave) {
		return true;
	}
	return false;
}