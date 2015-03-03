#include "SphereCollider.h"

bool SphereCollider::collidesWith(SphereCollider collider)
{
	float colliderDistance;
	
	float radiusSum = radius + collider.radius;

	colliderDistance = distance(position, collider.position);
	

	if (colliderDistance < radiusSum)
	{
		return true;
	}

	return false;
}

SphereCollider::SphereCollider(vec3 pos, float r)
{
	position.x = pos.x;
	position.y = pos.y;
	position.z = pos.z;

	radius = r;
}


SphereCollider::~SphereCollider(void)
{
}
