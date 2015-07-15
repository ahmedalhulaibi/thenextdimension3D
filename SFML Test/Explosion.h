#pragma once
#include "ParticlePoint.h"
#include <vector>

class Explosion
{
public:
	Explosion(void);
	//booleans x,y,z determin which axis the explosion is drawn around
	Explosion(int numberOfParticles, bool x, bool y, bool z, Vector velocity, Vector acceleration, Vector originPoint, float r, float g, float b, float alpha, float size, float lifetime);
	~Explosion(void);
	void draw(float dT);
	bool dead;
	std::vector <ParticlePoint*> p;
};

