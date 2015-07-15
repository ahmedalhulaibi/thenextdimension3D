#include "ShaderProgram.h"

GLuint ShaderProgram::index = 0;

ShaderProgram::ShaderProgram(void)
{
	this->programID = glCreateProgram();
}

void ShaderProgram::attachShader(Shader &shader)
{
	glAttachShader(this->programID,shader.getID());
	shaders_attached.push_back(shader.getID());
	/*GLsizei length;
	GLchar infoLog[101];
	glGetShaderInfoLog(this->programID,100,&length,infoLog);
	cout << infoLog << endl;*/
}

void ShaderProgram::attachShader(Shader *shader)
{
	glAttachShader(this->programID,shader->getID());
	shaders_attached.push_back(shader->getID());
	/*GLsizei length;
	GLchar infoLog[101];
	glGetShaderInfoLog(this->programID,100,&length,infoLog);
	cout << infoLog << endl;*/
}

void ShaderProgram::link()
{
	glLinkProgram(this->programID);
	GLsizei length;
	GLchar infoLog[101];
	glGetShaderInfoLog(this->programID,100,&length,infoLog);
	cout << infoLog << endl;
	GLint error;
	glGetProgramiv(this->programID,GL_LINK_STATUS,&error);
	if(error == GL_FALSE)
	{
		cout << "PRORGAM " << this->programID << " FAILED TO LINK." << endl;
	}
}

void ShaderProgram::useProgram()
{
	glUseProgram(this->programID);
}

void ShaderProgram::detachShader(GLuint &shaderID)
{
	glDetachShader(this->programID,shaderID);
}

GLint ShaderProgram::getUniformVarLoc(const char * varName)
{
	return glGetUniformLocation(this->programID, varName);
	GLsizei length;
	GLchar infoLog[101];
	glGetShaderInfoLog(this->programID,100,&length,infoLog);
	cout << infoLog << endl;
}

GLuint ShaderProgram::getUniformBlockLoc(const char * blockName)
{
	return glGetUniformBlockIndex(this->programID, blockName);
	GLsizei length;
	GLchar infoLog[101];
	glGetShaderInfoLog(this->programID,100,&length,infoLog);
	cout << infoLog << endl;
}

ShaderProgram::~ShaderProgram(void)
{
	for(int i = 0; i < shaders_attached.size(); i++)
	{
		this->detachShader(shaders_attached[i]);
	}
	glDeleteProgram(this->programID);
}
