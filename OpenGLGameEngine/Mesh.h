#pragma once

#include <vector>
#include "VertexBufferObject.h"

using namespace std;

class Mesh
{
public:
	// Local vertex, normal and texture coordinate containers
	vector<float> localVertexContainer;
	vector<float> localNormalContainer;
	vector<float> localTexCoordContainer;

	void addTriangle(float* data);

	void addTriangle (float x0, float y0, float z0,
					  float x1, float y1, float z1,
					  float x2, float y2, float z2);

	void addSquare(float v0x,float  v0y, float v0z, float v1x, float v1y, float v1z, float v2x, float v2y, float v2z, float v3x, float v3y, float v3z);

	void addTexCoordTriangle(float u0, float v0, float u1, float v1, float u2, float v2);

	// Initialize shape functions
	void makeCube (int subdivisions);
	void makeCylinder (float radius, int radialDivisions, int heightDivisions);
	void makeCone (float radius, int radialDivisions, int heightDivisions);
	void makeSphere (float radius, int slices, int stacks);

	inline float lerp (float min, float max, float t);

	Mesh(void);
	~Mesh(void);
};