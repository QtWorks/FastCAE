#include "DialogAssignProperty.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include "ModelData/modelDataBaseExtend.h"
#include "MeshData/meshSingleton.h"
#include "MeshData/meshSet.h"
#include "Geometry/geometryData.h"
#include "Geometry/GeoComponent.h"
#include "Material/MaterialSingletion.h"
#include "Material/Material.h"
#include "PythonModule/PyAgent.h"
#include "ModelData/elementProperty.h"
#include <QDebug>

namespace ProjectTree
{
	AssignPropertyDialog::AssignPropertyDialog(GUI::MainWindow *mainwindow, ModelData::ModelDataBaseExtend *data)
		: ComponentSelectDialogBase(mainwindow, nullptr, nullptr), _data(data)
	{
		_layout = new QHBoxLayout;
		_label = new QLabel("Property");
		_combobox = new QComboBox;
		_layout->addWidget(_label);
		_layout->addWidget(_combobox);
		this->setCustomLayout(_layout);
		init();
	}

	AssignPropertyDialog::~AssignPropertyDialog()
	{
		if (_label != nullptr)
			delete _label;
		if (_combobox != nullptr)
			delete _combobox;
		if (_layout != nullptr)
			delete _layout;
	}

	void AssignPropertyDialog::init()
	{
		MeshData::MeshData *meshdata = MeshData::MeshData::getInstance();
		QList<int> setlist = _data->getMeshSetList();
		for (int i = 0; i < setlist.size(); ++i)
		{
			int setid = setlist.at(i);
			MeshData::MeshSet *set = meshdata->getMeshSetByID(setid);
			if ((set == nullptr) || (set->getSetType() != MeshData::Element))
				continue;
			QString name = set->getName();
			this->appendItemToAvailableList(name, setid, ":/QUI/icon/mesh.png");
		}

		auto *geoData = Geometry::GeometryData::getInstance();
		QList<int> gcIDs = _data->getGeoComponentIDList();
		for (int gcID : gcIDs)
		{
			auto aGC = geoData->getGeoComponentByID(gcID);
			if (!aGC)
				continue;
			appendItemToAvailableList(aGC->getName(), gcID, ":/QUI/icon/geometry.png");
		}

		//		Material::MaterialSingleton* materialData = Material::MaterialSingleton::getInstance();
		//		const int n = materialData->getMaterialCount();
		const int n = _data->getElePropCount();
		for (int i = 0; i < n; ++i)
		{
			//			Material::Material* m = materialData->getMaterialAt(i);
			auto m = _data->getElePropertyAt(i);
			QString name = m->getName();
			const int id = m->getID();
			_combobox->addItem(name, id);
		}
	}

	void AssignPropertyDialog::accept()
	{
		QMap<int, QString> idname = this->getSelectedItemIDNames();
		QList<int> ids = idname.keys();
		const int currentindex = _combobox->currentIndex();
		const int mid = _combobox->itemData(currentindex).toInt();
		QString cpIDs;
		for (int i = 0; i < ids.size(); ++i)
		{
			int cpID = ids.at(i);
			cpIDs.append(QString::number(cpID)).append(';');
		}
		QString code = QString("Case.setProperty(%1,\"%2\",%3)").arg(_data->getID()).arg(cpIDs.left(cpIDs.size() - 1)).arg(mid);
		Py::PythonAgent::getInstance()->submit(code);
		ComponentSelectDialogBase::accept();
	}
}
