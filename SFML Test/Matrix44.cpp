#include "Matrix44.h"


Matrix44::Matrix44(void)
{
	for(int r = 0; r<3; r++)
	{
		for(int c = 0; c<3; c++)
		{
			if(r-c == 0)
				matrix44[r][c] =  1.0f;
			else
				matrix44[r][c] =  0.0f;
		}
	}
}

Matrix44::Matrix44(Vector &v, Matrix33 &R)
{
	for(int r = 0; r<4; r++)
	{
		for(int c = 0; c<4; c++)
		{
			if(r < 4 && c < 4)
			{
				if(r == 3 && c == 3)
				{
					matrix44[r][c] = 1.0f;
				}else if(r!=3 && c == 3)
				{
					matrix44[r][c] = v.X_Y_Z[c];
				}else
				{
					matrix44[r][c] =  R.matrix33[r][c];
				}
			}
		}
	}
}
Matrix44::Matrix44(Vector &v, Quaternion &R)
{
	
	this->matrix44[0][0] = 1.f - (2.f * ( (R.y*R.y)+(R.z*R.z) ) );
	this->matrix44[1][0] = (2.f * ( (R.x*R.y)-(R.w*R.z) ) );
	this->matrix44[2][0] = (2.f * ( (R.x*R.z)+(R.w*R.y) ) );
	this->matrix44[3][0] = v.thisVector.x;

	this->matrix44[0][1] = (2.f * ( (R.x*R.y)+(R.w*R.z) ) );
	this->matrix44[1][1] = 1.f - (2.f * ( (R.x*R.x)+(R.z*R.z) ) );
	this->matrix44[2][1] = (2.f * ( (R.y*R.z)-(R.w*R.x) ) );
	this->matrix44[3][1] = v.thisVector.y;

	this->matrix44[0][2] = (2.f * ( (R.x*R.z)-(R.w*R.y) ) );
	this->matrix44[1][2] = (2.f * ( (R.y*R.z)+(R.w*R.x) ) );
	this->matrix44[2][2] = 1.f - (2.f * ( (R.x*R.x)+(R.y*R.y) ) );
	this->matrix44[3][2] = v.thisVector.z;

	this->matrix44[0][3] = 0.f;
	this->matrix44[1][3] = 0.f;
	this->matrix44[2][3] = 0.f;
	this->matrix44[3][3] = 1.f;
	
}

Matrix44::Matrix44(Quaternion &R)
{
	/*
	this->matrix44[0][0] = 1.f - (2.f * ( (R.y*R.y)+(R.z*R.z) ) );
	this->matrix44[0][1] = (2.f * ( (R.x*R.y)-(R.w*R.z) ) );
	this->matrix44[0][2] = (2.f * ( (R.x*R.z)+(R.w*R.y) ) );
	this->matrix44[0][3] = 0.f;

	this->matrix44[1][0] = (2.f * ( (R.x*R.y)+(R.w*R.z) ) );
	this->matrix44[1][1] = 1.f - (2.f * ( (R.x*R.x)+(R.z*R.z) ) );
	this->matrix44[1][2] = (2.f * ( (R.y*R.z)-(R.w*R.x) ) );
	this->matrix44[1][3] = 0.f;

	this->matrix44[2][0] = (2.f * ( (R.x*R.z)-(R.w*R.y) ) );
	this->matrix44[2][1] = (2.f * ( (R.y*R.z)+(R.w*R.x) ) );
	this->matrix44[2][2] = 1.f - (2.f * ( (R.x*R.x)+(R.y*R.y) ) );
	this->matrix44[2][3] = 0.f;

	this->matrix44[3][0] = 0.f;
	this->matrix44[3][1] = 0.f;
	this->matrix44[3][2] = 0.f;
	this->matrix44[3][3] = 1.f;*/

	//The above code is what the rotation matrix should be but the transpose function seems to be messing things up
	//during glMultMatrix stuff so I'm doing this instead, presetting it to the transpose but still getting the same result, it rotates just fine
	//I believe the prblem is in the mouse coordinates
	this->matrix44[0][0] = 1.f - (2.f * ( (R.y*R.y)+(R.z*R.z) ) );
	this->matrix44[1][0] = (2.f * ( (R.x*R.y)-(R.w*R.z) ) );
	this->matrix44[2][0] = (2.f * ( (R.x*R.z)+(R.w*R.y) ) );
	this->matrix44[3][0] = 0.f;

	this->matrix44[0][1] = (2.f * ( (R.x*R.y)+(R.w*R.z) ) );
	this->matrix44[1][1] = 1.f - (2.f * ( (R.x*R.x)+(R.z*R.z) ) );
	this->matrix44[2][1] = (2.f * ( (R.y*R.z)-(R.w*R.x) ) );
	this->matrix44[3][1] = 0.f;

	this->matrix44[0][2] = (2.f * ( (R.x*R.z)-(R.w*R.y) ) );
	this->matrix44[1][2] = (2.f * ( (R.y*R.z)+(R.w*R.x) ) );
	this->matrix44[2][2] = 1.f - (2.f * ( (R.x*R.x)+(R.y*R.y) ) );
	this->matrix44[3][2] = 0.f;

	this->matrix44[0][3] = 0.f;
	this->matrix44[1][3] = 0.f;
	this->matrix44[2][3] = 0.f;
	this->matrix44[3][3] = 1.f;
}
Matrix44 Matrix44::transpose()
{
	Matrix44 _matrix44;
	for(int r = 0; r<4; r++)
	{
		for(int c = 0; c<4; c++)
		{
			if(r-c != 0)
			{
				_matrix44.matrix44[r][c] = matrix44[c][r];
			}
		}
	}

	return _matrix44;
}

void Matrix44::copyIntoSingleArray()
{
	int RC = 0;
	
	for(int r = 0; r < 4; r++)
	{
		for(int c = 0; c < 4; c++)
		{
			OneDmat[RC] = matrix44[r][c];
			RC++;
		}
	}
}
Matrix44::~Matrix44(void)
{
}
