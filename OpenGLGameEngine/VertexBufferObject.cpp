#include "VertexBufferObject.h"

void VertexBufferObject::loadBuffers(vector<float>* localVertexBufferPtr, vector<float>* localNormalBufferPtr, vector<float>* localTexCoordBufferPtr)
{
	size = localVertexBufferPtr->size();

	float* vertexArray = new float[size];
	float* normalArray = new float[size];

	for (int i = 0; i < size; i++)
	{
		vertexArray[i] = (*localVertexBufferPtr)[i];
		normalArray[i] = (*localNormalBufferPtr)[i];
	}

	float * texCoArray = new float[size * 2 / 3];

	for (int i = 0; i < size * 2 / 3; i++)
	{
		texCoArray[i] = (*localTexCoordBufferPtr)[i];
	}

	int dataSize = size * sizeof(float);
	int normSize = size * sizeof(float);
	int texCoSize = size * 2 / 3 * sizeof(float);

	glBufferData(GL_ARRAY_BUFFER, dataSize + normSize + texCoSize, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, dataSize, vertexArray);
	glBufferSubData(GL_ARRAY_BUFFER, dataSize, normSize, normalArray);

	glBufferSubData(GL_ARRAY_BUFFER, dataSize + normSize, texCoSize, texCoArray);

	//Element buffer
	GLushort * elementArray = new GLushort[size];

	for (int i=0; i < size; i++)
	{
		elementArray[i] = i;
	}

	int edataSize = size / 3 * sizeof (GLushort);
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, edataSize, elementArray, GL_STATIC_DRAW );

	delete[] vertexArray;
	delete[] normalArray;
	delete[] texCoArray;
	delete [] elementArray;
}

void VertexBufferObject::gen()
{
	glGenBuffers(1, &buffer);
	glGenBuffers(1, &ebuffer);
}

void VertexBufferObject::bind()
{
	glBindBuffer( GL_ARRAY_BUFFER, buffer );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebuffer );
}

VertexBufferObject::VertexBufferObject(void)
{
}

VertexBufferObject::~VertexBufferObject(void)
{
}
