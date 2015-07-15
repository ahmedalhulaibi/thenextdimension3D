#include "Matrix22.h"


Matrix22::Matrix22(void)
{
	matrix22[0][0] = 0;
	matrix22[0][1] = 0;
	matrix22[1][0] = 0;
	matrix22[1][1] = 0;
	CopyIntoSingleArray();
}

Matrix22::Matrix22(float a, float b, float c, float d)
{
	matrix22[0][0] = a;
	matrix22[0][1] = b;
	matrix22[1][0] = c;
	matrix22[1][1] = d;
	CopyIntoSingleArray();
}

Matrix22::Matrix22(float mat[2][2])
{
	matrix22[0][0] = mat[0][0];
	matrix22[0][1] = mat[0][1];
	matrix22[1][0] = mat[1][0];
	matrix22[1][1] = mat[1][1];
	CopyIntoSingleArray();
}

float Matrix22::determinant()
{
	return ( (matrix22[0][0]*matrix22[1][1]) - (matrix22[0][1]*matrix22[1][0]) );
}


void Matrix22::CopyIntoSingleArray()
{
	
	matrix22_singleArray[0] = matrix22[0][0];
	matrix22_singleArray[1] = matrix22[0][1];
	matrix22_singleArray[2] = matrix22[1][0];
	matrix22_singleArray[3] = matrix22[1][1];
}

Matrix22::~Matrix22(void)
{
}
