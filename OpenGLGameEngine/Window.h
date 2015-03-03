#pragma once

#include <stdlib.h>
#include <iostream>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <GL\GL.h>
#include <glm\glm.hpp>

using namespace std;
using namespace glm;

class Window
{
public:

	Window(char* name, int width, int height);

	Window(void);
	~Window(void);
};

