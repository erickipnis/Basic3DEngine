#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Mesh.h"
#include "VertexBufferObject.h"

using namespace glm;

class GameObject
{
public:

	// Texture file name
	char* textureFileName;

	int textureID;

	//Uniform Data
	vec3 thetaData;
	vec3 transData;
	vec3 scaleData;

	VertexBufferObject* vboPtr;
	Mesh* meshPtr;

	void initLocalUniforms();

	GameObject(void);
	~GameObject(void);
};

