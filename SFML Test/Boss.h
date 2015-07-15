#pragma once
#include "EnemyBase.h"
#include "ParticlePoint.h"
#include "Sound.h"
#include <iostream>
#include <ctime>
using namespace std;

//enum //STATE
//{
//	SEEK = 0,
//	WANDER,
//	FLEE,
//	REPEL
//};
//
//enum //SUBSTATES
//{
//	SEEK_PLAYER = 0,
//	SEEK_ENEMY,
//	SEEK_POINT,
//	FLEE_PLAYER,
//	FLEE_ENEMY,
//	FLEE_POINT,
//	SUB_WANDER,
//	REPEL_ENEMY,
//	REPEL_PLAYER,
//	REPEL_POINT
//};
//
//enum
//{
//	ENEMY_SPACE = 0,
//	ENEMY_OCEAN,
//	ENEMY_DESERT,
//	ENEMY_TROPICAL,
//	ENEMY_ICE,
//	ENEMY_LAVA
//};

enum //BOSS PHASES
{
	NEUTRAL = 0,
	PHASE1,
	PHASE2,
	PHASE3
};

class Boss : public Model
{
public:
	Boss(string filename, int h) : Model(filename)
	{
		phase = PHASE1;
		health = h;
		fullHealth = health;
		randomTarg = bulletSlerpSpeed = 1;
		prevTargSelect = lerpDeltaT = angle = deltaT = 0;
		this->velocity = Vector(0,1,0);
		position = Vector(0,0,0);

		lerpTarget[0] = Vector(0,0,0);
		lerpTarget[1] = Vector(100,0,0);
		lerpTarget[2] = Vector(50,100,0);
		lerpTarget[3] = Vector(-50,100,0);
		lerpTarget[4] = Vector(-100,0,0);
		lerpTarget[5] = Vector(-50,-100,0);
		lerpTarget[6] = Vector(50,-100,0);
	}
	void setSeekTarget(Player *target)
	{pTarget = target;};
	void setSeekTarget(EnemyBase *target)
	{eTarget = target;};
	void setSeekTarget(Vector &target)
	{pointTarget = target;};
	~Boss();

	void update();
	void seek();
	void flee();
	void wander();
	void repel();

	void morph();
	void render();

	void shoot(Model &);
	void shootParticle(Model &);

	int phase;
	Model *target1, *target2;
	float deltaT;
	Vector p[6];
	Vector pb[6];
	vector <Particle*> bullets;
	vector <Particle*> bullets2;
	int num[3];
	int numb[3];

	vector <Model*> Bullets;
	vector <ParticlePoint*> particleBullet;
	int fullHealth;
	float health;

	float max_force, max_speed, mass;
	float wanderAngle, wanderChange;
	Vector desiredVel;
	Vector wanderForce;
	Quaternion *angleWander;

	Player *pTarget;
	EnemyBase *eTarget;
	Vector pointTarget;
	
	int state, substate;
	int ID;

private:
	Vector origin[6];
	Vector bulletAccel;
	float morphSpeed;
	float bulletSlerpSpeed;
	float angle;
	Vector lerpTarget[7];
	double lerpDeltaT; 
	int prevTargSelect;
	int randomTarg;
};

