#pragma once
#include "Model.h"
#include <string>
using namespace std;

class Box : public Model
{
public:
	Box();
	Box(string filename, bool hori);
	~Box();
	void render();
	void setScale(float scaleX, float scaleY, float scaleZ);
private:
	bool hori; //Tracks whether the box is oriented horizontally or not
};