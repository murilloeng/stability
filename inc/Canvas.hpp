#pragma once

//qt
#include <QtOpenGLWidgets/QOpenGLWidget>

class Canvas : public QOpenGLWidget
{
public:
	//constructors
	Canvas(QWidget*);

	//destructor
	~Canvas(void);

	//openGL
	void initializeGL(void) override;
};