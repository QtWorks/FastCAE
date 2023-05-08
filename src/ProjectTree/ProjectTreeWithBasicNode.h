/**
 * @file ProjectTreeWithBasicNode.h
 * @brief 新建算例时默认树形菜单
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-07-07 10:36
 * @copyright Copyright (c) Since 2020 青岛数智船海科技有限公司  All rights reserved.
 *
 * ============================================================================
 * Program:   FastCAE
 *
 * Copyright (c) Since 2020 青岛数智船海科技有限公司  All rights reserved.
 * See License or http://www.fastcae.com/ for details.
 *
 * BSD 3-Clause License
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.
 * ==================================================================================
 */
#ifndef _PROJECTTREEWITHBASICNODE_H_
#define _PROJECTTREEWITHBASICNODE_H_

#include "projectTreeBase.h"
#include "ProjectTreeAPI.h"

class QTreeWidgetItem;
class QSignalMapper;

namespace GUI
{
	class MainWindow;
}
namespace ModelData
{
	class ModelDataBaseExtend;
}
namespace MeshData
{
	class MeshSet;
}
namespace Post
{
	class Post2DWindowInterface;
	class Post3DWindowInterface;
	class PostWindowBase;
}
namespace Geometry
{
	class GeoComponent;
}

namespace ProjectTree
{

	class PROJECTTREEAPI ProjectTreeWithBasicNode : public ProjectTreeBase
	{
		Q_OBJECT
	public:
		ProjectTreeWithBasicNode(GUI::MainWindow *mainwindow);
		~ProjectTreeWithBasicNode();
		//查看云图
		void viewCounterPost(QString variable);
		//查看向量
		void viewVectorPost(QString variable);
		virtual void reTranslate() override;
		virtual void updateTree() override;
		//更新子树节点
		virtual void updateGeometrySubTree();
		virtual void updateComponentSubTree();
		//		virtual void updateMeshSetSubTree();
		//		virtual void updateGeoComponentTree();
		virtual void updatePropTree();
		virtual void updateBCSubTree();
		virtual void updateReportTree();
		virtual void updateMonitorTree();
		virtual void updatePostTree();
		//获取关联的组件ID(包括网格组件和几何组件)
		const QList<int> &getComponentIDList();
		//通过组件ID删除算例中的项，并更新树
		void removeCaseComponentByID(int);
		//通过组件ID重命名算例中的项，并更新树
		void renameCaseComponentByID(int);

	signals:
		void highLightSet(MeshData::MeshSet *set);
		void openRealTimeWin(Post::RealTimeWindowBase *w, int id);
		void highLightGeoComponent(Geometry::GeoComponent *);
		void clearAllHighLightSig();
		void addComponentRootItemSig();

	protected:
		virtual void initBasicNode(QTreeWidgetItem *root) override;
		virtual void contextMenu(QMenu *menu) override;
		virtual void singleClicked() override;
		virtual void doubleClicked() override;
		virtual void setData(ModelData::ModelDataBase *data);
		virtual void d2PlotContextMenu(QMenu *menu);
		virtual void counterContextMenu(QMenu *menu);
		virtual void vectorContextMenu(QMenu *menu);
		virtual DataProperty::DataBase *getCurrentItemData();

		// bool readInForm();

	protected slots:
		virtual void importGeometry();
		virtual void importComponents();
		virtual void removeItem();
		virtual void addEleProperty();
		virtual void addBC();
		virtual void createReport();
		virtual void assignProperty();
		virtual void viewRealTimeWindow();
		virtual void viewPlot2D(QString variable);
		virtual void viewCounter(QString variable);
		virtual void viewVector(QString variable);
		virtual void closePostWindow(Post::PostWindowBase *w);
		void addComponentRootItemSlot();

	protected:
		QTreeWidgetItem *_geometryRootItem{};
		QTreeWidgetItem *_propertyRootItem{};
		QTreeWidgetItem *_ComponentRootItem{};
		QTreeWidgetItem *_simulationSettingItem{};
		QTreeWidgetItem *_boundaryConditionItem{};
		QTreeWidgetItem *_solverSettingItem{};
		QTreeWidgetItem *_monitorRootItem{};
		QTreeWidgetItem *_postRootItem{};
		QTreeWidgetItem *_post2DItem{};
		QTreeWidgetItem *_postCounterItem{};
		QTreeWidgetItem *_postVectorItem{};
		QTreeWidgetItem *_postStreamLineItem{};
		QTreeWidgetItem *_post3DItem{};
		QTreeWidgetItem *_reportItem{};

		QSignalMapper *_postMapper{};
		//
		// 		Post::Post2DWindowInterface* _post2DWindow{};
		// 		Post::Post3DWindowInterface* _post3DWindow{};

		QMenu *_nodeMenu{};
		QMenu *_cellMeun{};

		ModelData::ModelDataBaseExtend *_modelDataExtend{};

		QList<QTreeWidgetItem *> _ComponentItems;
	};

}

#endif
