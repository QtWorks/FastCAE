#ifndef _POSTTREEWIDGET_H_
#define _POSTTREEWIDGET_H_

#include "PostInterfaceAPI.h"
#include <QTreeWidget>

namespace GUI
{
	class MainWindow;
}

namespace Post
{
	class RenderDataManager;
	class RenderDataObject;
	class RenderWindowManager;

	class POSTINTERFACEAPI PostTreeWidget :public QTreeWidget
	{
		Q_OBJECT

	public:
		PostTreeWidget(GUI::MainWindow* m);
		~PostTreeWidget();

	signals:
		void showPostRenderWindowSig(int id, int type);
		void currentRenderDataChanged(RenderDataObject* obj);

	public:
		QMultiHash<int, int> getSelectedData(RenderDataObject* obj = nullptr);

		RenderDataObject* getCurrentRenderData();

		void setSelectedData(QMultiHash<int, int> dataHash);

		void reTranslate();
	
	public slots:
		void updatePostTree();

	private:
		void contextMenuEvent(QContextMenuEvent *e);
		void createTree(QTreeWidgetItem* parent,RenderDataObject* obj);
		QStringList getBlockDataProperty(RenderDataObject* obj, const int index);
		void setSelectedDataObject();

	private slots:
		void itemClicked(QTreeWidgetItem* item);
		void itemChanged(QTreeWidgetItem* item);
		void itemDoubleClicked(QTreeWidgetItem* item);
		void setObjectVisible(QTreeWidgetItem* item, bool v);

	private:
		GUI::MainWindow* _mainWindow{ nullptr };
		RenderDataManager* _dataManager{ nullptr };
		RenderWindowManager* _windowManager{ nullptr };
		QMultiHash<int, int> _selectedDataObject{};
	};
}

#endif