#pragma once
#include <string>


class Buff {
public:
	Buff(std::string name, float value, int costGold, int costRed) : name(name), value(value), costGold(costGold), costRed(costRed) {}

	std::string getName() { return name; }
	float getValue() { return value; }
	int getCostGold() { return costGold; }
	int getCostRed() { return costRed; }

private:
	std::string name;
	float value;
	int costGold;
	int costRed;
};