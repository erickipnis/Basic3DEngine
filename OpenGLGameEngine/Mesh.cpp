#include "Mesh.h"
#include <iostream>

using namespace std;

#define PI 3.14159

vector<float> points;

inline float Mesh::lerp(float min, float max, float t)
{
	return min + t*(max-min);
}

void Mesh::addTriangle(float* data)
{
	for (int i = 0; i < 9; i++)
	{
		localVertexContainer.push_back(data[i]);
	}
}

void Mesh::addTriangle(float x0, float y0, float z0,
					   float x1, float y1, float z1,
					   float x2, float y2, float z2)
{
	localVertexContainer.push_back(x0);
	localVertexContainer.push_back(y0);
	localVertexContainer.push_back(z0);

	localVertexContainer.push_back(x1);
	localVertexContainer.push_back(y1);
	localVertexContainer.push_back(z1);

	localVertexContainer.push_back(x2);
	localVertexContainer.push_back(y2);
	localVertexContainer.push_back(z2);

	// Variables representing the {x,y,z} values of the three points, p1, p2 and p3
	float p1[] = {x0, y0, z0};
	float p2[] = {x1, y1, z1};
	float p3[] = {x2, y2, z2};

	// Variables representing the {x,y,z} values of the ray from p1 to p2 and the ray from p1 to p3
	float r12[] = {p2[0] - p1[0], p2[1] - p1[1], p2[2] - p1[2]};
	float r13[] = {p3[0] - p1[0], p3[1] - p1[1], p3[2] - p1[2]};

	// Variable representing the unit (magnitude 1) normal vector 
	// Cross product r12 and r13 to get something perpendicular to them both
	float nx = r12[1] * r13[2] - r12[2] * r13[1];
	float ny = r12[2] * r13[0] - r12[0] * r13[2];
	float nz = r12[0] * r13[1] - r12[1] * r13[0];

	// Normalize the resulting cross product
	float normalMag = sqrt(nx * nx + ny * ny + nz * nz);
    nx = nx / normalMag;
	ny = ny / normalMag;
	nz = nz / normalMag;

	// Unit-Normal Vector
	float normal[] = {nx, ny, nz};

	// Push the normal vector onto the localNormalContainer once for each vertex
	localNormalContainer.push_back(normal[0]);
	localNormalContainer.push_back(normal[1]);
	localNormalContainer.push_back(normal[2]);

	localNormalContainer.push_back(normal[0]);
	localNormalContainer.push_back(normal[1]);
	localNormalContainer.push_back(normal[2]);

	localNormalContainer.push_back(normal[0]);
	localNormalContainer.push_back(normal[1]);
	localNormalContainer.push_back(normal[2]);
}


void Mesh::addSquare(float v0x,float  v0y, float v0z, float v1x, float v1y, float v1z, float v2x, float v2y, float v2z, float v3x, float v3y, float v3z)
{
	addTriangle(v0x, v0y, v0z,
				v1x, v1y, v1z,
				v2x, v2y, v2z);

	addTriangle(v3x, v3y, v3z,
				v2x, v2y, v2z,
				v1x, v1y, v1z);
}

// No z needed, textures are 2d not 3d. So only 6 floats are needed
void Mesh::addTexCoordTriangle(float u0, float v0, float u1, float v1, float u2, float v2)
{
	localTexCoordContainer.push_back(u0);
	localTexCoordContainer.push_back(v0);

	localTexCoordContainer.push_back(u1);
	localTexCoordContainer.push_back(v1);

	localTexCoordContainer.push_back(u2);
	localTexCoordContainer.push_back(v2);
}

