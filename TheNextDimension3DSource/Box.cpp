#include "Box.h"

Box::Box()
{

}

Box::Box(string filename, bool h) : Model(filename)
{
	hori = h;

	if(hori)
	{
		float temp;
		temp = radii[0];
		radii[0] = radii[1];
		radii[1] = temp;
	}
};

void Box::setScale(float scaleX, float scaleY, float scaleZ)
{
	scaleFactor[0] = scaleX;
	scaleFactor[1] = scaleY;
	scaleFactor[2] = scaleZ;

	if(!hori)
	{
		radii[0] *= scaleX;
		radii[1] *= scaleY;
		radii[2] *= scaleZ;
	}
	else
	{
		radii[0] *= scaleY;
		radii[1] *= scaleX;
		radii[2] *= scaleZ;
	}
}

void Box::render()
{
	glPushMatrix(); 
	//glTranslatef(position.X_Y_Z[0],position.X_Y_Z[1],position.X_Y_Z[2]);
	orientation.normalize();
	this->directionVec.multiplyVector(orientation);
	transform = Matrix44(position,orientation);
	transform.copyIntoSingleArray();
	glMultMatrixf(transform.OneDmat);
	if(hori)
	{
		glRotatef(90.f,0,0,1);
	}
	glScalef(scaleFactor[0], scaleFactor[1], scaleFactor[2]);

	glBindTexture(GL_TEXTURE_2D, modelTexture.texID);
	glmDraw(this->model,GLM_FLAT | GLM_TEXTURE);

	glPopMatrix();
}

Box::~Box()
{

}