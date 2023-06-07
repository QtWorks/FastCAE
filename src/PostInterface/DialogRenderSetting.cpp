#include "DialogRenderSetting.h"

#include "GraphWidget.h"
#include "PostInterface/RenderWindowManager.h"
#include "PostRenderData/RenderDataObject.h"
#include "PostRenderData/RenderProperty.h"
#include "PostTreeWidget.h"
#include "PythonModule/PyAgent.h"
#include "ui_DialogRenderSetting.h"

#include <QColorDialog>
#include <QHeaderView>

namespace Post {
	// 	RenderSettingDialog::RenderSettingDialog(RenderDataObject* obj, int index, QWidget *parent)
	// : 		QDialog(parent), 		_ui(new Ui::RenderSettingDialog), 		_dataObject(obj)
	// 	{
	// 		_ui->setupUi(this);
	// 		this->setWindowFlags(Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
	// 		this->setAttribute(Qt::WA_DeleteOnClose);
	// 		//this->setWindowModality(Qt::NonModal);
	// 		_ui->variableTreeWidget->header()->setSectionResizeMode(QHeaderView::Stretch);
	//
	// 		auto windowManager = PostDataManager::getInstance()->getRenderWindowManager();
	// 		if (windowManager == nullptr) return;
	// 		_renderWindow = windowManager->getRenderWindowByID(obj->getRenderWinID());
	//
	// 		if (index > -1)
	// 			_renderProperty = _dataObject->getPropertyListAt(index);
	//
	// 		init();
	//
	// 		connect(_ui->variableTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this,
	// SLOT(setColorByVariable(QTreeWidgetItem*))); 		connect(_ui->transparencyHorizontalSlider,
	// SIGNAL(valueChanged(int)), this, SLOT(setTransparency(const int)));
	// 		connect(_ui->transparencySpinBox, SIGNAL(valueChanged(int)), this,
	// SLOT(setTransparency(const int)));
	// 	}

	RenderSettingDialog::RenderSettingDialog(PostTreeWidget* tree, RenderDataObject* obj,
											 QWidget* parent /*= nullptr*/)
		: QDialog(parent)
		, _ui(new Ui::RenderSettingDialog)
		, _dataObject(obj)
		, _tree(tree)
	{
		_ui->setupUi(this);

		this->setWindowFlags(Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint | Qt::Dialog);
		this->setAttribute(Qt::WA_DeleteOnClose);

		_ui->variableTreeWidget->header()->setSectionResizeMode(QHeaderView::Stretch);
		_renderWindow =
			RenderWindowManager::getInstance()->getRenderWindowByID(_dataObject->getRenderWinID());

		init();
	}

	RenderSettingDialog::~RenderSettingDialog()
	{
		delete _ui;
	}

	void RenderSettingDialog::init()
	{
		auto initInterfaceUI = [=](RenderProperty* pro) {
			double color[3] = { 0 };
			pro->getPropertyColor(color);
			_ui->variableColorPushButton->setStyleSheet(QString("background-color: rgb(%1,%2,%3);")
															.arg(color[0] * 255)
															.arg(color[1] * 255)
															.arg(color[2] * 255));
			auto trans = pro->getTransparency();
			_ui->transparencyHorizontalSlider->setValue(trans * 100);
			_ui->transparencySpinBox->setValue(trans * 100);
			auto type = pro->getVariableType();
			if(type == 0) {
				_ui->colorBarCheckBox->setChecked(false);
				_ui->colorBarCheckBox->setEnabled(false);
				_ui->variableColorCheckBox->setChecked(false);
				_ui->variableColorCheckBox->setEnabled(false);
			} else {
				_ui->colorBarCheckBox->setChecked(pro->getShowColorMap());
				_ui->colorBarCheckBox->setEnabled(true);
				_ui->variableColorCheckBox->setChecked(true);
				_ui->variableColorCheckBox->setEnabled(true);
			}
		};

		QMultiHash<int, int> dataList = _tree->getSelectedData(_dataObject);

		if(dataList.size() > 0) {
			auto id	   = dataList.uniqueKeys().at(0);
			auto index = dataList.values(id).at(0);
			if(index == -1) {
				auto obj	= _dataObject->getObjectByID(id);
				auto objPro = obj->getPropertyListAt(0);
				initInterfaceUI(objPro);
			} else {
				auto objPro = _dataObject->getPropertyListAt(index);
				initInterfaceUI(objPro);
			}
		}

		QStringList pArrayList = _dataObject->getPointDataArray();
		QStringList cArrayList = _dataObject->getCellDataArray();
		initVariableTreeWidget(1, pArrayList);
		initVariableTreeWidget(2, cArrayList);

		connect(_ui->variableTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this,
				SLOT(setColorByVariable(QTreeWidgetItem*)));
		connect(_ui->transparencyHorizontalSlider, SIGNAL(valueChanged(int)), this,
				SLOT(setTransparency(const int)));
		connect(_ui->transparencySpinBox, SIGNAL(valueChanged(int)), this,
				SLOT(setTransparency(const int)));
	}

