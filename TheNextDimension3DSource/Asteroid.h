#pragma once
#include "Model.h"

class Asteroid : public Model
{
public:
	Asteroid(string filename) : Model (filename)
	{
		this->position = Vector(0,0,0);
		this->setScale(2,2,2);
	};

	~Asteroid();

	void direct();

	void rendra();
	void loadNormalMap(string texture_filename);

	Texture normalMap;
	float randAngle;
	Quaternion rotAngle;
};