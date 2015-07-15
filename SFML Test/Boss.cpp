#include "Boss.h"


void Boss::render()
{
	if(health != 0)
	{
		glPushMatrix();
		orientation.normalize();
		directionVec = Vector(1,0,0);
		this->directionVec.multiplyVector(orientation);
		directionVec.normalize();
		transform = Matrix44(position,orientation);
		transform.copyIntoSingleArray();
	
		glMultMatrixf(transform.OneDmat);
		glRotatef(angle,0,0,1.f);
		glRotatef(90.f,0,0,1);
		glRotatef(90.f,1,0,0);
		glScalef(scaleFactor[0],scaleFactor[1],scaleFactor[2]);

		glBindTexture(GL_TEXTURE_2D, this->modelTexture.texID);
		// Begin drawing of triangles.
		glmDraw(this->model, GLM_SMOOTH| GLM_TEXTURE);

		glPopMatrix();
		transform.~Matrix44();
	}
}

void Boss::seek()
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
	this->velocity.addVector(acceleration);
	desiredVel.~Vector();
}

void Boss::flee()
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
	this->velocity.addVector(acceleration);

	desiredVel.~Vector();
}

void Boss::wander()
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

void Boss::repel()
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
	this->velocity.addVector(acceleration);

	desiredVel.~Vector();
}

void Boss::update()
{
	/*position.addVector(velocity);
	Vector temp = pTarget->position.subVector(this->position);
	temp.normalize();
	directionVec = Vector(1,0,0);*/

	/*if(phase>=PHASE1)
	{
		for(int i = 0; i<bullets.size(); i++)
		{
			bullets[i]->velocity = this->velocity;
		}
		for(int i = 0; i<bullets2.size(); i++)
		{
			bullets2[i]->velocity = this->velocity;
		}
	}*/

	if(phase==PHASE1)
	{
		//if (position.thisVector.y < -100)
		//{
		//	velocity = Vector(0,1,0);
		//}
		//if (position.thisVector.y > 100)
		//{
		//	velocity = Vector(0,-1,0);
		//}
		////CHARGE, SPIN AND SHOOT
		if(health <= (fullHealth/2))
		{
			phase++;
			velocity = Vector(0,0,0);
			this->state =SEEK;
			this->substate = SEEK_PLAYER;
		}
		position = Vector(0,0,0);
		angle+=0.02 * (this->ID+1);
		orientation = Quaternion(angle,false,false,true);
	}
	else if(phase==PHASE3)
	{
		//LERP AROUND MAP AND SHOOT
		/*if (position.thisVector.y < -75)
		{
			velocity = Vector(0,2,0);
		}
		if (position.thisVector.y > 75)
		{
			velocity = Vector(0,-2,0);
		}*/
		if(health <= 0)
		{
			phase=NEUTRAL;
		}
		if(lerpDeltaT >= 1)
		{
			prevTargSelect = randomTarg;
			randomTarg = rand()%7;
			lerpDeltaT = 0;
		}/*else
		{*/
			lerpDeltaT += 1.0/240.0;
		/*}*/
			this->directionVec.thisVector.x = this->directionVec.X_Y_Z[0] = 1;
			this->directionVec.thisVector.y = this->directionVec.thisVector.z =  
				    this->directionVec.X_Y_Z[1] = this->directionVec.X_Y_Z[2] = 0;
			Vector temp = this->pTarget->position.subVector(this->position);
			angle = this->directionVec.angle(temp);
			if(temp.X_Y_Z[1] < 0)
			 {
				 angle = angle * (-1.f);
			 }
			this->orientation = Quaternion(angle,false,false,true);
		position.LERP(lerpTarget[prevTargSelect],lerpTarget[randomTarg],lerpDeltaT);
	}
	else if(phase==PHASE2)
	{
		//CHASE PLAYER AND SHOOT
		/*if (position.thisVector.y < -5)
		{
			velocity = Vector(0,4,0);
		}
		if (position.thisVector.y > 50)
		{
			velocity = Vector(0,-4,0);
		}*/
		if(health <= (fullHealth/4))
		{
			phase++;
			velocity = Vector(0,0,0);
		}
		this->directionVec.thisVector.x = this->directionVec.X_Y_Z[0] = 1;
			this->directionVec.thisVector.y = this->directionVec.thisVector.z =  
				    this->directionVec.X_Y_Z[1] = this->directionVec.X_Y_Z[2] = 0;
			Vector temp = this->pTarget->position.subVector(this->position);
			angle = this->directionVec.angle(temp);
			if(temp.X_Y_Z[1] < 0)
			 {
				 angle = angle * (-1.f);
			 }
			this->orientation = Quaternion(angle,false,false,true);
		this->seek();
		this->position.addVector(velocity);
		
	}
	/*this->position.thisVector.x = -100;
	this->position.X_Y_Z[0] = this->position.thisVector.x;*/

}

