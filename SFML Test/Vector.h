#pragma once
#include "Matrix33.h"
#include "Quaternion.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <OpenGL\glew.h>

class Quaternion;//forward include to avoid circular inclusion errors

struct coord //A struct to load in a 2D coordinate
{
	float x, y, z;
	coord(){}
	coord(float _x, float _y, float _z)
	{
		x = (float)_x;
		y = (float)_y;
		z = (float)_z;
	}
};

class Vector //Our Vector Class
{
public:
	Vector();
	Vector (coord start, coord end);
	Vector (float x, float y, float z);
	~Vector(void);

	void addVector(Vector *otherVector); //Adds a vector onto current vector
	void addVector(Vector &otherVector); 
	Vector addVec(Vector &);
	Vector addVec(Vector *);

	void subtractVector(Vector *otherVector); //Subtracts a vector from current vector
	void subtractVector(Vector &otherVector);
	Vector subVector(Vector &otherVector);
	Vector subVector(Vector *otherVector);

	void multiplyVector(float scalar); //Multiplies current vector by a scalar value
	void multiplyVector(Matrix33 *otherMatrix); //Multiplies current vector by a matrix
	void multiplyVector(Matrix33 &otherMatrix);
	void multiplyVector(Quaternion *rotationQuat); //Multiplies current vector by a quaternion
	void multiplyVector(Quaternion &rotationQuat);

	void translate(Vector *translationVector);

	float dotProduct(Vector *otherVector);//length of projection of one vector on a another
	float dotProduct(Vector &otherVector);
	float angle(Vector &other);
	Vector projectionVector(Vector *otherVector);//projection of one vector on other vector
	Vector crossProduct(Vector&);

	void normalize(); //normalize's current vector
	void reset(); //reset's current vector to initial given position 
	float returnLength(); //return's length of vector
	Vector truncateLength(float max_length);

	void updateVector(Matrix33 * rotationMatrix, Vector * translationVector); //updates vector given a rotation matrix and translation vector

	//Public Data variables for us to use
	coord thisVector;
	coord startVector;
	coord endVector;
	float length;
	//this will be used to pass some things into openGL mostly
	GLfloat X_Y_Z[3];

	Vector operator+(Vector &other);
	Vector operator-(Vector &other);
	Vector operator*(Matrix33 &other);
	Vector operator*(Quaternion &other);
	Vector operator*(float scalar);
	bool   operator==(Vector&);

	void LERP(const Vector &v1, const Vector &v2,double deltaT);
	void LERP(const Vector *v1, const Vector *v2,double deltaT);
	void SLERP(Vector&,Vector&,Vector&,Vector&, double deltaT);
	void BezSLERP(Vector& v1,Vector& v2,Vector& v3,Vector& v4, double deltaT);
	float speedControl_SLERP(Vector&,Vector&,Vector&,Vector&);
	float speedControl_BezSLERP(Vector& v1,Vector& v2,Vector& v3,Vector& v4);

private:
	coord initialStart, initialEnd; //coordinates to store our initial given vector for resetting
};