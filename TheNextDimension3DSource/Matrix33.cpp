#include "Matrix33.h"
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Matrix33::Matrix33(void)
{
	for(int r = 0; r<3; r++)
	{
		for(int c = 0; c<3; c++)
		{
			if(r-c == 0)
				matrix33[r][c] =  1.0f;
			else
				matrix33[r][c] =  0.0f;
		}
	}
}

Matrix33::Matrix33(float mat[3][3])
{
	for(int r = 0; r<3; r++)
	{
		for(int c = 0; c<3; c++)
		{
			matrix33[r][c] =  mat[r][c];
		}
	}
}

Matrix33::Matrix33(float a, float b, float c, float d, float e, float f, float g, float h, float i)
{
	matrix33[0][0] =  a;
	matrix33[0][1] =  b;
	matrix33[0][2] =  c;
	matrix33[1][0] =  d;
	matrix33[1][1] =  e;
	matrix33[1][2] =  f;
	matrix33[2][0] =  g;
	matrix33[2][1] =  h;
	matrix33[2][2] =  i;
}

Matrix33::Matrix33(float angleDegrees, bool x, bool y, bool z)
{
	float radians = (angleDegrees * (float)(M_PI))/180;
	if(x)
	{
		matrix33[0][0] = 1.0f;
		matrix33[0][1] = 0.0f;
		matrix33[0][2] = 0.0f;
		matrix33[1][0] = 0.0f;
		matrix33[1][1] =  cos(radians);
		matrix33[1][2] =  (-1)*sin(radians);
		matrix33[2][0] = 0.0f;
		matrix33[2][1] =  sin(radians);
		matrix33[2][2] =  cos(radians);
	}
	else if(y)
	{
		matrix33[0][0] =  cos(radians);
		matrix33[0][1] = 0.0f;
		matrix33[0][2] =  sin(radians);
		matrix33[1][0] = 0.0f;
		matrix33[1][1] = 1.0f;
		matrix33[1][2] = 0.0f;
		matrix33[2][0] =  (-1)*sin(radians);
		matrix33[2][1] = 0.0f;
		matrix33[2][2] =  cos(radians);
	}
	else if(z)
	{
		matrix33[0][0] =  cos(radians);
		matrix33[0][1] =  (-1)*sin(radians);
		matrix33[0][2] = 0.0f;
		matrix33[1][0] =  sin(radians);
		matrix33[1][1] =  cos(radians);
		matrix33[1][2] = 0.0f;
		matrix33[2][0] = 0.0f;
		matrix33[2][1] = 0.0f;
		matrix33[2][2] = 1.0f;
	}
}

Matrix33 Matrix33::add(Matrix33 *otherMat33)
{
	float mat33[3][3];
	for(int r = 0; r<3; r++)
	{
		for(int c = 0; c<3; c++)
		{
			mat33[r][c] = this->matrix33[r][c] + otherMat33->matrix33[r][c];
		}
	}

	return Matrix33(mat33);	
}

Matrix33 Matrix33::subtract(Matrix33 *otherMat33)
{
	float mat33[3][3];
	for(int r = 0; r<3; r++)
	{
		for(int c = 0; c<3; c++)
		{
			mat33[r][c] = this->matrix33[r][c] - otherMat33->matrix33[r][c];
		}
	}

	return Matrix33(mat33);
}

void Matrix33::multiplyScalar(float scalar)
{
	for(int r = 0; r<3; r++)
	{
		for(int c = 0; c<3; c++)
		{
			this->matrix33[r][c]*=scalar;
		}
	}
}

Matrix33 Matrix33::multiplayMatrix(Matrix33 *otherMat33)
{
	float mat33[3][3] = { {0,0,0}, {0,0,0}, {0,0,0} };
	int row = 0, col = 0;
	for(int r = 0; r<3; r++)
	{
		for(int c = 0; c<3; c++)
		{
			mat33[row][col] += this->matrix33[r][c] * otherMat33->matrix33[c][r];
		}
		col++;
		if(col == 3)
		{
			col = 0;
			row++;
		}
	}

	return Matrix33(mat33);
}

Matrix33 Matrix33::transpose()
{
	Matrix33 _matrix33(matrix33);
	
	for(int r = 0; r<3; r++)
	{
		for(int c = 0; c<3; c++)
		{
			if(r-c != 0)
			{
				_matrix33.matrix33[r][c] = matrix33[c][r];
			}
		}
	}

	return _matrix33;
}


void Matrix33::CopyIntoSingleArray()
{
	/*OPENGL IS COLUMN MAJOR, THEREFORE WHEN PASSING THE SINGLE ARRAY INTO OPENGL WE MUST TRANSPOSE THE MATRIX*/
	Matrix33 temp = this->transpose();
	int RC = 0;
	
	for(int r = 0; r < 3; r++)
	{
		for(int c = 0; c < 3; c++)
		{
			matrix33_singleArray[RC] = temp.matrix33[r][c];
			RC++;
		}
	}
}

Matrix33::~Matrix33(void)
{
}