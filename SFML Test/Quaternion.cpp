#include "Quaternion.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Quaternion::Quaternion(void)
{
	w = 1.0f;
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

//Quaternion::Quaternion(const Quaternion &q)
//{
//	this->w = q.w;
//	this->x = q.x;
//	this->y = q.y;
//	this->z = q.z;
//}
//
Quaternion::Quaternion(const Quaternion *q)
{
	this->w = q->w;
	this->x = q->x;
	this->y = q->y;
	this->z = q->z;
}

Quaternion::Quaternion(Vector *vector)
{
	w = 1.f;
	x = vector->thisVector.x;
	y = vector->thisVector.y;
	z = vector->thisVector.z;
}
Quaternion::Quaternion(Vector &vector)
{
	w = 1.f;
	x = vector.thisVector.x;
	y =  vector.thisVector.y;
	z =  vector.thisVector.z;
}
Quaternion::Quaternion(float radians, bool _x, bool _y, bool _z)
{	
	radians = radians/2;
	if(_x)
	{
		w =  cos(radians);
		x =  sin(radians);
		y = 0.0f;
		z = 0.0f;
	}
	else if(_y)
	{
		w =  cos(radians);
		x = 0.0f;
		y =  sin(radians);
		z = 0.0f;
	}
	else if(_z)
	{
		w =  cos(radians);
		x = 0.0f;
		y = 0.0f;
		z =	 sin(radians);
	}
}

Quaternion::Quaternion(float radians, Vector *vector)
{
	radians = radians/2;
	w =  cos(radians);
	x =  (vector->thisVector.x * sin(radians));
	y =  (vector->thisVector.y * sin(radians));
	z =  (vector->thisVector.z * sin(radians));
}
Quaternion::Quaternion(float radians, Vector &vector)
{
	radians = radians/2;
	w =  cos(radians);
	x =  (vector.thisVector.x * sin(radians));
	y =  (vector.thisVector.y * sin(radians));
	z =  (vector.thisVector.z * sin(radians));
}

Quaternion::Quaternion(float _w, float _x, float _y, float _z)
{
	w =  _w;
	x =  _x;
	y =  _y;
	z =  _z;
}

Quaternion Quaternion::multiply(Quaternion *other)
{
	Quaternion result;
	result.w = (this->w * other->w) - (this->x * other->x) - (this->y * other->y) - (this->z * other->z);
	result.x = (this->w * other->x) + (this->x * other->w) + (this->y * other->z) - (this->z * other->y);
	result.y = (this->w * other->y) - (this->x * other->z) + (this->y * other->w) + (this->z * other->x);
	result.z = (this->w * other->z) + (this->x * other->y) - (this->y * other->x) + (this->z * other->w);
	return result;
}

Quaternion Quaternion::multiply(Quaternion &other)
{
	Quaternion result;
	result.w = (this->w * other.w) - (this->x * other.x) - (this->y * other.y) - (this->z * other.z);
	result.x = (this->w * other.x) + (this->x * other.w) + (this->y * other.z) - (this->z * other.y);
	result.y = (this->w * other.y) - (this->x * other.z) + (this->y * other.w) + (this->z * other.x);
	result.z = (this->w * other.z) + (this->x * other.y) - (this->y * other.x) + (this->z * other.w);
	return result;
}
Quaternion Quaternion::multiply(float scale)
{
	return Quaternion(this->w *scale,this->x * scale, this->y * scale, this->z * scale);
}
void Quaternion::scale(float scale)
{
	w *= scale;
	x *= scale;
	y *= scale;
	z *= scale;
}

Quaternion Quaternion::add(Quaternion *other)
{
	Quaternion result;
	result.w = this->w + other->w;
	result.x = this->x + other->x;
	result.y = this->y + other->y;
	result.z = this->z + other->z;

	return result;
}

Quaternion Quaternion::add(Quaternion &other)
{
	Quaternion result;
	result.w = this->w + other.w;
	result.x = this->x + other.x;
	result.y = this->y + other.y;
	result.z = this->z + other.z;

	return result;
}

Quaternion Quaternion::subtract(Quaternion *other)
{
	Quaternion result;
	result.w = this->w - other->w;
	result.x = this->x - other->x;
	result.y = this->y - other->y;
	result.z = this->z - other->z;

	return result;
}

Quaternion Quaternion::subtract(Quaternion &other)
{
	Quaternion result;
	result.w = this->w - other.w;
	result.x = this->x - other.x;
	result.y = this->y - other.y;
	result.z = this->z - other.z;

	return result;
}

float Quaternion::dotProduct(Quaternion *other)
{
	return( (this->w*other->w) + (this->x*other->x) + (this->y*other->y) + (this->z*other->z) );
}

float Quaternion::dotProduct(Quaternion &other)
{
	return( (this->w*other.w) + (this->x*other.x) + (this->y*other.y) + (this->z*other.z) );
}

float Quaternion::dotAngle(Quaternion *other)
{
	float mag1 = this->returnLength();
	float mag2 = other->returnLength();
	float dot = this->dotProduct(other);

	return (acos(dot/(mag1*mag2))); 
}

float Quaternion::dotAngle(Quaternion &other)
{
	float mag1 = this->returnLength();
	float mag2 = other.returnLength();
	float dot = this->dotProduct(other);
	return (acos(dot/(mag1*mag2)));
}

float Quaternion::returnLength()
{
	return sqrt(pow(w,2) + pow(x,2) + pow(y,2) + pow(z,2));
}

void Quaternion::normalize()
{
	float div = this->returnLength();
	w = w/div;
	x = x/div;
	y = y/div;
	z = z/div;
}

Quaternion Quaternion::conjugate()
{
	return Quaternion(this->w,(-1) * this->x,(-1) * this->y,(-1) * this->z);
}

Quaternion Quaternion::LERP(Quaternion q1,Quaternion q2,float deltaT)
{
	float deltaT2 = 1.0-deltaT;
	q1.scale(deltaT2);
	q2.scale(deltaT);
	return q1.add(q2);
}


Quaternion Quaternion::SLERP(Quaternion p0, Quaternion p1 , float deltaT)
{
	float cosHalfTheta = p0.dotProduct(p1);
	float sinHalfTheta, halfTheta;
	/*if(abs(cosHalfTheta) >= 1.0)
	{
		return p0;
	}*/
	halfTheta = acos(cosHalfTheta);
	sinHalfTheta = sqrt(1.0 - pow(cosHalfTheta,2));
	/*if(abs(sinHalfTheta) < 0.001)
	{
		p0.scale(1-deltaT);
		p1.scale(deltaT);
		return p0.add(p1);
	}*/
	float var1 = (sin((1-deltaT) * halfTheta))/(sin(sinHalfTheta));
	float var2 = (sin(halfTheta*deltaT))/(sin(sinHalfTheta));
	p0.scale(var1);	p1.scale(var2);
	return p0.add(p1);
}


bool Quaternion::operator==(Quaternion &q)
{
	if(this->w == q.w)
		if(this->x == q.x)
			if(this->y == q.y)
				if(this->z == q.z)
					return true;

	return false;
}



Quaternion::~Quaternion(void)
{
}
