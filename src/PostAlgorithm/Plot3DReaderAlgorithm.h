#ifndef _PLOT3DREADER_H_
#define _PLOT3DREADER_H_

#include <QObject>
#include "PostRenderData/Macros.hxx"
#include "PostAlgorithmAPI.h"
#include <vtkSmartPointer.h>
#include <vtkMultiBlockDataSetAlgorithm.h>
#include <vtkMultiBlockPLOT3DReader.h>
#include <QHash>
#include <vtkDataSetAlgorithm.h>
#include <vtkUnstructuredGridAlgorithm.h>

ForwardDeclar(vtkMultiBlockDataSet)
ForwardDeclar(vtkAlgorithmOutput)
ForwardDeclar(vtkInformation)
ForwardDeclar(vtkDataSet)


/**
 * @brief 补充属性信息结构体
 * @since Version: 1.0.0
**/
typedef struct arrayInfo{
	int components;
	int tuples;
}ArrayInfo;


class POSTALGORITHMAPI Plot3DReaderAlgorithm : public vtkUnstructuredGridAlgorithm
{
public:

	/**
	 * @brief 创建Plot3DReader对象
	 * @since Version: 1.0.0
	**/
	static Plot3DReaderAlgorithm* New();
	/**
	 * @brief 类型判断宏
	 * @since Version: 1.0.0
	**/
	vtkTypeMacro(Plot3DReaderAlgorithm, vtkUnstructuredGridAlgorithm);
	/**
	 * @brief 信息打印函数
	 * @since Version: 1.0.0
	**/
	void PrintSelf(ostream& os, vtkIndent indent);

	/**
	 * @brief 设置/获取 文件读取名称
	 * @note  Set/Get the name of the file from which to read points.
	 * @since Version: 1.0.0
	**/
	vtkSetStringMacro(FileName);
	vtkGetStringMacro(FileName);

    int getNumberOfBlocks();

    void setVisible(int blockIndex, bool vis);

    QStringList getBlockNames();

    QStringList getBlockBCTypes();

	/**
	 * @brief 设置输出信息
	 * @since Version: 1.0.0
	**/
	int FillOutputPortInformation(int nPort, vtkInformation* info);
protected:

	Plot3DReaderAlgorithm();
	~Plot3DReaderAlgorithm();
	/**
	 * @brief 读取文件名称
	 * @since Version: 1.0.0
	**/
	char* FileName;

	/**
	 * @brief 请求数据函数
	 * @note  需重写	
	 * @since Version: 1.0.0
	**/
	int RequestData(vtkInformation*,vtkInformationVector**,vtkInformationVector*);

	/**
	 * @brief 处理请求函数
	 * @note  需重写
	 * @since Version: 1.0.0
	**/
	int ProcessRequest(vtkInformation* request, vtkInformationVector** inputVector,
		vtkInformationVector* outputVector);

private:
	/**
	 * @note  防止拷贝，使类创建统一走New()函数
	 * @since Version: 1.0.0
	**/
	Plot3DReaderAlgorithm(const Plot3DReaderAlgorithm&);
	void operator=(const Plot3DReaderAlgorithm&);

	/**
	 * @brief 递归遍历数据块
	 * @since Version: 1.0.0
	**/
	void getBlocks(vtkDataObject* blockData);
	
private:

	/**
	 * @brief 拆分成的数据链表
	 * @note  将multiblock拆分成dataset数据,存入链表
	 * @since Version: 1.0.0
	**/
	QList<vtkDataSet*> _blockList;

	/**
	 * @brief 属性全集哈希
	 * @note  QString-属性名称, int-属性维度
	 * @since Version: 1.0.0
	**/
	QHash<QString, ArrayInfo> _attributesPointList;
	QHash<QString, ArrayInfo> _attributesCellList;

    QList<bool> _visibleStates{};

    QStringList _blockNames{};
};

#endif
