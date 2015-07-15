#pragma once
#include <iostream>
#include "Vector.h"
using namespace std;
/*specifically a spring for camera
  to initialize one properly:
  new Spring(any num,any num, what camera is looking at, camera's position)
  then every frame call spring->update() this will move the camera accordingly

*/
class Spring
{
public:
	Spring();
	Spring(float _stiffness, float _damping_factor, Vector &_begin, Vector &_end);
	~Spring(void);
	Vector update(Vector &_begin, Vector &_end);
	float original_length;
	float current_length;
	float stiffness;
	float damping_factor;
	//Vector begin;//where spring is attached, this could be the
	//Vector end;//where the other end of the spring is
	Vector prev_end;
};

