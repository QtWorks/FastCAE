#include "PostModel.h"
#include "ModelBase.h"
#include "DataProperty/modelTreeItemType.h"

namespace FastCAEDesigner
{
	PostModel::PostModel(QString nameEng, QString nameChn, QString iconName, QObject *parent)
		: ModelBase(nameEng, nameChn, iconName, TreeItemType::ProjectPost, parent)
	{
	}

	PostModel::~PostModel()
	{
	}
}