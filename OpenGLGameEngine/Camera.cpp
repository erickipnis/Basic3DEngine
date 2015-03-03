#include "Camera.h"
#include <math.h>

void Camera::init()
{
	eyepoint.x = 0;
	eyepoint.y = 0;
	eyepoint.z = 0;

	lookat.x = 0;
	lookat.y = 0;
	lookat.z = -1;

	up.x = 0;
	up.y = 1;
	up.z = 0;

	projection.x = .1;
	projection.y = 100;
	projection.z = .1;
	projection.w = .1;

	yaw = 0;
	pitch = 0;
}

Camera::Camera(void)
{
}


Camera::~Camera(void)
{
}

void Camera::update()
{
	if (pitch < -PI / 2)
	{
		pitch = -PI / 2;
	}
	else if (pitch > PI / 2)
	{
		pitch = PI/ 2;
	}

	lookat.x = eyepoint.x - cos(pitch) * sin(yaw);
	lookat.y = eyepoint.y + sin(pitch);
	lookat.z = eyepoint.z - cos(pitch) * cos(yaw);

	up.x = -cos(pitch + PI / 2.0) * sin(yaw);
	up.y = sin(pitch + PI / 2.0);
	up.z = -cos(pitch + PI / 2.0) * cos(yaw);

}

void Camera::moveForward()
{
	float moveSpeed = .1;

	eyepoint.x -= moveSpeed * sin(yaw);
	eyepoint.z -= moveSpeed * cos(yaw);

	update();
}

void Camera::moveLeft()
{
	float moveSpeed = .1;

	eyepoint.x -= moveSpeed * cos(yaw);
	eyepoint.z += moveSpeed * sin(yaw);

	update();
}

void Camera::moveBackward()
{
	float moveSpeed = .1;

	eyepoint.x += moveSpeed * sin(yaw);
	eyepoint.z += moveSpeed * cos(yaw);

	update();
}

void Camera::moveRight()
{
	float moveSpeed = .1;

	eyepoint.x += moveSpeed * cos(yaw);
	eyepoint.z -= moveSpeed * sin(yaw);

	update();
}

void Camera::moveUp()
{
	float moveSpeed = .1;
	
	eyepoint.y += moveSpeed;

	update();
}

void Camera::moveDown()
{
	float moveSpeed = .1;
	
	eyepoint.y -= moveSpeed;

	update();
}