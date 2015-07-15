#include "Player.h"

void Player::morph()
{
	if(this->acceleration.returnLength() > 0)
	{
		for (int i = 1; i <= model->numvertices; i++) 
		 {
			this->model->vertices[3 * i + 0] = ((1-deltaT)*morphTargets[morphTargNum]->model->vertices[3 * i + 0]) +  (deltaT*morphTargets[morphTargNum]->model->vertices[3 * i + 0]);
			this->model->vertices[3 * i + 1] = ((1-deltaT)*morphTargets[morphTargNum]->model->vertices[3 * i + 1] )+  (deltaT*morphTargets[morphTargNum]->model->vertices[3 * i + 1]);
			this->model->vertices[3 * i + 2] = ((1-deltaT)*morphTargets[morphTargNum]->model->vertices[3 * i + 2] )+  (deltaT*morphTargets[morphTargNum]->model->vertices[3 * i + 2]);
		}
		deltaT += 0.5;
		if(deltaT >= 1)
		{
			deltaT = 0;
			morphTargNum++;
			if(morphTargNum >=15)
			{
				morphTargNum = 0;
			}
		}
	}else
	{
		deltaT = 0.0;
		morphTargNum = 4;
		for (int i = 1; i <= model->numvertices; i++) 
		 {
			this->model->vertices[3 * i + 0] = ((1-deltaT)*morphTargets[morphTargNum]->model->vertices[3 * i + 0]) +  (deltaT*morphTargets[morphTargNum]->model->vertices[3 * i + 0]);
			this->model->vertices[3 * i + 1] = ((1-deltaT)*morphTargets[morphTargNum]->model->vertices[3 * i + 1] )+  (deltaT*morphTargets[morphTargNum]->model->vertices[3 * i + 1]);
			this->model->vertices[3 * i + 2] = ((1-deltaT)*morphTargets[morphTargNum]->model->vertices[3 * i + 2] )+  (deltaT*morphTargets[morphTargNum]->model->vertices[3 * i + 2]);
		}
	}
}

void Player::render()
{
	morph();
	glPushMatrix();
	//glTranslatef(position.X_Y_Z[0],position.X_Y_Z[1],position.X_Y_Z[2]);
	orientation.normalize();
	this->directionVec.multiplyVector(orientation);
	transform = Matrix44(position,orientation);
	transform.copyIntoSingleArray();
	glMultMatrixf(transform.OneDmat);
	glRotatef(90.f,0,0,1);
	glRotatef(90.f,1,0,0);
	

	glBindTexture(GL_TEXTURE_2D, this->modelTexture.texID);
	// Begin drawing of triangles.
	glmDraw(this->model, GLM_SMOOTH | GLM_TEXTURE);

	glPopMatrix();
}


void Player::setVel(bool up, bool down, bool left, bool right)
{
	this->acceleration = Vector(0,0,0);
	if(up)
	{
		this->acceleration.addVector(Vector(0,1*accelWeight,0));
	}
	if(down)
	{
		this->acceleration.addVector(Vector(0,(-1)*accelWeight,0));
	}
	if(right)
	{
		this->acceleration.addVector(Vector(1*accelWeight,0,0));
	}
	if(left)
	{
		this->acceleration.addVector(Vector((-1)*accelWeight,0,0));
	}
}

void Player::fireBullet(Vector &dir, Model &bullet)
{
	dir.normalize();
	if(accelWeight > 0)
	{
		dir.multiplyVector(accelWeight + 1.f);
	}
	Vector temp = Vector(0.1,0.2,this->position.X_Y_Z[2]);
	orientation.normalize();
	temp.multiplyVector(orientation);
	bullets.push_back( new Particle(bullet.scaleFactor[0], this->position.addVec(temp), dir, Vector(0,0,0), 300.f, 60, bullet) );

	temp = Vector(0.1,-0.2,this->position.X_Y_Z[2]);
	orientation.normalize();
	temp.multiplyVector(orientation);
	bullets.push_back( new Particle(bullet.scaleFactor[0], this->position.addVec(temp), dir, Vector(0,0,0), 300.f, 60, bullet) );
	shooting_sound->update();
	shooting_sound->play(this->position.addVec(directionVec));
}

void Player::fireMissiles(Vector &dir, Model &missile)
{
	dir.normalize();
	dir.multiplyVector((accelWeight + 1)*0.5f);
	Vector temp = Vector(0.1,0.4,this->position.X_Y_Z[2]);
	orientation.normalize();
	temp.multiplyVector(orientation);
	missiles.push_back( new Particle(missile.scaleFactor[0], this->position.addVec(temp), dir, Vector(0,0,0), 60.f, 60, missile) );

	temp = Vector(0.1,-0.4,this->position.X_Y_Z[2]);
	orientation.normalize();
	temp.multiplyVector(orientation);
	missiles.push_back( new Particle(missile.scaleFactor[0], this->position.addVec(temp), dir, Vector(0,0,0), 60.f, 60, missile) );
}

