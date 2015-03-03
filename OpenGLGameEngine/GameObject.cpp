#include "GameObject.h"

GameObject::GameObject(void)
{
	transData.x = 0;
	transData.y = 0;
	transData.z = 0;

	scaleData.x = 1.0;
	scaleData.y = 1.0;
	scaleData.z = 1.0;

	thetaData.x = 0;
	thetaData.y = 0;
	thetaData.z = 0;
}


GameObject::~GameObject(void)
{
}
