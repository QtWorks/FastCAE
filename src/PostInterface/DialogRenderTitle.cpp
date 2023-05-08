#include "DialogRenderTitle.h"
#include "ui_DialogRenderTitle.h"
#include <vtkRenderWindow.h>
#include <vtkTextWidget.h>
#include <vtkTextActor.h>
#include <vtkTextRepresentation.h>
#include <vtkTextProperty.h>
#include <QPalette>
#include <QColorDialog>
#include <QCheckBox>

RenderTitleDialog::RenderTitleDialog(vtkTextWidget* textWidget, vtkRenderWindow* renderWindow, QWidget *parent) :
    QDialog(parent),
	_renderWindow(renderWindow),
	_textWidget(textWidget),
    _ui(new Ui::RenderTitleDialog)
{
    _ui->setupUi(this);
	
	this->setWindowFlags(Qt::WindowCloseButtonHint);

	if (_textWidget == nullptr || _renderWindow == nullptr)
		return;

	init();
}

RenderTitleDialog::~RenderTitleDialog()
{
    delete _ui;
}

void RenderTitleDialog::init()
{
	if (_textWidget == nullptr || _renderWindow == nullptr)
		return;

	vtkTextActor* actor = _textWidget->GetTextActor();
	vtkTextRepresentation* rep = vtkTextRepresentation::SafeDownCast(_textWidget->GetRepresentation());
	if (rep == nullptr)return;

	double nColor[3]{ 0 };
	double pos[2]{ 0 };
	double pos2[2]{ 0 };

	actor->GetTextProperty()->GetColor(nColor);
	rep->GetPositionCoordinate()->GetValue(pos);
	rep->GetPosition2Coordinate()->GetValue(pos2);

	_ui->titleLineEdit->setText(actor->GetInput());

	auto setDoubleSpinbox = [&](QDoubleSpinBox* dSpinBox, double v) {
		dSpinBox->setValue(v);	};

	setDoubleSpinbox(_ui->xDoubleSpinBox, pos[0]);
	setDoubleSpinbox(_ui->yDoubleSpinBox, pos[1]);
	setDoubleSpinbox(_ui->widthDoubleSpinBox, pos2[0]);
	setDoubleSpinbox(_ui->heightDoubleSpinBox, pos2[1]);

	_color = QColor(nColor[0] * 255, nColor[1] * 255, nColor[2] * 255);
	
	auto setPushButtonColor = [&](QPushButton* pushButton, QColor c) {
		QString sheet = QString("background-color: rgb(%1,%2,%3);").arg(c.red()).arg(c.green()).arg(c.blue());
		pushButton->setStyleSheet(sheet);	};

	setPushButtonColor(_ui->colorPushButton, _color);

	auto setCheckBox = [=](QCheckBox* checkBox, bool b) {
		checkBox->setChecked(b);	};

	setCheckBox(_ui->movableCheckBox, !_textWidget->GetSelectable());
	setCheckBox(_ui->visibleCheckBox, _textWidget->GetEnabled());
}

void RenderTitleDialog::accept()
{
	if (_textWidget == nullptr || _renderWindow == nullptr)
		return;

	vtkTextActor* actor = _textWidget->GetTextActor();
	vtkTextRepresentation* rep = vtkTextRepresentation::SafeDownCast(_textWidget->GetRepresentation());
	if (rep == nullptr)return;

	double pos[2]{ 0 };
	double pos2[2]{ 0 };

	auto getDoubleSpinbox = [=](QDoubleSpinBox* dSpinBox, double& v) {
		v = dSpinBox->value();	};

	getDoubleSpinbox(_ui->xDoubleSpinBox, pos[0]);
	getDoubleSpinbox(_ui->yDoubleSpinBox, pos[1]);
	getDoubleSpinbox(_ui->widthDoubleSpinBox, pos2[0]);
	getDoubleSpinbox(_ui->heightDoubleSpinBox, pos2[1]);

	auto getCheckBox = [=](QCheckBox* checkBox) {
		return checkBox->isChecked();	};

	QString2Char(_ui->titleLineEdit->text().trimmed(), title);
	actor->SetInput(title);
	actor->GetTextProperty()->SetColor(_color.redF(), _color.greenF(), _color.blueF());
	rep->GetPositionCoordinate()->SetValue(pos);
	rep->GetPosition2Coordinate()->SetValue(pos2);

	_textWidget->SetSelectable(!getCheckBox(_ui->movableCheckBox));
	_textWidget->SetEnabled(getCheckBox(_ui->visibleCheckBox));

	_renderWindow->Render();

	this->close();
}

void RenderTitleDialog::on_colorPushButton_clicked()
{
	QColor c = QColorDialog::getColor(_color);
	
	if (c.isValid())
	{
		_color = c;

		auto setPushButtonColor = [&](QPushButton* pushButton, QColor c) {
			QString sheet = QString("background-color: rgb(%1,%2,%3);").arg(c.red()).arg(c.green()).arg(c.blue());
			pushButton->setStyleSheet(sheet);	};

		setPushButtonColor(_ui->colorPushButton, _color);
	}
}
