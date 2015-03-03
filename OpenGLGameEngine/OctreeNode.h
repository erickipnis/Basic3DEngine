#pragma once
#include <vector>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "SphereCollider.h"
#include "AxisAlignedBoundingBox.h"

using namespace std;
using namespace glm;

class OctreeNode
{
public:

	vec3 center;
	float width;

	int depth;
	int maxDepth;
	int maxColliders;

	bool hasChildren;

	vector<OctreeNode> children;
	vector<int> colliderIndices;	

	vector<SphereCollider>* sphereColliderVectorPtr;

	AxisAlignedBoundingBox boundingBox;

	void add(int sphereColliderIndex);
	void split();
	bool detectCollision(SphereCollider* colliderPtr);

	OctreeNode(void);
	OctreeNode(vec3 octreeCenter, int d, float w, vector<SphereCollider>* scvPtr);
	~OctreeNode(void);
};

