#include "DialogCreateStreamLine.h"
#include "ui_DialogCreateStreamLine.h"
#include "LineWidget.h"
#include "PostTreeWidget.h"
#include "RenderDirector.h"
#include "RenderWindowManager.h"
#include "FLineCallback.h"
#include "GraphWidget.h"
#include "PostRenderData/RenderDataObject.h"
#include "PostRenderData/StreamLineRenderDataAlg.h"
#include "PostRenderData/RenderDataManager.h"
#include "PythonModule/PyAgent.h"
#include <QMessageBox>

namespace Post
{
	CreateStreamLineDialog::CreateStreamLineDialog(PostTreeWidget *tree, QWidget *parent) : PostFunctionDialogBase(tree, parent),
																							_ui(new Ui::CreateStreamLineDialog)
	{
		_ui->setupUi(this);

		init();
	}

	CreateStreamLineDialog::~CreateStreamLineDialog()
	{
		if (_lineWidget != nullptr)
			delete _lineWidget;
		delete _ui;
	}

	void CreateStreamLineDialog::init()
	{
		_ui->nameLineEdit->setText(tr("StreamLine"));
		setParentObject();
	}

	void CreateStreamLineDialog::accept()
	{
		if (_parentObject == nullptr)
		{
			QMessageBox::warning(this, tr("Warning!"), tr("No selected data!"));
			return;
		}

		bool isPoint = true;
		double s[3]{0};
		double e[3]{0};

		QString name = _ui->nameLineEdit->text();
		QString vName = _ui->vectorComboBox->currentText();
		int direct = _ui->directionComboBox->currentIndex();
		int seeds = _ui->seedNumSpinBox->value();
		int steps = _ui->stepNumSpinBox->value();
		double initStep = _ui->initStepDoubleSpinBox->value();
		double minStep = _ui->minStepDoubleSpinBox->value();
		double maxStep = _ui->maxStepDoubleSpinBox->value();
		double length = _ui->lengthDoubleSpinBox->value();

		if (_ui->vectorComboBox->currentData().toInt() == 2)
			isPoint = false;

		_lineWidget->getCallback()->getLine(s, e);

		QStringList codes{};

		codes += QString("streamline = PostProcess.StreamLine()");
		codes += QString("streamline.setParentID(%1)").arg(_parentObject->getID());
		codes += QString("streamline.setName('%1')").arg(name);
		codes += QString("streamline.setVectorName('%1')").arg(vName);
		codes += QString("streamline.setStartPoint(%1,%2,%3)").arg(s[0]).arg(s[1]).arg(s[2]);
		codes += QString("streamline.setEndPoint(%1,%2,%3)").arg(e[0]).arg(e[1]).arg(e[2]);
		codes += QString("streamline.setUsePointData(%1)").arg(isPoint);
		codes += QString("streamline.setSeedCount(%1)").arg(seeds);
		codes += QString("streamline.setMaxLength(%1)").arg(length);
		codes += QString("streamline.setInitStep(%1)").arg(initStep);
		codes += QString("streamline.setMinStep(%1)").arg(minStep);
		codes += QString("streamline.setMaxStep(%1)").arg(maxStep);
		codes += QString("streamline.setStepNumber(%1)").arg(steps);
		codes += QString("streamline.setDirection(%1)").arg(direct);

		codes += this->getSeletedDataCode("streamline");
		codes += QString("streamline.create()");

		_pyAgent->submit(codes);

		// 		StreamLineRenderDataAlg* alg = new StreamLineRenderDataAlg(_parentObject);
		// 		alg->setSelectedObjectHash(_tree->getSelectedData(_parentObject));
		// 		alg->setVector(vName);
		// 		alg->setUsePointData(isPoint);
		// 		alg->setLineSource(s, e);
		// 		alg->setSeedCount(seeds);
		// 		alg->setMaxLength(length);
		// 		alg->setInitStep(initStep);
		// 		alg->setMinStep(minStep);
		// 		alg->setMaxStep(maxStep);
		// 		alg->setStepNumber(steps);
		// 		alg->setDirection(direct);
		//
		// 		alg->updateParam();
		// 		alg->updateAlg();
		// 		alg->update();
		//
		//
		// 		_parentObject->appendSubObjects(alg);
		// 		RenderDirector::getInstance()->renderDataObjectToWindow(alg, _parentObject->getRenderWinID());
		//		_tree->updatePostTree();
		QDialog::accept();
		this->close();
	}

