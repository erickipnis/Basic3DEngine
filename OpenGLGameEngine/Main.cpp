#include <stdlib.h>
#include <iostream>
#include <string>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include "Camera.h"
#include "Light.h"
#include <GL\SOIL.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

#include "Window.h"
#include "Shader.h"
#include "VertexBufferObject.h"
#include "Mesh.h"
#include "GameObject.h"
#include "SphereCollider.h"
#include "Octree.h"

using namespace std;
using namespace glm;

#define PI 3.14159

Window window1;
Shader shader1;

VertexBufferObject cubeVBO;
VertexBufferObject sphereVBO;
VertexBufferObject cylinderVBO;
VertexBufferObject coneVBO;

Mesh cubeMesh;
Mesh sphereMesh;
Mesh coneMesh;
Mesh cylinderMesh;

Camera camera;

Light light1;

Octree octree;

vector<GameObject> gameObjectVector; 
vector<SphereCollider> sphereColliders;

int frameCount = 0;
int previousTime = 0;

void fpsCounter(void)
{
	// Increase frame count
	frameCount++;
	
	/// Get the number of milliseconds since glutInit called
	// (or first call to glutGet(GLUT ELAPSED TIME))
	int currentTime = glutGet(GLUT_ELAPSED_TIME);

	// calculate time passed
	int timeInterval = currentTime - previousTime;

	// Once per second, calculate average framerate
	if (timeInterval > 1000)
	{
		float fps = (float) frameCount / (( float) timeInterval / 1000.0f);
		
		// Set time
		previousTime = currentTime;

		// Reset frame count 
		frameCount = 0;

		cout << fps << endl;
		
	}
}

void spawnSphere(vec3 transVec, vec3 scaleVec, vec3 rotateVec)
{
	//Mesh sphere;
	GameObject sphere;
	SphereCollider collider(transVec, 0.5);

	sphere.meshPtr = &sphereMesh;
	sphere.vboPtr = &sphereVBO;
	sphere.textureID = int(shader1.wallTextureID);

	sphere.transData.x = transVec.x;
	sphere.transData.y = transVec.y;
	sphere.transData.z = transVec.z;

	sphere.scaleData.x = scaleVec.x;
	sphere.scaleData.y = scaleVec.y;
	sphere.scaleData.z = scaleVec.z;

	sphere.thetaData.x = rotateVec.x;
	sphere.thetaData.y = rotateVec.y;
	sphere.thetaData.z = rotateVec.z;

	for (unsigned int i = 0; i < octree.sphereColliders.size(); i++)
	{
		if (octree.detectCollision(collider))
		{
			return; // there is a collision so don't spawn a sphere
		}
	}

	gameObjectVector.push_back(sphere);
	octree.add(collider);
}

void spawnCube(vec3 transVec, vec3 scaleVec, vec3 rotateVec)
{
	GameObject cube;
	cube.meshPtr = &cubeMesh;
	cube.vboPtr = &cubeVBO;
	cube.textureID = int(shader1.roofTextureID);
	
	cube.transData.x = transVec.x;
	cube.transData.y = transVec.y;
	cube.transData.z = transVec.z;

	cube.scaleData.x = scaleVec.x;
	cube.scaleData.y = scaleVec.y;
	cube.scaleData.z = scaleVec.z;

	cube.thetaData.x = rotateVec.x;
	cube.thetaData.y = rotateVec.y;
	cube.thetaData.z = rotateVec.z;

	gameObjectVector.push_back(cube);
}

void spawnCylinder(vec3 transVec, vec3 scaleVec, vec3 rotateVec)
{
	GameObject cylinder;
	cylinder.meshPtr = &cylinderMesh;	
	cylinder.vboPtr = &cylinderVBO;
	cylinder.textureID = int(shader1.groundTextureID);
	
	cylinder.transData.x = transVec.x;
	cylinder.transData.y = transVec.y;
	cylinder.transData.z = transVec.z;
	
	cylinder.scaleData.x = scaleVec.x;
	cylinder.scaleData.y = scaleVec.y;
	cylinder.scaleData.z = scaleVec.z;
	
	cylinder.thetaData.x = rotateVec.x;
	cylinder.thetaData.y = rotateVec.y;
	cylinder.thetaData.z = rotateVec.z;

	gameObjectVector.push_back(cylinder);
}

void spawnCone(vec3 transVec, vec3 scaleVec, vec3 rotateVec)
{
	GameObject cone;
	cone.meshPtr = &coneMesh;	
	cone.vboPtr = &coneVBO;
	cone.textureID = int(shader1.wallTextureID);
	
	cone.transData.x = transVec.x;
	cone.transData.y = transVec.y;
	cone.transData.z = transVec.z;
	
	cone.scaleData.x = scaleVec.x;
	cone.scaleData.y = scaleVec.y;
	cone.scaleData.z = scaleVec.z;
	
	cone.thetaData.x = rotateVec.x;
	cone.thetaData.y = rotateVec.y;
	cone.thetaData.z = rotateVec.z;

	gameObjectVector.push_back(cone);
}

void mouseInit()
{
	//Hide the cursor for FPS-style mouselook
	glutSetCursor(GLUT_CURSOR_NONE);
}

void mouseclick(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		switch(button)
		{
			case GLUT_LEFT_BUTTON:	
				spawnSphere(camera.lookat,vec3(1.0, 1.0, 1.0), vec3(0, 0, 0));
				break;	// Left click functionality
			
			case GLUT_RIGHT_BUTTON:	
				spawnSphere(camera.lookat,vec3(1.0, 1.0, 1.0), vec3(0, 0, 0));
				break;	//Right click functionality
		}
	}

	glutPostRedisplay();
}

