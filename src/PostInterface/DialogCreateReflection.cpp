#include "DialogCreateReflection.h"
#include "ui_DialogCreateReflection.h"
#include "PostTreeWidget.h"
#include "RenderDirector.h"
#include "PostRenderData/ReflectionRenderDataAlg.h"
#include "PostRenderData/RenderDataManager.h"
#include "PythonModule/PyAgent.h"
#include <vtkDataSet.h>
#include <QMessageBox>
#include <QButtonGroup>

namespace Post
{
	CreateReflectionDialog::CreateReflectionDialog(PostTreeWidget *tree, QWidget *parent) : PostFunctionDialogBase(tree, parent),
																							_ui(new Ui::CreateReflectionDialog)
	{
		_ui->setupUi(this);

		init();
	}

	CreateReflectionDialog::~CreateReflectionDialog()
	{
		delete _ui;
	}

	void CreateReflectionDialog::init()
	{
		_ui->nameLineEdit->setText(tr("Reflection"));
		_buttonGroup = new QButtonGroup(this);
		_buttonGroup->addButton(_ui->xMinRadioButton, 0);
		_buttonGroup->addButton(_ui->yMinRadioButton, 1);
		_buttonGroup->addButton(_ui->zMinRadioButton, 2);
		_buttonGroup->addButton(_ui->xMaxRadioButton, 3);
		_buttonGroup->addButton(_ui->yMaxRadioButton, 4);
		_buttonGroup->addButton(_ui->zMaxRadioButton, 5);
		_buttonGroup->addButton(_ui->xRadioButton, 6);
		_buttonGroup->addButton(_ui->yRadioButton, 7);
		_buttonGroup->addButton(_ui->zRadioButton, 8);

		connect(_buttonGroup, SIGNAL(buttonToggled(int, bool)), this, SLOT(setReflectionPlane(int, bool)));

		setParentObject();

		setReflectionPlane(0, true);
	}

	void CreateReflectionDialog::accept()
	{
		if (_parentObject == nullptr)
		{
			QMessageBox::warning(this, tr("Warning!"), tr("No selected data!"));
			return;
		}

		QString name = _ui->nameLineEdit->text();
		double center = _ui->centerDoubleSpinBox->value();

		QStringList codes{};

		codes += QString("reflection = PostProcess.Reflection()");
		codes += QString("reflection.setParentID(%1)").arg(_parentObject->getID());
		codes += QString("reflection.setName('%1')").arg(name);
		codes += QString("reflection.setPlane(%1)").arg(int(_type));
		codes += QString("reflection.setCenter(%1)").arg(center);
		codes += this->getSeletedDataCode("reflection");
		codes += QString("reflection.create()");

		_pyAgent->submit(codes);

		// 		ReflectionRenderDataAlg* alg = new ReflectionRenderDataAlg(_parentObject);
		// 		alg->setSelectedObjectHash(_tree->getSelectedData(_parentObject));
		// 		alg->setPlane(int(_type));
		// 		alg->setCenter(center);
		//
		// 		alg->updateParam();
		// 		alg->updateAlg();
		// 		alg->update();
		//
		// 		_parentObject->appendSubObjects(alg);
		// 		RenderDirector::getInstance()->renderDataObjectToWindow(alg, _parentObject->getRenderWinID());
		//		_tree->updatePostTree();
		QDialog::accept();
		this->close();
	}

	void CreateReflectionDialog::reject()
	{
		QDialog::reject();
		this->close();
	}

	void CreateReflectionDialog::updateDisplayInterface()
	{
		getSelectedDataBound();

		auto setCenter = [=](double *range)
		{
			_ui->centerDoubleSpinBox->setMinimum(range[0]);
			_ui->centerDoubleSpinBox->setMaximum(range[1]);
		};

		switch (_type)
		{
		case Post::USE_X:
			setCenter(_xRange);
			break;
		case Post::USE_Y:
			setCenter(_yRange);
			break;
		case Post::USE_Z:
			setCenter(_zRange);
			break;
		}
	}

	void CreateReflectionDialog::getSelectedDataBound()
	{
		bool isFirst = false;
		double bounds[6]{0};

		auto maxBounds = [](double *fBound, double *sBound)
		{
			if (fBound[0] > sBound[0])
				fBound[0] = sBound[0];
			if (fBound[1] < sBound[1])
				fBound[1] = sBound[1];
			if (fBound[2] > sBound[2])
				fBound[2] = sBound[2];
			if (fBound[3] < sBound[3])
				fBound[3] = sBound[3];
			if (fBound[4] > sBound[4])
				fBound[4] = sBound[4];
			if (fBound[5] < sBound[5])
				fBound[5] = sBound[5];
		};

		auto idList = _tree->getSelectedData(_parentObject).uniqueKeys();
		for (auto id : idList)
		{
			auto obj = _dataManager->getObjectByID(id);
			if (obj == nullptr)
				continue;

			for (auto v : _tree->getSelectedData(_parentObject).values(id))
			{
				auto data = obj->getOutputData(v + 1);
				if (data == nullptr)
					continue;

				if (!isFirst)
				{
					data->GetBounds(bounds);
					isFirst = true;
				}
				else
				{
					double sBound[6]{0};
					data->GetBounds(sBound);
					maxBounds(bounds, sBound);
				}
			}
		}

		_xRange[0] = bounds[0];
		_xRange[1] = bounds[1];
		_yRange[0] = bounds[2];
		_yRange[1] = bounds[3];
		_zRange[0] = bounds[4];
		_zRange[1] = bounds[5];
	}

	void CreateReflectionDialog::setReflectionPlane(int id, bool c)
	{
		if (c == false)
			return;

		auto setCenterVisible = [=](bool v, double *range)
		{
			_ui->centerLabel->setVisible(v);
			_ui->centerDoubleSpinBox->setVisible(v);
			_ui->centerDoubleSpinBox->setMinimum(range[0]);
			_ui->centerDoubleSpinBox->setMaximum(range[1]);
			double val = (range[1] + range[0]) * 0.5;
			_ui->centerDoubleSpinBox->setValue(val);
		};

		switch (id)
		{
		case 0:
			_type = USE_XMIN;
			setCenterVisible(false, _xRange);
			break;
		case 1:
			_type = USE_YMIN;
			setCenterVisible(false, _xRange);
			break;
		case 2:
			_type = USE_ZMIN;
			setCenterVisible(false, _xRange);
			break;
		case 3:
			_type = USE_XMAX;
			setCenterVisible(false, _xRange);
			break;
		case 4:
			_type = USE_YMAX;
			setCenterVisible(false, _xRange);
			break;
		case 5:
			_type = USE_ZMAX;
			setCenterVisible(false, _xRange);
			break;
		case 6:
			_type = USE_X;
			setCenterVisible(true, _xRange);
			break;
		case 7:
			_type = USE_Y;
			setCenterVisible(true, _yRange);
			break;
		case 8:
			_type = USE_Z;
			setCenterVisible(true, _zRange);
			break;
		}
	}

}