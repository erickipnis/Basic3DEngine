#include "Octree.h"

void Octree::add(SphereCollider collider)
{
	// Add the sphere collider to the vector 
	sphereColliders.push_back(collider);

	// Pass this sphere collider's index to the root octreeNode's add method
	rootNode.add(sphereColliders.size() - 1);
}

bool Octree::detectCollision(SphereCollider collider)
{
	if(rootNode.detectCollision(&collider))
	{
		return true;
	}

	return false;
}

Octree::Octree(void)
{
	// Default center of the octree
	center.x = 0;
	center.y = 0;
	center.z = 0;

	// Default root node instantiation
	rootNode = OctreeNode(center, 0, 100, &sphereColliders);
}


Octree::~Octree(void)
{
}
