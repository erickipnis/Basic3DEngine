#pragma once
#include <vector>
#include "SphereCollider.h"
#include "AxisAlignedBoundingBox.h"
#include "OctreeNode.h"

#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

using namespace std;
using namespace glm;

class Octree
{
public:

	OctreeNode rootNode;

	vector<SphereCollider> sphereColliders;

	vec3 center;

	void add(SphereCollider collider);
	bool detectCollision(SphereCollider collider);

	Octree(void);
	~Octree(void);
};

