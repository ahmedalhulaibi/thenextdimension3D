#pragma once
#include "Model.h"
#include "EnemyBase.h"
#include "Player.h"
#include <string>
using namespace std;

class Spawner : public Model
{
public:
	Spawner();
	Spawner(string filename, int level);
	~Spawner();

	void render();

	bool update(int enemiesSize);
	
	int health;
	float spawnTime;
	float spawnCount;
	int sizeLimit;

	static Model *morphTargets[12];
	float deltaT;
	int morphTargNum;
	void morph();
	Sound *spawnerSound;
};