	void RenderSettingDialog::initVariableTreeWidget(int loc, QStringList arrayList)
	{
		QString locName = tr("Point");
		if(loc == 2)
			locName = tr("Cell");
		// 		int cType = 1;
		// 		int cIndex = -1;
		// 		QString cVariable;
		//
		// 		getCurrentVariable(cVariable, cType, cIndex);

		auto createTreeItem = [=](QString name, QString type, int loc, int index = -1) {
			auto item = new QTreeWidgetItem;
			item->setText(0, name);
			item->setText(1, type);
			item->setData(0, Qt::UserRole, loc);
			item->setData(1, Qt::UserRole, index);
			_ui->variableTreeWidget->addTopLevelItem(item);

			// 			if ((name == cVariable) && (loc == cType) && (index == cIndex))
			// 			{
			// 				_ui->variableTreeWidget->setCurrentItem(item);
			// 				item->setSelected(true);
			// 			}
		};

		for(auto name : arrayList) {
			const auto vType = _dataObject->variableType(loc, name);
			if(vType == "scalar") {
				createTreeItem(name, tr("%1Scalar").arg(locName), loc);
			} else if(vType == "vector") {
				createTreeItem(name, tr("%1Vector-X").arg(locName), loc, 0);
				createTreeItem(name, tr("%1Vector-Y").arg(locName), loc, 1);
				createTreeItem(name, tr("%1Vector-Z").arg(locName), loc, 2);
			} else if(vType == "tensor") {
				createTreeItem(name, tr("%1Tensor").arg(locName), loc);
			}
		}
	}

	QString RenderSettingDialog::getVariableType(int loc, int type)
	{
		QString locName = tr("Point");
		if(loc == 1)
			locName = tr("Cell");

		QString typeName;
		switch(type) {
			case 1:
				typeName = tr("Scalar");
				break;
			case 2:
				typeName = tr("Vector");
				break;
			case 3:
				typeName = tr("Tensor");
				break;
			default:
				break;
		}

		if(typeName.isEmpty())
			return typeName;

		return locName + typeName;
	}

	void RenderSettingDialog::getCurrentVariable(QString& name, int& loc, int& index)
	{
		Q_UNUSED(name)
		Q_UNUSED(loc)
		Q_UNUSED(index)
		// 		if (_renderProperty == nullptr)
		// 		{
		// 			auto pro = _dataObject->getPropertyListAt(_dataObject->getPropertyListCount() -
		// 1); 			if (pro == nullptr) return; 			name = pro->getVariableName(); 			loc =
		// pro->getVariableType(); 			index = pro->getComponentIndex();
		// 		}
		// 		else
		// 		{
		// 			name = _renderProperty->getVariableName();
		// 			loc = _renderProperty->getVariableType();
		// 			index = _renderProperty->getComponentIndex();
		// 		}
	}

	void RenderSettingDialog::getRenderPropertyList()
	{
		_propertyList.clear();

		QMultiHash<int, int> dataList = _tree->getSelectedData(_dataObject);

		for(auto id : dataList.uniqueKeys()) {
			auto obj = _dataObject->getObjectByID(id);
			if(obj == nullptr)
				continue;

			for(auto bIndex : dataList.values(id)) {
				if(bIndex == -1) {
					auto cPro = obj->getPropertyListAt(0);
					if(cPro == nullptr)
						continue;
					_propertyList.append(cPro);
				} else {
					auto bPro = obj->getPropertyListAt(bIndex);
					if(bPro == nullptr)
						continue;
					_propertyList.append(bPro);
				}
			}
		}
	}

