#include "Vector.h"
#include <math.h>

Vector::Vector()
{
	thisVector.x = 1.0f;
	thisVector.y = 1.0f;
	thisVector.z = 1.0f;
	coord g(thisVector.x,thisVector.y,thisVector.z);
	initialStart = coord(0,0,0);
	initialEnd = g;
	startVector = initialStart;
	endVector = initialEnd;
	
	this->X_Y_Z[0] = (GLfloat)thisVector.x;
	this->X_Y_Z[1] = (GLfloat)thisVector.y;
	this->X_Y_Z[2] = (GLfloat)thisVector.z;
}

Vector::Vector (float x, float y, float z)
{
	thisVector.x = x;
	thisVector.y = y;
	thisVector.z = z;
	coord g(thisVector.x,thisVector.y,thisVector.z);
	initialStart = coord(0,0,0);
	initialEnd = g;
	startVector = initialStart;
	endVector = initialEnd;
	
	this->X_Y_Z[0] = (GLfloat)thisVector.x;
	this->X_Y_Z[1] = (GLfloat)thisVector.y;
	this->X_Y_Z[2] = (GLfloat)thisVector.z;
}

Vector::Vector(coord start, coord end)
{
	thisVector.x = end.x - start.x ;
	thisVector.y = end.y - start.y ;
	thisVector.z = end.z - start.z ;
	initialStart = start;
	initialEnd = end;
	startVector = start;
	endVector = end;


	this->X_Y_Z[0] = (GLfloat)thisVector.x;
	this->X_Y_Z[1] = (GLfloat)thisVector.y;
	this->X_Y_Z[2] = (GLfloat)thisVector.z;

}

float Vector::returnLength()
{
	return sqrt((thisVector.x*thisVector.x) + (thisVector.y*thisVector.y) + (thisVector.z*thisVector.z));
}

void Vector::normalize()
{
	float length = this->returnLength();
	thisVector.x = thisVector.x/length;
	thisVector.y = thisVector.y/length;
	thisVector.z = thisVector.z/length;
	this->X_Y_Z[0] = (GLfloat)thisVector.x;
	this->X_Y_Z[1] = (GLfloat)thisVector.y;
	this->X_Y_Z[2] = (GLfloat)thisVector.z;
}

Vector Vector::truncateLength(float max_length)
{
	float max_length2 = max_length * max_length;
	float vecLength2 = this->returnLength() * this->returnLength();
	if(vecLength2 <= max_length2)
		return *this;
	else
		return (*this) * (max_length / sqrt(vecLength2));
}

void Vector::reset()
{
	
	startVector = initialStart;
	endVector = initialEnd;
}

void Vector::addVector(Vector * otherVector)
{
	thisVector.x += otherVector->thisVector.x;
	thisVector.y += otherVector->thisVector.y;
	thisVector.z += otherVector->thisVector.z;
	this->X_Y_Z[0] = (GLfloat)thisVector.x;
	this->X_Y_Z[1] = (GLfloat)thisVector.y;
	this->X_Y_Z[2] = (GLfloat)thisVector.z;
}

void Vector::addVector(Vector  &otherVector)
{
	thisVector.x += otherVector.thisVector.x;
	thisVector.y += otherVector.thisVector.y;
	thisVector.z += otherVector.thisVector.z;
	this->X_Y_Z[0] = (GLfloat)thisVector.x;
	this->X_Y_Z[1] = (GLfloat)thisVector.y;
	this->X_Y_Z[2] = (GLfloat)thisVector.z;
}

Vector Vector::addVec(Vector &v)
{
	return Vector(thisVector.x + v.thisVector.x,thisVector.y + v.thisVector.y, thisVector.z + v.thisVector.z);
}

Vector Vector::addVec(Vector *v)
{
	return Vector(thisVector.x + v->thisVector.x,thisVector.y + v->thisVector.y, thisVector.z + v->thisVector.z);
}

