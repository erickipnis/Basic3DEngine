#pragma once
#include <math.h>

#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

using namespace std;
using namespace glm;

class SphereCollider
{
public:

	float radius;
	vec3 position;
	
	bool collidesWith(SphereCollider collider);

	SphereCollider(vec3 pos, float r);
	~SphereCollider(void);
};

