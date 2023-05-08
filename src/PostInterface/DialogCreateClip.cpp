#include "DialogCreateClip.h"
#include "ui_DialogCreateClip.h"
#include "RenderWindowManager.h"
#include "PostTreeWidget.h"
#include "ShearPlaneWidget.h"
#include "FuncCallback.h"
#include "RenderWindowManager.h"
#include "RenderDirector.h"
#include "GraphWidget.h"
#include "PostRenderData/RenderDataObject.h"
#include "PostRenderData/RenderDataManager.h"
#include "PostRenderData/ClipRenderDataAlg.h"
#include "PostRenderData/SliceRenderDataAlg.h"
#include "PythonModule/PyAgent.h"
#include <vtkDataSet.h>
#include <QMessageBox>

namespace Post
{
	CreateClipDialog::CreateClipDialog(PostTreeWidget *tree, bool isClip, QWidget *parent) : PostFunctionDialogBase(tree, parent),
																							 _ui(new Ui::CreateClipDialog),
																							 _isClip(isClip),
																							 _isEdit(false)
	{
		_ui->setupUi(this);

		// 		this->setWindowFlags(Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint | Qt::Dialog);
		// 		this->setAttribute(Qt::WA_DeleteOnClose);

		init();
	}

	CreateClipDialog::CreateClipDialog(PostTreeWidget *tree, RenderDataObject *obj, bool isClip, QWidget *parent) : PostFunctionDialogBase(tree, parent),
																													_ui(new Ui::CreateClipDialog),
																													_isClip(isClip),
																													_isEdit(true)
	{
		_ui->setupUi(this);

		_editObject = obj;
		_parentObject = _editObject->getParentObj();

		initEidtInterface();
	}

	CreateClipDialog::~CreateClipDialog()
	{
		if (_shearPlane != nullptr)
			delete _shearPlane;
		delete _ui;
	}

	void CreateClipDialog::init()
	{
		if (_isClip)
		{
			_ui->nameLineEdit->setText(tr("Clip"));
			this->setWindowTitle(tr("CreateClip"));
		}
		else
		{
			_ui->nameLineEdit->setText(tr("Slice"));
			_ui->directionCheckBox->setVisible(false);
			this->setWindowTitle(tr("CreateSlice"));
		}
		setParentObject();

		// connect(_tree, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(setParentObject()));
	}

	void CreateClipDialog::initEidtInterface()
	{
		if (_editObject == nullptr)
			return;
		auto wid = _editObject->getRenderWinID();
		auto window = _windowManager->getRenderWindowByID(wid);
		if (window == nullptr)
			return;
		if (_shearPlane == nullptr)
		{
			_shearPlane = new ShearPlaneWidget(window, _editObject->getParentObj());

			connect(_shearPlane->getCallback(), SIGNAL(updatePlaneWidgetSig(double *, double *)), this, SLOT(updatePlaneWidget(double *, double *)));
		}

		double nor[3]{0};
		double ori[3]{0};

		if (_isClip)
		{
			this->setWindowTitle(tr("CreateClip"));
			auto clip = dynamic_cast<ClipRenderDataAlg *>(_editObject);
			if (clip == nullptr)
				return;

			_tree->setSelectedData(clip->getSelectedObjectHash());
			clip->getPlaneNormal(nor);
			clip->getPlaneOrigin(ori);

			_ui->directionCheckBox->setChecked(!clip->getInsideOut());
		}
		else
		{
			_ui->directionCheckBox->setVisible(false);
			this->setWindowTitle(tr("CreateSlice"));
			auto slice = dynamic_cast<SliceRenderDataAlg *>(_editObject);
			if (slice == nullptr)
				return;
			_tree->setSelectedData(slice->getSelectedObjectHash());
			slice->getPlaneNormal(nor);
			slice->getPlaneOrigin(ori);
		}

		_ui->nameLineEdit->setText(_editObject->getName());

		double bounds[6]{0};
		this->getSelectedObjectsBound(bounds);
		_shearPlane->setPlaceWidget(bounds);
		_shearPlane->setPlaneNormal(nor);
		_shearPlane->setPlaneOrigin(ori);

		blockDoubleSpinBoxSignals(true);
		_ui->xDoubleSpinBox->setValue(ori[0]);
		_ui->yDoubleSpinBox->setValue(ori[1]);
		_ui->zDoubleSpinBox->setValue(ori[2]);
		_ui->xLineEdit->setText(QString::number(nor[0], 'g', 4));
		_ui->yLineEdit->setText(QString::number(nor[1], 'g', 4));
		_ui->zLineEdit->setText(QString::number(nor[2], 'g', 4));
		blockDoubleSpinBoxSignals(false);

		window->reRender();
	}

