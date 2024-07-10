//stability
#include "stability/inc/Canvas.hpp"

//constructor
Canvas::Canvas(QWidget* parent) : QOpenGLWidget(parent), 
	m_vbo{QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer), QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer)},
	m_ibo{QOpenGLBuffer(QOpenGLBuffer::Type::IndexBuffer), QOpenGLBuffer(QOpenGLBuffer::Type::IndexBuffer)}
{
	return;
}

//destructor
Canvas::~Canvas(void)
{
	if(m_vao[0].isCreated()) m_vao[0].destroy();
	if(m_vao[1].isCreated()) m_vao[1].destroy();
	if(m_vbo[0].isCreated()) m_vbo[0].destroy();
	if(m_vbo[1].isCreated()) m_vbo[1].destroy();
	if(m_ibo[0].isCreated()) m_ibo[0].destroy();
	if(m_ibo[1].isCreated()) m_ibo[1].destroy();
}

//openGL
void Canvas::paintGL(void)
{
	//draw
	m_vao[0].bind();
	m_vbo[0].bind();
	m_ibo[0].bind();
	m_program[0].bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	//points
	m_vao[1].bind();
	m_vbo[1].bind();
	m_ibo[1].bind();
	m_program[1].bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
void Canvas::initializeGL(void)
{
	//data
	const unsigned ibo_data[] = {0, 1, 2, 0, 2, 3};
	const float vbo_data[] = {-1, -1, +1, -1, +1, +1, -1, +1};
	//setup
	initializeOpenGLFunctions();
	//buffers
	m_vao[0].create();
	m_vao[1].create();
	m_vbo[0].create();
	m_vbo[1].create();
	m_ibo[0].create();
	m_ibo[1].create();
	//data 0
	m_vao[0].bind();
	m_vbo[0].bind();
	m_ibo[0].bind();
	m_vbo[0].allocate(vbo_data, sizeof(vbo_data));
	m_ibo[0].allocate(ibo_data, sizeof(ibo_data));
	//attributes 0
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (unsigned*) (0 * sizeof(float)));
	//data 1
	m_vao[1].bind();
	m_vbo[1].bind();
	m_ibo[1].bind();
	m_vbo[1].allocate(vbo_data, sizeof(vbo_data));
	m_ibo[1].allocate(ibo_data, sizeof(ibo_data));
	//attributes 0
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
}