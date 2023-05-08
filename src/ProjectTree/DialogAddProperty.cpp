#include "DialogAddProperty.h"
#include <ui_DialogAddProperty.h>
#include "Material/Material.h"
#include "Material/MaterialSingletion.h"
#include "ModelData/elementProperty.h"
#include "ModelData/modelDataBaseExtend.h"

namespace ProjectTree
{
	AddPropDialog::AddPropDialog(GUI::MainWindow * mw, ModelData::ModelDataBaseExtend * model)
		:_mainWindow(mw), _model(model)
	{
		_ui = new Ui::CreateEleProp;
		_ui->setupUi(this);
		init();
	}

	AddPropDialog::~AddPropDialog()
	{
		if (_ui != nullptr) delete _ui;
	}

	void ProjectTree::AddPropDialog::init()
	{
		int id = ModelData::ElementProperty::getMaxID();
		QString text = QString("Prop_%1").arg(id+1);
		_ui->nameLineEdit->setPlaceholderText(text);

		auto mdata = Material::MaterialSingleton::getInstance();
		const int n = mdata->getMaterialCount();
		for (int i = 0; i < n; ++i)
		{
			auto m = mdata->getMaterialAt(i);
			const int id = m->getID();
			_ui->materialCombox->addItem(QIcon(), m->getName(), id);
		}
	}

	void AddPropDialog::accept()
	{
		QString name = _ui->nameLineEdit->text();
		if (name.isEmpty()) name = _ui->nameLineEdit->placeholderText();

		int matID = _ui->materialCombox->currentData(Qt::UserRole).toInt();
		if (matID < 1) return;

		auto prop = new  ModelData::ElementProperty();
		prop->setName(name);
		prop->setEleType(_ui->eleTypeCombox->currentText());
		prop->setMaterialID(matID);

		_model->appendEleProperty(prop);

		QDialog::accept();
	}

}

