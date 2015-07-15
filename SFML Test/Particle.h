#pragma once
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <OpenGL/glew.h>
#include "Vector.h"
#include "Model.h"

class Particle : public Model
{
public:
	Particle(string filename);
	Particle(float particleSize, Vector position, Vector initialVelocity, Vector acceleration, float lifetime_Seconds, int frameRate, string filename);
	Particle(float particleSize, Vector position, Vector initialVelocity, Vector acceleration, float lifetime_Seconds, int frameRate, Model model);
	~Particle(void);
	void render();
	void update(float dT);
	void setVelocity(Vector newVelocity);
	void setAcceleration(Vector newAcceleration);
	float lifetime;
	float angle;
private:
	 GLfloat size;
};
