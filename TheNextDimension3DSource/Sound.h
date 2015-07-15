#pragma once
#include <FMOD\fmod.h>
#include <FMOD\fmod.hpp>
#include <FMOD\fmod_errors.h>
#include <iostream>
#include "Vector.h"

using namespace std;

enum{
	SOUND = 0,
	STREAM
};

class Sound
{
public:
	Sound(const char *file, int mode, Vector &_pos, Vector&_vel,FMOD_SYSTEM *_system, FMOD_RESULT &_result);
	Sound(const char *file, int mode, Vector &_pos, Vector&_vel);
	Sound(const Sound &_sound);
	void setSoundMode(FMOD_MODE mode);
	void setChannelMode(FMOD_MODE mode);
	void set3DMinMaxDist(float min, float max);
	void play(Vector&position);
	void pause();
	void unpause();
	void update();

	static FMOD_SYSTEM *system;
	static FMOD_RESULT *result;

	/*FMOD::Sound*/FMOD_SOUND *sound;
	/*FMOD::Channel*/FMOD_CHANNEL *channel;

	FMOD_VECTOR f_pos;
	FMOD_VECTOR f_vel;
	Vector *pos;
	Vector *vel;
	int mode;	
	~Sound(void);
private:

	void ERRCHECK();
};

