#include "Spring.h"
Spring::Spring()
{

}

Spring::Spring(float _stiffness, float _damping_factor, Vector &begin, Vector &end)
{
	stiffness = _stiffness;
	damping_factor = _damping_factor;
	Vector temp = end.subVector(begin);
	current_length = original_length = temp.returnLength();
	prev_end = end;
}

Vector Spring::update(Vector &begin, Vector &end)
{
	Vector temp = end.subVector(begin);
	current_length = temp.returnLength();
	float length_diff = (current_length - original_length);
	temp.normalize();
	temp.multiplyVector((-1)*stiffness*length_diff);

	Vector velocity = end.subVector(prev_end);
	if(damping_factor)
	{
		velocity.multiplyVector((-1)*damping_factor);
	}
	prev_end = end;
	//velocity.multiplyVector(0.1);
	temp.addVector(velocity);
	temp.multiplyVector(0.1);
	return temp;
}


Spring::~Spring(void)
{
}
