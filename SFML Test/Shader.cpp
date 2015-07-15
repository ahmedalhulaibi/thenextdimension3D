#include "Shader.h"


Shader::Shader(SHADER_TYPE x, char *file)
{
	switch(x)
	{
	case VERT:
		this->shaderID = glCreateShader(GL_VERTEX_SHADER);
		shaderType = VERT;
		break;
	case FRAG:
		this->shaderID = glCreateShader(GL_FRAGMENT_SHADER);
		shaderType = FRAG;
		break;
	case GEOM:
		this->shaderID = glCreateShader(GL_GEOMETRY_SHADER);
		shaderType = GEOM;
		break;
	}


	char *code = this->readFromTextFile(file);
	const char *src = code;

	glShaderSource(this->shaderID,1,&src,NULL);
	free(code);
	glCompileShader(this->shaderID);
	GLint error;
	glGetShaderiv(this->shaderID,GL_COMPILE_STATUS,&error);
	if(error == GL_FALSE)
	{
		cout << "SHADER " << this->shaderID << " FAILED TO COMPILE" << endl;
	}

	GLsizei length;
	GLchar infoLog[101];
	glGetShaderInfoLog(this->shaderID,100,&length,infoLog);
	cout << infoLog << endl;
}

GLuint Shader::getID()
{
	return this->shaderID;
}

char* Shader::readFromTextFile(char *fn)
{
	FILE *fp;
    char *content = NULL;
 
    int count=0;
 
    if (fn != NULL) {
        fp = fopen(fn,"rt");
 
        if (fp != NULL) {
 
      fseek(fp, 0, SEEK_END);
      count = ftell(fp);
      rewind(fp);
 
            if (count > 0) {
                content = (char *)malloc(sizeof(char) * (count+1));
                count = fread(content,sizeof(char),count,fp);
                content[count] = '\0';
            }
            fclose(fp);
        }
    }
    return content;
}

int Shader::getShaderType()
{
	return shaderType;
}

Shader::~Shader(void)
{
	glDeleteShader(this->shaderID);
}
