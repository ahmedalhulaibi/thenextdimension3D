#pragma once
#include "Vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

class Quaternion
{
	friend class Vector;
public:
	Quaternion(void);
	~Quaternion(void);

	Quaternion(Vector *vector);//quaternion from 3D vector
	Quaternion(Vector &vector);
	/*Quaternion(const Quaternion&);*/
	Quaternion(const Quaternion*);
	Quaternion(float angleRads, bool x, bool y, bool z);//rotation
	Quaternion(float angleRads, Vector *vector);
	Quaternion(float angleRads, Vector &vector);
	Quaternion(float _w, float _x, float _y, float _z);

	Quaternion multiply(Quaternion *other);
	Quaternion multiply(Quaternion &other);
	Quaternion multiply(float);
	void scale(float);

	Quaternion add(Quaternion *other);
	Quaternion add(Quaternion &other);

	Quaternion subtract(Quaternion *other);
	Quaternion subtract(Quaternion &other);

	float dotProduct(Quaternion *other);
	float dotProduct(Quaternion &other);
	float dotAngle(Quaternion *other);
	float dotAngle(Quaternion &other);

	float returnLength();
	void normalize();

	Quaternion conjugate();

	Quaternion LERP(Quaternion,Quaternion,float);
	static Quaternion SLERP(Quaternion,Quaternion,float);

	float w,x,y,z;


	bool operator==(Quaternion&);
};

