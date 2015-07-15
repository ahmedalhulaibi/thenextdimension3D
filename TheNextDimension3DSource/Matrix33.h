#pragma once
#include <stdio.h>

class Matrix33
{
	friend class Vector;
public:
	Matrix33(void);
	~Matrix33(void);

	Matrix33(float mat[3][3]);
	Matrix33(float a, float b, float c, float d, float e, float f, float g, float h, float i);
	Matrix33(float angleDegrees, bool x, bool y, bool z);//Makes rotation matrix based on which boolean is true
	
	Matrix33 add(Matrix33 *otherMat33);
	Matrix33 subtract(Matrix33 *otherMat33);

	Matrix33 multiplayMatrix(Matrix33 *otherMat33);
	void multiplyScalar(float scalar);

	Matrix33 transpose();

	float matrix33_singleArray[9];//this will be used to pass to openGL
	float matrix33[3][3];
	void CopyIntoSingleArray();
};

