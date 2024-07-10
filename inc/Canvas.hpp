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
	void resizeGL(int, int) override;
	void initializeGL(void) override;

	//data
	QOpenGLBuffer m_vbo;
	QOpenGLBuffer m_ibo;
	QOpenGLVertexArrayObject m_vao;
	QOpenGLShaderProgram m_program[2];
};