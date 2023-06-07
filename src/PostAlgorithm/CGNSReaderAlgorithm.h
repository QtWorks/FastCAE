#ifndef _READER_CGNS_H
#define _READER_CGNS_H

#include "PostAlgorithmAPI.h"
#include "PostRenderData/Macros.hxx"

#include <QHash>
#include <QString>
#include <vtkUnstructuredGridAlgorithm.h>

ForwardDeclar(vtkInformation);
ForwardDeclar(vtkDataSet);
ForwardDeclar(vtkDataObject);
ForwardDeclar(vtkDataArray);

class POSTALGORITHMAPI CGNSReaderAlgorithm : public vtkUnstructuredGridAlgorithm {
public:
	static CGNSReaderAlgorithm* New();
	vtkTypeMacro(CGNSReaderAlgorithm, vtkUnstructuredGridAlgorithm);
	/**
	 * @brief 打印对象当前对象(包括超类)的信息
	 *
	 * @param[in] os 输出流
	 * @param[in] indent 缩进
	 */
	void PrintSelf(ostream& os, vtkIndent indent) override;
	/** @name Set/Get宏
	 * 相当于setter/getter，同vtkSetMacro(FileName, char*)/vtkGetMacro(FileName, char*)
	 * @{
	 */
	vtkSetStringMacro(FileName);
	vtkGetStringMacro(FileName);
	/** @} */

	void		setVisible(int blockIndex, bool vis);

	int			getNumberOfBlocks();

	QStringList getBlockNames();

	QStringList getBlockBCTypes();

	/**
	 * @brief 填充该算法的输入端口信息对象
	 * @param[in] port 端口序号，从0开始
	 */
	int			FillInputPortInformation(int port, vtkInformation* info) override;
	/**
	 * @brief 填充该算法的输入端口信息对象
	 * @param[in] port 端口序号，从0开始
	 */
	int			FillOutputPortInformation(int port, vtkInformation* info) override;

	/**
	 * @brief 获取块数据
	 * @param block 数据
	 */
	void		getBlocks(vtkDataObject* block, const char* cuttentName = "");
	/**
	 * @brief 获取dataset中所有point属性
	 * @param dataset
	 */
	void		getPointArray(vtkDataSet* dataset);
	/**
	 * @brief 获取dataset中所有cell属性
	 * @param dataset
	 */
	void		getCellArray(vtkDataSet* dataset);
	/**
	 * @brief 填充point的属性
	 * @param dataset
	 */
	void		fillPointArray(vtkDataSet* dataset);
	/**
	 * @brief 填充cell的属性
	 * @param dataset
	 */
	void		fillCellArray(vtkDataSet* dataset);

protected:
	CGNSReaderAlgorithm();
	~CGNSReaderAlgorithm();

	/**
	 * @brief 当VTK管道更新时，过滤器可能会收到请求，要求它处理一些信息和/或数据。
	 * 这些请求首先被发送到过滤器的执行对象，然后由该对象发送请求
	 * 通过调用虚拟方法vtkAlgorithm::ProcessRequest()来实现算法。
	 * 该方法给出了请求信息对象和一组输入输出管道信息要操作的对象。它负责尝试完成请求并报告成功或失败。
	 * 每个算法对象必须按原样提供ProcessRequest()的实现算法执行的入口点.
	 *
	 * \param request
	 * \param inputVector
	 * \param outputVector
	 * \return
	 */
	int	 ProcessRequest(vtkInformation* request, vtkInformationVector** inputVector,
						vtkInformationVector* outputVector) override;

	int	 RequestData(vtkInformation*, vtkInformationVector**, vtkInformationVector*) override;

	bool useVTKCGNSReader();

protected:
	char* FileName;

private:
	CGNSReaderAlgorithm(const CGNSReaderAlgorithm&);
	void				 operator=(const CGNSReaderAlgorithm&);

	/**
	 * @brief 块数据列表
	 * @since Version: 1.0.0
	 */
	QList<vtkDataSet*>	 _blockList{};
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

	QList<bool>			 _visibleStates{};

	QStringList			 _blockNames{};

	QStringList			 _bcTypes;
};

#endif