void Vector::subtractVector(Vector * otherVector)
{
	thisVector.x -= otherVector->thisVector.x;
	thisVector.y -= otherVector->thisVector.y;
	thisVector.z -= otherVector->thisVector.z;
	this->X_Y_Z[0] = (GLfloat)thisVector.x;
	this->X_Y_Z[1] = (GLfloat)thisVector.y;
	this->X_Y_Z[2] = (GLfloat)thisVector.z;
}

void Vector::subtractVector(Vector &otherVector)
{
	thisVector.x -= otherVector.thisVector.x;
	thisVector.y -= otherVector.thisVector.y;
	thisVector.z -= otherVector.thisVector.z;
	this->X_Y_Z[0] = (GLfloat)thisVector.x;
	this->X_Y_Z[1] = (GLfloat)thisVector.y;
	this->X_Y_Z[2] = (GLfloat)thisVector.z;
}

Vector Vector::subVector(Vector * otherVector)
{
	return Vector(thisVector.x - otherVector->thisVector.x,thisVector.y - otherVector->thisVector.y,thisVector.z - otherVector->thisVector.z);
}

Vector Vector::subVector(Vector &otherVector)
{
	return Vector(thisVector.x - otherVector.thisVector.x,thisVector.y - otherVector.thisVector.y,thisVector.z - otherVector.thisVector.z);
}

void Vector::multiplyVector(Matrix33 *mat)
{
	this->thisVector.x = (mat->matrix33[0][0] * this->thisVector.x) + (mat->matrix33[0][1] * this->thisVector.y) + (mat->matrix33[0][2] * this->thisVector.z);
	this->thisVector.y = (mat->matrix33[1][0] * this->thisVector.x) + (mat->matrix33[1][1] * this->thisVector.y) + (mat->matrix33[1][2] * this->thisVector.z);
	this->thisVector.z = (mat->matrix33[2][0] * this->thisVector.x) + (mat->matrix33[2][1] * this->thisVector.y) + (mat->matrix33[2][2] * this->thisVector.z);
	this->X_Y_Z[0] = (GLfloat)thisVector.x;
	this->X_Y_Z[1] = (GLfloat)thisVector.y;
	this->X_Y_Z[2] = (GLfloat)thisVector.z;
}

void Vector::multiplyVector(Matrix33 &mat)
{
	this->thisVector.x = (mat.matrix33[0][0] * this->thisVector.x) + (mat.matrix33[0][1] * this->thisVector.y) + (mat.matrix33[0][2] * this->thisVector.z);
	this->thisVector.y = (mat.matrix33[1][0] * this->thisVector.x) + (mat.matrix33[1][1] * this->thisVector.y) + (mat.matrix33[1][2] * this->thisVector.z);
	this->thisVector.z = (mat.matrix33[2][0] * this->thisVector.x) + (mat.matrix33[2][1] * this->thisVector.y) + (mat.matrix33[2][2] * this->thisVector.z);
	this->X_Y_Z[0] = (GLfloat)thisVector.x;
	this->X_Y_Z[1] = (GLfloat)thisVector.y;
	this->X_Y_Z[2] = (GLfloat)thisVector.z;
}

void Vector::multiplyVector(Quaternion *rotationQuat)
{
	Quaternion *vector = new Quaternion(this);
	Quaternion *rotationQuat_conjugate = new Quaternion(rotationQuat->conjugate());
	Quaternion *vectorNew = new Quaternion(vector->multiply(rotationQuat_conjugate));
	Quaternion *result = new Quaternion(rotationQuat->multiply(vectorNew));
	thisVector.x = result->x;
	thisVector.y = result->y;
	thisVector.z = result->z;
	this->X_Y_Z[0] = (GLfloat)thisVector.x;
	this->X_Y_Z[1] = (GLfloat)thisVector.y;
	this->X_Y_Z[2] = (GLfloat)thisVector.z;
	delete vector;
	delete rotationQuat_conjugate;
	delete vectorNew;
	delete result;
}

