#pragma once
#include <string>
#include <OpenGL\glew.h>
#include <iostream>
using namespace std;

//SHADER TYPE
enum SHADER_TYPE{
	VERT = 0,
	FRAG,
	GEOM
};

class Shader
{
public:
	Shader(SHADER_TYPE x, char *file);
	GLuint getID();
	int getShaderType();
	~Shader(void);
private:
	char *readFromTextFile(char *file);
	GLuint shaderID;
	SHADER_TYPE shaderType;
};

