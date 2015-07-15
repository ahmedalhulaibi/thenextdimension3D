#pragma once
#include "model.h"

enum
{
	GRAVITY_BOMB = 1,
	SHIELD,
	FREEZE_TIME,
	SPEED_UP,
	SLOW_DOWN
};

class Powerup : public Model
{
public:
	Powerup(string filename);

	~Powerup(void);

	void render();

	int ID;
	bool alive;
	float angle;
	Quaternion q1, q2;
	float slerpDT;
};

