#include "DialogLightSetting.h"
#include "ui_DialogLightSetting.h"
#include <vtkRenderer.h>
#include <vtkLight.h>
#include <vtkLightCollection.h>
#include <QColorDialog>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>

LightSettingDialog::LightSettingDialog(vtkRenderer* renderer, vtkRenderWindow* renderWindow,  QWidget *parent) :
    QDialog(parent),
	_renderer(renderer),
	_renderWindow(renderWindow),
    _ui(new Ui::LightSettingDialog)
{
    _ui->setupUi(this);
	this->setWindowFlags(Qt::WindowCloseButtonHint);

	initLightList();

	connect(_ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(listWidgetItemClicked()));
}

LightSettingDialog::~LightSettingDialog()
{
	DeleteItem(_ui)
}

void LightSettingDialog::initLightList()
{
	_lightList.clear();
	_ui->listWidget->clear();

	vtkLightCollection* lightColl = _renderer->GetLights();
	lightColl->InitTraversal();
	const int nLight = lightColl->GetNumberOfItems();
	for (int i = 0; i < nLight; i++)
	{
		vtkLight* light = lightColl->GetNextItem();
		if (light == nullptr) continue;
		_ui->listWidget->addItem(tr("Light_%1").arg(i + 1));
		_lightList.append(light);
	}
}

void LightSettingDialog::on_addPushButton_clicked()
{
	vtkSmartPointer<vtkLight> light = vtkSmartPointer<vtkLight>::New();
	light->PositionalOff();//平行光
	light->SetPosition(1, 1, 1);
	light->SetFocalPoint(0, 0, 0);
	light->SetColor(1, 1, 1);
	_renderer->AddLight(light);
	_renderWindow->Render();

	initLightList();
}

void LightSettingDialog::on_deletePushButton_clicked()
{
	if (_currentLight == nullptr) return;
	//_ui->listWidget->takeItem(_ui->listWidget->currentRow());
	//_lightList.removeOne(_currentLight);
	_renderer->RemoveLight(_currentLight);
	_renderWindow->Render();

	initLightList();
}

void LightSettingDialog::on_okPushButton_clicked()
{
	if (_currentLight == nullptr) return;

	double pc[3]{ 0 };
	double fc[3]{ 0 };

	pc[0] = _ui->pXDoubleSpinBox->value();
	pc[1] = _ui->pYDoubleSpinBox->value();
	pc[2] = _ui->pZDoubleSpinBox->value();
	fc[0] = _ui->fXDoubleSpinBox->value();
	fc[1] = _ui->fYDoubleSpinBox->value();
	fc[2] = _ui->fZDoubleSpinBox->value();

	QColor color = _ui->colorPushButton->palette().color(QPalette::Background);

	_currentLight->SetColor(color.redF(), color.greenF(), color.blueF());
	_currentLight->SetPosition(pc);
	_currentLight->SetFocalPoint(fc);

	_renderWindow->Render();
}

void LightSettingDialog::on_colorPushButton_clicked()
{
	QColor c = _ui->colorPushButton->palette().color(QPalette::Background);

	QColor color = QColorDialog::getColor(c);
	if (color.isValid())
	{
		_ui->colorPushButton->setStyleSheet(QString("background-color: rgb(%1,%2,%3);").arg(color.red()).arg(color.green()).arg(color.blue()));
	}
}

void LightSettingDialog::listWidgetItemClicked()
{
	const int index = _ui->listWidget->currentRow();
	_currentLight = _lightList.at(index);
	if (_currentLight == nullptr) return;

	double pc[3]{ 0 };
	double fc[3]{ 0 };
	double color[3]{ 0 };

	_currentLight->GetPosition(pc);
	_currentLight->GetFocalPoint(fc);
	_currentLight->GetDiffuseColor(color);
	
	_ui->pXDoubleSpinBox->setValue(pc[0]);
	_ui->pYDoubleSpinBox->setValue(pc[1]);
	_ui->pZDoubleSpinBox->setValue(pc[2]);
	_ui->fXDoubleSpinBox->setValue(fc[0]);
	_ui->fYDoubleSpinBox->setValue(fc[1]);
	_ui->fZDoubleSpinBox->setValue(fc[2]);
	_ui->colorPushButton->setStyleSheet(QString("background-color: rgb(%1,%2,%3);").arg(color[0] * 255).arg(color[1] * 255).arg(color[2] * 255));
}
