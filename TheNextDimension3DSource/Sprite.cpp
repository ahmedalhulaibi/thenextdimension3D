#include "Sprite.h"
using namespace std;

/* THE SPRITE CLASS DEFINITION */
Sprite::Sprite(string spriteSheetFilename, float width, float height)
{
	sheet.width = width;
	sheet.height = height;
	this->loadSpriteSheet(spriteSheetFilename.c_str());
	currentAnimation = 0;
	layerID = 0;
	theta = 0;
	centerX = 0;
	centerY = 0;
	scale = 0.065f;
	velocityVector = new Vector(coord(0,0,0),coord(0,0,0));
	this->numberOfFrames = 0;
	this->currentFrame = 0;
	this->playAnimOnce = false;
	scaleX = scaleY = scaleZ = 1;
	
}

Sprite::~Sprite(void)
{
}

void Sprite::loadSpriteSheet(const string &filename)
{
	/*sheet.textureID = ilutGLLoadImage((char*)filename);
	sheet.width = ilGetInteger(IL_IMAGE_WIDTH);
	sheet.height = ilGetInteger(IL_IMAGE_HEIGHT);*/

	imageID.loadFromFile(filename);

	glGenTextures(1, &sheet.textureID);
	glBindTexture(GL_TEXTURE_2D, sheet.textureID);

	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RGBA,
		sheet.width, sheet.height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, imageID.getPixelsPtr()
	);

	//set clamping methods
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void Sprite::setSpriteFrameSize(int width, int height)
{
	sz.width = width;
	sz.height = height;
	sz.normalizedWidth = (float)width/(float)sheet.width;
	sz.normalizedHeight = (float)height/(float)sheet.height;
}

void Sprite::setNumberOfAnimations(int num)
{
	numberOfAnimations = num;
	animations.reserve(num);
	for(int i=0;i<num;i++)
	{
		SpriteAnimation *anim = new SpriteAnimation();
		animations.push_back(anim);
	}
}

//*
// * addSpriteAnimFrame()
// *  - this adds a sprite animation frame to the end of the particular animation list
// *  - (x,y) specify the pixel values of the bottom left corner of the frame
// *  - animationNumber specifies which animation (i.e. JUMP, RUN, etc)
// *    you could use enum's for easier coding 
// */
void Sprite::addSpriteAnimFrame(int animationNumber, int x, int y)
{
	float u,v;
	u = (float)x/sheet.width;
	v = (float)y/sheet.height;
	this->numberOfFrames++;
	XY_Coordinate *xy = new XY_Coordinate(x,y, u,v);
	animations[animationNumber]->coords.push_back(xy);
}

void Sprite::addSpriteAnimRow(int animationNumber, float startX, float startY, float spacingX, float spacingY, int numFrames)
{
	float x,y;
	x = startX;
	this->numberOfFrames+=numFrames;
	y = startY;
	for(int i=0;i<numFrames;i++)
	{
		x += spacingX;
		y += spacingY;
		addSpriteAnimFrame(animationNumber, x,y);
	}
}

//*
// * draw()
// * - this draws the sprite texture at its current frame of its current animation
// * - it positions the sprite based on the transformation formula:
// *    v' = RotationMatrix*(v-center) + position
// * where position is the bottom left corner of the sprite
// * and v is each corner of the sprite rectangle, v' is the transformed corner
// * and RotationMatrix is defined by the sprite's theta value (counter clockwise)
// */
void Sprite::draw()
{
	glEnable(GL_TEXTURE_2D);

	/* draw the sprite */
	glPushMatrix();
	//glRotatef(180,1,0,0);
	glScalef(0.065f, 0.065f, 0.065f);
	//glScalef(scale, scale, scale);

	/* position the sprite into the particular pixel location */
	glTranslatef(position.thisVector.x,position.thisVector.y,position.thisVector.z);
	// apply the rotation around the center of the sprite
	glTranslatef(centerX,centerY,0);
	glRotatef(theta, 0,0,1);
	glTranslatef(-centerX,-centerY,0);
	glScalef(scaleX, scaleY, scaleZ);

	
	/* get the texture coordinate from the sprite so we know which frame to draw */
	SpriteAnimation *anim = animations[currentAnimation];
	//currentFrame = anim->currentFrame;
	float u,v;
	u = anim->coords[currentFrame]->u;
	v = anim->coords[currentFrame]->v;
	//(GL_ALPHA_TEST);
		/* bind the appropriate texture frame */
		/* draw the image as a quad the size of the first loaded image */
	glBindTexture(GL_TEXTURE_2D, sheet.textureID);
	
	glColor4f(0,0,0,1.0);
		glBegin(GL_QUADS);
			
		   //bottom left
		    glTexCoord2f(u ,v+sz.normalizedHeight);
			glVertex3f(0,0,0);
			glNormal3f(0,1,0);
			
			//top left
			glTexCoord2f(u ,v);
			glVertex3f(0,sz.height,0);
			glNormal3f(0,1,0);
			
			//top right
			glTexCoord2f(u + sz.normalizedWidth,v);
			glVertex3f(sz.width,sz.height,0);
			glNormal3f(0,1,0);
			
			//bottom right
			glTexCoord2f(u + sz.normalizedWidth,v+sz.normalizedHeight);
			glVertex3f(sz.width,0,0);
			glNormal3f(0,1,0);
		glEnd();
	glPopMatrix();
	glColor4f(1,1,1,1);
}

//* update()
// * - this function could update things like physics and position
// */
void Sprite::update()
{
	//Update sprite here


}
