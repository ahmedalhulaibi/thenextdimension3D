#pragma once
//THIS CLASS IS BEING USED FOR COFACTORS
class Matrix22
{
public:
	Matrix22(void);
	Matrix22(float a, float b, float c, float d);
	Matrix22(float mat[2][2]);
	~Matrix22(void);
	float determinant();
	float matrix22_singleArray[4];
private:
	void CopyIntoSingleArray();
	float matrix22[2][2];
};

