#ifndef _DATASETINTEGRATIONALGORITHM_H_
#define _DATASETINTEGRATIONALGORITHM_H_

#include "PostAlgorithmAPI.h"
#include <vtkUnstructuredGridAlgorithm.h>
#include <QString>
#include <QHash>

class vtkDataSet;

class POSTALGORITHMAPI DataSetIntegrationAlgorithm : public vtkUnstructuredGridAlgorithm
{
public:
	static DataSetIntegrationAlgorithm *New();
	vtkTypeMacro(DataSetIntegrationAlgorithm, vtkUnstructuredGridAlgorithm);
	void PrintSelf(ostream &os, vtkIndent indent);

protected:
	DataSetIntegrationAlgorithm();

	~DataSetIntegrationAlgorithm();

	/**
	 * @brief 输入端口信息说明
	 */
	int FillInputPortInformation(int port, vtkInformation *info);
	/**
	 * @brief 输出端口信息说明
	 */
	int FillOutputPortInformation(int port, vtkInformation *info);

	/**
	 * @brief 处理外部请求
	 */
	int ProcessRequest(vtkInformation *request, vtkInformationVector **inputVector, vtkInformationVector *outputVector);
	/**
	 * @brief 算法实现函数
	 */
	int RequestData(vtkInformation *request, vtkInformationVector **inputVector, vtkInformationVector *outputVector);

private:
	DataSetIntegrationAlgorithm(const DataSetIntegrationAlgorithm &);
	void operator=(const DataSetIntegrationAlgorithm &);

	/**
	 * @brief 获取块数据
	 * @param blockData 数据
	 */
	void getBlocks(vtkDataObject *blockData);
	/**
	 * @brief 获取dataset中所有point属性
	 * @param dataset
	 */
	void getPointArray(vtkDataSet *dataset);
	/**
	 * @brief 获取dataset中所有cell属性
	 * @param dataset
	 */
	void getCellArray(vtkDataSet *dataset);
	/**
	 * @brief 填充point的属性
	 * @param dataset
	 */
	void fillPointArray(vtkDataSet *dataset);
	/**
	 * @brief 填充cell的属性
	 * @param dataset
	 */
	void fillCellArray(vtkDataSet *dataset);

private:
	/**
	 * @brief 块数据列表
	 * @since Version: 1.0.0
	 */
	QList<vtkDataSet *> _blockList{};
	/**
	 * @brief 所有point属性数据
	 * @note 缺少tuple
	 * @since Version: 1.0.0
	 */
	QHash<QString, int *> _pointDataArray{};
	/**
	 * @brief 所有cell属性数据
	 * @note 缺少tuple
	 * @since Version: 1.0.0
	 */
	QHash<QString, int *> _cellDataArray{};
};

#endif // _DATASETINTEGRATIONALGORITHM_H_