void Vector::multiplyVector(Quaternion &rotationQuat)
{
	Quaternion *vector = new Quaternion(this);
	Quaternion *rotationQuat_conjugate = new Quaternion(rotationQuat.conjugate());
	Quaternion *vectorNew = new Quaternion(vector->multiply(rotationQuat_conjugate));
	Quaternion *result = new Quaternion(rotationQuat.multiply(vectorNew));
	thisVector.x = result->x;
	thisVector.y = result->y;
	thisVector.z = result->z;
	this->X_Y_Z[0] = (GLfloat)thisVector.x;
	this->X_Y_Z[1] = (GLfloat)thisVector.y;
	this->X_Y_Z[2] = (GLfloat)thisVector.z;
	delete vector;
	delete rotationQuat_conjugate;
	delete vectorNew;
	delete result;
}

void Vector::multiplyVector(float scalar)
{
	thisVector.x *= scalar;
	thisVector.y *= scalar;
	thisVector.z *= scalar;
	this->X_Y_Z[0] = (GLfloat)thisVector.x;
	this->X_Y_Z[1] = (GLfloat)thisVector.y;
	this->X_Y_Z[2] = (GLfloat)thisVector.z;
}

float Vector::dotProduct(Vector *otherVector)
{
	return ( (thisVector.x * otherVector->thisVector.x) +
			 (thisVector.y * otherVector->thisVector.y) +
			 (thisVector.z * otherVector->thisVector.z) );
}

float Vector::dotProduct(Vector &otherVector)
{
	return ( (thisVector.x * otherVector.thisVector.x) +
			 (thisVector.y * otherVector.thisVector.y) +
			 (thisVector.z * otherVector.thisVector.z) );
}

float Vector::angle(Vector &other)
{
	float mag1 = this->returnLength();
	float mag2 = other.returnLength();
	float dot = this->dotProduct(&other);
	return (acos(dot/(mag1*mag2)));
}

Vector Vector::crossProduct(Vector &vec)
{
	return Vector( ( (this->thisVector.y)*(vec.thisVector.z) - (this->thisVector.z)*(vec.thisVector.y) ),
		           ( (this->thisVector.x)*(vec.thisVector.z) - (this->thisVector.z)*(vec.thisVector.x) ),
				   ( (this->thisVector.x)*(vec.thisVector.y) - (this->thisVector.y)*(vec.thisVector.x) ) );
} 

void Vector::updateVector(Matrix33 * rotationMatrix, Vector * translationVector)
{
}


/*******************************************
*                                          *
*		OVERLOADED OPERATORS               *
*                                          *
*******************************************/
Vector Vector::operator+(Vector &other)
{
	return this->addVec(other);
}

Vector Vector::operator-(Vector &other)
{
	return this->subVector(other);
}

Vector Vector::operator*(Matrix33 &other)
{
	Vector newV = *this;
	newV.multiplyVector(other);
	return newV;
}

Vector Vector::operator*(Quaternion &other)
{
	Vector newV = *this;
	newV.multiplyVector(other);
	return newV;
}

Vector Vector::operator*(float scalar)
{
	Vector newV = *this;
	newV.multiplyVector(scalar);
	return newV;
}

bool Vector::operator==(Vector &v)
{
	if(this->thisVector.x == v.thisVector.x || this->X_Y_Z[0] == v.X_Y_Z[0])
		if(this->thisVector.y == v.thisVector.y || this->X_Y_Z[1] == v.X_Y_Z[1])
			if(this->thisVector.z == v.thisVector.z || this->X_Y_Z[2] == v.X_Y_Z[2])
				return true;

	return false;
}

void Vector::LERP(const Vector &v1, const Vector &v2,double deltaT)
{
	double deltaT2 = 1.0-deltaT;
	this->thisVector.x = (v1.thisVector.x *deltaT2) + (v2.thisVector.x *deltaT);
	this->thisVector.y = (v1.thisVector.y *deltaT2) + (v2.thisVector.y *deltaT);
	this->thisVector.z = (v1.thisVector.z *deltaT2) + (v2.thisVector.z *deltaT);
	this->X_Y_Z[0] = (GLfloat)thisVector.x;
	this->X_Y_Z[1] = (GLfloat)thisVector.y;
	this->X_Y_Z[2] = (GLfloat)thisVector.z;
}

