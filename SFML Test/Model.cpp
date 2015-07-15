#include "Model.h"

Model::Model()
{

}

Model::Model(string filename)
{
	model = glmReadOBJ((char *)filename.c_str());
	if (!model) exit(0);
	//glmUnitize(model);
	glmFacetNormals(model);
	glmVertexNormals(model,90.0);
	this->directionVec = Vector(1,0,0);

	scaleFactor[0]=scaleFactor[1]=scaleFactor[2] = 1;
	glmDimensions(model, dimensions);
	radii[0] = dimensions[0]/2.0;
	radii[1] = dimensions[1]/2.0;
	radii[2] = dimensions[2]/2.0;
	colliding = false;
	collided = false;
}

void Model::loadTexture(string texture_filename)
{
	LoadTGA(&modelTexture, (char *)texture_filename.c_str());
	glGenTextures(1, &modelTexture.texID);
	glBindTexture(GL_TEXTURE_2D, modelTexture.texID);
	glTexImage2D(GL_TEXTURE_2D, 0, modelTexture.bpp / 8, 
		modelTexture.width, modelTexture.height, 0,
		modelTexture.type,GL_UNSIGNED_BYTE,modelTexture.imageData);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glEnable(GL_TEXTURE_2D);
	if(modelTexture.imageData)
	{
		free(modelTexture.imageData);
	}
}

void Model::setScale(float scaleX, float scaleY, float scaleZ)
{
	scaleFactor[0] = scaleX;
	scaleFactor[1] = scaleY;
	scaleFactor[2] = scaleZ;
	radii[0] *= scaleX;
	radii[1] *= scaleY;
	radii[2] *= scaleZ;
}

void Model::render()
{
	
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


Model::~Model()
{

}
