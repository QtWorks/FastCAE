/* 
* 
* @file   SimplifyAlgorithm.h
* @brief  网格简化算法
* @author XuXinwei
* 
*/
#ifndef _SIMPLIFYALGORITHM_H_
#define _SIMPLIFYALGORITHM_H_

#include "PostRenderData/Macros.hxx"
#include "PostAlgorithmAPI.h"
#include <vtkPolyDataAlgorithm.h>

ForwardDeclar(vtkDataSetSurfaceFilter)
ForwardDeclar(vtkTriangleFilter)
ForwardDeclar(vtkDecimatePro)
ForwardDeclar(vtkCellDataToPointData)

class POSTALGORITHMAPI SimplifyAlgorithm:public vtkPolyDataAlgorithm
{
public:
	static SimplifyAlgorithm* New();
	vtkTypeMacro(SimplifyAlgorithm, vtkPolyDataAlgorithm);
	void PrintSelf(ostream& os, vtkIndent indent);

	AddPropertyWriteOnly(double, SurfaceReduce)

protected:
	SimplifyAlgorithm();
	~SimplifyAlgorithm();

	/**
	* @brief 输入端口信息说明
	*/
	int FillInputPortInformation(int port, vtkInformation* info);
	/**
	* @brief 输出端口信息说明
	*/
	int FillOutputPortInformation(int port, vtkInformation* info);

	/**
	* @brief 处理外部请求
	*/
	int ProcessRequest(vtkInformation* request, vtkInformationVector** inputVector, vtkInformationVector* outputVector);
	/**
	* @brief 算法实现函数
	*/
	int RequestData(vtkInformation* request, vtkInformationVector** inputVector, vtkInformationVector* outputVector);

private:
	SimplifyAlgorithm(const SimplifyAlgorithm&);
	void operator=(const SimplifyAlgorithm&);

	/**
	* @brief 重命名单元数据中物理场
	* @param cellData 单元数据
	*/
	void renameCellArray(vtkCellData* cellData);

private:
#ifdef Q_OS_WIN
	DeclarVTKSmartPtr(vtkDataSetSurfaceFilter, _surface)
	DeclarVTKSmartPtr(vtkTriangleFilter, _triangle)
	DeclarVTKSmartPtr(vtkDecimatePro, _decimate)
	DeclarVTKSmartPtr(vtkCellDataToPointData, _cellToPoint)
 #else
    // 临时解决方案，待处理
    vtkDataSetSurfaceFilter* _surface = nullptr;
    vtkTriangleFilter* _triangle = nullptr;
    vtkDecimatePro* _decimate = nullptr;
    vtkCellDataToPointData* _cellToPoint = nullptr;
#endif
};


#endif // !1


