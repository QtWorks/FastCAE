#ifndef _FCGNSUNSTRUCTEGRIDREADER_H__
#define _FCGNSUNSTRUCTEGRIDREADER_H__

#include "FCGNSGridReaderBase.h"

#include <cgnslib.h>
#include <cgnstypes.h>
#include <QList>
#include <QString>
#include <vtkUnstructuredGrid.h>

/**
 * @brief section属性结构体
 * @since 2.5.0
 */
struct FSection {
	FSection(QString name, int b, int e)
		: _name(name)
		, _begin(b)
		, _end(e)
	{
	}
	/**
	 * @brief 名称
	 * @since 2.5.0
	 */
	QString _name{};
	/**
	 * @brief 第一个单元的索引
	 * @since 2.5.0
	 */
	int		_begin{ 0 };
	/**
	 * @brief 最后一个单元的索引
	 * @since 2.5.0
	 */
	int		_end{ 0 };
};

class FCGNSUnStructeGridReader : public FCGNSGridReaderBase {
public:
	FCGNSUnStructeGridReader(vtkMultiBlockDataSet* root);
	~FCGNSUnStructeGridReader() = default;

	void read() override;

private:
	/**
	 * @brief 添加单元到vtkUnstructuredGrid对象中
	 * @param[out] grid 要添加单元的vtkUnstructuredGrid对象
	 * @param[in] ncell 单元数量
	 * @param[in] type 单元类型
	 * @param[in] eles 单元数组
	 * @param[in] connectOffset 单元偏移数组，仅在type=mixed时可用
	 * @since 2.5.0
	 */
	void	   addCells(vtkUnstructuredGrid* grid, int ncell, CGNS_ENUMT(ElementType_t) type,
						cgsize_t* eles, cgsize_t* connectOffset);

	vtkIdType  addBar2Cell(vtkUnstructuredGrid* grid, vtkIdType id1, vtkIdType id2);
	vtkIdType  addTri3Cell(vtkUnstructuredGrid* grid, vtkIdType id1, vtkIdType id2, vtkIdType id3);
	vtkIdType  addTetra4Cell(vtkUnstructuredGrid* grid, vtkIdType id1, vtkIdType id2, vtkIdType id3,
							 vtkIdType id4);
	vtkIdType  addQuad4Cell(vtkUnstructuredGrid* grid, vtkIdType id1, vtkIdType id2, vtkIdType id3,
							vtkIdType id4);
	vtkIdType  addHexa8Cell(vtkUnstructuredGrid* grid, vtkIdType id1, vtkIdType id2, vtkIdType id3,
							vtkIdType id4, vtkIdType id5, vtkIdType id6, vtkIdType id7,
							vtkIdType id8);
	vtkIdType  addPenta6Cell(vtkUnstructuredGrid* grid, vtkIdType id1, vtkIdType id2, vtkIdType id3,
							 vtkIdType id4, vtkIdType id5, vtkIdType id6);
	vtkIdType  addPyra5Cell(vtkUnstructuredGrid* grid, vtkIdType id1, vtkIdType id2, vtkIdType id3,
							vtkIdType id4, vtkIdType id5);

	void	   spllitSection(vtkUnstructuredGrid* gird);

	QList<int> sectionOrder(int nsec);

private:
	QList<FSection> _sections;
};

#endif
