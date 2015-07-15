#include "Spawner.h"

Model* Spawner::morphTargets[12];

Spawner::Spawner()
{
}

Spawner::Spawner(string filename, int level) : Model(filename)
{
	this->velocity = Vector(0,0,0);
	spawnCount = 0;
	deltaT = 0;
	morphTargNum = 0;
	if (level == 1)
	{
		health = 100;
		spawnTime = 180;
		sizeLimit = 20;
	}
	else if (level == 2)
	{
		health = 150;
		spawnTime = 180;
		sizeLimit = 40;
	}
	else if (level == 3)
	{
		health = 200;
		spawnTime = 120;
		sizeLimit = 60;
	}
	else if (level == 4)
	{
		health = 250;
		spawnTime = 120;
		sizeLimit = 80;
	}
	else if (level == 5)
	{
		health = 300;
		spawnTime = 120;
		sizeLimit = 80;
	}
}

bool Spawner::update(int enemiesSize)
{
	
	if(enemiesSize < sizeLimit)
	{
		if(spawnTime == spawnCount)
		{
			spawnCount = 0;
			//cout << "Spawned at X: " << enemies.back()->position.thisVector.x << " " << enemies.back()->position.thisVector.y << endl;
			return true;
		}
		else
		{
			spawnCount++;
		}
	}
	return false;
}

void Spawner::morph()
{
	spawnerSound->pos = &this->position;
	spawnerSound->vel = &this->velocity;
	spawnerSound->update();
	for (int i = 1; i <= model->numvertices; i++) 
	{
		this->model->vertices[3 * i + 0] = ((1-deltaT)*morphTargets[morphTargNum]->model->vertices[3 * i + 0]) +  (deltaT*morphTargets[morphTargNum]->model->vertices[3 * i + 0]);
		this->model->vertices[3 * i + 1] = ((1-deltaT)*morphTargets[morphTargNum]->model->vertices[3 * i + 1] )+  (deltaT*morphTargets[morphTargNum]->model->vertices[3 * i + 1]);
		this->model->vertices[3 * i + 2] = ((1-deltaT)*morphTargets[morphTargNum]->model->vertices[3 * i + 2] )+  (deltaT*morphTargets[morphTargNum]->model->vertices[3 * i + 2]);
	}
	deltaT += 0.25;
	if(deltaT >= 1)
	{
		deltaT = 0;
		morphTargNum++;
		if(morphTargNum >=12)
		{
			morphTargNum = 0;
		}
	}
}

void Spawner::render()
{
	morph();
	glPushMatrix(); 
	//glTranslatef(position.X_Y_Z[0],position.X_Y_Z[1],position.X_Y_Z[2]);
	orientation.normalize();
	this->directionVec.multiplyVector(orientation);
	transform = Matrix44(position,orientation);
	transform.copyIntoSingleArray();
	glMultMatrixf(transform.OneDmat);
	glRotatef(90.f,1,0,0);
	glScalef(scaleFactor[0], scaleFactor[1], scaleFactor[2]);

	glBindTexture(GL_TEXTURE_2D, modelTexture.texID);
	glmDraw(this->model,GLM_SMOOTH | GLM_TEXTURE);

	glPopMatrix();
}

Spawner::~Spawner()
{
}