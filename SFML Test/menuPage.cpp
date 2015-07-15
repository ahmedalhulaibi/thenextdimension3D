#include "menuPage.h"

menuPage::menuPage(string filename, float w, float h) : 
Sprite(filename, w, h)

{
	//constructor things here
	currentButton = NULL;
	currentJoystickButton = 0;
	oldKey = 0;
	exitClick = false;
	stopCollision = false;
}

void menuPage::createButton(int x, int y, int width, int height)
{
	button temp = {x,y,width, height};

	//setting up the box boundries
	temp.top = temp.y + temp.height;
	temp.bottom = y;
	temp.left = x;
	temp.right = x + temp.width;

	buttons.push_back(temp);
}

bool menuPage::checkButtonCollision(int mouseX, int mouseY)
{
	if(!stopCollision)
	{
		for(int i = 0; i<buttons.size(); i++)
		{
			if((mouseY >= buttons[i].bottom && mouseY <= buttons[i].top) &&
				(mouseX >= buttons[i].left && mouseX <= buttons[i].right))
			{
				currentButton = i;
				return true;
			}
		}
		currentButton = 999;
		return false;
	}
	else
		return false;
}

void menuPage::initKeys()
{
	keys["A"] = 0;  keys["B"] = 1;  keys["C"] = 2;  keys["D"] = 3;
	keys["E"] = 4;  keys["F"] = 5;  keys["G"] = 6;  keys["H"] = 7;
	keys["I"] = 8;  keys["J"] = 9;  keys["K"] = 10; keys["L"] = 11;
	keys["M"] = 12; keys["N"] = 13; keys["O"] = 14; keys["P"] = 15;
	keys["Q"] = 16; keys["R"] = 17; keys["S"] = 18; keys["T"] = 19;
	keys["U"] = 20; keys["V"] = 21; keys["W"] = 22; keys["X"] = 23;
	keys["Y"] = 24; keys["Z"] = 25;

	keys["Num 0"] = 26; keys["Num 1"] = 27; keys["Num 2"] = 28; keys["Num 3"] = 29;
	keys["Num 4"] = 30; keys["Num 5"] = 31; keys["Num 6"] = 32; keys["Num 7"] = 33;
	keys["Num 8"] = 34; keys["Num 9"] = 35; 

	keys["LControl"] = 37;  keys["LShift"] = 38; keys["LAlt"] = 39;   keys["RControl"] = 41;
	keys["RShift"] = 42;    keys["RAlt"] = 43;   keys["["] = 46;      keys["]"] = 47;
	keys[";"] = 48;         keys[","] = 49;      keys["."] = 50;      keys["'"] = 51;
	
	keys["/"] = 52;	   keys["Backslash"] =53;  keys["Tilde"] = 54;    keys["="] = 55;
	keys["-"] = 56;    keys["Spacebar"] = 57;  keys["Return"] = 58;   keys["Backspace"] = 59;
	keys["Tab"] = 60;  keys["PageUp"] = 61;    keys["PageDown"] = 62; keys["End"] = 63;
	keys["Home"] = 64; keys["Insert"] = 65;    keys["Delete"] = 66;

	keys["Left"] = 71;  keys["Right"] = 72;  keys["Up"] = 73;  keys["Down"] = 74;

	keys["F1"] = 85;   keys["F2"] = 86;   keys["F3"] = 87;   keys["F4"] = 88;
	keys["F5"] = 89;   keys["F6"] = 90;   keys["F7"] = 91;   keys["F8"] = 92;
	keys["F9"] = 93;   keys["F10"] = 94;  keys["F11"] = 95;  keys["F12"] = 96;

	//changing keys
	keys["..."] = 99;

}

menuPage::~menuPage(void)
{
	//destructor things here
}
