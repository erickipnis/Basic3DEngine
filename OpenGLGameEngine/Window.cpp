#include "Window.h"

Window::Window(char* name, int width, int height)
{
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
		
	glutInitWindowSize(width, height);
	glutCreateWindow( name );

	//Whenever the draw command clears the color buffer, this color covers the screen
	vec3 cornflowerBlueRGB = vec3(.392, .584, .929);
	glClearColor(cornflowerBlueRGB.r, cornflowerBlueRGB.g, cornflowerBlueRGB.b, 1.0);
}

Window::Window(void)
{
}


Window::~Window(void)
{
}