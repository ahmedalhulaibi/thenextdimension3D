#include "Explosion.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Explosion::Explosion(void)
{
	Quaternion *rotation = new Quaternion(((360*M_PI)/180)/20,false,false,true);
	Vector acceleration(0,-0.001,0);
	Vector velocity(0.1,0,0);
	Vector position(0,0,0);
	for(int n = 0; n<20; n++)
	{
		p.push_back(new ParticlePoint(1.0, 1.0, 1.0, 1.0, 10, position, velocity, acceleration, 10, 60));
		velocity.multiplyVector(rotation);
	}
	dead = false;
	delete rotation;
}

Explosion::Explosion(int numberOfParticles, bool x, bool y, bool z, Vector velocity, Vector acceleration, Vector originPoint, float r, float g, float b, float alpha, float size, float lifetime)
{
	Quaternion *rotation;
	if(x)
	{
		rotation = new Quaternion(((360.0/(float)numberOfParticles)*M_PI)/180.0,true,false,false);
	}else if(y){
		rotation = new Quaternion(((360.0/(float)numberOfParticles)*M_PI)/180.0,false,true,false);
	}else if(z){
		rotation = new Quaternion(((360.0/(float)numberOfParticles)*M_PI)/180.0,false,false,true);
	}

	for(int n = 0; n<numberOfParticles; n++)
	{
		p.push_back(new ParticlePoint(r, g, b, alpha, size, originPoint, velocity, acceleration, lifetime, 60));
		velocity.multiplyVector(rotation);
	}
	dead = false;
}

void Explosion::draw(float dT)
{
	
	for(int i = 0; i< p.size(); i++)
	{
		p[i]->draw(dT);
	}
	if(p[0]->lifetime <= 0)
	{
		dead = true;
	}
}

Explosion::~Explosion(void)
{
}
