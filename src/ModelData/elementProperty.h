#ifndef __ELEMENTPROPERTY_H__
#define __ELEMENTPROPERTY_H__

#include "modelDataAPI.h"
#include "DataProperty/DataBase.h"

namespace ModelData
{
	class MODELDATAAPI ElementProperty : public DataProperty::DataBase
	{
	public:
		ElementProperty();
		~ElementProperty() = default;

		void setEleType(QString s);
		QString getEleType();

		void setMaterialID(int id);
		int getMaterialID();

		static int getMaxID();

	private:
		QString _eletype{};
		int _materialID{ -1 };

		static int MaxID;

	};

	 
}



#endif