	void CreateClipDialog::accept()
	{
		if (_parentObject == nullptr)
		{
			QMessageBox::warning(this, tr("Warning!"), tr("No selected data!"));
			return;
		}

		QString name = _ui->nameLineEdit->text();
		if (name.isEmpty())
		{
			QMessageBox::warning(this, tr("Warning!"), tr("Input is wrong!"));
			return;
		}

		double org[3]{0};
		double nor[3]{0};

		org[0] = _ui->xDoubleSpinBox->value();
		org[1] = _ui->yDoubleSpinBox->value();
		org[2] = _ui->zDoubleSpinBox->value();
		nor[0] = _ui->xLineEdit->text().toDouble();
		nor[1] = _ui->yLineEdit->text().toDouble();
		nor[2] = _ui->zLineEdit->text().toDouble();

		QStringList codes{};
		QString algName;
		if (_isClip)
		{
			algName = QString("clip");
			codes += QString("clip = PostProcess.Clip()");
			codes += QString("clip.setInsideOut(%1)").arg(_ui->directionCheckBox->isChecked());
		}
		else
		{
			algName = QString("slice");
			codes += QString("slice = PostProcess.Slice()");
		}

		codes += QString("%1.setName('%2')").arg(algName).arg(name);
		codes += QString("%1.setOrigin(%2,%3,%4)").arg(algName).arg(org[0]).arg(org[1]).arg(org[2]);
		codes += QString("%1.setNormal(%2,%3,%4)").arg(algName).arg(nor[0]).arg(nor[1]).arg(nor[2]);

		auto dataHash = _tree->getSelectedData(_parentObject);
		auto objList = dataHash.uniqueKeys();
		for (auto obj : objList)
		{
			auto blockList = dataHash.values(obj);
			for (auto block : blockList)
			{
				codes += QString("%1.appendBlock(%2,%3)").arg(algName).arg(obj).arg(block);
			}
		}

		if (!_isEdit)
		{
			codes += QString("%1.setParentID(%2)").arg(algName).arg(_parentObject->getID());
			codes += QString("%1.create()").arg(algName);
		}
		else
		{
			codes += QString("%1.setID(%2)").arg(algName).arg(_editObject->getID());
			codes += QString("%1.edit()").arg(algName);
		}
		_pyAgent->submit(codes);

		// 		if (_isClip)
		// 		{
		// 			ClipRenderDataAlg* alg = new ClipRenderDataAlg(_parentObject);
		// 			alg->setSelectedObjectHash(_tree->getSelectedData(_parentObject));
		// 			alg->setPlaneNormal(nor);
		// 			alg->setPlaneOri(org);
		// 			alg->setInsideOut(!_ui->directionCheckBox->isChecked());
		//
		// 			alg->updateParam();
		// 			alg->updateAlg();
		// 			alg->update();
		//
		//
		// 			_parentObject->appendSubObjects(alg);
		// 			RenderDirector::getInstance()->renderDataObjectToWindow(alg, _parentObject->getRenderWinID());
		// 		}
		// 		else
		// 		{
		// 			SliceRenderDataAlg* alg = new SliceRenderDataAlg(_parentObject);
		// 			alg->setSelectedObjectHash(_tree->getSelectedData(_parentObject));
		// 			alg->setPlaneNormal(nor);
		// 			alg->setPlaneOri(org);
		//
		//  			alg->updateParam();
		// 			alg->updateAlg();
		// 			alg->update();
		//
		//
		// 			_parentObject->appendSubObjects(alg);
		// 			RenderDirector::getInstance()->renderDataObjectToWindow(alg, _parentObject->getRenderWinID());
		// 		}
		// 		_tree->updatePostTree();
		QDialog::accept();
		this->close();
	}

	void CreateClipDialog::reject()
	{
		QDialog::reject();
		this->close();
	}

