#include "ParticlePoint.h"


ParticlePoint::ParticlePoint(void)
{
	r = g = b = alpha = size =  1.0;
	lifetime = 10;//*60;//10 seconds * 60fps = actual number of frames
	position = Vector(1,1,0);
	velocity = Vector(1,1,0);
	acceleration = Vector(0,-0.01,0);
	alpha_fadeIncr = alpha/lifetime;
	useRand = true;
}

ParticlePoint::ParticlePoint(float _r, float _g, float _b, float _alpha, float pointSize, Vector& position, Vector& initialVelocity, Vector& acceleration, float lifetime_Seconds, int frameRate)
{
	r = _r;
	g = _g;
	b = _b;
	alpha = _alpha;
	size = pointSize;
	this->position = position;
	velocity = initialVelocity;
	this->acceleration = acceleration;
	lifetime = lifetime_Seconds;// * frameRate;
	alpha_fadeIncr =  alpha/lifetime;
	useRand = true;
}

void ParticlePoint::update(float dT)
{
	lifetime-=dT;
	position.addVector(velocity);
	position.addVector(acceleration);
	velocity.addVector(acceleration);
}

void ParticlePoint::draw(float dT)
{
	if(lifetime>0)
	{
		update(dT);
		/*glPushMatrix();
		glPointSize(size);
		glBegin(GL_POINTS);*/
		glColor4f(r,g,b,alpha);
		if(useRand)
		{
			if(randomX <0)
			{
				randomX = (((float)rand()/(float)RAND_MAX)*(-1));
			}
			else
			{
				randomX = ((float)rand()/(float)RAND_MAX);
			}
			if(randomY <0)
			{
				randomY = (((float)rand()/(float)RAND_MAX)*(-1));
			}
			else
			{
				randomY = ((float)rand()/(float)RAND_MAX);
			}
			glVertex3f(this->position.thisVector.x+randomX,this->position.thisVector.y+randomY,-1);
		}else
		{
			glVertex3f(this->position.thisVector.x,this->position.thisVector.y,-1);
		}

		
			
		/*glEnd();*/
		alpha -= alpha_fadeIncr;
		/*glPopMatrix();*/
	}
	glColor4f(1,1,1,1);
}

void ParticlePoint::setColor(float _r, float _g, float _b, float _alpha)
{
	r = _r;
	g = _g;
	b = _b;
	alpha = _alpha;
}

void ParticlePoint::setVelocity(Vector &newVelocity)
{
	velocity = newVelocity;
}

void ParticlePoint::setAcceleration(Vector &newAcceleration)
{
	acceleration = newAcceleration;
}

ParticlePoint::~ParticlePoint(void)
{
}