void Vector::LERP(const Vector *v1, const Vector *v2,double deltaT)
{
	double deltaT2 = 1.0-deltaT;
	this->thisVector.x = (v1->thisVector.x *deltaT2) + (v2->thisVector.x *deltaT);
	this->thisVector.y = (v1->thisVector.y *deltaT2) + (v2->thisVector.y *deltaT);
	this->thisVector.z = (v1->thisVector.z *deltaT2) + (v2->thisVector.z *deltaT);
	this->X_Y_Z[0] = (GLfloat)thisVector.x;
	this->X_Y_Z[1] = (GLfloat)thisVector.y;
	this->X_Y_Z[2] = (GLfloat)thisVector.z;
}

void Vector::SLERP(Vector& v1,Vector& v2,Vector& v3,Vector& v4, double deltaT)
{
	double deltaT2 = deltaT * deltaT;
	double deltaT3 = deltaT * deltaT2;
	*this = ( 
		(v2 * 2)  + 
		(((v1 * (-1))+v3) * deltaT)+
		(((v1*2)-(v2*5)+(v3*4) - v4)*deltaT2)+
		(((v1*(-1))+(v2*3)-(v3*3) + v4)*deltaT3)
		) * 0.5;
	/**this = (v1 * ((-0.5 * deltaT3)+(deltaT2)-(0.5*deltaT))) +
			(v2 * ((1.5*deltaT3) + (2.5*deltaT2) + 1)) +
			(v3 * ((-1.5*deltaT3) + (2.0*deltaT2) + (0.5*deltaT))) +
			(v4 * ((0.5*deltaT3) - (0.5*deltaT2)));*/
		/*this->thisVector.x = (v1.thisVector.x*deltaT3) + (v2.thisVector.x*deltaT2) + (v3.thisVector.x*deltaT) + v4.thisVector.x;
	this->thisVector.y = (v1.thisVector.y*deltaT3) + (v2.thisVector.y*deltaT2) + (v3.thisVector.y*deltaT) + v4.thisVector.y;
	this->thisVector.z = (v1.thisVector.z*deltaT3) + (v2.thisVector.z*deltaT2) + (v3.thisVector.z*deltaT) + v4.thisVector.z;*/
	this->X_Y_Z[0] = (GLfloat)thisVector.x;
	this->X_Y_Z[1] = (GLfloat)thisVector.y;
	this->X_Y_Z[2] = (GLfloat)thisVector.z;
}

void Vector::BezSLERP(Vector& v1,Vector& v2,Vector& v3,Vector& v4, double deltaT)
{
	double deltaT2 = deltaT * deltaT;
	double deltaT3 = deltaT * deltaT2;
	double dT = 1-deltaT;
	double dT2 = dT * dT;
	double dT3 = dT* dT2;

	*this = (
		(v1 * dT3) + 
	   ((v2 * deltaT) * 3 * dT2) +
	   ((v3 * deltaT2)  * 3 * dT) +
	   (v4 * deltaT3)
		);
}

float Vector::speedControl_SLERP(Vector& v1,Vector& v2,Vector& v3,Vector& v4)
{
	Vector current = *this;
	Vector prev;
	Vector temp;
	float distance;
	float totalDistance = 0;

	for (int f=0; f<120; f++)
	{
		prev=current;
		current.SLERP(v1, v2, v3, v4, f/120.0);
		temp=current.subVector(prev);
		distance=temp.returnLength();
		totalDistance+=distance;
	}

	return totalDistance;
}

float Vector::speedControl_BezSLERP(Vector& v1,Vector& v2,Vector& v3,Vector& v4)
{
	Vector current = *this;
	Vector prev;
	Vector temp;
	float distance;
	float totalDistance = 0;

	for (int f=0; f<60; f++)
	{
		prev=current;
		current.BezSLERP(v1, v2, v3, v4, f/60.0);
		temp=current.subVector(prev);
		distance=temp.returnLength();
		totalDistance+=distance;
	}

	return totalDistance;
}

Vector::~Vector()
{

}