void Mesh::makeCube(int subdivisions)
{
	//front face
	for (int i = 0; i < subdivisions; i++)
	{
		for (int j = 0 ; j < subdivisions; j++)
		{
			//x0 and x1 are theta min and theta max
			//y0 and y1 are phi min and phi max
			float x0 = lerp(-.5, .5,  i		/ float(subdivisions));
			float x1 = lerp(-.5, .5, (i+1)	/ float(subdivisions));
			float y0 = lerp(-.5, .5,  j		/ float(subdivisions));
			float y1 = lerp(-.5, .5, (j+1)	/ float(subdivisions));
			
			//z is -.5 for the front of the cube
			float z = -.5;

			//v0, v1, v2 and v3 are the 4 vector corners of the square patch
			float v0x = x0;
			float v0y = y0;
			float v0z = z;
			
			float v1x = x1;
			float v1y = y0;
			float v1z = z;

			float v2x = x0;
			float v2y = y1;
			float v2z = z;

			float v3x = x1;
			float v3y = y1;
			float v3z = z;

			addSquare(	v3x, v3y, v3z,
						v1x, v1y, v1z,
						v2x, v2y, v2z,
						v0x, v0y, v0z);

			// Texture coordinates
			float u0 = i / float(subdivisions);
			float u1 = (i+1) / float(subdivisions);
			float v0 = j / float(subdivisions);
			float v1 = (j+1) / float(subdivisions);

			addTexCoordTriangle(u0, v0, u1, v0, u0, v1); // Triangle ABC
			addTexCoordTriangle(u1, v1, u0, v1, u1, v0); // Triangle DCB
		}
	}

	//back face
	for (int i = 0; i < subdivisions; i++)
	{
		for (int j = 0 ; j < subdivisions; j++)
		{
			//x0 and x1 are theta min and theta max
			//y0 and y1 are phi min and phi max
			float x0 = lerp(-.5, .5,  i		/ float(subdivisions));
			float x1 = lerp(-.5, .5, (i+1)	/ float(subdivisions));
			float y0 = lerp(-.5, .5,  j		/ float(subdivisions));
			float y1 = lerp(-.5, .5, (j+1)	/ float(subdivisions));
			
			//z is .5 for the back of the cube
			float z = .5;

			//v0, v1, v2 and v3 are the 4 vector corners of the square patch
			float v0x = x0;
			float v0y = y0;
			float v0z = z;
			
			float v1x = x1;
			float v1y = y0;
			float v1z = z;

			float v2x = x0;
			float v2y = y1;
			float v2z = z;

			float v3x = x1;
			float v3y = y1;
			float v3z = z;

			addSquare(	v0x, v0y, v0z,
						v1x, v1y, v1z,
						v2x, v2y, v2z,
						v3x, v3y, v3z);

			// Texture coordinates
			float u0 = i / float(subdivisions);
			float u1 = (i+1) / float(subdivisions);
			float v0 = j / float(subdivisions);
			float v1 = (j+1) / float(subdivisions);

			addTexCoordTriangle(u0, v0, u1, v0, u0, v1); // Triangle ABC
			addTexCoordTriangle(u1, v1, u0, v1, u1, v0); // Triangle DCB
		}
	}


	//left face
	for (int i = 0; i < subdivisions; i++)
	{
		for (int j = 0 ; j < subdivisions; j++)
		{
			//x0 and x1 are theta min and theta max
			//y0 and y1 are phi min and phi max
			float y0 = lerp(-.5, .5,  i		/ float(subdivisions));
			float y1 = lerp(-.5, .5, (i+1)	/ float(subdivisions));
			float z0 = lerp(-.5, .5,  j		/ float(subdivisions));
			float z1 = lerp(-.5, .5, (j+1)	/ float(subdivisions));
			
			//x is -.5 for the left side of the cube
			float x = -.5;

			//v0, v1, v2 and v3 are the 4 vector corners of the square patch
			float v0x = x;
			float v0y = y0;
			float v0z = z0;
			
			float v1x = x;
			float v1y = y1;
			float v1z = z0;

			float v2x = x;
			float v2y = y0;
			float v2z = z1;

			float v3x = x;
			float v3y = y1;
			float v3z = z1;

			addSquare(	v3x, v3y, v3z,
						v1x, v1y, v1z,
						v2x, v2y, v2z,
						v0x, v0y, v0z);

			// Texture coordinates
			float u0 = i / float(subdivisions);
			float u1 = (i+1) / float(subdivisions);
			float v0 = j / float(subdivisions);
			float v1 = (j+1) / float(subdivisions);

			addTexCoordTriangle(u0, v0, u1, v0, u0, v1); // Triangle ABC
			addTexCoordTriangle(u1, v1, u0, v1, u1, v0); // Triangle DCB
		}
	}

	//right face
	for (int i = 0; i < subdivisions; i++)
	{
		for (int j = 0 ; j < subdivisions; j++)
		{
			//x0 and x1 are theta min and theta max
			//y0 and y1 are phi min and phi max
			float y0 = lerp(-.5, .5,  i		/ float(subdivisions));
			float y1 = lerp(-.5, .5, (i+1)	/ float(subdivisions));
			float z0 = lerp(-.5, .5,  j		/ float(subdivisions));
			float z1 = lerp(-.5, .5, (j+1)	/ float(subdivisions));
			
			//x is .5 for the right side of the cube
			float x = .5;

			//v0, v1, v2 and v3 are the 4 vector corners of the square patch
			float v0x = x;
			float v0y = y0;
			float v0z = z0;
			
			float v1x = x;
			float v1y = y1;
			float v1z = z0;

			float v2x = x;
			float v2y = y0;
			float v2z = z1;

			float v3x = x;
			float v3y = y1;
			float v3z = z1;

			addSquare(	v0x, v0y, v0z,
						v1x, v1y, v1z,
						v2x, v2y, v2z,
						v3x, v3y, v3z);

			// Texture coordinates
			float u0 = i / float(subdivisions);
			float u1 = (i+1) / float(subdivisions);
			float v0 = j / float(subdivisions);
			float v1 = (j+1) / float(subdivisions);

			addTexCoordTriangle(u0, v0, u1, v0, u0, v1); // Triangle ABC
			addTexCoordTriangle(u1, v1, u0, v1, u1, v0); // Triangle DCB
		}
	}

	//top face
	for (int i = 0; i < subdivisions; i++)
	{
		for (int j = 0 ; j < subdivisions; j++)
		{
			//x0 and x1 are theta min and theta max
			//y0 and y1 are phi min and phi max
			float x0 = lerp(-.5, .5,  i		/ float(subdivisions));
			float x1 = lerp(-.5, .5, (i+1)	/ float(subdivisions));
			float z0 = lerp(-.5, .5,  j		/ float(subdivisions));
			float z1 = lerp(-.5, .5, (j+1)	/ float(subdivisions));
			
			//y is .5 for the top of the cube
			float y = .5;

			//v0, v1, v2 and v3 are the 4 vector corners of the square patch
			float v0x = x0;
			float v0y = y;
			float v0z = z0;
			
			float v1x = x1;
			float v1y = y;
			float v1z = z0;

			float v2x = x0;
			float v2y = y;
			float v2z = z1;

			float v3x = x1;
			float v3y = y;
			float v3z = z1;

			addSquare(	v3x, v3y, v3z,
						v1x, v1y, v1z,
						v2x, v2y, v2z,
						v0x, v0y, v0z);

			// Texture coordinates
			float u0 = i / float(subdivisions);
			float u1 = (i+1) / float(subdivisions);
			float v0 = j / float(subdivisions);
			float v1 = (j+1) / float(subdivisions);

			addTexCoordTriangle(u0, v0, u1, v0, u0, v1); // Triangle ABC
			addTexCoordTriangle(u1, v1, u0, v1, u1, v0); // Triangle DCB
		}
	}

	//bottom face
	for (int i = 0; i < subdivisions; i++)
	{
		for (int j = 0 ; j < subdivisions; j++)
		{
			//x0 and x1 are theta min and theta max
			//y0 and y1 are phi min and phi max
			float x0 = lerp(-.5, .5,  i		/ float(subdivisions));
			float x1 = lerp(-.5, .5, (i+1)	/ float(subdivisions));
			float z0 = lerp(-.5, .5,  j		/ float(subdivisions));
			float z1 = lerp(-.5, .5, (j+1)	/ float(subdivisions));
			
			//y is -.5 for the bottom of the cube
			float y = -.5;

			//v0, v1, v2 and v3 are the 3 vector corners of the square patch
			float v0x = x0;
			float v0y = y;
			float v0z = z0;
			
			float v1x = x1;
			float v1y = y;
			float v1z = z0;

			float v2x = x0;
			float v2y = y;
			float v2z = z1;

			float v3x = x1;
			float v3y = y;
			float v3z = z1;

			addSquare(	v0x, v0y, v0z,
						v1x, v1y, v1z,
						v2x, v2y, v2z,
						v3x, v3y, v3z);

			// Texture coordinates
			float u0 = i / float(subdivisions);
			float u1 = (i+1) / float(subdivisions);
			float v0 = j / float(subdivisions);
			float v1 = (j+1) / float(subdivisions);

			addTexCoordTriangle(u0, v0, u1, v0, u0, v1); // Triangle ABC
			addTexCoordTriangle(u1, v1, u0, v1, u1, v0); // Triangle DCB
		}
	}
}

