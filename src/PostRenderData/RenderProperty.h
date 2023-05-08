#ifndef _RENDERPROPERTY_H__
#define _RENDERPROPERTY_H__

#include "PostRenderDataAPI.h"
#include "Macros.hxx"

#include <QString>
#include <vtkSmartPointer.h>
#include <vtkScalarBarWidget.h>
#include <vtkLookupTable.h>
ForwardDeclar(vtkMapper)
ForwardDeclar(vtkActor)
ForwardDeclar(vtkRenderWindowInteractor)

namespace Post {
	ForwardDeclar(RenderDataObject)

	class POSTRENDERDATAAPI RenderProperty
	{
		//显示模式 0-点  1-线框 2-面 3-带线的面
		AddPropertySetOverride(int, DisplayMode, 2)
		//用于着色的变量类型 0-solidColor，1-PointData 2-CellData
		AddProperty(int, VariableType, 0)
		//变量名称
		AddProperty(QString, VariableName)
		//组分索引 -1-模  0- x  1-y  2-z
		AddProperty(int, ComponentIndex, -1)
		//是否显示颜色条
		AddPropertySetOverride(bool, ShowColorMap, false)
		//透明度
		AddPropertySetOverride(double, Transparency, 1.0)

		AddPropertySetOverride(bool, ShowStatus, true)

	public:
		RenderProperty(RenderDataObject* vobj, vtkMapper* mapper, vtkActor* actor);
        virtual ~RenderProperty() = default;
		/**
		 * @brief 设置当前变量
		 * @param  type    用于着色的变量类型 0-solidColor，1-PointData 2-CellData
		 * @param  vaName  变量名称
		 * @param  componentIndex  组分索引 -1-模  0- x  1-y  2-z
		 */
		virtual void setCurrentVariable(int type, QString vaName = QString(), int componentIndex = -1);
		/**
		 * @brief 更新颜色条显示状态
		 */
		virtual void updateScalarBar(vtkRenderWindowInteractor* interactor);

		virtual void setColorMapProperty(int level, double min, double max);

		virtual void setColorMapColor(int index, double r, double g, double b);

//		virtual void getRange(double* range, int type, QString vaName, int componentIndex);
		/**
		 * @brief 更改颜色阶数
		 * @note  num-要更改到的颜色阶数
		**/
		void updateColorScaleNums(int num);

		void getPropertyColor(double* color);

		void setPropertyColor(double r, double g, double b);

		//bool isVariableColor();

	private:
		void initScalarBar();

	private:
		RenderDataObject* _renderDataObj{ nullptr };
		vtkMapper* _mapper{ nullptr };
		vtkActor* _actor{ nullptr };
		DeclarVTKSmartPtr(vtkScalarBarWidget, _scalarBar)
		DeclarVTKSmartPtr(vtkLookupTable,_lookupTable)
		double _color[3]{ 0 };
		//bool _variableColor{ false };
	};
}
#endif
