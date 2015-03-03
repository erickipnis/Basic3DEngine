#include "AxisAlignedBoundingBox.h"

bool AxisAlignedBoundingBox::collidesWith(SphereCollider* sphereColliderPtr)
{
	vec3 sphereCenter = sphereColliderPtr->position;

	float sphereRadius = sphereColliderPtr->radius;
	float* AABBVertices = vertices;

	float distSqrd = 0;

	// Iterate over x, y, z axes
	for (int i = 0; i < 3; i++)
	{
		// Coordinate value of the lower/far/left plane along this axis
		float vMin = min(AABBVertices[i], AABBVertices[i + 3]);

		// Coordinate value of the upper/near/right plane along this axis
		float vMax = max(AABBVertices[i], AABBVertices[i + 3]);

		// Distance (displacement) from sphere to planes along this axis
		float dMin = sphereCenter[i] - vMin;
		float dMax = sphereCenter[i] - vMax;

		// Case 1: Sphere is below/beyond/left of the planes
		// Case 2: Sphere is above/before/right of the planes
		// Case 3: Sphere is between the planes

		if (dMin < 0)
		{
			distSqrd += dMin * dMin;
		}
		else if (dMax > 0)
		{
			distSqrd += dMax * dMax;
		}
		// else distSqrd += 0;

		return (distSqrd <= sphereRadius * sphereRadius);
	}
}

float AxisAlignedBoundingBox::min(float a, float b)
{
	if (a < b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

float AxisAlignedBoundingBox::max(float a, float b)
{
	if (a > b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

AxisAlignedBoundingBox::AxisAlignedBoundingBox(void)
{

}

AxisAlignedBoundingBox::AxisAlignedBoundingBox(vec3 center, float width)
{
	// min X, Y, Z 
	vertices[0] = center.x - (width / 2.0);
	vertices[1] = center.y - (width / 2.0);
	vertices[2] = center.z - (width / 2.0); 
						
	// max X, Y, Z 		
	vertices[3] = center.x + (width / 2.0);
	vertices[4] = center.y + (width / 2.0);
	vertices[5] = center.z + (width / 2.0); 
}


AxisAlignedBoundingBox::~AxisAlignedBoundingBox(void)
{
}
