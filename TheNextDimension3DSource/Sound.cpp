#include "Sound.h"

FMOD_SYSTEM* Sound::system = NULL;
FMOD_RESULT* Sound::result = NULL;

Sound::Sound(const char *file, int _mode,Vector &_pos, Vector&_vel, FMOD_SYSTEM *_system, FMOD_RESULT &_result)
{
	system = _system;
	result = &_result;
	if(_mode > 1)
	{
		mode =_mode = 0;
	}else
	{
		mode = _mode;
	}
	
	switch(_mode)
	{
	case SOUND:
		*result = FMOD_System_CreateSound(system, file, FMOD_DEFAULT, 0, &sound);
		this->setSoundMode(FMOD_LOOP_OFF);
		break;
	case STREAM:
		*result =  FMOD_System_CreateStream(system, file, FMOD_DEFAULT, 0,&sound);
		this->setSoundMode(FMOD_LOOP_NORMAL);
		break;
	}
	ERRCHECK();

	pos = &_pos;
	vel = &_vel;

	f_pos.x = pos->X_Y_Z[0];
	f_pos.y = pos->X_Y_Z[1];
	f_pos.z = pos->X_Y_Z[2];

	f_vel.x = vel->X_Y_Z[0];
	f_vel.y = vel->X_Y_Z[1];
	f_vel.z = vel->X_Y_Z[2];

	//*result = channel->set3DAttributes(&f_pos,&f_vel);
	*result = FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sound, true, &channel);
	ERRCHECK();
	*result = FMOD_Channel_Set3DAttributes(channel,&f_pos,&f_vel);
	ERRCHECK();
	*result = FMOD_Channel_SetPaused(channel, true);
	ERRCHECK();
}

Sound::Sound(const char *file, int _mode,Vector &_pos, Vector&_vel)
{
	if(_mode > 1)
	{
		mode =_mode = 0;
	}else
	{
		mode = _mode;
	}

	switch(_mode)
	{
	case SOUND:
		*result = FMOD_System_CreateSound(system, file, FMOD_DEFAULT, 0, &sound);
		this->setSoundMode(FMOD_LOOP_OFF);
		break;
	case STREAM:
		*result =  FMOD_System_CreateStream(system, file, FMOD_DEFAULT, 0,&sound);
		this->setSoundMode(FMOD_LOOP_NORMAL);
		break;
	}

	pos = &_pos;
	vel = &_vel;

	f_pos.x = pos->X_Y_Z[0];
	f_pos.y = pos->X_Y_Z[1];
	f_pos.z = pos->X_Y_Z[2];

	f_vel.x = vel->X_Y_Z[0];
	f_vel.y = vel->X_Y_Z[1];
	f_vel.z = vel->X_Y_Z[2];

	//*result = channel->set3DAttributes(&f_pos,&f_vel);
	*result = FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sound, true, &channel);
	ERRCHECK();
	*result = FMOD_Channel_Set3DAttributes(channel,&f_pos,&f_vel);
	ERRCHECK();
	*result = FMOD_Channel_SetPaused(channel, true);
	ERRCHECK();
}

Sound::Sound(const Sound &_sound)
{
	//FMOD_SOUND *temp = *&_sound.sound;
	this->sound = *&_sound.sound;
	f_pos = _sound.f_pos;
	f_vel = _sound.f_vel;
	*result = FMOD_Channel_Set3DAttributes(channel,&f_pos,&f_vel);
	ERRCHECK();
	*result = FMOD_Channel_SetPaused(channel, true);
	ERRCHECK();

	pos = new Vector(_sound.pos->X_Y_Z[0],_sound.pos->X_Y_Z[1],_sound.pos->X_Y_Z[2]);
	vel = new Vector(_sound.vel->X_Y_Z[0],_sound.vel->X_Y_Z[1],_sound.vel->X_Y_Z[2]);
}


void Sound::ERRCHECK()
{
	if (*result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(*result));
    }
}

void Sound::setSoundMode(FMOD_MODE mode)
{	
	*result = FMOD_Sound_SetMode(sound, mode);
	ERRCHECK();
}

void Sound::setChannelMode(FMOD_MODE mode)
{	
	*result = FMOD_Channel_SetMode(channel, mode);
	ERRCHECK();
}

void Sound::set3DMinMaxDist(float min, float max)
{
	*result = FMOD_Sound_Set3DMinMaxDistance(sound,min,max);
	ERRCHECK();
	*result = FMOD_Channel_Set3DMinMaxDistance(channel,min,max);
	ERRCHECK();
}

void Sound::play(Vector &position)
{
	pos = &position;
	f_pos.x = pos->X_Y_Z[0];
	f_pos.y = pos->X_Y_Z[1];
	f_pos.z = pos->X_Y_Z[2];

	f_vel.x = vel->X_Y_Z[0];
	f_vel.y = vel->X_Y_Z[1];
	f_vel.z = vel->X_Y_Z[2];
	
	*result = FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sound, false, &channel);
	ERRCHECK();
	*result = FMOD_Channel_Set3DAttributes(channel,&f_pos,&f_vel);
	ERRCHECK();
}

void Sound::pause()
{
	//this->channel->setPaused(true);
	*result = FMOD_Channel_SetPaused(channel,true);
	ERRCHECK();
}

void Sound::unpause()
{
	//this->channel->setPaused(false);
	*result = FMOD_Channel_SetPaused(channel,false);
	ERRCHECK();
}

void Sound::update()
{
	f_pos.x = pos->X_Y_Z[0];
	f_pos.y = pos->X_Y_Z[1];
	f_pos.z = pos->X_Y_Z[2];

	f_vel.x = vel->X_Y_Z[0];
	f_vel.y = vel->X_Y_Z[1];
	f_vel.z = vel->X_Y_Z[2];

	//*result = channel->set3DAttributes(&f_pos,&f_vel);
	*result = FMOD_Channel_Set3DAttributes(channel,&f_pos,&f_vel);
	ERRCHECK();
}

Sound::~Sound(void)
{
	*result = FMOD_Sound_Release(sound);
    ERRCHECK();
}
