#pragma once
#include <vector>
#include "Vector.h"
#include "Quaternion.h"
#include "Matrix44.h"
#include <iostream>
#include <fstream>
#include <ios>
#include <string>
#include <sstream>
#include <cstdlib>
#include <Windows.h>
#include <OpenGL\glew.h>
#include "glmObjLoader.h"
#include "Texture.h"
using namespace std;


class Model
{
public:
	Model();
	Model(string filename);
	void render();
	void update(float dT)
	{position = position + (velocity * dT) /*+ (acceleration) * ((dT*dT)/2)*/;};
	
	void setVelocity(Vector &vel)
	{this->velocity = vel;};

	void setDirectionVec(Vector &dir)
	{this->directionVec = dir;};

	void setAcceleration(Vector & accel)
	{this->acceleration = accel;};

	void setOrientation(Quaternion &quat)
	{this->orientation = quat;};

	void setScale(float scaleX, float scaleY, float scaleZ);

	void loadTexture(string texture_filename);

	~Model(void);

	GLMmodel *model;
	Texture modelTexture;
	bool colliding;
	bool collided;
	float scaleFactor[3];

	Vector velocity;
	Vector acceleration;
	Vector position;
	Vector directionVec;
	Quaternion orientation;
	Matrix44 transform;

	float dimensions[3];
	float radii[3];
};