void Mesh::makeCylinder(float radius, int radialDivisions, int heightDivisions)
{
	float r = radius;

	for (int i = 0; i < radialDivisions; i++)
	{
		// Top and Bottom Circle
		float t0 = lerp(0, 2*PI,	i /float(radialDivisions));
		float t1 = lerp(0, 2*PI, (i+1)/float(radialDivisions));
			
		float u0x = 0;
		float u0y = 0;
		float u0z = .5;

		float u1x = r * cos(t0);
		float u1y = r * sin(t0);
		float u1z = .5;

		float u2x = r * cos(t1);
		float u2y = r * sin(t1);
		float u2z = .5;

		addTriangle(u0x, u0y, u0z,
					u1x, u1y, u1z,
					u2x, u2y, u2z);

		addTriangle(u2x, u2y, -u2z,
					u1x, u1y, -u1z,
					u0x, u0y, -u0z);

		addTexCoordTriangle(u0x + 0.5, u0y + 0.5, u1x + 0.5, u1y + 0.5, u2x + 0.5, u2y + 0.5);
		addTexCoordTriangle(u0x - 0.5, u0y - 0.5, u1x - 0.5, u1y - 0.5, u2x - 0.5, u2y - 0.5); 
	}

	for (int i = 0; i < radialDivisions; i++)
	{
		for (int j = 0; j < heightDivisions; j++)
		{
			//t0 and t1 are theta min and theta max
			//z0 and z1 are phi min and phi max
			float t0 = lerp(0, 2*PI,	i /float(radialDivisions));
			float t1 = lerp(0, 2*PI, (i+1)/float(radialDivisions));
			float z0 = lerp(-.5, .5,	j /float(heightDivisions));
			float z1 = lerp(-.5, .5, (j+1)/float(heightDivisions));

			// Cylinder Body
			float v0x = r * cos(t0);
			float v0y = r * sin(t0);
			float v0z = z0;

			float v1x = r * cos(t1);
			float v1y = r * sin(t1);
			float v1z = z0;

			float v2x = r * cos(t0);
			float v2y = r * sin(t0);
			float v2z = z1;

			float v3x = r * cos(t1);
			float v3y = r * sin(t1);
			float v3z = z1;

			addSquare(v0x, v0y, v0z,
					  v1x, v1y, v1z,
					  v2x, v2y, v2z,
					  v3x, v3y, v3z);

			// Texture coordinates
			float u0 = i / float(radialDivisions);			
			float u1 = (i + 1) / float(radialDivisions);		
			
			float v0 = j / float(heightDivisions);
			float v1 = (j+1) / float(heightDivisions);
		
			addTexCoordTriangle(u0, v0, u1, v0, u0, v1); // Triangle ABC
			addTexCoordTriangle(u1, v1, u0, v1, u1, v0); // Triangle DCB
		}
	}	
}

