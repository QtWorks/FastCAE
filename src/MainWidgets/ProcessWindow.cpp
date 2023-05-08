#include "ProcessWindow.h"
#include "MainWindow/MainWindow.h"

namespace MainWidget
{

	ProcessWindow::ProcessWindow(GUI::MainWindow *mainwindow, QWidget *parent) : ProcessWindowBase(mainwindow)
	{
		Q_UNUSED(parent)
		this->repaintTitleBar();
		//		this->titleBarWidget()->setVisible(false);

		// 		QWidget* lTitleBar = this->titleBarWidget();
		// 		QWidget* lEmptyWidget = new QWidget();
		// 		this->setTitleBarWidget(lEmptyWidget);
		// 		delete lTitleBar;
	}
	ProcessWindow::~ProcessWindow()
	{
	}
}
