#pragma once

//qt
#include <QtWidgets/QMainWindow>

namespace Ui
{
	class Window;
}

class Window : public QMainWindow
{
public:
	//constructor
	Window(void);

	//destructor
	~Window(void);

private:
	//data
	Ui::Window* m_ui;
};