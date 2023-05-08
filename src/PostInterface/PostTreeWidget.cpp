#include "PostTreeWidget.h"
#include "DialogRenderSetting.h"
#include "RenderDirector.h"
#include "GraphWidget.h"
#include "DialogCreateClip.h"
#include "MainWindow/MainWindow.h"
#include "PostRenderData/RenderDataManager.h"
#include "PostInterface/RenderWindowManager.h"
#include "PostRenderData/RenderDataObject.h"
#include "PostRenderData/RenderProperty.h"
#include <QMenu>
#include <QContextMenuEvent>
#include <QHeaderView>

namespace Post
{

	PostTreeWidget::PostTreeWidget(GUI::MainWindow *m) : _mainWindow(m)
	{
		this->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
		this->setSelectionMode(QAbstractItemView::ExtendedSelection); //设置多选模式
		this->setHeaderLabels(QStringList() << tr("Name") << tr("Transparency") << tr("Color") << tr("Variable"));

		_dataManager = RenderDataManager::getInstance();
		_windowManager = RenderWindowManager::getInstance();

		connect(_mainWindow, SIGNAL(updatePostTreeSig()), this, SLOT(updatePostTree()));
		connect(this, SIGNAL(showPostRenderWindowSig(int, int)), _mainWindow, SIGNAL(showPostWindowInfoSig(int, int)));
		connect(this, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(itemClicked(QTreeWidgetItem *)));
		connect(this, SIGNAL(itemChanged(QTreeWidgetItem *, int)), this, SLOT(itemChanged(QTreeWidgetItem *)));
		connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), this, SLOT(itemDoubleClicked(QTreeWidgetItem *)));
	}

	PostTreeWidget::~PostTreeWidget()
	{
	}

	void PostTreeWidget::contextMenuEvent(QContextMenuEvent *e)
	{
		QMenu popMenu;
		QAction *action = nullptr;
		auto item = this->itemAt(e->pos());
		if (item == nullptr)
			return;
		itemClicked(item);

		const int id = item->data(0, Qt::UserRole).toInt();
		const int index = item->data(1, Qt::UserRole).toInt();

		auto obj = _dataManager->getObjectByID(id);
		if (obj == nullptr)
			return;

		auto createWindowMenu = [=, &popMenu]()
		{
			QMenu *wMenu = new QMenu(&popMenu);
			QAction *act = nullptr;
			const int nWindow = _windowManager->getRenderWindowListCount();
			for (int j = 0; j < nWindow; j++)
			{
				auto window = _windowManager->getRenderWindowListAt(j);
				if (window == nullptr)
					continue;
				act = wMenu->addAction(tr("Window_%1").arg(j + 1));
				connect(act, &QAction::triggered, [=]
						{
                RenderDirector::getInstance()->renderDataObjectToWindow(obj, window->getID());
                emit showPostRenderWindowSig(window->getID(), window->getPostType()); });
			}

			return wMenu;
		};

		if (item->parent() == nullptr)
		{

			action = popMenu.addAction(tr("Show"));
			connect(action, &QAction::triggered, [=]
					{ setObjectVisible(item, true); });
			action = popMenu.addAction(tr("Hide"));
			connect(action, &QAction::triggered, [=]
					{ setObjectVisible(item, false); });
		}

		// action = popMenu.addAction(tr("Render to New Window"));
		action = popMenu.addAction(tr("Render to Window"));
		action->setMenu(createWindowMenu());
		action = popMenu.addAction(tr("Property Setting"));
		connect(action, &QAction::triggered, [=]
				{
        RenderSettingDialog* dlg = new RenderSettingDialog(this, obj, _mainWindow);
        dlg->show(); });

		if (index == -1)
		{
			// 			if (item->parent() != nullptr)
			// 			{
			// 				action = popMenu.addAction(tr("Edit"));
			// 				connect(action, &QAction::triggered, [=] {
			// 					auto clip = new CreateClipDialog(this, obj, true, _mainWindow);
			// 					clip->show(); });
			//
			// 			}

			action = popMenu.addAction(tr("Remove"));
			connect(action, &QAction::triggered, [=]
					{
            auto window = _windowManager->getRenderWindowByID(obj->getRenderWinID());
            window->removeObject(obj);
            QList<RenderDataObject*> sObjList;
            obj->getSubObjects(sObjList);
            for (auto sObj : sObjList)
                window->removeObject(sObj);

            window->reRender();
            _dataManager->removeObject(obj);
            this->updatePostTree(); });
		}

		popMenu.exec(QCursor::pos());
	}

	void PostTreeWidget::createTree(QTreeWidgetItem *parent, RenderDataObject *obj)
	{
		auto createItem = [=](RenderDataObject *dObj, QStringList proList, int index)
		{
			auto item = new QTreeWidgetItem(parent);
			item->setText(0, proList.at(0));
			item->setText(1, proList.at(1));
			item->setBackground(2, Qt::white);
			item->setText(3, proList.at(2));
			item->setData(0, Qt::UserRole, dObj->getID());
			item->setData(1, Qt::UserRole, index);
			RenderProperty *pro = nullptr;
			if (index == -1)
				pro = dObj->getPropertyListAt(0);
			else
				pro = dObj->getPropertyListAt(index);

			if (pro != nullptr)
			{
				double color[3]{0};
				pro->getPropertyColor(color);
				item->setBackground(2, QColor(color[0] * 255, color[1] * 255, color[2] * 255));
			}

			return item;
		};

		const int nBlock = obj->getNumberOfBlocks();

		for (int i = 0; i < nBlock; i++)
		{
			const int id = obj->getID();
			QStringList proList = getBlockDataProperty(obj, i);
			if (proList.size() != 3)
				continue;
			int index = i;
			if (nBlock == 1)
				index = -1;
			auto bItem = createItem(obj, proList, index);
			Qt::CheckState state = Qt::Checked;
			if (!obj->getBlockShowStatus(i))
				state = Qt::Unchecked;
			bItem->setCheckState(0, state);
		}

		const int nChild = obj->getSubObjectsCount();
		for (int i = 0; i < nChild; i++)
		{
			auto cObj = obj->getSubObjectsAt(i);
			const QString name = cObj->getName();
			const int id = cObj->getID();
			QStringList proList = getBlockDataProperty(cObj, -1);
			if (proList.size() != 3)
				continue;
			auto cItem = createItem(cObj, proList, -1);
			Qt::CheckState state = Qt::Checked;
			if (!cObj->getShowStatus())
				state = Qt::Unchecked;
			cItem->setCheckState(0, state);
			createTree(parent, cObj);
		}
	}

	QStringList PostTreeWidget::getBlockDataProperty(RenderDataObject *obj, const int index)
	{
		QStringList pList;
		QString name = obj->getBlockName(index);
		if (index == -1)
			name = obj->getName();
		if (name.isEmpty())
			name = QString("Zone_%1").arg(index + 1);

		pList.append(name);

		int pIndex = index;
		if (pIndex == -1)
			pIndex = 0;

		auto dProperty = obj->getPropertyListAt(pIndex);
		if (dProperty == nullptr)
			return pList;

		QString transp = QString("%1%").arg(dProperty->getTransparency() * 100);
		QString varName = dProperty->getVariableName();
		if (varName.isEmpty() || dProperty->getVariableType() == 0)
			varName = tr("SolidColor");

		pList.append(transp);
		pList.append(varName);

		return pList;
	}

	void PostTreeWidget::setSelectedDataObject()
	{
		_selectedDataObject.clear();

		QList<QTreeWidgetItem *> items = this->selectedItems();

		QTreeWidgetItem *parentItem = nullptr;

		for (auto item : items)
		{
			if (parentItem == nullptr)
			{
				if (item->parent() == nullptr)
					parentItem = item;
				else
				{
					parentItem = item->parent();
					auto id = item->data(0, Qt::UserRole).toInt();
					auto index = item->data(1, Qt::UserRole).toInt();
					_selectedDataObject.insert(id, index);
				}
			}
			else
			{
				if (item->parent() == nullptr)
					continue;

				if (item->parent() != parentItem)
					continue;

				auto id = item->data(0, Qt::UserRole).toInt();
				auto index = item->data(1, Qt::UserRole).toInt();
				_selectedDataObject.insert(id, index);
			}
		}
	}

	QMultiHash<int, int> PostTreeWidget::getSelectedData(RenderDataObject *obj)
	{
		if (obj == nullptr)
			return _selectedDataObject;

		const int id = obj->getID();

		auto idList = _selectedDataObject.uniqueKeys();

		if (!idList.contains(id))
			return QMultiHash<int, int>();

		return _selectedDataObject;
	}

	Post::RenderDataObject *PostTreeWidget::getCurrentRenderData()
	{
		auto item = this->currentItem();
		if (item == nullptr)
			return nullptr;

		auto id = item->data(0, Qt::UserRole).toInt();

		return _dataManager->getObjectByID(id);
	}

	void PostTreeWidget::setSelectedData(QMultiHash<int, int> dataHash)
	{
		_selectedDataObject = dataHash;
		// 		auto idList = dataHash.uniqueKeys();
		//
		//
		// 		auto
		//
		// 		const int ntop = this->topLevelItemCount();
		// 		for (int i = 0; i < ntop; i++)
		// 		{
		// 			auto topItem = this->topLevelItem(i);
		//
		// 		}
	}

	void PostTreeWidget::reTranslate()
	{
		QStringList hLabel{};
		hLabel.append(tr("Name"));
		hLabel.append(tr("Transparency"));
		hLabel.append(tr("Color"));
		hLabel.append(tr("Variable"));
		this->setHeaderLabels(hLabel);
	}

	void PostTreeWidget::updatePostTree()
	{
		this->clear();
		const int n = _dataManager->getRenderObjectListCount();
		for (int i = 0; i < n; ++i)
		{
			auto vObj = _dataManager->getRenderObjectListAt(i);
			const QString name = vObj->getName();
			const int id = vObj->getID();
			auto treeItem = new QTreeWidgetItem();
			treeItem->setText(0, name);
			treeItem->setData(0, Qt::UserRole, id);
			treeItem->setData(1, Qt::UserRole, -1);
			// 			Qt::CheckState state = Qt::Checked;
			// 			if (!vObj->getShowStatus()) state = Qt::Unchecked;
			// 			treeItem->setCheckState(0, state);
			createTree(treeItem, vObj);
			this->addTopLevelItem(treeItem);
		}
		this->expandAll();
		// 		emit currentViewOBjChanged(nullptr);
		// 		int id = ViewDataObject::getMaxID();
		// 		do
		// 		{
		// 			auto vobj = dataManager->getObjectByID(id);
		// 			if (vobj != nullptr && vobj->getShowStatus())
		// 			{
		// 				emit currentViewOBjChanged(vobj);
		// 				break;
		// 			}
		// 			id--;
		// 		} while (id > 0);
	}

	void PostTreeWidget::itemClicked(QTreeWidgetItem *item)
	{
		if (item == nullptr)
			return;

		if (item->childCount() > 0)
		{
			int nChild = item->childCount();
			for (int i = 0; i < nChild; i++)
			{
				item->child(i)->setSelected(true);
			}
		}

		const int id = item->data(0, Qt::UserRole).toInt();
		auto obj = _dataManager->getObjectByID(id);
		if (obj != nullptr)
		{
			const int index = item->data(1, Qt::UserRole).toInt();
			if (index == -1)
				emit currentRenderDataChanged(obj);

			auto window = _windowManager->getRenderWindowByID(obj->getRenderWinID());
			if (window != nullptr)
				emit showPostRenderWindowSig(window->getID(), window->getPostType());
		}

		setSelectedDataObject();
	}

	void PostTreeWidget::itemChanged(QTreeWidgetItem *item)
	{
		if (item == nullptr)
			return;

		if (item->childCount() > 0)
		{
			int nChild = item->childCount();
			for (int i = 0; i < nChild; i++)
			{
				item->child(i)->setSelected(true);
			}
		}

		const int id = item->data(0, Qt::UserRole).toInt();
		const int index = item->data(1, Qt::UserRole).toInt();

		bool show = false;
		if (item->checkState(0) == Qt::Checked)
			show = true;

		RenderDirector::getInstance()->updateDataObjectShowStatus(id, show, index);
	}

	void PostTreeWidget::itemDoubleClicked(QTreeWidgetItem *item)
	{
		if (item == nullptr)
			return;

		bool ok = false;
		// vtkDataSet* data = nullptr;

		int id = item->data(0, Qt::UserRole).toInt(&ok);
		if (!ok)
			return;

		auto obj = _dataManager->getObjectByID(id);
		if (obj == nullptr)
			return;

		// 		data = obj->getOutputData();

		// int index = item->data(1, Qt::UserRole).toInt(&ok);
		//  		if (ok) data = obj->getOutputData(index);
		//
		//  		if (data == nullptr)return;

		RenderSettingDialog *dlg = new RenderSettingDialog(this, obj, _mainWindow);
		dlg->show();
	}

	void PostTreeWidget::setObjectVisible(QTreeWidgetItem *item, bool v)
	{
		if (item == nullptr)
			return;
		if (item->parent() != nullptr)
			return;

		auto id = item->data(0, Qt::UserRole).toInt();
		// auto index = item->data(2, Qt::UserRole).toInt();

		auto obj = _dataManager->getObjectByID(id);
		if (obj == nullptr)
			return;
		obj->setShowStatus(v);

		auto nChild = item->childCount();
		for (int i = 0; i < nChild; i++)
		{
			auto child = item->child(i);
			if (child == nullptr)
				continue;

			auto cID = child->data(0, Qt::UserRole).toInt();
			if (cID == id)
				continue;

			auto cObj = _dataManager->getObjectByID(cID);
			if (cObj == nullptr)
				continue;

			auto cIndex = child->data(1, Qt::UserRole).toInt();
			if (cIndex == -1)
				cObj->setShowStatus(v);
		}

		auto window = RenderWindowManager::getInstance()->getRenderWindowByID(obj->getRenderWinID());
		window->reRender();
		this->updatePostTree();
	}

}
