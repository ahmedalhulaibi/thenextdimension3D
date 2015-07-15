#pragma once
#include "Player.h"
#include <OpenGL\glew.h>
//#include "glmObjLoader.h"
//#include "Texture.h"
using namespace std;

enum //STATE
{
	SEEK = 0,
	WANDER,
	FLEE,
	REPEL
};

enum //SUBSTATES
{
	SEEK_PLAYER = 0,
	SEEK_ENEMY,
	SEEK_POINT,
	FLEE_PLAYER,
	FLEE_ENEMY,
	FLEE_POINT,
	SUB_WANDER,
	REPEL_ENEMY,
	REPEL_PLAYER,
	REPEL_POINT
};

enum
{
	ENEMY_SPACE = 0,
	ENEMY_OCEAN,
	ENEMY_DESERT,
	ENEMY_TROPICAL,
	ENEMY_ICE,
	ENEMY_LAVA
};

class EnemyBase
{
public:
	EnemyBase(int enemyID)/*:Model(filename)*/
	/*{
		health = 1;
		lerpSpeed = 10;
		angle = wanderAngle = lerpDT = 0;
		newQ = Quaternion();
		angleWander = new Quaternion();
		seekPos = Vector();
		this->directionVec = Vector(1,0,0);
		wanderChange = 0.3;
		max_speed = 0.6;
		mass = 10;
		setScale(0.25, 0.25, 0.25);
		state = SEEK;
		substate = SEEK_POINT;
		ID = 0;
		prevPos = Vector(0,0,0);
	}*/;
	void render();
	void fire();
	void seek();
	void flee();
	void wander();
	void repel();
	/*void orientSLERP(Player *);*/
	void fire(Player *);//checks if player is within fov
	void setSeekTarget(Player *target)
	{pTarget = target;};
	void setSeekTarget(EnemyBase *target)
	{eTarget = target;};
	void setSeekTarget(Vector &target)
	{pointTarget = target;};
	void update(float dT)
	{
		if(state == SEEK)
		{
			seek();
		}else if(state == FLEE)
		{
			flee();
		}else if(state == WANDER)
		{
			wander();
		}else if(state == REPEL)
		{
			repel();
		}
		prevPos = position;
		acceleration.multiplyVector(dT + 0.7);
		this->velocity.addVector(acceleration);
		//velocity.multiplyVector(dT+0.5);
		position.addVector(velocity);
		explode->pos = &position;
		explode->vel = &velocity;
		explode->update();
	};
	void setScale(float scaleX, float scaleY, float scaleZ);

	static void loadTexture();
	static void initializeEnemyModels();
	void loadCollisionDimensions(int ID);
	/*float quatslerpDT;
	float quatslerpSpeed;*/
	float angle;
	float lerpDT;
	float lerpSpeed;
	float max_force, max_speed, mass;
	float wanderAngle, wanderChange;
	Vector desiredVel;
	Vector wanderForce;
	Quaternion *angleWander;

	Vector prevPos;

	Player *pTarget;
	EnemyBase *eTarget;
	Vector pointTarget;
	
	int state, substate;
	float health;
	int ID;

	Quaternion newQ;
	Vector seekPos;

	static GLMmodel *model[7];
	static Texture modelTexture1,modelTexture2,modelTexture3,modelTexture4,modelTexture5;

	bool colliding;
	bool collided;
	float scaleFactor[3];

	Vector velocity;
	Vector acceleration;
	Vector position;
	Vector directionVec;
	Quaternion orientation;
	Matrix44 transform;

	float dimensions[3];
	float radii[3];

	Sound *explode;
	~EnemyBase(void);
};

