#include "Listener.h"

FMOD_SYSTEM * Listener::system = NULL;
FMOD_RESULT * Listener::result = NULL;

Listener::Listener(Vector &_pos, Vector &_vel, Vector &_up,
					Vector &_right, Vector &_dir, FMOD_SYSTEM *_system, FMOD_RESULT &_result)
{
	system = _system;
	result = &_result;
	pos = &_pos;
	vel = &_vel;
	up = &_up;
	right = &_right;
	dir = &_dir;
	*result = FMOD_System_Set3DListenerAttributes(system, 0, &f_pos, &f_vel, &f_dir, &f_up);
    ERRCHECK();
}

Listener::Listener(Vector &_pos, Vector &_vel, Vector &_up,
					Vector &_right, Vector &_dir)
{
	pos = &_pos;
	vel = &_vel;
	up = &_up;
	right = &_right;
	dir = &_dir;
	*result = FMOD_System_Set3DListenerAttributes(system, 0, &f_pos, &f_vel, &f_dir, &f_up);
    ERRCHECK();
}

void Listener::update()
{
	f_pos.x = pos->X_Y_Z[0];
	f_pos.y = pos->X_Y_Z[1];
	f_pos.z = pos->X_Y_Z[2];

	f_vel.x = vel->X_Y_Z[0];
	f_vel.y = vel->X_Y_Z[1];
	f_vel.z = vel->X_Y_Z[2];

	f_up.x = up->X_Y_Z[0];
	f_up.y = up->X_Y_Z[1];
	f_up.z = up->X_Y_Z[2];

	f_right.x = right->X_Y_Z[0];
	f_right.y = right->X_Y_Z[1];
	f_right.z = right->X_Y_Z[2];

	f_dir.x = dir->X_Y_Z[0];
	f_dir.y = dir->X_Y_Z[1];
	f_dir.z = dir->X_Y_Z[2];

	*result = FMOD_System_Set3DListenerAttributes(system, 0, &f_pos, &f_vel, &f_dir, &f_up);
    ERRCHECK();
}

void Listener::ERRCHECK()
{
	if (*result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(*result));
    }
}

Listener::~Listener(void)
{
}
