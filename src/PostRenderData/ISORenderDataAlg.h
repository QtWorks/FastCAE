#ifndef _ISO_RENDERDATAALG_H_
#define _ISO_RENDERDATAALG_H_

#include "RenderDataAlgorithm.h"
#include <QString>

namespace Post {
	class POSTRENDERDATAAPI ISORenderDataAlg : public RenderDataAlgorithm
	{
		//变量名称
		AddProperty(QString, Variable)
		// 等值
		//AddProperty(double, Value, -1e66)

		//AddProperty(int,ValueCount,1)
	public:
		ISORenderDataAlg(RenderDataObject* parent);
		~ISORenderDataAlg() = default;

		void  updateParam() override;

		void appendToValueList(double val);

		int getValueCount();

		double valueAt(int index);

	protected:
		QList<double> _valueList{};

	};

}

#endif