void Mesh::makeSphere(float radius, int slices, int stacks)
{
	float R = radius;
	//makeTorus(.1, .5, slices);

	//Iterate over every i,j square patch on the surface
	for (int i = 0; i < slices; i++)
	{
		for (int j = 0; j < stacks; j++)
		{
			//t0 and t1 are theta min and theta max
			//p0 and p1 are phi min and phi max
			float t0 = lerp(0, 2*PI,	i /float(slices));
			float t1 = lerp(0, 2*PI, (i+1)/float(slices));
			float p0 = lerp(-PI / 2.0, PI / 2.0,	j /float(stacks));
			float p1 = lerp(-PI / 2.0, PI / 2.0, (j+1)/float(stacks));

			//v0, v1, v2 and v3 are the 3 vector corners of the square
		    
			float v0x = R * cos(p0) * cos(t0);			
			float v0y = R * cos(p0) * sin(t0);			
			float v0z = R * sin(p0);
			
			float v1x = R * cos(p0) * cos(t1);			
			float v1y = R * cos(p0) * sin(t1);			
			float v1z = R * sin(p0);
			
			float v2x = R * cos(p1) * cos(t0);			
			float v2y = R * cos(p1) * sin(t0);			
			float v2z = R * sin(p1);

			float v3x = R * cos(p1) * cos (t1);
			float v3y = R * cos(p1) * sin(t1);
			float v3z = R * sin(p1);

			addSquare(	v0x, v0y, v0z,
						v1x, v1y, v1z,
						v2x, v2y, v2z,
						v3x, v3y, v3z);

			// Texture coordinates
			float u0 = i / float(slices);			
			float u1 = (i + 1) / float(slices);		
			
			float v0 = j / float(stacks);
			float v1 = (j+1) / float(stacks);
		
			addTexCoordTriangle(u0, v0, u1, v0, u0, v1); // Triangle ABC
			addTexCoordTriangle(u1, v1, u0, v1, u1, v0); // Triangle DCB
		}
	}
}

