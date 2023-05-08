#ifndef _READER_CGNS_H
#define _READER_CGNS_H

#include "PostAlgorithmAPI.h"
#include "PostRenderData/Macros.hxx"
#include <vtkUnstructuredGridAlgorithm.h>
#include <QString>
#include <QHash>

ForwardDeclar(vtkInformation)
ForwardDeclar(vtkDataSet)
ForwardDeclar(vtkDataObject)
ForwardDeclar(vtkDataArray)

class POSTALGORITHMAPI CGNSReaderAlgorithm :public vtkUnstructuredGridAlgorithm
{
public:
	static CGNSReaderAlgorithm* New();
	vtkTypeMacro(CGNSReaderAlgorithm, vtkUnstructuredGridAlgorithm);
	void PrintSelf(ostream& os, vtkIndent indent);

	vtkSetStringMacro(FileName);
	vtkGetStringMacro(FileName);

    void setVisible(int blockIndex, bool vis);

    int getNumberOfBlocks();

    QStringList getBlockNames();

    QStringList getBlockBCTypes();

	int FillOutputPortInformation(int port, vtkInformation* info);

	/**
	* @brief 获取块数据
	* @param block 数据
	*/
	void getBlocks(vtkDataObject* block, const char* cuttentName ="");
	/**
	* @brief 获取dataset中所有point属性
	* @param dataset 
	*/
	void getPointArray(vtkDataSet* dataset);
	/**
	* @brief 获取dataset中所有cell属性
	* @param dataset 
	*/
	void getCellArray(vtkDataSet* dataset);
	/**
	* @brief 填充point的属性
	* @param dataset 
	*/
	void fillPointArray(vtkDataSet* dataset);
	/**
	* @brief 填充cell的属性
	* @param dataset 
	*/
	void fillCellArray(vtkDataSet* dataset);

protected:
	CGNSReaderAlgorithm();
	~CGNSReaderAlgorithm();
	
	int ProcessRequest(vtkInformation* request, vtkInformationVector** inputVector, vtkInformationVector* outputVector);
	int RequestData(vtkInformation*, vtkInformationVector**, vtkInformationVector*);

    bool useVTKCGNSReader();

protected:
	char* FileName;

private:
	CGNSReaderAlgorithm(const CGNSReaderAlgorithm&);
	void operator=(const CGNSReaderAlgorithm&);

	/**
	* @brief 块数据列表
	* @since Version: 1.0.0
	*/
	QList<vtkDataSet*> _blockList{};
	/**
	* @brief 所有point属性数据
	* @note 缺少tuple
	* @since Version: 1.0.0
	*/
	QHash<QString, int*> _pointDataArray{};
	/**
	* @brief 所有cell属性数据
	* @note 缺少tuple
	* @since Version: 1.0.0
	*/
	QHash<QString, int*> _cellDataArray{};

    QList<bool> _visibleStates{};

    QStringList _blockNames{}; 

    QStringList _bcTypes;
};

#endif
