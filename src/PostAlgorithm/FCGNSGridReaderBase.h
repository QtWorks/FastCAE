#ifndef _FCGNSGRIDREADER_H__
#define _FCGNSGRIDREADER_H__

#include <cgnslib.h>
#include <cgnstypes.h>
#include <QHash>
#include <QVector>

class vtkMultiBlockDataSet;
class vtkDataSet;
class vtkDataArray;

/**
 * @brief 用于存储点坐标的结构体
 * @since 2.5.0
 */
struct VPoint {
	double x{ 0 };
	double y{ 0 };
	double z{ 0 };
};

class FCGNSGridReaderBase {
public:
	/**
	 * @brief 构造函数
	 * @param[out] root 包含数据的vtkMultiBlockDataSet对象
	 */
	FCGNSGridReaderBase(vtkMultiBlockDataSet* root);
	virtual ~FCGNSGridReaderBase() = default;

	/**
	 * @brief 设置要读取zone的信息
	 *
	 * @param[in] fileIndex 文件索引
	 * @param[in] baseIndex 单库base的索引
	 * @param[in] zoneIndex 区域zone的索引
	 */
	void		 setInfo(int fileIndex, int baseIndex, int zoneIndex);

	/**
	 * @brief zone读取函数，由子类重写
	 * @since 2.5.0
	 */
	virtual void read() = 0;

protected:
	/**
	 * @brief 读取zone中的坐标信息
	 * @param[in] dim 维数
	 * @param[in] count 顶点数
	 * @param[out] range_from 指定读取范围的最小索引，全部读取时为1
	 * @param[out] range_to 指定读取范围的最大索引，全部读取时为顶点数
	 * @since 2.5.0
	 */
	void readCoordinate(int dim, int count, cgsize_t range_from[3], cgsize_t range_to[3]);
	/**
	 * @brief 读取zone中的计算结果
	 * @param[out] grid 要保存计算结果的vtkDataSet对象
	 * @since 2.5.0
	 */
	void readFlowSolution(vtkDataSet* grid);
	/**
	 * @brief 读取场数据
	 * @param[in] solIndex 计算结果索引
	 * @param[in] loc 计算结果存储位置
	 * @param[out] varNames 场变量名称数组
	 * @param[out] valueType 场变量类型数组
	 * @param[out] values 场变量数据数组
	 * @since 2.5.0
	 */
	void readFieldData(int solIndex, CGNS_ENUMT(GridLocation_t) loc, QList<QString>& varNames,
					   QList<int>& valueType, QList<void*>& values);
	/**
	 * @brief 添加场数据到vtk格式数据中
	 * @param[in] loc 场变量位置
	 * @param[in] varNames 场变量名称数组
	 * @param[in] valueType 场变量类型数组
	 * @param[in] values 场变量数据数组
	 * @since 2.5.0
	 */
	void addValueToGrid(CGNS_ENUMT(GridLocation_t) loc, QList<QString> varNames,
						QList<int> valueType, QList<void*> values);

	/**
	 * @brief 判断场变量是否为矢量分量
	 * @param[in] name 场变量名称
	 * @param[out] vecName 场变量名称（不含分量x,y,z）
	 * @param[out] comp 分量(x,y,z)
	 * @note 该函数判断依据为变量名称的最后一个字母是否为x,y,z(不区分大小写)。
	 * @since 2.5.0
	 */
	bool isVectorComponent(QString name, QString& vecName, QString& comp);
	/**
	 * @brief 生成标量场的vtkDataArray
	 * @param[in] varName 场变量名称
	 * @param[in] num 场变量值数组大小
	 * @param[in] type 场变量数据类型
	 * @param[in] va 场变量值数组
	 * @since 2.5.0
	 */
	vtkDataArray* generateScalarArray(QString varName, int num, int type, void* va);

	/**
	 * @brief 生成矢量场的vtkDataArray
	 * @param[in] varName 场变量名称
	 * @param[in] num 场变量值数组大小
	 * @param[in] xtype 场变量数据x分量类型
	 * @param[in] x 场变量值x分量数组
	 * @param[in] ytype 场变量数据y分量类型
	 * @param[in] y 场变量值y分量数组
	 * @param[in] ztype 场变量数据z分量类型
	 * @param[in] z 场变量值z分量数组
	 * @since 2.5.0
	 */
	vtkDataArray* generateVectorArray(QString varName, int num, int xtype, void* x, int ytype,
									  void* y, int ztype, void* z);

protected:
	/**
	 * @brief 存储要返回的结果数据
	 */
	vtkMultiBlockDataSet* _root{};
	/**
	 * @brief CGNS文件索引
	 */
	int					  _fileIndex{ -1 };
	/**
	 * @brief base索引
	 */
	int					  _baseIndex{ -1 };
	/**
	 * @brief zone索引
	 */
	int					  _zoneIndex{ -1 };
	/**
	 * @brief 是否为结构化数据
	 */
	bool				  _isStructedGrid{ false };
	/**
	 * @brief 数据维度
	 */
	int					  _dim{ 2 };
	vtkDataSet*			  _dataSet{};
	QString				  _zoneName;

	/**
	 * @brief 节点数组
	 * @since 2.5.0
	 */
	QVector<VPoint>		  _vertexList{};
};

#endif
