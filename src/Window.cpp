//stability
#include "stability/inc/Window.hpp"

//uic
#include "stability/build/uic/Window.hpp"

//constructors
Window::Window(void) : m_ui(new Ui::Window)
{
	m_ui->setupUi(this);
	m_ui->table_points->setColumnCount(2);
	m_ui->table_points->setHorizontalHeaderItem(0, new QTableWidgetItem("X₁"));
	m_ui->table_points->setHorizontalHeaderItem(1, new QTableWidgetItem("X₂"));
	m_ui->table_points->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	m_ui->table_points->setSelectionMode(QAbstractItemView::SelectionMode::MultiSelection);
}

//destructor
Window::~Window(void)
{
	delete m_ui;
}