#pragma once
#include "Sprite.h"
#include <vector>
#include <string>
#include <map>
using namespace std;

struct button{
	//button location
	int x,y;
	int width, height;

	//button borders
	int top, bottom, left, right;

};

//class that will handle menu
//button detection and such
//attach a background sprite and buttons to it

//HOW TO---------------------------------------------------
//creat a menupage object associated with the menupage sprite
//add all the buttons manually, in order
//you can access the buttons through vector built in to this class

class menuPage : public Sprite
{
public:
	menuPage(string filename, float w, float h);

	void createButton(int x, int y, int width,int height);
	void initKeys();
	bool checkButtonCollision(int mouseX, int mouseY);

	~menuPage(void);

	vector<button> buttons;
	vector<int> actionKeys;
	Sprite* menuSprite;
	int oldKey;
	int currentButton;
	int currentJoystickButton;
	bool stopCollision;
	bool exitClick;

	map<string, int> keys;
};

