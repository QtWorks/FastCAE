#include "PostFunctionDialogBase.h"
#include "PostTreeWidget.h"
#include "RenderWindowManager.h"
#include "PostRenderData/RenderDataManager.h"
#include "PostRenderData/RenderDataObject.h"
#include "PythonModule/PyAgent.h"
#include <QDebug>

namespace Post
{
	PostFunctionDialogBase::PostFunctionDialogBase(PostTreeWidget *tree, QWidget *parent /*= nullptr*/) : QDialog(parent)
	{
		this->setWindowFlags(Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint | Qt::Dialog);
		this->setAttribute(Qt::WA_DeleteOnClose);

		_tree = tree;
		_dataManager = RenderDataManager::getInstance();
		_windowManager = RenderWindowManager::getInstance();
		_pyAgent = Py::PythonAgent::getInstance();

		connect(_tree, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(setParentObject()));
	}

	PostFunctionDialogBase::~PostFunctionDialogBase()
	{
		qDebug() << "~PostFunctionDialogBase()";
	}

	QStringList PostFunctionDialogBase::getSeletedDataCode(QString name)
	{
		QStringList codes{};
		auto dataHash = _tree->getSelectedData(_parentObject);
		auto objList = dataHash.uniqueKeys();
		for (auto obj : objList)
		{
			auto blockList = dataHash.values(obj);
			for (auto block : blockList)
			{
				codes += QString("%1.appendBlock(%2,%3)").arg(name).arg(obj).arg(block);
			}
		}

		return codes;
	}

	void PostFunctionDialogBase::setParentObject()
	{
		_parentObject = nullptr;

		auto idList = _tree->getSelectedData().uniqueKeys();

		std::function<RenderDataObject *(RenderDataObject * obj)> getParentObject;
		getParentObject = [&getParentObject](RenderDataObject *obj)
		{
			if (obj->getParentObj() == nullptr)
				return obj;

			return getParentObject(obj->getParentObj());
		};

		if (idList.size() == 1)
		{
			auto id = idList.at(0);
			auto indList = _tree->getSelectedData().values(id);
			if (indList.size() == 1 && indList.at(0) == -1)
			{
				_parentObject = _dataManager->getObjectByID(id);
				updateDisplayInterface();
				return;
			}
		}

		for (auto id : idList)
		{
			auto obj = _dataManager->getObjectByID(id);
			if (obj == nullptr)
				continue;

			_parentObject = getParentObject(obj);
			if (_parentObject != nullptr)
				break;
		}
		updateDisplayInterface();
	}

	void PostFunctionDialogBase::updateDisplayInterface()
	{
		qDebug() << "Display Interface";
	}

}
