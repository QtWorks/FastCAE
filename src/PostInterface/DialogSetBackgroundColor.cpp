#include "DialogSetBackgroundColor.h"
#include "ui_DialogSetBackgroundColor.h"
#include "PythonModule/PyAgent.h"
#include <QColorDialog>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>

SetBackgroundColorDialog::SetBackgroundColorDialog(QWidget *parent) : QDialog(parent),
																	  _ui(new Ui::SetBackgroundColorDialog)
{
	_ui->setupUi(this);
}

SetBackgroundColorDialog::SetBackgroundColorDialog(vtkRenderer *renderer, vtkRenderWindow *renderWin)
	: _renderer(renderer), _renderWindow(renderWin)
{
	_ui = new Ui::SetBackgroundColorDialog;
	_ui->setupUi(this);

	double colorTop[3] = {0, 0, 0}, colorBottom[3] = {0, 0, 0};
	_renderer->GetBackground(colorBottom);
	_renderer->GetBackground2(colorTop);

	_topColor = QColor(int(colorTop[0] * 255), int(colorTop[1] * 255), int(colorTop[2] * 255));
	_bottomColor = QColor(int(colorBottom[0] * 255), int(colorBottom[1] * 255), int(colorBottom[2] * 255));

	auto setButtonColor = [&](QPushButton *button, QColor color)
	{
        QString sheet = QString("background-color: rgb(%1,%2,%3);").arg(color.red()).arg(color.green()).arg(color.blue());
        button->setStyleSheet(sheet); };

	setButtonColor(_ui->bottomColorPushButton, _bottomColor);
	setButtonColor(_ui->topColorPushButton, _topColor);
}

SetBackgroundColorDialog::~SetBackgroundColorDialog()
{
	DeleteItem(_ui)
}

void SetBackgroundColorDialog::on_topColorPushButton_clicked()
{
	QColor c = QColorDialog::getColor(_topColor);

	if (c.isValid())
	{
		_topColor = c;
		_ui->topColorPushButton->setStyleSheet(QString("background-color: rgb(%1,%2,%3);").arg(c.red()).arg(c.green()).arg(c.blue()));
	}
}

void SetBackgroundColorDialog::on_bottomColorPushButton_clicked()
{
	QColor c = QColorDialog::getColor(_bottomColor);

	if (c.isValid())
	{
		_bottomColor = c;
		_ui->bottomColorPushButton->setStyleSheet(QString("background-color: rgb(%1,%2,%3);").arg(c.red()).arg(c.green()).arg(c.blue()));
	}
}

void SetBackgroundColorDialog::accept()
{
	_renderer->SetBackground(_bottomColor.redF(), _bottomColor.greenF(), _bottomColor.blueF());
	_renderer->SetBackground2(_topColor.redF(), _topColor.greenF(), _topColor.blueF());
	_renderWindow->Render();
	QDialog::accept();
}
