#pragma once
#include <FMOD\fmod.h>
#include <FMOD\fmod.hpp>
#include <FMOD\fmod_errors.h>
#include <iostream>
using namespace std;

class SoundEngine
{
public:
	SoundEngine(void);
	void update();
	~SoundEngine(void);
	void set3DSettings(float dopplerScale,float distFactor, float rolloffscale);
	FMOD_SYSTEM *system;
	FMOD_RESULT result;
private:
	void ERRCHECK();
	int numdrivers;
	FMOD_CAPS caps;//capabilities of sound card
	FMOD_SPEAKERMODE speakermode;//windows speakermode eg. stereo
};

