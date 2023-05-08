#ifndef _GLYPHING_RENDERDATAALG_H_
#define _GLYPHING_RENDERDATAALG_H_

#include "RenderDataAlgorithm.h"
#include "Macros.hxx"
#include <vtkSmartPointer.h>

namespace Post {
	class POSTRENDERDATAAPI GlyphingRenderDataAlg : public RenderDataAlgorithm
	{
		//箭头锥维度
		AddProperty(int, TipResolution, 6)
			//箭头锥半径
			AddProperty(double, TipRadius, 0.06)
			//箭头锥长度
			AddProperty(double, TipLength, 0.4)
			//箭头轴维度
			AddProperty(int, ShaftResolution, 6)
			//箭头轴半径
			AddProperty(double, ShaftRadius, 0.02)
			//是否使用节点值
			AddProperty(bool, UsePointData, true)
			//矢量名称
			AddProperty(QString, Vector)
			//最大数量
			AddProperty(int, MaxNumber, 1000)
			//箭头缩放比例
			AddProperty(double, ScaleFactor, 15)
			//箭头比例模式:0-scalar,1-vector,2-vectorcomponent,3-off
			AddProperty(int, ScaleMode, 1)

	public:
		GlyphingRenderDataAlg(RenderDataObject* parent);
		~GlyphingRenderDataAlg();

		void updateParam() override;

// 	private:
// 		void combineSelectedObjects();
// 
// 	private:
// 		DeclarVTKSmartPtr(vtkAppendFilter,_append)

	};
}

#endif // !VIEWDATALG_GLYPHING__H
