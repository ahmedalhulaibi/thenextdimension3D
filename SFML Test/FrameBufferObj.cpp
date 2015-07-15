#include "FrameBufferObj.h"

FrameBufferObj::FrameBufferObj(int numColorTargets, bool useDepth, 
							   unsigned int _width, unsigned int _height,
							   bool useLinearFiltering, bool useHDR)
{
	width = _width;
	height = _height;

	if (!numColorTargets && !useDepth)
	{
		numColorTargets = 1;
	}
	// generate FBO in graphics memory
	glGenFramebuffers(1, &fboHandle);
	glBindFramebuffer(GL_FRAMEBUFFER, fboHandle);

	GLint texParam = useLinearFiltering ? GL_LINEAR : GL_NEAREST;
	GLint internalFormat = useHDR ? GL_RGBA16 : GL_RGBA8;
	GLint internalType = useHDR ? GL_UNSIGNED_SHORT : GL_UNSIGNED_BYTE;


	// create a texture for colour storage
	for ( unsigned int i = 0; i < numColorTargets; ++i )
	{
		glGenTextures(1, &fboColorTexture);
		glBindTexture(GL_TEXTURE_2D, fboColorTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, 
			GL_RGBA, internalType, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, 
			GL_TEXTURE_2D, fboColorTexture, 0);
		fboColorTextures.push_back(fboColorTexture);
	}

	// create a texture for depth storage
	if (useDepth)
	{
		glGenTextures(1, &fboDepthTexture);
		glBindTexture(GL_TEXTURE_2D, fboDepthTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, 
			GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, 
			GL_TEXTURE_2D, fboDepthTexture, 0);
	}


	// clear for takeoff... sry :p
	int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		cout << "FRAMEBUFFER CREATION FAILED" << endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glDeleteFramebuffers(1, &fboHandle);
		glDeleteTextures(1, &fboDepthTexture);
		glDeleteTextures(1, &fboColorTexture);
		for(int i = 0; i < fboColorTextures.size(); i++)
		{
			glDeleteTextures(1,&fboColorTextures[i]);
		}
		fboColorTexture = 0;
		fboDepthTexture = 0;
	}

	// finished: good practice is to disable stuff because this is the state 
	// that we had when we started this process
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBufferObj::drawToFBO(void (*pre_draw)(),void (*draw)())//S
{
	this->bindAsFBO();
	pre_draw();
	draw();
	glBindFramebuffer(GL_FRAMEBUFFER,0);
}

void FrameBufferObj::drawFBO(bool color, bool depth)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glViewport(0,0,800,432);

	//glEnable(GL_TEXTURE_2D);
	if(color)
	{
		this->bindAsColorTexture(0);
	}else if(depth)
	{
		this->bindAsDepthTexture();
	}
	
	glColor4f(1.0f, 1.0f, 1.0f,1.0f);
	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1, -1, -1.0f);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f( 1, -1, -1.0f);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1,  1, -1.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 1,  1, -1.0f);
	glEnd();

	this->unbindFBO();
}

FrameBufferObj::~FrameBufferObj(void)
{
}