void Boss::morph()
{
	for (int i = 1; i <= model->numvertices; i++) 
	 {
		this->model->vertices[3 * i + 0] = ((1-deltaT)*target1->model->vertices[3 * i + 0]) +  (deltaT*target2->model->vertices[3 * i + 0]);
        this->model->vertices[3 * i + 1] = ((1-deltaT)*target1->model->vertices[3 * i + 1] )+  (deltaT*target2->model->vertices[3 * i + 1]);
        this->model->vertices[3 * i + 2] = ((1-deltaT)*target1->model->vertices[3 * i + 2] )+  (deltaT*target2->model->vertices[3 * i + 2]);
    }
	deltaT += 0.001;
	if(deltaT >= 1)
	{
		deltaT = 1;
		this->radii[0] = target2->radii[0]*0.3;
		this->radii[1] = target2->radii[1]*0.3;
		this->radii[2] = target2->radii[2]*0.1;
	}
	this->orientation = Quaternion(0.0,false,false,true);
	this->position.thisVector.x = this->position.thisVector.y = this->position.thisVector.z = 
	            this->position.X_Y_Z[0] = this->position.X_Y_Z[1] = this->position.X_Y_Z[2] = 0;
	this->lerpDeltaT = this->angle = 0.0;

}

void Boss::shoot(Model & bullet)
{
	Vector mod = Vector(4,-2,0);
	orientation.normalize();
	mod.multiplyVector(orientation);
	p[0] = this->position.addVec(mod);
	p[1] = p[0];
	p[2] = p[0].addVec(Vector(5,-20,0));
	p[3] = p[0].addVec(Vector(-5,-40,0));
	p[4] = p[0].addVec(Vector(0,-60,0));
	p[5] = p[4];

	float distance = p[0].speedControl_SLERP(p[0],p[1],p[2],p[3]);
	distance/=2;
	num[0] = floor(distance);
	for (int i = 0; i<num[0]; i++)
	{
		bullets.push_back( new Particle(3.f, p[0], Vector(0,0,0), Vector(0,0,0), 10000.f, 60, bullet) );
	}
	for (int i = 0; i<num[0]; i++)
	{
		bullets[i]->position.SLERP(p[0], p[1], p[2], p[3], (float)i/(float)num[0]);
	}

	float d2 = p[1].speedControl_SLERP(p[1],p[2],p[3],p[4]);
	d2/=2;
	num[1] = floor(d2);
	for (int i = 0; i<num[1]; i++)
	{
		bullets.push_back( new Particle(3.f, p[1], Vector(0,0,0), Vector(0,0,0), 10000.f, 60, bullet) );
	}
	for (int i = num[0]; i<(num[0]+num[1]); i++)
	{
		bullets[i]->position.SLERP(p[1], p[2], p[3], p[4], (float)(i-num[0])/(float)num[1]);
	}

	float d3 = p[2].speedControl_SLERP(p[2],p[3],p[4],p[5]);
	d3/=2;
	num[2] = floor(d3);
	for (int i = 0; i<num[2]; i++)
	{
		bullets.push_back( new Particle(3.f, p[2], Vector(0,0,0), Vector(0,0,0), 10000.f, 60, bullet) );
	}
	for (int i = (num[0]+num[1]); i<(num[0]+num[1]+num[2]); i++)
	{
		bullets[i]->position.SLERP(p[2], p[3], p[4], p[5], (float)(i-(num[0]+num[1]))/(float)num[2]);
	}

	Vector modb = Vector(-4,-2,0);
	modb.multiplyVector(orientation);
	pb[0] = this->position.addVec(modb);
	pb[1] = pb[0];
	pb[2] = pb[0].addVec(Vector(5,-20,0));
	pb[3] = pb[0].addVec(Vector(-5,-40,0));
	pb[4] = pb[0].addVec(Vector(0,-60,0));
	pb[5] = pb[4];

	float distanceb = pb[0].speedControl_SLERP(pb[0],pb[1],pb[2],pb[3]);
	distanceb/=2;
	numb[0] = floor(distanceb);
	for (int i = 0; i<numb[0]; i++)
	{
		bullets2.push_back( new Particle(3.f, pb[0], Vector(0,0,0), Vector(0,0,0), 10000.f, 60, bullet) );
	}
	for (int i = 0; i<numb[0]; i++)
	{
		bullets2[i]->position.SLERP(pb[0], pb[1], pb[2], pb[3], (float)i/(float)numb[0]);
	}

	float d2b = p[1].speedControl_SLERP(pb[1],pb[2],pb[3],pb[4]);
	d2b/=2;
	numb[1] = floor(d2b);
	for (int i = 0; i<numb[1]; i++)
	{
		bullets2.push_back( new Particle(3.f, pb[1], Vector(0,0,0), Vector(0,0,0), 10000.f, 60, bullet) );
	}
	for (int i = numb[0]; i<(numb[0]+numb[1]); i++)
	{
		bullets2[i]->position.SLERP(pb[1], pb[2], pb[3], pb[4], (float)(i-numb[0])/(float)numb[1]);
	}

	float d3b = pb[2].speedControl_SLERP(pb[2],pb[3],pb[4],pb[5]);
	d3b/=2;
	numb[2] = floor(d3b);
	for (int i = 0; i<numb[2]; i++)
	{
		bullets2.push_back( new Particle(3.f, p[2], Vector(0,0,0), Vector(0,0,0), 10000.f, 60, bullet) );
	}
	for (int i = (numb[0]+numb[1]); i<(numb[0]+numb[1]+numb[2]); i++)
	{
		bullets2[i]->position.SLERP(pb[2], pb[3], pb[4], pb[5], (float)(i-(numb[0]+numb[1]))/(float)numb[2]);
	}
}

