#pragma once
#include "SphereCollider.h"

class AxisAlignedBoundingBox
{
public:

	float vertices[6];

	bool collidesWith(SphereCollider* sphereColliderPtr);

	float min(float a, float b);
	float max(float a, float b);

	AxisAlignedBoundingBox(void);
	AxisAlignedBoundingBox(vec3 center, float width);
	~AxisAlignedBoundingBox(void);
};

