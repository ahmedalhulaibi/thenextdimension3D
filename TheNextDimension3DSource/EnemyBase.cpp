#include "EnemyBase.h"
#include <ctime>

GLMmodel *EnemyBase::model[7]/* = {NULL,
							NULL,
							NULL,
							NULL,
							NULL,
							NULL,
							NULL
						   }*/;
								/*{glmReadOBJ((char *)"Obj/Enemies/EnemyShip1/EnemyShip1.obj"),
								 glmReadOBJ((char *)"Obj/Enemies/EnemyShip2/EnemyShip2.obj"),
								 glmReadOBJ((char *)"Obj/Enemies/EnemyShip3/EnemyShip3.obj"),
								 glmReadOBJ((char *)"Obj/Enemies/EnemyShip4/EnemyShip4.obj"),
								 glmReadOBJ((char *)"Obj/Enemies/EnemyShip5/EnemyShip5.obj")};*/
Texture EnemyBase::modelTexture1;
Texture EnemyBase::modelTexture2;
Texture EnemyBase::modelTexture3;
Texture EnemyBase::modelTexture4;
Texture EnemyBase::modelTexture5;

//LoadTGA(EnemyBase::modelTexture[0], (char *)texture_filename.c_str());
//	glGenTextures(1, &modelTexture->texID);
//	glBindTexture(GL_TEXTURE_2D, modelTexture->texID);
//	glTexImage2D(GL_TEXTURE_2D, 0, modelTexture->bpp / 8, 
//		modelTexture->width, modelTexture->height, 0,
//		modelTexture->type,GL_UNSIGNED_BYTE,modelTexture->imageData);
//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//	glEnable(GL_TEXTURE_2D);
//	if(modelTexture->imageData)
//	{
//		free(modelTexture->imageData);
//	}
void EnemyBase::initializeEnemyModels()
{
	model[0] = (GLMmodel*)glmReadOBJ((char *)"Obj/Enemies/EnemyShip1/EnemyShip1.obj");//space
	
	model[1] = (GLMmodel*)glmReadOBJ((char *)"Obj/Enemies/EnemyShip3/EnemyShip3.obj");//ocean
	model[2] = (GLMmodel*)glmReadOBJ((char *)"Obj/Enemies/EnemyShip2/EnemyShip2.obj");//desert
	model[3] = (GLMmodel*)glmReadOBJ((char *)"Obj/Enemies/EnemyShip4/EnemyShip4.obj");//tropical
	model[4] = (GLMmodel*)glmReadOBJ((char *)"Obj/Enemies/EnemyShip5/EnemyShip5.obj");//ice
	model[5] = (GLMmodel*)glmReadOBJ((char *)"Obj/Enemies/EnemyShip5/EnemyShip5_Hull.obj");//ice collision
	model[6] = (GLMmodel*)glmReadOBJ((char *)"Obj/Enemies/EnemyShip1/EnemyShip1_Hull.obj");//space collision

	for(int i = 0; i < 5; i++)
	{
		glmFacetNormals(model[i]);
		glmVertexNormals(model[i],90.0);
	}
}

void EnemyBase::loadCollisionDimensions(int _ID)
{
		scaleFactor[0]=scaleFactor[1]=scaleFactor[2] = 1;
		glmDimensions(model[_ID], dimensions);
		radii[0] = dimensions[0]/2.0;
		radii[1] = dimensions[1]/2.0;
		radii[2] = dimensions[2]/2.0;
		colliding = false;
		collided = false;
}

