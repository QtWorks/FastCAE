#include "DialogCreateVector.h"
#include "ui_DialogCreateVector.h"
#include "PostTreeWidget.h"
#include "RenderDirector.h"
#include "PostRenderData/RenderDataManager.h"
#include "PostInterface/RenderWindowManager.h"
#include "PostRenderData/GlyphingRenderDataAlg.h"
#include "PythonModule/PyAgent.h"
#include <vtkDataSet.h>
#include <QTreeWidget>
#include <QMessageBox>

namespace Post
{
	CreateVectorDialog::CreateVectorDialog(PostTreeWidget *tree, QWidget *parent /*= nullptr*/) : // QDialog(parent),
																								  PostFunctionDialogBase(tree, parent),
																								  _ui(new Ui::CreateVectorDialog)
	// 		_tree(tree),
	// 		_dataManager(RenderDataManager::getInstance()),
	// 		_windowManager(RenderWindowManager::getInstance())
	{
		_ui->setupUi(this);

		// 		this->setWindowFlags(Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint | Qt::Dialog);
		// 		this->setAttribute(Qt::WA_DeleteOnClose);

		init();
	}

	CreateVectorDialog::~CreateVectorDialog()
	{
		delete _ui;
	}

	void CreateVectorDialog::init()
	{
		_ui->nameLineEdit->setText(tr("Vector"));
		setParentObject();
		//	connect(_tree, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(setParentObject()));
	}

	void CreateVectorDialog::accept()
	{
		if (_parentObject == nullptr)
		{
			QMessageBox::warning(this, tr("Warning!"), tr("No selected data!"));
			return;
		}

		QString name = _ui->nameLineEdit->text();
		QString vName = _ui->vectorComboBox->currentText();
		bool isPoint = true;
		if (_ui->vectorComboBox->currentData().toInt() == 2)
			isPoint = false;

		int sMode = _ui->scaleModeComboBox->currentIndex();
		int maxnum = _ui->maxinumPointsSpinBox->value();
		double sFactor = _ui->scaleFactorDoubleSpinBox->value();

		QStringList codes{};

		codes += QString("vector = PostProcess.Vector()");
		codes += QString("vector.setParentID(%1)").arg(_parentObject->getID());
		codes += QString("vector.setName('%1')").arg(name);
		codes += QString("vector.setVectorName('%1')").arg(vName);
		codes += QString("vector.setMaxNumber(%1)").arg(maxnum);
		codes += QString("vector.setScaleMode(%1)").arg(sMode);
		codes += QString("vector.setScaleFactor(%1)").arg(sFactor);
		codes += QString("vector.setUsePointData(%1)").arg(isPoint);

		codes += this->getSeletedDataCode("vector");
		codes += QString("vector.create()");

		_pyAgent->submit(codes);

		// 		GlyphingRenderDataAlg* alg = new GlyphingRenderDataAlg(_parentObject);
		// 		alg->setSelectedObjectHash(_tree->getSelectedData(_parentObject));
		// 		alg->setName(name);
		// 		alg->setMaxNumber(maxnum);
		// 		alg->setUsePointData(isPoint);
		// 		alg->setScaleMode(sMode);
		// 		alg->setVector(vName);
		// 		alg->setScaleFactor(sFactor);
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

	void CreateVectorDialog::reject()
	{
		QDialog::reject();
		this->close();
	}

	void CreateVectorDialog::updateDisplayInterface()
	{
		if (_parentObject == nullptr)
			return;

		updateVectorComboBox();
		_ui->nameLineEdit->setText(tr("Vector_%1").arg(_parentObject->getNumberOfAlgorithmByType(Post::AlgorithmType::Vector) + 1));

		const int maxnum = [](int a, int b)
		{ return a > b ? a : b; }(_parentObject->getCellDataNum(), _parentObject->getPointDataNum());
		_ui->maxinumPointsSpinBox->setMaximum(maxnum);
		_ui->maxinumPointsSpinBox->setValue(int(maxnum * 0.6));

		auto data = _parentObject->getOutputData();
		if (data != nullptr)
		{
			double mfactor = data->GetLength();
			_ui->scaleFactorDoubleSpinBox->setMaximum(mfactor * 0.1);
			_ui->scaleFactorDoubleSpinBox->setValue(mfactor * 0.06);
		}
	}

	void CreateVectorDialog::updateVectorComboBox()
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

	// 	void CreateVectorDialog::setSelectedObjectList()
	// 	{
	// 		if (_parentObject == nullptr) return;
	//
	// 		_selectedObjects.clear();
	//
	// 		auto objs = _tree->getSelectedData();
	// 		for (auto id : objs.uniqueKeys())
	// 		{
	// 			auto obj = _dataManager->getObjectByID(id);
	// 			if(obj == nullptr) continue;
	//
	// 			auto vList = objs.values(id);
	// 			if ((vList.size() == 1) && (vList.at(0) == -1))
	// 				_selectedObjects.append(obj->getOutputData());
	// 			else if (vList.size() == obj->getNumberOfBlocks())
	// 				_selectedObjects.append(obj->getOutputData());
	//
	//
	// 		}
	// 	}

	// 	void CreateVectorDialog::setParentObject()
	// 	{
	// 		_parentObject = nullptr;
	//
	// 		auto idList = _tree->getSelectedData().uniqueKeys();
	//
	// 		std::function<RenderDataObject*(RenderDataObject* obj)> getParentObject;
	// 		getParentObject = [&getParentObject](RenderDataObject* obj) {
	// 			if (obj->getParentObj() == nullptr) return obj;
	//
	// 			return getParentObject(obj->getParentObj());
	// 		};
	//
	// 		if (idList.size() == 1)
	// 		{
	// 			auto id = idList.at(0);
	// 			auto indList = _tree->getSelectedData().values(id);
	// 			if (indList.size() == 1 && indList.at(0) == -1)
	// 			{
	// 				_parentObject = _dataManager->getObjectByID(id);
	// 				updateDisplayInterface();
	// 				return;
	// 			}
	// 		}
	//
	// 		for (auto id : idList)
	// 		{
	// 			auto obj = _dataManager->getObjectByID(id);
	// 			if (obj == nullptr) continue;
	//
	// 			_parentObject = getParentObject(obj);
	// 			if (_parentObject != nullptr) break;
	// 		}
	// 		updateDisplayInterface();
	// 	}

}