	void CreateStreamLineDialog::reject()
	{
		QDialog::reject();
		this->close();
	}

	void CreateStreamLineDialog::updateDisplayInterface()
	{
		updateVectorComboBox();
		showLineWidget();

		_ui->lengthDoubleSpinBox->setMaximum(_length);
		_ui->lengthDoubleSpinBox->setValue(_length);
		_ui->lengthHorizontalSlider->setValue(100);
	}

	void CreateStreamLineDialog::showLineWidget()
	{
		if (_parentObject == nullptr)
			return;
		auto wid = _parentObject->getRenderWinID();
		auto window = _windowManager->getRenderWindowByID(wid);
		if (window == nullptr)
			return;
		if (_lineWidget == nullptr)
		{
			_lineWidget = new LineWidget(window, _parentObject);

			connect(_lineWidget->getCallback(), SIGNAL(updateLineWidgetSig(double *, double *)), this, SLOT(updateLineWidget(double *, double *)));
		}

		double start[3]{0};
		double end[3]{0};
		this->getSelectedObjectsBound(start, end);
		_lineWidget->setLine(start, end);
		_length = fabs(end[0] - start[0]);

		_ui->xStartPointLineEdit->setText(QString::number(start[0], 'g', 4));
		_ui->yStartPointLineEdit->setText(QString::number(start[1], 'g', 4));
		_ui->zStartPointLineEdit->setText(QString::number(start[2], 'g', 4));
		_ui->xEndPointLineEdit->setText(QString::number(end[0], 'g', 4));
		_ui->yEndPointLineEdit->setText(QString::number(end[1], 'g', 4));
		_ui->zEndPointLineEdit->setText(QString::number(end[2], 'g', 4));
		window->reRender();
	}

	void CreateStreamLineDialog::getSelectedObjectsBound(double *start, double *end)
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

		for (int i = 0; i < 3; i++)
		{
			start[i] = bounds[i * 2];
			end[i] = bounds[(i * 2) + 1];
		}
	}

	void CreateStreamLineDialog::updateVectorComboBox()
	{
		if (_parentObject == nullptr)
			return;
		_ui->vectorComboBox->clear();

		QStringList pArrayList = _parentObject->getPointDataArray();
		for (auto pArray : pArrayList)
		{
			if (_parentObject->variableType(1, pArray) == 2)
				_ui->vectorComboBox->addItem(QIcon("://QUI/post/val_on_point.png"), pArray, 1);
		}

		QStringList cArrayList = _parentObject->getCellDataArray();
		for (auto cArray : cArrayList)
		{
			if (_parentObject->variableType(2, cArray) == 2)
				_ui->vectorComboBox->addItem(QIcon("://QUI/post/val_on_cell.png"), cArray, 2);
		}
	}

	void CreateStreamLineDialog::updateLineWidget(double *start, double *end)
	{
		_ui->xStartPointLineEdit->setText(QString::number(start[0], 'g', 4));
		_ui->yStartPointLineEdit->setText(QString::number(start[1], 'g', 4));
		_ui->zStartPointLineEdit->setText(QString::number(start[2], 'g', 4));
		_ui->xEndPointLineEdit->setText(QString::number(end[0], 'g', 4));
		_ui->yEndPointLineEdit->setText(QString::number(end[1], 'g', 4));
		_ui->zEndPointLineEdit->setText(QString::number(end[2], 'g', 4));
	}

	void CreateStreamLineDialog::on_lengthDoubleSpinBox_valueChanged(double v)
	{
		_ui->lengthHorizontalSlider->blockSignals(true);
		double per = v / _length;
		_ui->lengthHorizontalSlider->setValue(per * 100);
		_ui->lengthHorizontalSlider->blockSignals(false);
	}

	void CreateStreamLineDialog::on_lengthHorizontalSlider_valueChanged(int v)
	{
		_ui->lengthDoubleSpinBox->blockSignals(true);
		double per = (double)v / 100;
		_ui->lengthDoubleSpinBox->setValue(per * _length);
		_ui->lengthDoubleSpinBox->blockSignals(false);
	}

}