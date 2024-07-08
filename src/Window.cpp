//stability
#include "stability/inc/Window.hpp"

//uic
#include "stability/build/uic/Window.hpp"

//constructors
Window::Window(void) : m_ui(new Ui::Window)
{
	m_ui->setupUi(this);
}

//destructor
Window::~Window(void)
{
	delete m_ui;
}