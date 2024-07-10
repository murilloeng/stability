//stability
#include "stability/inc/Canvas.hpp"

//constructor
Canvas::Canvas(QWidget* parent) : QOpenGLWidget(parent), 
	m_vbo(QOpenGLBuffer::Type::VertexBuffer), m_ibo(QOpenGLBuffer::Type::IndexBuffer)
{
	return;
}

//destructor
Canvas::~Canvas(void)
{
	if(m_vao.isCreated()) m_vao.destroy();
	if(m_vbo.isCreated()) m_vbo.destroy();
	if(m_ibo.isCreated()) m_ibo.destroy();
}

//openGL
void Canvas::paintGL(void)
{
	//clear
	glClear(GL_COLOR_BUFFER_BIT);
	//buffers
	m_vao.bind();
	m_vbo.bind();
	m_ibo.bind();
	//program draw
	m_program[0].bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	//program points
	m_program[1].bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
void Canvas::resizeGL(int w, int h)
{
	//draw
	m_program[0].bind();
	m_program[0].setUniformValue("width", w);
	m_program[0].setUniformValue("height", h);
	//points
	m_program[1].bind();
	m_program[1].setUniformValue("width", w);
	m_program[1].setUniformValue("height", h);
}
void Canvas::initializeGL(void)
{
	//data
	const unsigned ibo_data[] = {0, 1, 2, 0, 2, 3};
	const float vbo_data[] = {-1, -1, +1, -1, +1, +1, -1, +1};
	QVector2D points_data[] = {{0, 0}, {-0.5, -0.5}, {+0.5, -0.5}, {+0.5, +0.5}, {-0.5, +0.5}};
	//setup
	initializeOpenGLFunctions();
	//buffers
	m_vao.create();
	m_vbo.create();
	m_ibo.create();
	//data 0
	m_vao.bind();
	m_vbo.bind();
	m_ibo.bind();
	m_vbo.allocate(vbo_data, sizeof(vbo_data));
	m_ibo.allocate(ibo_data, sizeof(ibo_data));
	//attributes
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (unsigned*) (0 * sizeof(float)));
	//shaders draw
	m_program[0].addShaderFromSourceFile(QOpenGLShader::ShaderTypeBit::Vertex, "shd/draw.vert");
	m_program[0].addShaderFromSourceFile(QOpenGLShader::ShaderTypeBit::Fragment, "shd/draw.frag");
	m_program[0].link();
	//shaders points
	m_program[1].addShaderFromSourceFile(QOpenGLShader::ShaderTypeBit::Vertex, "shd/points.vert");
	m_program[1].addShaderFromSourceFile(QOpenGLShader::ShaderTypeBit::Fragment, "shd/points.frag");
	m_program[1].link();
	//uniforms
	m_program[1].bind();
	m_program[1].setUniformValue("points_count", 5);
	m_program[1].setUniformValue("points_size", 0.02f);
	m_program[1].setUniformValue("points_color", QVector4D(1, 1, 1, 1));
	m_program[1].setUniformValueArray("points", points_data, 5);
}