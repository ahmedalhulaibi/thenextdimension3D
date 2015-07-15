#include "Audio.h"

void Audio::initializeSound()
{
	result = System_Create(&fmodSystem);
	result = fmodSystem->init(NUM_CHANNELS, FMOD_INIT_NORMAL, 0);
}

void Audio::updateSound()
{
	result = fmodSystem->update();
}

void Audio::loadSounds()
{
	result = fmodSystem->createSound("sounds/Pew_Pew.wav", FMOD_DEFAULT, 0, &bullet1);
	bullet1->setMode (FMOD_LOOP_OFF);

	result = fmodSystem->createStream("sounds/Background_Music.wav", FMOD_DEFAULT, 0, &soundtrack1);
	soundtrack1->setMode(FMOD_LOOP_NORMAL);

	result = fmodSystem->createSound("sounds/Blast_1.wav", FMOD_DEFAULT, 0, &enemyDeath);
	enemyDeath->setMode(FMOD_LOOP_OFF);

	result = fmodSystem->createSound("sounds/Boing_1.wav", FMOD_DEFAULT, 0, &bossDeath);
	bossDeath->setMode(FMOD_LOOP_OFF);

	result = fmodSystem->createSound("sounds/Chime.wav", FMOD_DEFAULT, 0, &healthDrop);
	healthDrop->setMode(FMOD_LOOP_OFF);

	result = fmodSystem->createSound("sounds/Cuckoo_1.wav", FMOD_DEFAULT, 0, &powerPickup);
	powerPickup->setMode(FMOD_LOOP_OFF);
}

void Audio::playBullet1()
{
	result = fmodSystem->playSound(FMOD_CHANNEL_FREE, bullet1, false, &channel);
	
}

void Audio::playSoundtrack1()
{
	result = fmodSystem->playSound(FMOD_CHANNEL_FREE, soundtrack1, false, &channel);
}

void Audio::playEnemyDeath()
{
	result = fmodSystem->playSound(FMOD_CHANNEL_FREE, enemyDeath, false, &channel);
}

void Audio::playBossDeath()
{
	result = fmodSystem->playSound(FMOD_CHANNEL_FREE, bossDeath, false, &channel);
}

void Audio::playHealthDrop()
{
	result = fmodSystem->playSound(FMOD_CHANNEL_FREE, healthDrop, false, &channel);
}

void Audio::playPowerPickup()
{
	result = fmodSystem->playSound(FMOD_CHANNEL_FREE, powerPickup, false, &channel);
}