void Boss::shootParticle(Model &model)
{
	//directionVec = Vector(1,0,0);
	Vector dirCopy = directionVec;
	dirCopy.multiplyVector(0.05);
	dirCopy.X_Y_Z[2] = dirCopy.thisVector.z = 0.0;
	
	Vector dirCopy_2 = dirCopy;
	dirCopy_2.thisVector.y*=(-1);
	dirCopy_2.X_Y_Z[1] = dirCopy_2.thisVector.y;
	if(ID == ENEMY_SPACE)
	{

		origin[0] = Vector(3,10,2);
		origin[1] = Vector(3,9.5,2);
		origin[2] = Vector(3,9,2);
		origin[3] = Vector(3,8.5,2);
		origin[4] = Vector(3,8,2);

		origin[0].multiplyVector(orientation);
		origin[1].multiplyVector(orientation);
		origin[2].multiplyVector(orientation);
		origin[3].multiplyVector(orientation);
		origin[4].multiplyVector(orientation);


		origin[0].addVector(position);
		origin[1].addVector(position);
		origin[2].addVector(position);
		origin[3].addVector(position);
		origin[4].addVector(position);

		for(int i = 0; i < 5; i++)
		{
			Bullets.push_back(new Model(model));
			particleBullet.push_back(new ParticlePoint(1,0,0,1,10.f,origin[i],directionVec,Vector(0,0,0),600,60));
		}

		origin[0] = Vector(3,-10,2);
		origin[1] = Vector(3,-9.5,2);
		origin[2] = Vector(3,-9,2);
		origin[3] = Vector(3,-8.5,2);
		origin[4] = Vector(3,-8,2);

		origin[0].multiplyVector(orientation);
		origin[1].multiplyVector(orientation);
		origin[2].multiplyVector(orientation);
		origin[3].multiplyVector(orientation);
		origin[4].multiplyVector(orientation);


		origin[0].addVector(position);
		origin[1].addVector(position);
		origin[2].addVector(position);
		origin[3].addVector(position);
		origin[4].addVector(position);

		for(int i = 0; i < 5; i++)
		{
			Bullets.push_back(new Model(model));
			particleBullet.push_back(new ParticlePoint(1,0,0,1,10.f,origin[i],directionVec,Vector(0,0,0),600,60));
		}

		//bulletAccel = Vector(0,0,0);
		//origin[0] = Vector(0,6,0);/* = position.addVec(Vector(0,6,0));*/
		//origin[1] = origin[0];
		//origin[1].thisVector.y *= (-1);
		//origin[1].X_Y_Z[1] = origin[1].thisVector.y;
		//origin[0].multiplyVector(this->orientation);
		//origin[1].multiplyVector(this->orientation);

		//Quaternion *q = new Quaternion((((1)*M_PI)/180)*(-1),false,false,true);
		//for(int i = 0; i < 50; i++)
		//{
		//	Bullets.push_back(new Model(model));
		//	Bullets.push_back(new Model(model));
		//	particleBullet.push_back(new ParticlePoint(1,0,0,1,4.f,origin[0].addVec(position),dirCopy,bulletAccel,10,60));
		//	particleBullet.push_back(new ParticlePoint(1,0,0,1,4.f,origin[1].addVec(position),dirCopy_2,bulletAccel,10,60));
		//	origin[0].thisVector.y -= 5/50;
		//	origin[0].X_Y_Z[1] = origin[0].thisVector.y;
		//	origin[1] = origin[0];
		//	origin[1].thisVector.y *= (-1);
		//	origin[1].X_Y_Z[1] = origin[1].thisVector.y;
		//}
		//for(int i = 0; i < 50; i++)
		//{
		//	Bullets.push_back(new Model(model));
		//	Bullets.push_back(new Model(model));
		//	dirCopy.multiplyVector(q);
		//	/*dirCopy.multiplyVector(0.1);*/
		//	dirCopy_2 = dirCopy;
		//	dirCopy_2.thisVector.y*=(-1);
		//	dirCopy_2.X_Y_Z[1] = dirCopy_2.thisVector.y;
		//	particleBullet.push_back(new ParticlePoint(1,0,0,1,4.f,origin[0].addVec(position),dirCopy,bulletAccel,10,60));
		//	particleBullet.push_back(new ParticlePoint(1,0,0,1,4.f,origin[1].addVec(position),dirCopy_2,bulletAccel,10,60));
		//}


	}else if(ID == ENEMY_DESERT)
	{
		origin[0] = Vector(3,10,2);
		origin[1] = Vector(3,9.5,2);
		origin[2] = Vector(3,9,2);
		origin[3] = Vector(3,8.5,2);
		origin[4] = Vector(3,8,2);

		origin[0].multiplyVector(orientation);
		origin[1].multiplyVector(orientation);
		origin[2].multiplyVector(orientation);
		origin[3].multiplyVector(orientation);
		origin[4].multiplyVector(orientation);


		origin[0].addVector(position);
		origin[1].addVector(position);
		origin[2].addVector(position);
		origin[3].addVector(position);
		origin[4].addVector(position);

		for(int i = 0; i < 5; i++)
		{
			Bullets.push_back(new Model(model));
			particleBullet.push_back(new ParticlePoint(1,1,0,1,10.f,origin[i],directionVec,Vector(0,0,0),600,60));
		}

		origin[0] = Vector(3,-10,2);
		origin[1] = Vector(3,-9.5,2);
		origin[2] = Vector(3,-9,2);
		origin[3] = Vector(3,-8.5,2);
		origin[4] = Vector(3,-8,2);

		origin[0].multiplyVector(orientation);
		origin[1].multiplyVector(orientation);
		origin[2].multiplyVector(orientation);
		origin[3].multiplyVector(orientation);
		origin[4].multiplyVector(orientation);


		origin[0].addVector(position);
		origin[1].addVector(position);
		origin[2].addVector(position);
		origin[3].addVector(position);
		origin[4].addVector(position);

		for(int i = 0; i < 5; i++)
		{
			Bullets.push_back(new Model(model));
			particleBullet.push_back(new ParticlePoint(1,1,0,1,10.f,origin[i],directionVec,Vector(0,0,0),600,60));
		}


		origin[0] = Vector(3,3.5,2);
		origin[1] = Vector(3,3.4,2);
		origin[2] = Vector(3,3.3,2);
		origin[3] = Vector(3,3.2,2);
		origin[4] = Vector(3,3.1,2);

		origin[0].multiplyVector(orientation);
		origin[1].multiplyVector(orientation);
		origin[2].multiplyVector(orientation);
		origin[3].multiplyVector(orientation);
		origin[4].multiplyVector(orientation);


		origin[0].addVector(position);
		origin[1].addVector(position);
		origin[2].addVector(position);
		origin[3].addVector(position);
		origin[4].addVector(position);

		for(int i = 0; i < 5; i++)
		{
			Bullets.push_back(new Model(model));
			particleBullet.push_back(new ParticlePoint(1,1,0,1,10.f,origin[i],directionVec,Vector(0,0,0),600,60));
		}

		origin[0] = Vector(3,-3.5,2);
		origin[1] = Vector(3,-3.4,2);
		origin[2] = Vector(3,-3.3,2);
		origin[3] = Vector(3,-3.2,2);
		origin[4] = Vector(3,-3.1,2);

		origin[0].multiplyVector(orientation);
		origin[1].multiplyVector(orientation);
		origin[2].multiplyVector(orientation);
		origin[3].multiplyVector(orientation);
		origin[4].multiplyVector(orientation);


		origin[0].addVector(position);
		origin[1].addVector(position);
		origin[2].addVector(position);
		origin[3].addVector(position);
		origin[4].addVector(position);

		for(int i = 0; i < 5; i++)
		{
			Bullets.push_back(new Model(model));
			particleBullet.push_back(new ParticlePoint(1,1,0,1,10.f,origin[i],directionVec,Vector(0,0,0),600,60));
		}


		//bulletAccel = Vector(0,0,0);
		//origin[0] = Vector(0,6,0);/* = position.addVec(Vector(0,6,0));*/
		//origin[1] = origin[0];
		//origin[1].thisVector.y *= (-1);
		//origin[1].X_Y_Z[1] = origin[1].thisVector.y;
		//Quaternion *q = new Quaternion((((1)*M_PI)/180)*(-1),false,false,true);
		//for(int i = 0; i < 50; i++)
		//{
		//	Bullets.push_back(new Model(model));
		//	Bullets.push_back(new Model(model));
		//	particleBullet.push_back(new ParticlePoint(1,0.65,0,1,4.f,origin[0].addVec(position),dirCopy,bulletAccel,10,60));
		//	particleBullet.push_back(new ParticlePoint(1,0.65,0,1,4.f,origin[1].addVec(position),dirCopy_2,bulletAccel,10,60));
		//	origin[0].thisVector.y -= 5/50;
		//	origin[0].X_Y_Z[1] = origin[0].thisVector.y;
		//	origin[1] = origin[0];
		//	origin[1].thisVector.y *= (-1);
		//	origin[1].X_Y_Z[1] = origin[1].thisVector.y;
		//}
		//for(int i = 0; i < 50; i++)
		//{
		//	Bullets.push_back(new Model(model));
		//	Bullets.push_back(new Model(model));
		//	dirCopy.multiplyVector(q);
		//	/*dirCopy.multiplyVector(0.1);*/
		//	dirCopy_2 = dirCopy;
		//	dirCopy_2.thisVector.y*=(-1);
		//	dirCopy_2.X_Y_Z[1] = dirCopy_2.thisVector.y;
		//	particleBullet.push_back(new ParticlePoint(1,0.65,0,1,4.f,origin[0].addVec(position),dirCopy,bulletAccel,10,60));
		//	particleBullet.push_back(new ParticlePoint(1,0.65,0,1,4.f,origin[1].addVec(position),dirCopy_2,bulletAccel,10,60));
		//}
	}else if(ID == ENEMY_OCEAN)
	{
		origin[0] = Vector(3,10,2);
		origin[1] = Vector(3,9.5,2);
		origin[2] = Vector(3,9,2);
		origin[3] = Vector(3,8.5,2);
		origin[4] = Vector(3,8,2);

		origin[0].multiplyVector(orientation);
		origin[1].multiplyVector(orientation);
		origin[2].multiplyVector(orientation);
		origin[3].multiplyVector(orientation);
		origin[4].multiplyVector(orientation);


		origin[0].addVector(position);
		origin[1].addVector(position);
		origin[2].addVector(position);
		origin[3].addVector(position);
		origin[4].addVector(position);

		for(int i = 0; i < 5; i++)
		{
			Bullets.push_back(new Model(model));
			particleBullet.push_back(new ParticlePoint(0,0.5,1,1,10.f,origin[i],directionVec,Vector(0,0,0),600,60));
		}

		origin[0] = Vector(3,-10,2);
		origin[1] = Vector(3,-9.5,2);
		origin[2] = Vector(3,-9,2);
		origin[3] = Vector(3,-8.5,2);
		origin[4] = Vector(3,-8,2);

		origin[0].multiplyVector(orientation);
		origin[1].multiplyVector(orientation);
		origin[2].multiplyVector(orientation);
		origin[3].multiplyVector(orientation);
		origin[4].multiplyVector(orientation);


		origin[0].addVector(position);
		origin[1].addVector(position);
		origin[2].addVector(position);
		origin[3].addVector(position);
		origin[4].addVector(position);

		for(int i = 0; i < 5; i++)
		{
			Bullets.push_back(new Model(model));
			particleBullet.push_back(new ParticlePoint(0,0.5,1,1,10.f,origin[i],directionVec,Vector(0,0,0),600,60));
		}

		origin[0] = Vector(3,0.4,2);
		origin[1] = Vector(3,0.2,2);
		origin[2] = Vector(3,0,2);
		origin[3] = Vector(3,-0.2,2);
		origin[4] = Vector(3,-0.4,2);

		origin[0].multiplyVector(orientation);
		origin[1].multiplyVector(orientation);
		origin[2].multiplyVector(orientation);
		origin[3].multiplyVector(orientation);
		origin[4].multiplyVector(orientation);


		origin[0].addVector(position);
		origin[1].addVector(position);
		origin[2].addVector(position);
		origin[3].addVector(position);
		origin[4].addVector(position);

		for(int i = 0; i < 5; i++)
		{
			Bullets.push_back(new Model(model));
			particleBullet.push_back(new ParticlePoint(0,0,1,1,10.f,origin[i],directionVec,Vector(0,0,0),600,60));
		}


		//bulletAccel = Vector(0,0,0);
		//origin[0] = Vector(0,6,0);/* = position.addVec(Vector(0,6,0));*/
		//origin[1] = origin[0];
		//origin[1].thisVector.y *= (-1);
		//origin[1].X_Y_Z[1] = origin[1].thisVector.y;
		//Quaternion *q = new Quaternion((((1)*M_PI)/180)*(-1),false,false,true);
		//for(int i = 0; i < 50; i++)
		//{
		//	Bullets.push_back(new Model(model));
		//	Bullets.push_back(new Model(model));
		//	particleBullet.push_back(new ParticlePoint(0,0.2,1,1,4.f,origin[0].addVec(position),dirCopy,bulletAccel,10,60));
		//	particleBullet.push_back(new ParticlePoint(0,0.2,1,1,4.f,origin[1].addVec(position),dirCopy_2,bulletAccel,10,60));
		//	origin[0].thisVector.y -= 5/50;
		//	origin[0].X_Y_Z[1] = origin[0].thisVector.y;
		//	origin[1] = origin[0];
		//	origin[1].thisVector.y *= (-1);
		//	origin[1].X_Y_Z[1] = origin[1].thisVector.y;
		//}
		//for(int i = 0; i < 50; i++)
		//{
		//	Bullets.push_back(new Model(model));
		//	Bullets.push_back(new Model(model));
		//	dirCopy.multiplyVector(q);
		//	/*dirCopy.multiplyVector(0.1);*/
		//	dirCopy_2 = dirCopy;
		//	dirCopy_2.thisVector.y*=(-1);
		//	dirCopy_2.X_Y_Z[1] = dirCopy_2.thisVector.y;
		//	particleBullet.push_back(new ParticlePoint(0,0.2,1,1,4.f,origin[0].addVec(position),dirCopy,bulletAccel,10,60));
		//	particleBullet.push_back(new ParticlePoint(0,0.2,1,1,4.f,origin[1].addVec(position),dirCopy_2,bulletAccel,10,60));
		//}
	}else if(ID == ENEMY_TROPICAL)
	{
		origin[0] = Vector(3,10,2);
		origin[1] = Vector(3,9.5,2);
		origin[2] = Vector(3,9,2);
		origin[3] = Vector(3,8.5,2);
		origin[4] = Vector(3,8,2);

		origin[0].multiplyVector(orientation);
		origin[1].multiplyVector(orientation);
		origin[2].multiplyVector(orientation);
		origin[3].multiplyVector(orientation);
		origin[4].multiplyVector(orientation);


		origin[0].addVector(position);
		origin[1].addVector(position);
		origin[2].addVector(position);
		origin[3].addVector(position);
		origin[4].addVector(position);

		for(int i = 0; i < 5; i++)
		{
			Bullets.push_back(new Model(model));
			particleBullet.push_back(new ParticlePoint(0,1,0.2,1,10.f,origin[i],directionVec,Vector(0,0,0),600,60));
		}

		origin[0] = Vector(3,-10,2);
		origin[1] = Vector(3,-9.5,2);
		origin[2] = Vector(3,-9,2);
		origin[3] = Vector(3,-8.5,2);
		origin[4] = Vector(3,-8,2);

		origin[0].multiplyVector(orientation);
		origin[1].multiplyVector(orientation);
		origin[2].multiplyVector(orientation);
		origin[3].multiplyVector(orientation);
		origin[4].multiplyVector(orientation);


		origin[0].addVector(position);
		origin[1].addVector(position);
		origin[2].addVector(position);
		origin[3].addVector(position);
		origin[4].addVector(position);

		for(int i = 0; i < 5; i++)
		{
			Bullets.push_back(new Model(model));
			particleBullet.push_back(new ParticlePoint(0,1,0.2,1,10.f,origin[i],directionVec,Vector(0,0,0),600,60));
		}

		origin[0] = Vector(3,2,2);
		origin[1] = Vector(3,1,2);
		origin[2] = Vector(3,0,2);
		origin[3] = Vector(3,-1,2);
		origin[4] = Vector(3,-2,2);

		origin[0].multiplyVector(orientation);
		origin[1].multiplyVector(orientation);
		origin[2].multiplyVector(orientation);
		origin[3].multiplyVector(orientation);
		origin[4].multiplyVector(orientation);


		origin[0].addVector(position);
		origin[1].addVector(position);
		origin[2].addVector(position);
		origin[3].addVector(position);
		origin[4].addVector(position);

		for(int i = 0; i < 5; i++)
		{
			Bullets.push_back(new Model(model));
			particleBullet.push_back(new ParticlePoint(0.1,1,0.1,1,10.f,origin[i],directionVec,Vector(0,0,0),600,60));
		}


		//bulletAccel = Vector(0,0,0);
		//origin[0] = Vector(0,6,0);/* = position.addVec(Vector(0,6,0));*/
		//origin[1] = origin[0];
		//origin[1].thisVector.y *= (-1);
		//origin[1].X_Y_Z[1] = origin[1].thisVector.y;
		//Quaternion *q = new Quaternion((((1)*M_PI)/180)*(-1),false,false,true);
		//for(int i = 0; i < 50; i++)
		//{
		//	Bullets.push_back(new Model(model));
		//	Bullets.push_back(new Model(model));
		//	particleBullet.push_back(new ParticlePoint(0,1,0.2,1,4.f,origin[0].addVec(position),dirCopy,bulletAccel,10,60));
		//	particleBullet.push_back(new ParticlePoint(0,1,0.2,1,4.f,origin[1].addVec(position),dirCopy_2,bulletAccel,10,60));
		//	origin[0].thisVector.y -= 5/50;
		//	origin[0].X_Y_Z[1] = origin[0].thisVector.y;
		//	origin[1] = origin[0];
		//	origin[1].thisVector.y *= (-1);
		//	origin[1].X_Y_Z[1] = origin[1].thisVector.y;
		//}
		//for(int i = 0; i < 50; i++)
		//{
		//	Bullets.push_back(new Model(model));
		//	Bullets.push_back(new Model(model));
		//	dirCopy.multiplyVector(q);
		//	/*dirCopy.multiplyVector(0.1);*/
		//	dirCopy_2 = dirCopy;
		//	dirCopy_2.thisVector.y*=(-1);
		//	dirCopy_2.X_Y_Z[1] = dirCopy_2.thisVector.y;
		//	particleBullet.push_back(new ParticlePoint(0,1,0.2,1,4.f,origin[0].addVec(position),dirCopy,bulletAccel,10,60));
		//	particleBullet.push_back(new ParticlePoint(0,1,0.2,1,4.f,origin[1].addVec(position),dirCopy_2,bulletAccel,10,60));
		//}
	}else if(ID == ENEMY_ICE)
	{
		origin[0] = Vector(3,10,2);
		origin[1] = Vector(3,9.5,2);
		origin[2] = Vector(3,9,2);
		origin[3] = Vector(3,8.5,2);
		origin[4] = Vector(3,8,2);

		origin[0].multiplyVector(orientation);
		origin[1].multiplyVector(orientation);
		origin[2].multiplyVector(orientation);
		origin[3].multiplyVector(orientation);
		origin[4].multiplyVector(orientation);


		origin[0].addVector(position);
		origin[1].addVector(position);
		origin[2].addVector(position);
		origin[3].addVector(position);
		origin[4].addVector(position);

		for(int i = 0; i < 5; i++)
		{
			Bullets.push_back(new Model(model));
			particleBullet.push_back(new ParticlePoint(0,1,1,1,10.f,origin[i],directionVec,Vector(0,0,0),600,60));
		}

		origin[0] = Vector(3,-10,2);
		origin[1] = Vector(3,-9.5,2);
		origin[2] = Vector(3,-9,2);
		origin[3] = Vector(3,-8.5,2);
		origin[4] = Vector(3,-8,2);

		origin[0].multiplyVector(orientation);
		origin[1].multiplyVector(orientation);
		origin[2].multiplyVector(orientation);
		origin[3].multiplyVector(orientation);
		origin[4].multiplyVector(orientation);


		origin[0].addVector(position);
		origin[1].addVector(position);
		origin[2].addVector(position);
		origin[3].addVector(position);
		origin[4].addVector(position);

		for(int i = 0; i < 5; i++)
		{
			Bullets.push_back(new Model(model));
			particleBullet.push_back(new ParticlePoint(0,1,1,1,10.f,origin[i],directionVec,Vector(0,0,0),600,60));
		}


		//bulletAccel = Vector(0,0,0);
		//origin[0] = Vector(0,6,0);/* = position.addVec(Vector(0,6,0));*/
		//origin[1] = origin[0];
		//origin[1].thisVector.y *= (-1);
		//origin[1].X_Y_Z[1] = origin[1].thisVector.y;
		//Quaternion *q = new Quaternion((((1)*M_PI)/180)*(-1),false,false,true);
		//for(int i = 0; i < 50; i++)
		//{
		//	Bullets.push_back(new Model(model));
		//	Bullets.push_back(new Model(model));
		//	particleBullet.push_back(new ParticlePoint(0,1,1,1,4.f,origin[0].addVec(position),dirCopy,bulletAccel,10,60));
		//	particleBullet.push_back(new ParticlePoint(0,1,1,1,4.f,origin[1].addVec(position),dirCopy_2,bulletAccel,10,60));
		//	origin[0].thisVector.y -= 5/50;
		//	origin[0].X_Y_Z[1] = origin[0].thisVector.y;
		//	origin[1] = origin[0];
		//	origin[1].thisVector.y *= (-1);
		//	origin[1].X_Y_Z[1] = origin[1].thisVector.y;
		//}
		//for(int i = 0; i < 50; i++)
		//{
		//	Bullets.push_back(new Model(model));
		//	Bullets.push_back(new Model(model));
		//	dirCopy.multiplyVector(q);
		//	/*dirCopy.multiplyVector(0.1);*/
		//	dirCopy_2 = dirCopy;
		//	dirCopy_2.thisVector.y*=(-1);
		//	dirCopy_2.X_Y_Z[1] = dirCopy_2.thisVector.y;
		//	particleBullet.push_back(new ParticlePoint(0,1,1,1,4.f,origin[0].addVec(position),dirCopy,bulletAccel,10,60));
		//	particleBullet.push_back(new ParticlePoint(0,1,1,1,4.f,origin[1].addVec(position),dirCopy_2,bulletAccel,10,60));
		//}
	}
	}