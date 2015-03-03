#pragma once
#include <glm\glm.hpp>

using namespace glm;

#define PI 3.14159

class Camera
{
public:

	vec3 eyepoint;
	vec3 lookat;
	vec3 up;
	vec4 projection;

	float yaw;
	float pitch;

	void init();

	void update();

	void moveForward();
	void moveLeft();
	void moveBackward();
	void moveRight();
	void moveUp();
	void moveDown();

	void passViewMatrix();

	Camera(void);
	~Camera(void);
};

