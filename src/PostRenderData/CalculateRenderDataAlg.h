#ifndef _CALCULATE_RENDERDATAALG_H__
#define _CALCULATE_RENDERDATAALG_H__

#include "RenderDataAlgorithm.h"
#include "Macros.hxx"
#include <QStringList>

namespace Post
{
	class POSTRENDERDATAAPI CalculateRenderDataAlg : public RenderDataAlgorithm
	{
		//设置计算公式
		AddProperty(QString, Function)
			//是否使用节点值
			AddProperty(bool, UsePointData, true)
			//输入标量名称
			AddListProperty(QString, InputScalars)
			//输入矢量名称
			AddListProperty(QString, InputVectors)
			//结果变量名称
			AddProperty(QString, ResultArrayName)

				public : CalculateRenderDataAlg(RenderDataObject *parent);
		~CalculateRenderDataAlg() = default;

		void updateParam() override;

	protected:
	private:
	};
}
#endif
