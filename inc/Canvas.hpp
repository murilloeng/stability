#pragma once

//qt
#include <QtGui/QOpenGLFunctions>
#include <QtOpenGLWidgets/QOpenGLWidget>

class Canvas : public QOpenGLWidget, public QOpenGLFunctions
{
public:
	//constructors
	Canvas(QWidget*);

	//destructor
	~Canvas(void);

	//openGL
	void initializeGL(void) override;
};