void EnemyBase::loadTexture()
{
	string filenames[5];
	filenames[0] = "Obj/Enemies/EnemyShip1/EnemyShip1Texture.tga";
	filenames[1] = "Obj/Enemies/EnemyShip3/Enemy_Model_3_BadUV_polySurfaceShape14.tga";
	filenames[2] = "Obj/Enemies/EnemyShip2/Enemy_Model_2_BadUV_2_polySurfaceShape11.tga";
	filenames[3] = "Obj/Enemies/EnemyShip4/Enemy_Model_4_BadUV_polySurfaceShape8.tga";
	filenames[4] = "Obj/Enemies/EnemyShip5/Enemy_Model_5_BadUV_polySurfaceShape8.tga";


	
		LoadTGA(&modelTexture1, (char *)filenames[0].c_str());
		glGenTextures(1, &modelTexture1.texID);
		glBindTexture(GL_TEXTURE_2D, modelTexture1.texID);
		glTexImage2D(GL_TEXTURE_2D, 0, modelTexture1.bpp / 8, 
			modelTexture1.width, modelTexture1.height, 0,
			modelTexture1.type,GL_UNSIGNED_BYTE,modelTexture1.imageData);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glEnable(GL_TEXTURE_2D);
		if(modelTexture1.imageData)
		{
			free(modelTexture1.imageData);
		}

		LoadTGA(&modelTexture2, (char *)filenames[1].c_str());
		glGenTextures(1, &modelTexture2.texID);
		glBindTexture(GL_TEXTURE_2D, modelTexture2.texID);
		glTexImage2D(GL_TEXTURE_2D, 0, modelTexture2.bpp / 8, 
			modelTexture2.width, modelTexture2.height, 0,
			modelTexture2.type,GL_UNSIGNED_BYTE,modelTexture2.imageData);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glEnable(GL_TEXTURE_2D);
		if(modelTexture2.imageData)
		{
			free(modelTexture2.imageData);
		}
		
		LoadTGA(&modelTexture3, (char *)filenames[2].c_str());
		glGenTextures(1, &modelTexture3.texID);
		glBindTexture(GL_TEXTURE_2D, modelTexture3.texID);
		glTexImage2D(GL_TEXTURE_2D, 0, modelTexture3.bpp / 8, 
			modelTexture3.width, modelTexture3.height, 0,
			modelTexture3.type,GL_UNSIGNED_BYTE,modelTexture3.imageData);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glEnable(GL_TEXTURE_2D);
		if(modelTexture3.imageData)
		{
			free(modelTexture3.imageData);
		}

		LoadTGA(&modelTexture4, (char *)filenames[3].c_str());
		glGenTextures(1, &modelTexture4.texID);
		glBindTexture(GL_TEXTURE_2D, modelTexture4.texID);
		glTexImage2D(GL_TEXTURE_2D, 0, modelTexture4.bpp / 8, 
			modelTexture4.width, modelTexture4.height, 0,
			modelTexture4.type,GL_UNSIGNED_BYTE,modelTexture4.imageData);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glEnable(GL_TEXTURE_2D);
		if(modelTexture4.imageData)
		{
			free(modelTexture4.imageData);
		}

		LoadTGA(&modelTexture5, (char *)filenames[4].c_str());
		glGenTextures(1, &modelTexture5.texID);
		glBindTexture(GL_TEXTURE_2D, modelTexture5.texID);
		glTexImage2D(GL_TEXTURE_2D, 0, modelTexture5.bpp / 8, 
			modelTexture5.width, modelTexture5.height, 0,
			modelTexture5.type,GL_UNSIGNED_BYTE,modelTexture5.imageData);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glEnable(GL_TEXTURE_2D);
		if(modelTexture5.imageData)
		{
			free(modelTexture5.imageData);
		}
}

EnemyBase::EnemyBase(int enemyID)
{
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
		ID = enemyID;
		prevPos = Vector(0,0,0);
}

void EnemyBase::render()
{
	if(health != 0)
	{
		glPushMatrix();
		orientation.normalize();
		this->directionVec.multiplyVector(orientation);
		//directionVec.normalize();
		transform = Matrix44(position,orientation);
		transform.copyIntoSingleArray();
	
		glMultMatrixf(transform.OneDmat);
		glRotatef(angle,0,0,1.f);
		glRotatef(90.f,0,0,1);
		glRotatef(90.f,1,0,0);
		glScalef(scaleFactor[0],scaleFactor[1],scaleFactor[2]);

		switch(ID)
		{
		case ENEMY_SPACE:
			glBindTexture(GL_TEXTURE_2D, this->modelTexture1.texID);
			break;
		case ENEMY_OCEAN:
			glBindTexture(GL_TEXTURE_2D, this->modelTexture2.texID);
			break;
		case ENEMY_DESERT:
			glBindTexture(GL_TEXTURE_2D, this->modelTexture3.texID);
			break;
		case ENEMY_TROPICAL:
			glBindTexture(GL_TEXTURE_2D, this->modelTexture4.texID);
			break;
		case ENEMY_ICE:
			glBindTexture(GL_TEXTURE_2D, this->modelTexture5.texID);
			break;
		}
			
		// Begin drawing of triangles.
		glmDraw(this->model[ID], GLM_FLAT| GLM_TEXTURE);

		glPopMatrix();
		transform.~Matrix44();
	}
}


void EnemyBase::setScale(float scaleX, float scaleY, float scaleZ)
{
	scaleFactor[0] = scaleX;
	scaleFactor[1] = scaleY;
	scaleFactor[2] = scaleZ;
	radii[0] *= scaleX;
	radii[1] *= scaleY;
	radii[2] *= scaleZ;
}

