#include "SimulationModel.h"
#include "EditorDescripttionSetup.h"
#include "DataProperty/modelTreeItemType.h"
#include <QTreeWidgetItem>

namespace FastCAEDesigner
{
	SimulationModel::SimulationModel(QString nameEng, QString nameChn, QString iconName, QObject *parent)
		: CustomParameterModel(nameEng, nameChn, iconName, TreeItemType::ProjectSimulationSetting, parent)
	{
	}

	SimulationModel::~SimulationModel()
	{
	}

}