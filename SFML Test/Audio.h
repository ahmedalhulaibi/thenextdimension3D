#pragma once
#ifndef NUM_CHANNELS
#define NUM_CHANNELS 50
#endif
#include <FMOD\fmod.hpp>

class Audio
{
public:
	FMOD::System *fmodSystem; 
	FMOD_RESULT result;

	char name[256];

	FMOD::Channel *channel;

	//Sound Objects
	FMOD::Sound *soundtrack1;  //Level 1 Done
	FMOD::Sound *soundtrack2;
	FMOD::Sound *soundtrack3;
	FMOD::Sound *soundtrack4;
	FMOD::Sound *soundtrack5;
	FMOD::Sound *soundtrack6;
	FMOD::Sound *bullet1;     //Player Bullets Done
	FMOD::Sound *water;
	FMOD::Sound *fire;
	FMOD::Sound *timeFreeze;
	FMOD::Sound *gravityBomb;
	FMOD::Sound *enemyDeath;  //Bomb Done
	FMOD::Sound *enterPortal;
	FMOD::Sound *bossDeath; //Boing
	FMOD::Sound *playerDeath;
	FMOD::Sound *speedup;
	FMOD::Sound *healthDrop; //Chime
	FMOD::Sound *powerPickup; //Cuckoo

	void initializeSound();
	void updateSound();
	void loadSounds();

	//intializing Sound Play Fucntions
	void playSoundtrack1();
	void playSoundtrack2();
	void playSoundtrack3();
	void playSoundtrack4();
	void playSoundtrack5();
	void playSoundtrack6();
	void playBullet1();
	void playWater();
	void playFire();
	void playEnemyDeath();
	void playEnterPortal();
	void playBossDeath();
	void playPlayerDeath();
	void playGravityBomb();
	void playTimeFreeze();
	void playSpeedup();
	void playHealthDrop();
	void playPowerPickup();

};

