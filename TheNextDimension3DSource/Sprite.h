#pragma once
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <OpenGL\glew.h>
#include "il.h"
#include "ilu.h"
#include "ilut.h"
#include "Vector.h"
#include <string>
#include <SFML\Graphics\Image.hpp>
using namespace std;

class XY_Coordinate
{
public:
	XY_Coordinate(float _x, float _y, float _u, float _v){ x=_x; y=_y; u = _u; v=_v;}
	~XY_Coordinate(){}
	float x,y;
	float u,v;
};

class SpriteAnimation 
{
public:
	SpriteAnimation(void)
	{
		currentFrame = 0;
		doesLoop = true;
	}
	~SpriteAnimation(void){}
	
	void nextFrame()
	{
		int numFrames = coords.size();
		currentFrame++;
		if(currentFrame >= numFrames)
		{
			if(doesLoop) currentFrame = 0;
			else currentFrame = numFrames - 1;
		}
	}

	void setLooping(bool loop) {doesLoop = loop;}

	/* each animation has a list of x,y coordinates
	   that can be cycled through */
	std::vector<XY_Coordinate*> coords;
	bool doesLoop;
	int currentFrame;
};

typedef struct _SpriteSheetInfo
{
	unsigned int textureID;
	float width,height;
}SpriteSheetInfo;

typedef struct _SpriteSize
{
	float width, height;
	float normalizedWidth,normalizedHeight;
}SpriteSize;

/* Sprite class
 * - this class takes care of everything
     related to sprites 
	 loading/drawing/setting states etc.
 */ 
class Sprite
{
public:
	Sprite(string spriteSheetFilename, float width, float height);
	~Sprite(void);

	void loadSpriteSheet(const string &filename);
	void setSpriteFrameSize(int width, int height);
	void setNumberOfAnimations(int num);
	void addSpriteAnimFrame(int animationNumber, int x, int y);
	void addSpriteAnimRow(int animationNumber, float startX, float startY, float spacingX, float spacingY, int numFrames);

	void setLayerID(float value) {
		layerID = value;
	}

	void setCenter(float x, float y) {
		centerX = x; centerY = y;
	}
	void setPosition(float x, float y, float z) {
		position.thisVector.x = x; position.thisVector.y = y; position.thisVector.z = z;
	}
	void setOrientation(float _theta) {
		theta = _theta;
	}
	float getOrientation() {return theta;}
	float getRadius()
	{
		return sqrt((centerX*centerX)+(centerY*centerY));
	}

	/* drawing */
	virtual void draw();

	void setCurrentAnimation(int anim) {
		currentAnimation = anim;
		if(currentAnimation >= animations.size()) currentAnimation = 0;
	}
	/* update */
	virtual void update();

	void nextFrame(){
		animations[currentAnimation]->nextFrame();
		if(this->currentFrame != this->numberOfFrames)
			this->currentFrame++;
		else
			currentFrame = 1;
	}

	void playOnce(){
		animations[currentAnimation]->setLooping(false);
	}

	void loop(){
		animations[currentAnimation]->setLooping(true);
	}

	/* sprite info */
	SpriteSize sz;
	SpriteSheetInfo sheet;
	int numberOfAnimations;
	int currentAnimation;
	int numberOfFrames;
	int currentFrame;
	bool playAnimOnce;
	/* position/center/orientation */
	/* these should be VECTORS! */
	float centerX,centerY;
	float theta;
	float scale;
	float scaleX,scaleY,scaleZ;
	Vector position;
	Vector *velocityVector;
	Vector *acceleration;

	// which layer this sprite is on, lower is further away, 
	// background is 0, foreground > 0
	int layerID; 
	sf::Image imageID;

	/* list of animations */
	std::vector<SpriteAnimation*> animations;
};
