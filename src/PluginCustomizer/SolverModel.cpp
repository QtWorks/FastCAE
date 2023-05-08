#include "SolverModel.h"
#include "EditorDescripttionSetup.h"
#include "DataProperty/modelTreeItemType.h"

namespace FastCAEDesigner
{
	SolverModel::SolverModel(QString nameEng, QString nameChn, QString iconName, QObject *parent)
		: CustomParameterModel(nameEng, nameChn, iconName, TreeItemType::ProjectSolver, parent)
	{
	}

	SolverModel::~SolverModel()
	{
	}

}