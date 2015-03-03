#include "Shader.h"

void Shader::loadMeshUniforms(vec3 thetaData, vec3 scaleData, vec3 transData)
{
	glUniform3fv(theta, 1, value_ptr(thetaData));
	glUniform3fv(scale, 1, value_ptr(scaleData));
	glUniform3fv(translation, 1, value_ptr(transData));
}

void Shader::loadCameraUniforms(vec3 eyeData, vec3 lookatData, vec3 upData, vec4 projectionData)
{
	glUniform3fv(eye, 1,  value_ptr(eyeData));
	glUniform3fv(lookat, 1, value_ptr(lookatData));
	glUniform3fv(up, 1, value_ptr(upData));
	glUniform4fv(projection, 1, value_ptr(projectionData));
}

void Shader::loadAttribute()
{
	glVertexAttribPointer( vPosition, 3, GL_FLOAT, GL_FALSE, 0, ((char *)NULL ));
}

void Shader::loadLightUniforms(vec3 lightPositionData)
{
	glUniform3fv(lightPosition, 1, value_ptr(lightPositionData));
}

void Shader::loadAttributes(int secondOffset, int thirdOffset)
{
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, ((void*) 0));
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, ((void*) secondOffset));
	glVertexAttribPointer(vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, ((void*) thirdOffset));
}

void Shader::loadTexture(char* textureFileName, GLuint* textureIDPtr)
{
	*textureIDPtr = SOIL_load_OGL_texture(textureFileName, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
}

Shader::Shader(char* vertexShaderFile, char* fragmentShaderFile)
{
	//Activating culling and drawing behavior
	glEnable( GL_DEPTH_TEST ); 
	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );

	//Initialize Shader, its Uniforms, and its Attributes

	//Shader
	program = setUpAShader( vertexShaderFile, fragmentShaderFile );
	if (!program) {
		cerr << "Error setting up shaders" << endl;
		exit(1);
	}
	glUseProgram( program );

	//Uniforms
	theta = glGetUniformLocation(program, "theta");
	translation = glGetUniformLocation(program, "trans");
	scale = glGetUniformLocation(program, "scale");
	eye = glGetUniformLocation(program, "eye");
	lookat = glGetUniformLocation(program, "lookat");
	up = glGetUniformLocation(program, "up");
	projection = glGetUniformLocation(program, "projection");
	lightPosition = glGetUniformLocation(program, "lightPosition");

	//Varying (Attributes)
	vPosition = glGetAttribLocation(program, "vPosition" );
	glEnableVertexAttribArray( vPosition );

	vNormal = glGetAttribLocation(program, "vNormal");
	glEnableVertexAttribArray(vNormal);

	vTexCoord = glGetAttribLocation(program, "vTexCoord");
	glEnableVertexAttribArray(vTexCoord);
}

Shader::Shader(void)
{
}


Shader::~Shader(void)
{
}
