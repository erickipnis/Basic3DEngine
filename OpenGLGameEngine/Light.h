#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

using namespace glm;

class Light
{
public:
	vec3 lightPosition;

	Light(void);
	~Light(void);
};