	void CreateClipDialog::updateDisplayInterface()
	{
		showShearPlane();

		blockDoubleSpinBoxSignals(true);
		double nor[3]{0};
		double org[3]{0};
		if (_shearPlane != nullptr)
		{
			_shearPlane->getPlaneNormal(nor);
			_shearPlane->getPlaneOrigin(org);
		}

		_ui->xDoubleSpinBox->setValue(org[0]);
		_ui->yDoubleSpinBox->setValue(org[1]);
		_ui->zDoubleSpinBox->setValue(org[2]);
		_ui->xLineEdit->setText(QString::number(nor[0], 'g', 4));
		_ui->yLineEdit->setText(QString::number(nor[1], 'g', 4));
		_ui->zLineEdit->setText(QString::number(nor[2], 'g', 4));
		blockDoubleSpinBoxSignals(false);
	}

	void CreateClipDialog::showShearPlane()
	{
		if (_parentObject == nullptr)
			return;
		auto wid = _parentObject->getRenderWinID();
		auto window = _windowManager->getRenderWindowByID(wid);
		if (window == nullptr)
			return;
		if (_shearPlane == nullptr)
		{
			_shearPlane = new ShearPlaneWidget(window, _parentObject);

			connect(_shearPlane->getCallback(), SIGNAL(updatePlaneWidgetSig(double *, double *)), this, SLOT(updatePlaneWidget(double *, double *)));
		}

		double bounds[6]{0};
		double origin[3]{0};
		double normal[3]{1, 0, 0};
		this->getSelectedObjectsBound(bounds);
		_shearPlane->setPlaceWidget(bounds);

		origin[0] = (bounds[1] + bounds[0]) / 2;
		origin[1] = (bounds[3] + bounds[2]) / 2;
		origin[2] = (bounds[5] + bounds[4]) / 2;

		_shearPlane->setPlaneNormal(normal);
		_shearPlane->setPlaneOrigin(origin);

		window->reRender();
	}

	void CreateClipDialog::getSelectedObjectsBound(double *bounds)
	{
		bool isFirst = false;
		//	double mBounds[6]{ 0 };
		auto maxBounds = [](double *fBound, double *sBound)
		{
			// 			auto Max = [](double a, double b) {if (a < b) a = b; };
			// 			auto Min = [](double a, double b) {if (a > b) a = b; };
			//
			// 			Min(fBound[0], sBound[0]);
			// 			Max(fBound[1], sBound[1]);
			// 			Min(fBound[2], sBound[2]);
			// 			Max(fBound[3], sBound[3]);
			// 			Min(fBound[4], sBound[4]);
			// 			Max(fBound[5], sBound[5]);
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
	}

	void CreateClipDialog::blockDoubleSpinBoxSignals(bool b)
	{
		_ui->xDoubleSpinBox->blockSignals(b);
		_ui->yDoubleSpinBox->blockSignals(b);
		_ui->zDoubleSpinBox->blockSignals(b);
	}

	void CreateClipDialog::updatePlaneWidget(double *normal, double *origin)
	{
		blockDoubleSpinBoxSignals(true);
		_ui->xDoubleSpinBox->setValue(origin[0]);
		_ui->yDoubleSpinBox->setValue(origin[1]);
		_ui->zDoubleSpinBox->setValue(origin[2]);

		_ui->xLineEdit->setText(QString::number(normal[0], 'g', 4));
		_ui->yLineEdit->setText(QString::number(normal[1], 'g', 4));
		_ui->zLineEdit->setText(QString::number(normal[2], 'g', 4));
		blockDoubleSpinBoxSignals(false);
	}

	void CreateClipDialog::on_xDoubleSpinBox_valueChanged(double x)
	{
		double origin[3]{0};

		origin[0] = x;
		origin[1] = _ui->yDoubleSpinBox->value();
		origin[2] = _ui->zDoubleSpinBox->value();

		_shearPlane->setPlaneOrigin(origin);
	}

	void CreateClipDialog::on_yDoubleSpinBox_valueChanged(double y)
	{
		double origin[3]{0};

		origin[0] = _ui->xDoubleSpinBox->value();
		origin[1] = y;
		origin[2] = _ui->zDoubleSpinBox->value();

		_shearPlane->setPlaneOrigin(origin);
	}

	void CreateClipDialog::on_zDoubleSpinBox_valueChanged(double z)
	{
		double origin[3]{0};

		origin[0] = _ui->xDoubleSpinBox->value();
		origin[1] = _ui->yDoubleSpinBox->value();
		origin[2] = z;

		_shearPlane->setPlaneOrigin(origin);
	}

}