void Mesh::makeCone(float radius, int radialDivisions, int heightDivisions)
{
	float r = radius;

	for (int i = 0; i < radialDivisions; i++)
	{
		// Bottom Circle
		float t0 = lerp(0, 2 * PI,	i /float(radialDivisions));
		float t1 = lerp(0, 2 * PI, (i+1)/float(radialDivisions));
			
		float u0x = 0;
		float u0y = 0;
		float u0z = .5;

		float u1x = r * cos(t0);
		float u1y = r * sin(t0);
		float u1z = .5;

		float u2x = r * cos(t1);
		float u2y = r * sin(t1);
		float u2z = .5;

		addTriangle(u0x, u0y, u0z,
					u1x, u1y, u1z,
					u2x, u2y, u2z);

		addTexCoordTriangle(u0x + 0.5, u0y + 0.5, u1x + 0.5, u1y + 0.5, u2x + 0.5, u2y + 0.5);
	}

	for (int i = 0; i < radialDivisions; i++)
	{
		for (int j = 0; j < heightDivisions; j++)
		{
			//t0 and t1 are theta min and theta max
			//z0 and z1 are phi min and phi max
			float t0 = lerp(0, 2 * PI,	i /float(radialDivisions));
			float t1 = lerp(0, 2 * PI, (i+1)/float(radialDivisions));
			float z0 = lerp(-.5, .5,	j /float(heightDivisions));
			float z1 = lerp(-.5, .5, (j+1)/float(heightDivisions));			

			float v0x = r * cos(t0) * (z0 + .5);
			float v0y = r * sin(t0) * (z0 + .5);
			float v0z = z0;

			float v1x = r * cos(t1) * (z0 + .5);
			float v1y = r * sin(t1) * (z0 + .5);
			float v1z = z0;

			float v2x = r * cos(t0) * (z1 + .5);
			float v2y = r * sin(t0) * (z1 + .5);;
			float v2z = z1;

			float v3x = r * cos(t1) * (z1 + .5);
			float v3y = r * sin(t1) * (z1 + .5);
			float v3z = z1;

			addSquare(v0x, v0y, v0z,
					  v1x, v1y, v1z,
					  v2x, v2y, v2z,
					  v3x, v3y, v3z);

			// Texture Coordinates
			float u0 = i / float(radialDivisions);
			float u1 = (i+1) / float(radialDivisions);

			float v0 = j / float(heightDivisions);
			float v1 = (j+1) / float(heightDivisions);
			
			addTexCoordTriangle(u0, v0, u1, v0, u0, v1); // Triangle ABC
			addTexCoordTriangle(u1, v1, u0, v1, u1, v0); // Triangle DCB
		}
	}	
}

Mesh::Mesh(void)
{
}


Mesh::~Mesh(void)
{
}
