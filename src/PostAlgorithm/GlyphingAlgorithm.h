/* 
* 
* @file   GlyphingAlgorithm.h
* @brief  生成矢量算法
* @author XuXinwei
* 
*/
#ifndef _GLYPHINGALGORHITHM_H_
#define _GLYPHINGALGORHITHM_H_

#include "PostRenderData/Macros.hxx"
#include "PostAlgorithmAPI.h"
#include <vtkPolyDataAlgorithm.h>
#include <QString>

ForwardDeclar(vtkPoints)
ForwardDeclar(vtkArrowSource)
ForwardDeclar(vtkGlyph3D)
ForwardDeclar(vtkMaskPoints)

class POSTALGORITHMAPI GlyphingAlgorithm : public vtkPolyDataAlgorithm
{
	/*
	*brief 矢量名称
	*/
	AddProperty(QString, VectorName)
	/*
	*brief 箭头维度
	*/
	AddProperty(int, TipResolution, 6)
	/*
	*brief 箭头半径
	*/
	AddProperty(double, TipRadius,0.06 )
	/*
	*brief 箭头长度
	*/
	AddProperty(double, TipLength, 0.4)
	/*
	*brief 箭柄维度
	*/
	AddProperty(int, ShaftResolution, 6)
	/*
	*brief 箭柄半径
	*/
	AddProperty(double, ShaftRadius, 0.02)
	/*
	*brief 箭头缩放比例
	*/
	AddProperty(double, ScaleFactor, 15)
	/*
	*brief 使用点数据
	*/
	AddProperty(bool, PointDataUsed, true)
	/*
	*brief 最大采样点
	*/
	AddProperty(int, MaxNumber, 100000)
	/*
	*brief 箭头比例模式:0-scalar,1-vector,2-vectorcomponent,3-off
	*/
	AddProperty(int, ScaleMode, 1)

public:
	static GlyphingAlgorithm* New();
	vtkTypeMacro(GlyphingAlgorithm, vtkPolyDataAlgorithm);
	void PrintSelf(ostream& os, vtkIndent indent);
	
protected:
	GlyphingAlgorithm();
	~GlyphingAlgorithm();

	/**
	* @brief 输入端口说明
	*/
	int FillInputPortInformation(int port, vtkInformation* info);
	/**
	* @brief 输出端口说明
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
	GlyphingAlgorithm(const GlyphingAlgorithm&);
	void operator+= (const GlyphingAlgorithm&);

	/*
	*brief 提取点
	*/
	bool extractPoints(vtkDataSet* inputData);
	void extractPointDataArray(vtkDataSet* inputData);
	void extractCellDataArray(vtkDataSet* inputData);

private:
	/*
	*brief 点的数量
	*/
	int _pointsNumber{};

private:
	//vtkPoints* _points;
// 	vtkPolyData* _polyData;
// 	vtkMaskPoints* _maskPoints;
// 	vtkGlyph3D* _glyph;
// 	vtkArrowSource* _arrowSource;

// 	DeclarVTKSmartPtr(vtkPoints, _points);
#ifdef Q_OS_WIN
	DeclarVTKSmartPtr(vtkPolyData, _polyData);
	DeclarVTKSmartPtr(vtkMaskPoints, _maskPoints);
	DeclarVTKSmartPtr(vtkGlyph3D, _glyph);
	DeclarVTKSmartPtr(vtkArrowSource, _arrowSource);
#else
    // 临时解决方案
    vtkPolyData* _polyData = nullptr;
    vtkMaskPoints* _maskPoints = nullptr;
    vtkGlyph3D* _glyph = nullptr;
    vtkArrowSource* _arrowSource = nullptr;
#endif
};

#endif
