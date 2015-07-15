#pragma once
#include "Shader.h"
#include <vector>
using namespace std;
class ShaderProgram
{
public:
	static void unbindShaders()
	{
		glUseProgram(0);
	};
	ShaderProgram(void);
	~ShaderProgram(void);
	void attachShader(Shader &shader);
	void attachShader(Shader *shader);
	void detachShader(GLuint &shaderID);
	void useProgram();
	void link();

	GLint getUniformVarLoc(const char *varName);
	GLuint getUniformBlockLoc(const char *blockName);

	static GLuint index;//for attributes

	GLuint programID;
	vector <GLuint> shaders_attached;
};

