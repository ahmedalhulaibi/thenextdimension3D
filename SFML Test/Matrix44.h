#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "Matrix22.h"
#include "Matrix33.h"
#include "Vector.h"
#include "Quaternion.h"
class Matrix44
{
public:
	Matrix44(void);
	Matrix44(Vector &, Matrix33 &);
	Matrix44(Vector &, Quaternion &);
	Matrix44(Quaternion &);
	void setPerspective(float fovy,float aspect,float zNear, float zFar);
	void loadIdentity();
	Matrix44 transpose();
	void copyIntoSingleArray();
	~Matrix44(void);

	float matrix44[4][4];
	float OneDmat[16];
};

