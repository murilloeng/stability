//stability
#include "stability/inc/Canvas.hpp"

//constructor
Canvas::Canvas(QWidget* parent) : QOpenGLWidget(parent)
{
	return;
}

//destructor
Canvas::~Canvas(void)
{
	return;
}

//openGL
void Canvas::initializeGL(void)
{
	//setup
	initializeOpenGLFunctions();
	//clear color
	glClearColor(0, 0, 1, 1);
	
}