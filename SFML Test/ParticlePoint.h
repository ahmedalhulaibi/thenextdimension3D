#pragma once
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <OpenGL/glew.h>
#include <OpenGL/glut.h>
#include "Vector.h"

class ParticlePoint
{
public:
	ParticlePoint(void);
	ParticlePoint(float r, float g, float b, float alpha, float pointSize,Vector& position, Vector& initialVelocity, Vector& acceleration, float lifetime_Seconds, int frameRate);
	~ParticlePoint(void);
	void draw(float dT);
	void update(float dT);
	void setColor(float r, float g, float b, float alpha);
	void setVelocity(Vector &newVelocity);
	void setAcceleration(Vector &newAcceleration);
	float lifetime;
	Vector position;
	float randomX, randomY;
	 GLfloat r, g, b, alpha;//alpha full intensity = 1
	 GLfloat size;
	 GLfloat alpha_fadeIncr;
	 Vector velocity; 
	 Vector acceleration;
	 bool useRand;
};