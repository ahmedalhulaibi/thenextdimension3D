#pragma once
#include "Asteroid.h"

void Asteroid::loadNormalMap(string texture_filename)
{
	LoadTGA(&normalMap, (char *)texture_filename.c_str());
	glGenTextures(1, &normalMap.texID);
	glBindTexture(GL_TEXTURE_2D, normalMap.texID);
	glTexImage2D(GL_TEXTURE_2D, 0, normalMap.bpp / 8, 
		normalMap.width, normalMap.height, 0,
		normalMap.type,GL_UNSIGNED_BYTE,normalMap.imageData);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glEnable(GL_TEXTURE_2D);
	if(normalMap.imageData)
	{
		free(normalMap.imageData);
	}
}

void Asteroid::rendra()
{
	glPushMatrix();
	//glTranslatef(position.X_Y_Z[0],position.X_Y_Z[1],position.X_Y_Z[2]);
	orientation.normalize();
	this->directionVec.multiplyVector(orientation);
	transform = Matrix44(position,orientation);
	transform.copyIntoSingleArray();
	glMultMatrixf(transform.OneDmat);
	glScalef(scaleFactor[0], scaleFactor[1], scaleFactor[2]);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->modelTexture.texID);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, this->normalMap.texID);
	// Begin drawing of triangles.
	glmDraw(this->model, GLM_SMOOTH | GLM_TEXTURE);

	glPopMatrix();
}

void Asteroid::direct()
{
	float angle;
	angle = rand()%360;
	randAngle = angle;
	rotAngle = new Quaternion((randAngle*M_PI)/180,false,false,true);
	rotAngle.normalize();
	directionVec.multiplyVector(rotAngle);
	velocity = directionVec;
	velocity.thisVector.z = 0;
	velocity.X_Y_Z[2] = 0;
	velocity.multiplyVector(0.2);
}