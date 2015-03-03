#pragma once

#include <stdlib.h>
#include <iostream>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <GL\GL.h>
using namespace std;

#include <vector>

class VertexBufferObject
{
public:
	//Buffers
	GLuint buffer;
	GLuint ebuffer;
	int size;

	void loadBuffers(vector<float>* localVertexBufferPtr, vector<float>* localNormalBufferPtr, vector<float>* localTexCoordBufferPtr);

	void bind();
	void gen();

	VertexBufferObject(void);
	~VertexBufferObject(void);
};