void mouselook(int x, int y)
{
	// calculate a yaw and pitch for the camera based on the current position of the mouse
	float ms = 0.005;
	int dx = 800/2 - x;
	camera.yaw += ms*float(dx);	
		
	int dy = 800/2 - y;
	camera.pitch += ms*float(dy);

	if (dx != 0 || dy != 0)
	{
		glutWarpPointer(800/2, 800/2);
	}
		
	camera.update();

	glutPostRedisplay();
}

void processNormalKeys(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 033:	exit(0);
					break;

		case 'w':   camera.moveForward();
					break;

		case 'a':   camera.moveLeft();
					break;

		case 's':	camera.moveBackward();
					break;

		case 'd':	camera.moveRight();
					break;

	    case 'q':   camera.moveUp();
					break;

		case 'e':   camera.moveDown();
					break;
	}

	glutPostRedisplay();
}

void processSpecialKeys(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:    camera.moveUp();
							 break;

		case GLUT_KEY_DOWN:  camera.moveDown();
							 break;
	}

	glutPostRedisplay();
}

void loadAndDrawGameObject(GameObject * gameObjectPtr)
{
	//Load this mesh's data into the shader program and the GPU vertex buffer
	gameObjectPtr->vboPtr->bind();

	int secondOffset = (gameObjectPtr->meshPtr->localVertexContainer).size() * sizeof(float);
	int thirdOffset = (gameObjectPtr->meshPtr->localNormalContainer.size() * sizeof(float) + secondOffset);
	shader1.loadAttributes(secondOffset, thirdOffset);

	shader1.loadMeshUniforms(gameObjectPtr->thetaData, gameObjectPtr->scaleData, gameObjectPtr->transData);

	glBindTexture(GL_TEXTURE_2D, (gameObjectPtr->textureID));
	
	//Draw what's on the GPU 
	GLsizei count = gameObjectPtr->meshPtr->localVertexContainer.size() / 3;
	glDrawElements (GL_TRIANGLES, count,  GL_UNSIGNED_SHORT, (void *)0);
}

void loadMeshData()
{
	Mesh tempCube;
	tempCube.makeCube(6);
	cubeVBO.gen();
	cubeVBO.bind();
	cubeVBO.loadBuffers(&(tempCube.localVertexContainer), &(tempCube.localNormalContainer), &(tempCube.localTexCoordContainer));

	Mesh tempCylinder;
	tempCylinder.makeCylinder(0.5, 12, 12);
	cylinderVBO.gen();
	cylinderVBO.bind();
	cylinderVBO.loadBuffers(&(tempCylinder.localVertexContainer), &(tempCylinder.localNormalContainer), &(tempCylinder.localTexCoordContainer));

	Mesh tempSphere;
	tempSphere.makeSphere(0.5, 12, 12);
	sphereVBO.gen();
	sphereVBO.bind();
	sphereVBO.loadBuffers(&(tempSphere.localVertexContainer), &(tempSphere.localNormalContainer), &(tempSphere.localTexCoordContainer));

	Mesh tempCone;
	tempCone.makeCone(0.5, 12, 12);
	coneVBO.gen();
	coneVBO.bind();
	coneVBO.loadBuffers(&(tempCone.localVertexContainer), &(tempCone.localNormalContainer), &(tempCone.localTexCoordContainer));
}

void draw( void )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	//load-and-draw game objects
	for (auto &gameObject : gameObjectVector)
	{
		loadAndDrawGameObject(&gameObject);
	}

	shader1.loadCameraUniforms(camera.eyepoint, camera.lookat, camera.up, camera.projection);
	shader1.loadLightUniforms(light1.lightPosition);

	glutSwapBuffers();

	glutPostRedisplay();

	fpsCounter();
}

int main(int argc, char **argv)
{
	glutInit( &argc, argv );

	window1 = Window("OpenGL Game Engine", 800, 800);
	
	glewInit();
	
	shader1 = Shader("vshader.glsl", "fshader.glsl");
	
	loadMeshData();

	mouseInit();

	camera.init();

	glutMouseFunc( mouseclick );
	glutPassiveMotionFunc( mouselook );
	glutKeyboardFunc( processNormalKeys );
	glutSpecialFunc( processSpecialKeys );
	glutDisplayFunc( draw );

	// Initialize each shape mesh's texture file name
	shader1.loadTexture("wallTexture.jpg", &(shader1.wallTextureID));
	shader1.loadTexture("roofTexture2.jpg", &(shader1.roofTextureID));
	shader1.loadTexture("groundTexture.jpg", &(shader1.groundTextureID));

	// Cube
	cubeMesh.makeCube(6);
	spawnCube(vec3(-0.6, 0.6, -3.0), vec3(1.0, 1.0, 1.0), vec3(30, 30, 60));

	// Sphere
	sphereMesh.makeSphere(0.5, 12, 12);
	spawnSphere(vec3(1.0, 0.6, -3.0), vec3(1.0, 1.0, 1.0), vec3(60, 30, 30));

	// Cone
	coneMesh.makeCone(0.5, 12, 12);
	spawnCone(vec3(-0.6, -1.0, -3.0), vec3(1.0, 1.0, 1.0), vec3(90, 30, 30)); 
	
	// Cylinder 
	cylinderMesh.makeCylinder(0.5, 12, 12);
	spawnCylinder(vec3(1.0, -1.0, -3.0), vec3(1.0, 1.0, 1.0), vec3(30, 30, -30));

    glutMainLoop();

	return 0;
}