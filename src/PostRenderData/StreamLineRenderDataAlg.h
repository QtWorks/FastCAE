#ifndef _STREAMLINE_RENDERDATAALG_H_
#define _STREAMLINE_RENDERDATAALG_H_

#include "RenderDataAlgorithm.h"
#include "Macros.hxx"
#include <vtkLineSource.h>
#include <vtkSmartPointer.h>
#include <vtkGlyph3D.h> 

class GlyphingAlgorithm;

namespace Post {
	class POSTRENDERDATAAPI StreamLineRenderDataAlg : public RenderDataAlgorithm
	{
		//使用节点值进行计算
		AddProperty(bool, UsePointData, true)
			//变量名称
			AddProperty(QString, Vector)
			//初始步长
			AddProperty(double, InitStep, 0.2)
			//最小步长
			AddProperty(double, MinStep, 0.01)
			//最大步长
			AddProperty(double, MaxStep, 0.5)
			//迭代步数
			AddProperty(double, StepNumber, 1000)
			//积分方向 0-向两侧积分 1-向前 2-向后
			AddProperty(int, Direction, 0)
			//最大流线长度
			AddProperty(double, MaxLength, 5000)
			//种子点数量
			AddProperty(int, SeedCount, 1000)

			//箭头点数量
			AddProperty(int, ArrowCount, 2000)
			//箭头比例
			AddProperty(double, ArrowFactor, 0.01)
			//箭头分布比例-turn on every nth point
			AddProperty(int, Ratio, 10)
			//箭头尖端分辨率
			AddProperty(double, TipResolution, 6)
			//箭头尖端半径
			AddProperty(double, TipRadius, 0.06)
			//箭头尖端长度
			AddProperty(double, TipLength, 0.4)
			//箭头柄分辨率
			AddProperty(double, ShaftResolution, 6)
			//箭头柄半径
			AddProperty(double, ShaftRadius, 0.02)

			AddPropertySetOverride(bool, ShowArrow, true)

	public:
		StreamLineRenderDataAlg(RenderDataObject* parent);
		~StreamLineRenderDataAlg();

		void setLineSource(double* start, double* end);

		void updateParam() override;

		void setArrowColor(double* rgb);

		void updateAlg() override;
		void update() override;

	private:
		void addActorGlyph(vtkDataSet* dataset);

	private:
#ifdef Q_OS_WIN
        DeclarVTKSmartPtr(vtkLineSource, _line)
        DeclarVTKSmartPtr(vtkMapper, _vecMapper)
        DeclarVTKSmartPtr(GlyphingAlgorithm, _glyph3D)
        //DeclarVTKSmartPtr(vtkGlyph3D, _glyph3D)
#else
        vtkLineSource* _line = nullptr;
        vtkMapper* _vecMapper = nullptr;
        GlyphingAlgorithm* _glyph3D = nullptr;
#endif

	};
}


#endif
