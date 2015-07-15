#pragma once
#include <FMOD\fmod.h>
#include <FMOD\fmod.hpp>
#include <FMOD\fmod_errors.h>
#include "Vector.h"

class Listener
{
public:
	Listener(Vector &pos, Vector &vel, Vector &up, Vector &right,
		Vector &dir, FMOD_SYSTEM *_system, FMOD_RESULT &_result);

	Listener(Vector &_pos, Vector &_vel, Vector &_up,
					Vector &_right, Vector &_dir);

	~Listener(void);

	void update();
	void ERRCHECK();

	FMOD_VECTOR f_pos, f_vel, f_up, f_right, f_dir;
	Vector *pos;
	Vector *vel;
	Vector *up;
	Vector *right;
	Vector *dir;
	static FMOD_SYSTEM *system;
	static FMOD_RESULT *result;
};

