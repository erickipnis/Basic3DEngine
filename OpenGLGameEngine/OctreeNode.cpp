#include "OctreeNode.h"

void OctreeNode::add(int sphereColliderIndex)
{
	SphereCollider* sphereColliderPtr = &(*sphereColliderVectorPtr)[sphereColliderIndex];

	if (hasChildren)
	{
		for (int i = 0; i < children.size(); i++) 
		{
			if (children[i].boundingBox.collidesWith(sphereColliderPtr))
			{
				children[i].add(i);
			}
		}
	}
	else if (colliderIndices.size() >= maxColliders && (depth < maxDepth))
	{
		split();

		// Call this collider's add method to re-add the spehere to this node once it has been split
		add(sphereColliderIndex);
	}
	else
	{
		colliderIndices.push_back(sphereColliderIndex);
	}
}

void OctreeNode::split()
{
	if (hasChildren)
	{
		return;
	}
	else
	{
		hasChildren = true;

		for (int k = -1; k <= 1; k += 2) // For z values (far and then near)
		{
			for (int j = -1; j <= 1; j += 2) // For y values (down and then up)
			{
				for (int i = -1; i <= 1; i += 2) // For x values (left and then right)
				{
					vec3 childCenter;
					float halfWidth = width / 2.0;
					float quarterWidth = halfWidth / 2.0;

					childCenter.x = center.x + i * quarterWidth;
					childCenter.x = center.y + j * quarterWidth;
					childCenter.x = center.z + k * quarterWidth;

					children.push_back(OctreeNode(childCenter, depth + 1, halfWidth, sphereColliderVectorPtr));
				}
			}
		}

		while (colliderIndices.size() > 0)
		{
			add(colliderIndices[colliderIndices.size() - 1]);
			colliderIndices.pop_back();
		}

	}
}

bool OctreeNode::detectCollision(SphereCollider* colliderPtr)
{
	if (!hasChildren)
	{
		// check each sphere collider in the collection of this node against this current sphereCollider
		for (int i = 0; i < colliderIndices.size(); i++)
		{
			if ((*sphereColliderVectorPtr)[i].collidesWith(*colliderPtr))
			{
				return true;
			}
		}
	}
	else
	{
		for (int i = 0; i < children.size(); i++)
		{
			// Check if the current collider collides with the bounding box
			if(boundingBox.collidesWith(colliderPtr))
			{
				if (children[i].detectCollision(colliderPtr))
				{
					return true;
				}				
			}

		}
	}

	// No collision was detected
	return false;
}

OctreeNode::OctreeNode(void)
{

}

OctreeNode::OctreeNode(vec3 octreeCenter, int d, float w, vector<SphereCollider>* scvPtr)
{
	hasChildren = false;
	maxColliders = 8;
	maxDepth = 4;

	// OctreeNode Center X, Y and Z values
	center.x = octreeCenter.x;
	center.y = octreeCenter.y;
	center.z = octreeCenter.z;

	depth = d;
	width = w;

	sphereColliderVectorPtr = scvPtr;

	// Once the center of the OctreeNode is calculated, create its bounding box
	boundingBox = AxisAlignedBoundingBox(center, width);
}


OctreeNode::~OctreeNode(void)
{
}
