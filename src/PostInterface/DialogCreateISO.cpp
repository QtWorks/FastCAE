#include "DialogCreateISO.h"
#include "ui_DialogCreateISO.h"
#include "PostTreeWidget.h"
#include "RenderDirector.h"
#include "PostRenderData/RenderDataObject.h"
#include "PostRenderData/ISOCurveRenderDataAlg.h"
#include "PostRenderData/ISORenderDataAlg.h"
#include "PythonModule/PyAgent.h"
#include <QMessageBox>

namespace Post
{
	CreateISODialog::CreateISODialog(PostTreeWidget *tree, bool isoSurface, QWidget *parent) : PostFunctionDialogBase(tree, parent),
																							   _ui(new Ui::CreateISODialog),
																							   _isSurface(isoSurface)
	{
		_ui->setupUi(this);
		init();
	}

	CreateISODialog::~CreateISODialog()
	{
		delete _ui;
	}

	void CreateISODialog::init()
	{
		_ui->nameLineEdit->setText(tr("ISOCurve"));
		this->setWindowTitle(tr("CreateISOCurve"));
		if (_isSurface)
		{
			this->setWindowTitle(tr("CreateISOSurface"));
			_ui->nameLineEdit->setText(tr("ISOSurface"));
		}
		_ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
		_ui->tableWidget->horizontalHeader()->setVisible(false);
		_ui->tableWidget->setColumnCount(1);

		setParentObject();
	}

	void CreateISODialog::accept()
	{
		if (_parentObject == nullptr)
		{
			QMessageBox::warning(this, tr("Warning!"), tr("No selected data!"));
			return;
		}

		QString algName;
		QStringList codes{};

		if (_isSurface)
		{
			algName = QString("ISOsurface");
			codes += QString("ISOsurface = PostProcess.ISOSurface()");
		}
		else
		{
			algName = QString("ISOcurve");
			codes += QString("ISOcurve = PostProcess.ISOCurve()");
		}

		QString name = _ui->nameLineEdit->text();
		QString vName = _ui->variableComboBox->currentText();

		codes += QString("%1.setParentID(%2)").arg(algName).arg(_parentObject->getID());
		codes += QString("%1.setName('%2')").arg(algName).arg(name);
		codes += QString("%1.setVariable('%2')").arg(algName).arg(vName);

		const int count = _ui->tableWidget->rowCount();
		for (int i = 0; i < count; i++)
		{
			auto item = _ui->tableWidget->item(i, 0);
			auto val = item->text().toDouble();
			codes += QString("%1.appendValue(%2)").arg(algName).arg(val);
		}

		codes += this->getSeletedDataCode(algName);

		codes += QString("%1.create()").arg(algName);

		_pyAgent->submit(codes);

		// 		ISORenderDataAlg* alg = nullptr;
		// 		if (_isSurface) alg = new ISORenderDataAlg(_parentObject);
		// 		else alg = new ISOCurveRenderDataAlg(_parentObject);
		// 		if (alg == nullptr) return;
		//
		// 		alg->setSelectedObjectHash(_tree->getSelectedData(_parentObject));
		//
		// 		QString name = _ui->nameLineEdit->text();
		// 		QString vName = _ui->variableComboBox->currentText();
		// 		const int count = _ui->tableWidget->rowCount();
		// 		for (int i = 0; i < count; i++)
		// 		{
		// 			auto item = _ui->tableWidget->item(i, 0);
		// 			auto val = item->text().toDouble();
		// 			alg->appendToValueList(val);
		// 		}
		//
		// 		alg->setVariable(vName);
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

	void CreateISODialog::reject()
	{
		QDialog::reject();
		this->close();
	}

	void CreateISODialog::updateDisplayInterface()
	{
		if (_parentObject == nullptr)
			return;

		updateVariableComboBox();
	}

	void CreateISODialog::updateVariableComboBox()
	{
		if (_parentObject == nullptr)
			return;
		_ui->variableComboBox->blockSignals(true);
		_ui->variableComboBox->clear();

		QStringList pArray = _parentObject->getPointDataArray();
		for (auto array : pArray)
		{
			if (_parentObject->variableType(1, array) != 1)
				continue;

			_ui->variableComboBox->addItem(array);
		}

		on_variableComboBox_currentIndexChanged(0);
		_ui->variableComboBox->blockSignals(false);
	}

	void CreateISODialog::on_addPushButton_clicked()
	{
		if (_parentObject == nullptr)
			return;
		QString name = _ui->variableComboBox->currentText();

		_parentObject->getRange(_range, 1, name, -1);

		if (_range[1] <= _range[0])
			return;

		double v = (_range[1] + _range[0]) * 0.5;
		const int row = _ui->tableWidget->rowCount();
		auto item = new QTableWidgetItem;

		item->setText(QString::number(v, 'g', 4));
		_ui->tableWidget->insertRow(row);
		_ui->tableWidget->setItem(row, 0, item);
	}

	void CreateISODialog::on_removePushButton_clicked()
	{
		const int row = _ui->tableWidget->currentRow();
		if (row < 0 || row >= _ui->tableWidget->rowCount())
			return;

		_ui->tableWidget->removeRow(row);
	}

	void CreateISODialog::on_removeAllPushButton_clicked()
	{
		_ui->tableWidget->clear();
		_ui->tableWidget->setRowCount(0);
	}

	void CreateISODialog::on_variableComboBox_currentIndexChanged(int index)
	{
		Q_UNUSED(index)
		if (_parentObject == nullptr)
			return;
		QString name = _ui->variableComboBox->currentText();

		_parentObject->getRange(_range, 1, name, -1);

		if (_range[1] <= _range[0])
			return;

		_ui->tableWidget->clear();
		_ui->tableWidget->setRowCount(1);
		_ui->tableWidget->setColumnCount(1);

		QString sRange = QString(tr("Range:[%1,%2]").arg(_range[0]).arg(_range[1]));
		double v = (_range[1] + _range[0]) * 0.5;
		auto item = new QTableWidgetItem();

		item->setText(QString::number(v, 'g', 4));
		//_ui->tableWidget->insertRow(0);
		_ui->tableWidget->setItem(0, 0, item);
		_ui->rangeLabel->setText(sRange);
	}

}