//void EnemyBase::orientSLERP(Player *p)
//{
//	
//	Vector temp = p->position.subVector(position);
//	temp.thisVector.z = 0;
//	temp.X_Y_Z[2] = 0;
//	temp.normalize();
//	float angleRads = this->directionVec.angle(temp);
//	/*if(!(newQ == Quaternion(angleRads,false,false,true)))
//	{*/
//		newQ = Quaternion(angleRads,false,false,true);
//	/*}*/
//	newQ.normalize();
//	orientation.normalize();
//	quatslerpDT += 0.1f/300.f/*angleRads/this->quatslerpSpeed*/;
//	
//	this->orientation = orientation.SLERP(orientation,newQ,this->quatslerpDT);
//	newQ.~Quaternion();	
//}

void EnemyBase::seek()
{
	
	if(substate == SEEK_PLAYER)
	{
		desiredVel = pTarget->position.subVector(position);
		desiredVel.normalize();
		desiredVel.multiplyVector(this->max_speed);
		desiredVel.subtractVector(velocity);
		desiredVel.multiplyVector(1/mass);
		this->acceleration = desiredVel;
	}else if(substate == SEEK_ENEMY)
	{
		desiredVel = eTarget->position.subVector(position);
		desiredVel.normalize();
		desiredVel.multiplyVector(this->max_speed);
		desiredVel.subtractVector(velocity);
		desiredVel.multiplyVector(1/mass);
		this->acceleration = desiredVel;
	}else if(substate == SEEK_POINT)
	{
		desiredVel = pointTarget.subVector(position);
		desiredVel.normalize();
		desiredVel.multiplyVector(this->max_speed);
		desiredVel.subtractVector(velocity);
		desiredVel.multiplyVector(1/mass);
		desiredVel.multiplyVector(0.3f);
		this->acceleration = desiredVel;
	}
	desiredVel.~Vector();
}

void EnemyBase::flee()
{
	
	if(substate == FLEE_PLAYER)
	{
		desiredVel = pTarget->position.subVector(position);
		desiredVel.normalize();
		desiredVel.multiplyVector(this->max_speed);
		desiredVel.subtractVector(velocity);
		desiredVel.multiplyVector(1/mass);
		desiredVel.multiplyVector(-1.f);
		this->acceleration = desiredVel;
	}else if(substate == FLEE_ENEMY)
	{
		desiredVel = eTarget->position.subVector(position);
		desiredVel.normalize();
		desiredVel.multiplyVector(this->max_speed);
		desiredVel.subtractVector(velocity);
		desiredVel.multiplyVector(1/mass);
		desiredVel.multiplyVector(-1.f);
		this->acceleration = desiredVel;
	}else if(substate == FLEE_POINT)
	{
		desiredVel = pointTarget.subVector(position);
		desiredVel.normalize();
		desiredVel.multiplyVector(this->max_speed);
		desiredVel.subtractVector(velocity);
		desiredVel.multiplyVector(1/mass);
		desiredVel.multiplyVector(-1.f);
		this->acceleration = desiredVel;
	}
	desiredVel.~Vector();
}

void EnemyBase::wander()
{
	//srand ( time(NULL) );
	Vector circleMiddle = velocity;
	circleMiddle.normalize();
	circleMiddle.multiplyVector(this->radii[0]);
	wanderForce = Vector(0,0.3,0);
	delete angleWander;
	angleWander = new Quaternion((this->wanderAngle*M_PI)/180,false,false,true);
	angleWander->normalize();
	wanderForce.multiplyVector(angleWander);
	wanderAngle = ((rand()%45) * wanderChange) - (wanderChange * 0.5);
	wanderForce.addVector(circleMiddle);
	wanderForce.normalize();
	wanderForce.multiplyVector(0.001);
	velocity.addVector(wanderForce);
	circleMiddle.~Vector();
}

void EnemyBase::repel()
{
	
	if(substate == REPEL_PLAYER)
	{
		desiredVel = pTarget->position.subVector(position);
		desiredVel.normalize();
		desiredVel.multiplyVector(this->max_speed);
		desiredVel.subtractVector(velocity);
		desiredVel.multiplyVector(1/mass);
		desiredVel.multiplyVector(-1.5f);
		this->acceleration = desiredVel;
	}else if(substate == REPEL_ENEMY)
	{
		desiredVel = eTarget->position.subVector(position);
		desiredVel.normalize();
		desiredVel.multiplyVector(this->max_speed);
		desiredVel.subtractVector(velocity);
		desiredVel.multiplyVector(1/mass);
		desiredVel.multiplyVector(-1.f);
		this->acceleration = desiredVel;
	}else if(substate == REPEL_POINT)
	{
		desiredVel = pointTarget.subVector(position);
		desiredVel.normalize();
		desiredVel.multiplyVector(this->max_speed);
		desiredVel.subtractVector(velocity);
		desiredVel.multiplyVector(1/mass);
		desiredVel.multiplyVector(-0.7f);
		this->acceleration = desiredVel;
	}
	desiredVel.~Vector();
}

EnemyBase::~EnemyBase(void)
{
}