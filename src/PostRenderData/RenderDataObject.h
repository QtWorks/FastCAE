#ifndef _RENDERDATAOBJECT_H_
#define _RENDERDATAOBJECT_H_

#include "PostRenderDataAPI.h"
#include "Macros.hxx"
#include <QList>
#include <vtkSmartPointer.h>
#include <vtkAlgorithm.h>
#include <vtkActor.h>
#include <vtkDataSetMapper.h>
#include <QStringList>
#include <vtkScalarBarWidget.h>
#include <vtkLookupTable.h>
#include <vtkAssembly.h>
#include <QColor>


ForwardDeclar(vtkDataObject)
ForwardDeclar(vtkDataSet)
ForwardDeclar(vtkDataArray)

static QList<QColor> colorList = { QColor(255,0,0),QColor(0,255,0),QColor(0,0,255),QColor(0,255,255),QColor(127,0,255),
									QColor(255,255,0),QColor(255,0,255),QColor(255,127,0),QColor(0,127,127) };

namespace Post {
	ForwardDeclar(RenderProperty)

	enum ObjType
	{
		TNone,
		Imp, //直接导入的数据对象
		Alg, //过滤器算法生成
	};

	typedef struct attributeInfo {
		QString kind;
		QString name;
		QString type;
		QString range;
	}AttributeInfo;


	class POSTRENDERDATAAPI RenderDataObject
	{
		//自动分配ID，自增
		AutoDistributeID
		//子对象指针链表
		AddPtrListProperty(RenderDataObject, SubObjects, protected:)
		//数据对象类型，导入或者算法产生
		AddProperty(ObjType, DataType, ObjType::TNone)
		//父对象
		AddProperty(RenderDataObject*, ParentObj, nullptr)
		//显示窗口ID
		AddProperty(int, RenderWinID, 0)
		//显示状态是否显示
		AddPropertySetOverride(bool, ShowStatus, true)
		//显示相关的属性设置
		AddPtrListProperty(RenderProperty, PropertyList, protected:)

		AddPtrListProperty(vtkDataSetMapper, Mappers, protected:)

		AddPtrListProperty(vtkActor, ActorList, protected:)

		AddPtrListProperty(vtkActor, AssistActors, protected:)

		AddPropertySetOverride(int,DisplayMode,2)

	public:
		RenderDataObject(RenderDataObject* parent = nullptr);
		virtual ~RenderDataObject();
		/**
		 * @brief 获取数据对象 dataset
		 * @return  vtkDataSet*
		 */
		virtual vtkDataSet* getOutputData();
		virtual vtkDataSet* getOutputData(const int port);
		/**
		 * @brief 获取Object名称
		 * @return QString
		 */
		QString getName();
		/**
		 * @brief 获取actor
		 * @return vtkActor*
		 */
		vtkAssembly*  getAssembly();
		/**
		 * @brief 获取方法输出接口
		 * @return vtkAlgorithmOutput*
		 */
		vtkAlgorithmOutput* getOutputPort();
		vtkAlgorithmOutput* getOutputPort(const int port);
		/**
		 * @brief 设置方法输入接口
		 * @param  alg   输入接口指针
		 */
		virtual void setInputConnection(vtkAlgorithmOutput* alg);
		/**
		 * @brief 刷新管线，mapper 更新
		 */
		virtual void update();
		/**
		 * @brief 刷新算法, alg更新
		 */
		virtual void updateAlg();
		/**
	   * @brief 获取点数据的变量名称
	   * @return QStringList
	   */
		QStringList getPointDataArray();
		QStringList getBlockPointDataArray(int index);
		/**
		 * @brief 获取单元数据的变量名称集合
		 * @return QStringList
		 */
		QStringList getCellDataArray();
		QStringList getBlockCellDataArray(int index);

		/**
		 * @brief 获取变量类型
		 * @param  vaLocation 变量所在位置 1-pointData  2-cellData
		 * @param  vaName  变量名称
		 * @return QString 变量类型:scalar\vector\tensor\Unknown
		 * @note 在vtk中通过分量数量判断数据类型并不是十分准确
		 */
		QString variableType(int vaLocation, QString vaName);
		/**
		 * @brief 获取变量成员数量
		 * @param  vaLocation 变量所在位置 1-pointData  2-cellData
		 * @param  vaName  变量名称
		 * @return int 组成成员数量 0-错误值
		 */
		int variableComponentCount(int vaLocation, QString vaName);
		/*
		 * @brief 获取颜色条
		 * @return vtkScalarBarWidget*
		 */
// 		vtkScalarBarWidget* getScalarBarWidget();
// 		vtkLookupTable* getLookupTable();
		/*
		 * @brief 获取最根节点
		 * @return vtkScalarBarWidget*
		 */
		RenderDataObject* getRootViewObject();
		/*
		* @brief 移除对象
		*/
		void removeObject(RenderDataObject* obj);
		/**
		 * @brief 根据ID获取对象
		 */
		RenderDataObject* getObjectByID(int id);
		/**
		 * @brief 获取全部子节点，包含各级子节点
		 */
		void getSubObjects(QList<RenderDataObject*> &objs);
		/**
		 * @brief 获取边界(包围盒)范围
		 * @return double* (xmin,xmax, ymin,ymax, zmin,zmax).
		 */
		double* getBoundary();
		/**
	  * @brief  获取变量数组
	  * @param  vaLocation 变量所在位置 1-pointData  2-cellData
	  * @param  vaName  变量名称
	  * @return vtkDataArray*
	  */
		vtkDataArray* getArray(int location, QString name);

		/**
		 * @brief 获取节点个数
		 */
		int getPointDataNum();
		int getNumberOfBlockPoints(int index);
		/**
		 * @brief 获取单元个数
		 */
		int getCellDataNum();
		int getNumberOfBlockCells(int index);

		/**
	   * @brief 获取点数据的变量名称
	   * @return QStringList
	   */
		QVector<AttributeInfo> getPointDataArrayInfo();
		virtual void getRange(double* range, int type, QString vaName, int componentIndex);

		QStringList getBlockNames();

		bool getBlockShowStatus(const int index);

		void setBlockShowStatus(const int index, bool show);

		QString getBlockName(const int index);

		int getNumberOfBlocks();

		int getNumberOfAlgorithmByType(int type);

		void updateScalarBar(vtkRenderWindowInteractor* interactor);

	protected:
//		void initScalarBar();
		/**
		* @brief 获取属性类型名称 标量 矢量 张量
		* @param n 维度
		*/
		QString getTypeName(int dim);

		vtkDataSetMapper* createMapper(bool assist);

	protected:
		QString _name{};
		QStringList _blockNames{};
		int _blockNumber{ -1 };

		DeclarVTKSmartPtr(vtkAlgorithm, _vtkAlg)
		DeclarVTKSmartPtr(vtkAssembly, _actors)
		DeclarVTKSmartPtr(vtkAssembly, _assistActors)
		DeclarVTKSmartPtr(vtkAssembly, _assembly)
// 		DeclarVTKSmartPtr(vtkScalarBarWidget, _ScalarBar)
// 		DeclarVTKSmartPtr(vtkLookupTable, _LookupTable)

	};
}
#endif