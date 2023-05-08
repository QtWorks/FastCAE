/**
 * @file NastranH5ReaderAlgorithm.h
 * @brief NastranH5ReaderAlgorithm
 * @author 闫智慧(chanyuantiandao@126.com)
 * @version 1.0.0
 * @date 2022-07-18 08:54:53
 */
#ifndef NastranH5ReaderAlgorithm_H
#define NastranH5ReaderAlgorithm_H

#include "PostAlgorithmAPI.h"
#include <vtkUnstructuredGridAlgorithm.h>
#include <QString>
#include <string>

 /**
  * @brief NastranH5ReaderAlgorithm类
  * @since 1.0.0
  */
class POSTALGORITHMAPI NastranH5ReaderAlgorithm : public vtkUnstructuredGridAlgorithm
{
public:
	static NastranH5ReaderAlgorithm* New();
	vtkTypeMacro(NastranH5ReaderAlgorithm, vtkUnstructuredGridAlgorithm)
		void SetFileName(std::string name);
	/**
		* @brief 打印信息
		*/
	void PrintSelf(ostream& os, vtkIndent indent) override;
	/**
	 * @brief 设置输出端口信息
	 */
	int FillOutputPortInformation(int port, vtkInformation* info) override;

protected:
	NastranH5ReaderAlgorithm();
	~NastranH5ReaderAlgorithm();
	/**
	 * @brief 进程实现---数据获取函数调用入口
	 */
	int ProcessRequest(vtkInformation* request, vtkInformationVector** inputVector, vtkInformationVector* outputVector);
	/**
	 * @brief 数据获取---读取实现函数
	 */
	int RequestData(vtkInformation*, vtkInformationVector**, vtkInformationVector*);
private:
	NastranH5ReaderAlgorithm(const NastranH5ReaderAlgorithm&);
	void operator=(const NastranH5ReaderAlgorithm&);

private:
	std::string m_FileName = "";
};

#endif // NastranH5ReaderAlgorithm_H
