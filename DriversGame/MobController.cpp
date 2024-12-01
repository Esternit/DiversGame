#include "MobController.h"
#include <iostream>
#include <random>

MobController::MobController(float delay, float delayWave) : delay(delay), delayWave(delayWave) , currentSpawner(-1,-1) {
	timer.restart();
    timerWave.restart();
}

void MobController::spawnEnemies(std::vector<Enemy>& enemies, std::vector<Spawner>& spawners, sf::View& view, int& currentId) {
    if (timer.getElapsedTime().asSeconds() > delay && enemies.size() < 150) {
        
		timer.restart();
        if (currentSpawner.posX == -1 && currentSpawner.posY == -1) {
            std::vector<Spawner> calculatedSpawners = calculateSpawners(spawners, view);
            int index = rand() % calculatedSpawners.size();
            currentSpawner = calculatedSpawners[index];
        }
        
        currentId++;
        enemies.push_back(Enemy(TextureHolder::GetTexture("Assets/Enemy/firebug.png"), currentSpawner.posX, currentSpawner.posY, FrameAnimation(0, 90, 0, 100), 65, 40, 20, 3, 2, "Firebug", 5, 5, currentId));
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
        timerWave.restart();
		return true;
	}
    if(timerWave.getElapsedTime().asSeconds() > delayWave) {
		return true;
	}
	return false;
}