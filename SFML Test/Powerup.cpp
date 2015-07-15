#include "Powerup.h"


Powerup::Powerup(string filename) : Model(filename)
{
	ID=0;
	slerpDT = angle = 0;
	alive=true;
	q1 = Quaternion();
	q2 = Quaternion((359*M_PI)/180,false,true,false);
	setScale(0.3,0.3,0.3);
}

void Powerup::render()
{
	if(slerpDT >= 1)
	{
		slerpDT = 0;
	}
	this->orientation = Quaternion::SLERP(q1,q2,slerpDT);
	orientation.normalize();
	transform = Matrix44(position,orientation);
	transform.copyIntoSingleArray();
	glPushMatrix();
	glMultMatrixf(transform.OneDmat);
	//glTranslatef(position.X_Y_Z[0], position.X_Y_Z[1], position.X_Y_Z[2]);
	//glRotatef(angle,0,1,0);
	glScalef(scaleFactor[0],scaleFactor[1],scaleFactor[2]);
	glBindTexture(GL_TEXTURE_2D, this->modelTexture.texID);
	// Begin drawing of triangles.
	glmDraw(this->model, GLM_SMOOTH | GLM_TEXTURE);
	angle++;
	glPopMatrix();
	slerpDT += 0.1/15;

}

Powerup::~Powerup(void)
{
}
