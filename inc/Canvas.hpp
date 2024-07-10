#pragma once

//qt gui
#include <QtGui/QOpenGLFunctions>

//qt opengl widgets
#include <QtOpenGLWidgets/QOpenGLWidget>

//qt opengl
#include <QtOpenGL/QOpenGLBuffer>
#include <QtOpenGL/QOpenGLShaderProgram>
#include <QtOpenGL/QOpenGLVertexArrayObject>

class Canvas : public QOpenGLWidget, public QOpenGLFunctions
{
public:
	//constructors
	Canvas(QWidget*);

	//destructor
	~Canvas(void);

	//openGL
	void paintGL(void) override;
	void initializeGL(void) override;

	//data
	QOpenGLBuffer m_vbo[2];
	QOpenGLBuffer m_ibo[2];
	QOpenGLVertexArrayObject m_vao[2];
	QOpenGLShaderProgram m_program[2];
};