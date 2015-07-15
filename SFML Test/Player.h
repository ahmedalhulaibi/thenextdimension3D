#pragma once
#include "Vector.h"
#include "Quaternion.h"
#include "Matrix44.h"
#include "Model.h"
#include "IL\il.h"
#include "IL\ilu.h"
#include "IL\ilut.h"
#include "Particle.h"
#include "ParticlePoint.h"
#include "Powerup.h"
#include "Listener.h"
#include "Sound.h"
#include <vector>
using namespace std;

class Player : public Model
{
public:
	Player(string filename) : Model(filename)
	{
		accelWeight = 0.2;
		boostFuel = 100;
		health = 100;
		shield = 100;
		waterFuel = 100;
		flamethrowerFuel = 100;
		this->position = Vector(0,0,0);
		this->directionVec = Vector(1,0,0);
		deltaT = morphTargNum = 0;
		shieldActive = false;
	};

	void setVel(bool up, bool down, bool left, bool right);

	void render();
	void morph();
	void setMorphTargets(Model &straight, Model &left, Model &right)
	{
		morphTargets[0] = &straight;
		morphTargets[1] = &left;
		morphTargets[2] = morphTargets[0];
		morphTargets[3] = &right;
	};
	void update(float dT)
	{
		acceleration.multiplyVector(dT+0.1);
		velocity.addVector(acceleration);
		velocity = velocity.truncateLength(accelWeight + 0.7);
		position.addVector(velocity);
		listener->update();
	};

	void fireBullet(Vector &, Model &);//used for regular bullets 
	void fireMissiles(Vector &, Model &);//used for missiles
	void sprayWater(Vector, Model &);//to be used for water spray 
	void flamethrower(Vector, Model &);//used for flamethrower
	/*void fireEmitter(Vector);*/
	void bomb(Vector &, Model &);
	~Player(void);

	Model *morphTargets[16];
	float deltaT;
	int morphTargNum;


	float accelWeight;
	float maxSpeed;
	
	float width;
	float height;

	float health, boostFuel, waterFuel, flamethrowerFuel, shield;
	bool shieldActive;
	vector <Particle *> bullets;
	vector <Particle *> missiles;
	vector <Particle *> water;
	vector <Particle *> fire;
	vector <ParticlePoint *> waterP;
	vector <ParticlePoint *> fireP;

	vector <Particle *> bombs;

	vector <int> powerups;

	Listener *listener;
	Vector listenerUp, listenerRight, listenerDir;
	Sound *shooting_sound;

};

