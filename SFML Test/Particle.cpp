#include "Particle.h"


Particle::Particle(string filename) : Model(filename)
{
	lifetime = 10*60;//10 seconds * 60fps = actual number of frames
	position = Vector(1,1,0);
	velocity = Vector(1,1,0);
	acceleration = Vector(0,-0.01,0);
	angle = 0;
}

Particle::Particle(float particleSize, Vector position, Vector initialVelocity, Vector acceleration, float lifetime_Seconds, int frameRate, string filename) : Model (filename)
{
	size = particleSize;
	this->position = position;
	velocity = initialVelocity;
	this->acceleration = acceleration;
	lifetime = lifetime_Seconds * frameRate;
	this->radii[0] *= particleSize;
	this->radii[1] *= particleSize;
	this->radii[2] *= particleSize;
	angle = 0;
}

Particle::Particle(float particleSize, Vector position, Vector initialVelocity, Vector acceleration, float lifetime_Seconds, int frameRate, Model model) : Model (model)
{
	angle = 0;
	size = particleSize;
	this->position = position;
	velocity = initialVelocity;
	this->acceleration = acceleration;
	lifetime = lifetime_Seconds;// * frameRate;
	this->radii[0] *= particleSize;
	this->radii[1] *= particleSize;
	this->radii[2] *= particleSize;
}

void Particle::update(float dT)
{
	lifetime-=dT;
	position.addVector(velocity);
	position.addVector(acceleration);
	velocity.addVector(acceleration);
}

void Particle::render()
{
	if(lifetime>0)
	{
		update(1);
		glPushMatrix();
		//glTranslatef(position.X_Y_Z[0],position.X_Y_Z[1],position.X_Y_Z[2]);
		orientation.normalize();
		this->directionVec.multiplyVector(orientation);
		transform = Matrix44(position,orientation);
		transform.copyIntoSingleArray();
		glMultMatrixf(transform.OneDmat);
		glScalef(size,size,size);
		glRotatef(angle,1,0,0);
		angle+=angle;
		glBindTexture(GL_TEXTURE_2D, this->modelTexture.texID);
		// Begin drawing of triangles.
		glmDraw(this->model, GLM_FLAT| GLM_TEXTURE);

		glPopMatrix();
	}
	
}

void Particle::setVelocity(Vector newVelocity)
{
	velocity = newVelocity;
}

void Particle::setAcceleration(Vector newAcceleration)
{
	acceleration = newAcceleration;
}

Particle::~Particle(void)
{
}
