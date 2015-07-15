#pragma once
#include <OpenGL\glew.h>
#include <iostream>
#include <vector>
using namespace std;
class FrameBufferObj
{
public:
	FrameBufferObj(int numColorTargets, bool useDepth, 
				   unsigned int width, unsigned int height,
				   bool useLinearFiltering, bool useHDR);
	void drawToFBO(void (*pre_draw)(),void (*draw)());
	void drawFBO(bool color, bool depth);

	void bindAsFBO()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fboHandle);
	};

	void bindAsDepthTexture()
	{
		glEnable(GL_TEXTURE_2D); 
		glBindTexture(GL_TEXTURE_2D, fboDepthTexture);
	};

	void bindAsColorTexture(int targNum)
	{
		glEnable(GL_TEXTURE_2D); 
		glBindTexture(GL_TEXTURE_2D, fboColorTextures[targNum]);
	};

	static void unbindFBO()
	{
		glEnable(GL_TEXTURE_2D); 
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	};

	~FrameBufferObj(void);
	GLuint fboHandle;
	
	vector <GLuint> fboColorTextures;
	GLuint fboDepthTexture;
	unsigned int width;
	unsigned int height;
private:
	GLuint fboColorTexture;
};

