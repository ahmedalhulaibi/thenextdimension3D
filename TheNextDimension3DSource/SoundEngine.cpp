#include "SoundEngine.h"


SoundEngine::SoundEngine(void)
{
	result = FMOD_System_Create(&system);
	this->ERRCHECK();
	result = FMOD_System_GetDriverCaps(system, 0, &caps, 0, &speakermode);
    ERRCHECK();
	if(result == FMOD_OK)
	{
		result = FMOD_System_SetSpeakerMode(system, FMOD_SPEAKERMODE_STEREO);
        this->ERRCHECK();
		result = FMOD_System_Init(system, 100, FMOD_INIT_NORMAL, NULL); 
		ERRCHECK();
	}else if (result == FMOD_ERR_OUTPUT_CREATEBUFFER)         /* Ok, the speaker mode selected isn't supported by this soundcard.  Switch it back to stereo... */
    {
        result = FMOD_System_SetSpeakerMode(system, FMOD_SPEAKERMODE_STEREO);
        this->ERRCHECK();
            
       result = FMOD_System_Init(system, 100, FMOD_INIT_NORMAL, NULL);/* ... and re-init. */
       this-> ERRCHECK();
    }
	result = FMOD_System_Set3DSettings(system, 1.0, 1.0/*1 meter*/, 1.0f);
    this->ERRCHECK();
}
void SoundEngine::ERRCHECK()
{
	if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
    }
}

void SoundEngine::update()
{
	result = FMOD_System_Update(system);
	ERRCHECK();
}

SoundEngine::~SoundEngine(void)
{
	result = FMOD_System_Close(system);
    ERRCHECK();
    result = FMOD_System_Release(system);
    ERRCHECK();
}