void Player::flamethrower(Vector dir, Model &flame)
{
	if(flamethrowerFuel > 0)
	{
		Quaternion *q = new Quaternion((-10*M_PI)/180,false,false,true);
		Vector temp = dir;
		temp.addVector(position);
		Vector accel;
		orientation.normalize();
		//temp.multiplyVector(orientation);
		int changeX = 1;
		int changeY = 1;
		if(temp.X_Y_Z[0] < position.X_Y_Z[0])
		{
			changeX = -1;
		}
		if(temp.X_Y_Z[1] < position.X_Y_Z[1])
		{
			changeY = -1;
		}
		temp = Vector(0.5,0,0);
		temp.multiplyVector(orientation);
		temp.addVector(position);
		dir.multiplyVector(q);
		dir.normalize();
		dir.multiplyVector(0.001);
		accel = dir;
		accel.multiplyVector(10);
		delete q;
		/*accel.thisVector.z = ((float)(rand()%2+1))/100;
		accel.X_Y_Z[2] = accel.thisVector.z;*/
		//fireP.push_back( new ParticlePoint(1,0.65,0,1,4.f,this->position.addVec(temp),dir,accel,0.5f,60));
		//fire.push_back( new Particle(0.1f, this->position.addVec(temp), dir, accel, 0.9f, 60, flame) );
		accel.~Vector();
	
		q = new Quaternion(((0.5)*M_PI)/180,false,false,true);
		for(int i = 0; i<50;i++)
		{
			dir.multiplyVector(q);
			dir.normalize();
			dir.multiplyVector(0.001);
			accel = dir;
			accel.multiplyVector(10);
			/*accel.thisVector.z = ((float)(rand()%2+1))/100;
			accel.X_Y_Z[2] = accel.thisVector.z;*/
			fireP.push_back( new ParticlePoint(1,0.65,0,1,4.f,temp,dir,accel,30.f,60));
			fireP[i]->randomX = ((float)rand()/(float)RAND_MAX) * changeX;
			fireP[i]->randomY = ((float)rand()/(float)RAND_MAX) * changeY;
			if(i%10==0)
			{
				fire.push_back( new Particle(0.1f, temp, dir, accel, 30.f, 60, flame) );
			}
			accel.~Vector();
			dir.normalize();
		}
	}
	
}

void Player::sprayWater(Vector dir, Model &water_drop)
{
	if(waterFuel >0)
	{
		Quaternion *q = new Quaternion((-10*M_PI)/180,false,false,true);
		Vector temp = dir;
		temp.addVector(position);
		Vector accel;
		orientation.normalize();
		/*temp.multiplyVector(orientation);*/
		int changeX = 1;
		int changeY = 1;
		if(temp.X_Y_Z[0] < position.X_Y_Z[0])
		{
			changeX = -1;
		}
		if(temp.X_Y_Z[1] < position.X_Y_Z[1])
		{
			changeY = -1;
		}
		temp = Vector(0.5,0,0);
		temp.multiplyVector(orientation);
		temp.addVector(position);
		dir.multiplyVector(q);
		dir.normalize();
		dir.multiplyVector(0.001);
		accel = dir;
		accel.multiplyVector(10);
		delete q;
		accel.thisVector.z = ((float)(rand()%2+1))/100;
		accel.X_Y_Z[2] = accel.thisVector.z;
		waterP.push_back( new ParticlePoint(0,1,1,0.7,4.f,temp,dir,accel,30.f,60));
		water.push_back( new Particle(0.1f, temp, dir, accel, 30.f, 60, water_drop) );
		accel.~Vector();
	
		q = new Quaternion(((0.01)*M_PI)/180,false,false,true);
		for(int i = 1; i<30;i++)
		{
			dir.multiplyVector(q);
			dir.normalize();
			dir.multiplyVector(0.001);
			accel = dir;
			accel.multiplyVector(10);
			accel.thisVector.z = ((float)(rand()%2+1))/100;
			accel.X_Y_Z[2] = accel.thisVector.z;
			waterP.push_back( new ParticlePoint(0,1,1,0.7,4.f,temp,dir,accel,30.f,60));
			waterP[i]->randomX = ((float)rand()/(float)RAND_MAX) * changeX;
			waterP[i]->randomY = ((float)rand()/(float)RAND_MAX) * changeY;
			if(i%10==0)
			{
				water.push_back( new Particle(0.1f, temp, dir, accel, 30.f, 60, water_drop) );
			}
			accel.~Vector();
			dir.normalize();
		}
	}
}

void Player::bomb(Vector &dir, Model &bomb)
{
	dir.normalize();
	Vector temp = dir;
	temp.multiplyVector(0.001);
	bombs.push_back( new Particle(0.07f, this->position, temp, Vector(0,0,0), 120.f, 60, bomb) );
}

//void Player::fireEmitter(Vector dir)
//{
//	Quaternion *q = new Quaternion((-10*M_PI)/180,false,false,true);
//
//	Vector temp = Vector(0.1,0,this->position.X_Y_Z[2]);
//	Vector accel;
//	orientation.normalize();
//	temp.multiplyVector(orientation);
//
//	dir.multiplyVector(q);
//	dir.normalize();
//	dir.multiplyVector(0.001);
//	accel = dir;
//	accel.multiplyVector(10);
//	delete q;
//	accel.thisVector.z = ((float)(rand()%2+1))/100;
//	accel.X_Y_Z[2] = accel.thisVector.z;
//	fireP.push_back( new ParticlePoint(1,0.65,0,1,4.f,this->position.addVec(temp),dir,accel,0.5f,60));
//	accel.~Vector();
//	
//	q = new Quaternion(((0.1)*M_PI)/180,false,false,true);
//	for(int i = 0; i<199;i++)
//	{
//		dir.multiplyVector(q);
//		dir.normalize();
//		dir.multiplyVector(0.001);
//		accel = dir;
//		accel.multiplyVector(10);
//		accel.thisVector.z = ((float)(rand()%2+1))/100;
//		accel.X_Y_Z[2] = accel.thisVector.z;
//		fireP.push_back( new ParticlePoint(1,0.65,0,1,4.f,this->position.addVec(temp),dir,accel,0.5f,60));
//		accel.~Vector();
//		dir.normalize();
//	}
//}

Player::~Player(void)
{
}
