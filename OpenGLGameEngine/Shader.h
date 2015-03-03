#pragma once

#include <stdlib.h>
#include <iostream>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <GL\GL.h>
#include <GL\SOIL.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <vector>

#include "shaderProgram.h"

using namespace std;
using namespace glm;

class Shader
{
public:
	//Shader
	GLuint program;

	//Uniform Accessors
	GLuint theta;
	GLuint translation;
	GLuint scale;
	GLuint eye;
	GLuint lookat;
	GLuint up;
	GLuint projection;
	GLuint lightPosition;
	GLuint vNormal;
	GLuint vTexCoord;
	
	GLuint groundTextureID;
	GLuint wallTextureID;
	GLuint roofTextureID;

	//Varying (Attributes)
	GLuint vPosition;

	void loadMeshUniforms(vec3 thetaData, vec3 scaleData, vec3 transData);

	void loadCameraUniforms(vec3 eyeData, vec3 lookatData, vec3 upData, vec4 projectionData);	

	void loadLightUniforms(vec3 lightPositionData);

	void loadAttributes(int secondOffset, int thirdOffset);

	void loadAttribute();

	void loadTexture(char* textureFileName, GLuint* textureIDPtr);

	Shader(char* vertexShaderFile, char* fragmentShaderFile);

	Shader(void);
	~Shader(void);
};