	void RenderSettingDialog::on_variableColorPushButton_clicked()
	{
		QColor c	 = _ui->variableColorPushButton->palette().color(QPalette::Background);

		QColor color = QColorDialog::getColor(c, this);
		if(color.isValid()) {
			_ui->variableColorCheckBox->setChecked(false);
			_ui->variableColorCheckBox->setEnabled(false);
			_ui->colorBarCheckBox->setChecked(false);
			_ui->colorBarCheckBox->setEnabled(false);
			_ui->variableColorPushButton->setStyleSheet(QString("background-color: rgb(%1,%2,%3);")
															.arg(color.red())
															.arg(color.green())
															.arg(color.blue()));

			// 			getRenderPropertyList();
			//
			// 			for (auto pro : _propertyList)
			// 				pro->setPropertyColor(color.redF(), color.greenF(), color.blueF());

			auto		dataHash = _tree->getSelectedData(_dataObject);
			QStringList codes{};

			codes += QString("variablecolor = PostProcess.VariableColor()");
			codes += QString("variablecolor.setColor(%1,%2,%3)")
						 .arg(color.redF())
						 .arg(color.greenF())
						 .arg(color.blueF());

			for(auto obj : dataHash.uniqueKeys()) {
				auto blockList = dataHash.values(obj);
				for(auto block : blockList) {
					codes += QString("variablecolor.appendBlock(%1,%2)").arg(obj).arg(block);
				}
			}

			codes += QString("variablecolor.updateColor()");

			Py::PythonAgent::getInstance()->submit(codes);

			_renderWindow->reRender();
			_tree->updatePostTree();
		}
	}

	void RenderSettingDialog::on_variableColorCheckBox_clicked()
	{
		if(!_ui->variableColorCheckBox->isChecked()) {
			_ui->variableColorCheckBox->setEnabled(false);
			_ui->colorBarCheckBox->setChecked(false);
			_ui->colorBarCheckBox->setEnabled(false);
			QColor		color = _ui->variableColorPushButton->palette().color(QPalette::Background);

			// 			getRenderPropertyList();
			//
			// 			for (auto pro : _propertyList)
			// 				pro->setPropertyColor(color.redF(), color.greenF(), color.blueF());

			auto		dataHash = _tree->getSelectedData(_dataObject);
			QStringList codes{};

			codes += QString("variablecolor = PostProcess.VariableColor()");
			codes += QString("variablecolor.setColor(%1,%2,%3)")
						 .arg(color.redF())
						 .arg(color.greenF())
						 .arg(color.blueF());

			for(auto obj : dataHash.uniqueKeys()) {
				auto blockList = dataHash.values(obj);
				for(auto block : blockList) {
					codes += QString("variablecolor.appendBlock(%1,%2)").arg(obj).arg(block);
				}
			}

			codes += QString("variablecolor.updateColor()");

			Py::PythonAgent::getInstance()->submit(codes);

			_renderWindow->reRender();
			_tree->updatePostTree();
		}
	}

	void RenderSettingDialog::on_colorBarCheckBox_clicked()
	{
		bool show = _ui->colorBarCheckBox->isChecked();

		getRenderPropertyList();

		for(auto pro : _propertyList)
			pro->setShowColorMap(show);

		_renderWindow->reRender();
	}

	void RenderSettingDialog::setTransparency(const int value)
	{
		_ui->transparencyHorizontalSlider->blockSignals(true);
		_ui->transparencySpinBox->blockSignals(true);
		_ui->transparencyHorizontalSlider->setValue(value);
		_ui->transparencySpinBox->setValue(value);
		_ui->transparencyHorizontalSlider->blockSignals(false);
		_ui->transparencySpinBox->blockSignals(false);

		if(_dataObject == nullptr)
			return;

		double trans = (double)value / 100;

		getRenderPropertyList();

		for(auto pro : _propertyList)
			pro->setTransparency(trans);

		_renderWindow->reRender();
		_tree->updatePostTree();
	}

	void RenderSettingDialog::setColorByVariable(QTreeWidgetItem* item)
	{
		_ui->variableColorCheckBox->setEnabled(true);
		_ui->variableColorCheckBox->setChecked(true);
		_ui->colorBarCheckBox->setEnabled(true);

		QString		name	 = item->text(0);
		int			type	 = item->data(0, Qt::UserRole).toInt();
		int			index	 = item->data(1, Qt::UserRole).toInt();

		// 		getRenderPropertyList();
		//
		// 		for (auto pro : _propertyList)
		// 			pro->setCurrentVariable(type, name, index);

		auto		dataHash = _tree->getSelectedData(_dataObject);
		QStringList codes{};

		codes += QString("variablecolor = PostProcess.VariableColor()");
		codes += QString("variablecolor.selectVariable(%1,'%2',%3)").arg(type).arg(name).arg(index);

		for(auto obj : dataHash.uniqueKeys()) {
			auto blockList = dataHash.values(obj);
			for(auto block : blockList) {
				codes += QString("variablecolor.appendBlock(%1,%2)").arg(obj).arg(block);
			}
		}

		codes += QString("variablecolor.useVariable()");
		codes += QString("variablecolor.updateColor()");

		Py::PythonAgent::getInstance()->submit(codes);

		_renderWindow->reRender();
		_tree->updatePostTree();
	}

} // namespace Post
