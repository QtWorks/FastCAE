#include "MeshModel.h"
#include "ModelBase.h"
#include "DataProperty/modelTreeItemType.h"

namespace FastCAEDesigner
{
	MeshModel::MeshModel(QString nameEng, QString nameChn, QString iconName, QObject *parent)
		: ModelBase(nameEng, nameChn, iconName, TreeItemType::ProjectComponent, parent)
	{
	}

	MeshModel::~MeshModel()
	{
	}
}