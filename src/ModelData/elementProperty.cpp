#include "elementProperty.h"

namespace ModelData
{
	int ElementProperty::MaxID = 0;

	ElementProperty::ElementProperty()
	{
		this->setID(++MaxID);
	}
	void ElementProperty::setEleType(QString s)
	{
		_eletype = s;
		this->appendProperty("Type", s);
	}
	QString ElementProperty::getEleType()
	{
		return _eletype;
	}

	void ElementProperty::setMaterialID(int id)
	{
		_materialID = id;
		this->appendProperty("Material", id);
	}

	int ElementProperty::getMaterialID()
	{
		return _materialID;
	}

	int ElementProperty::getMaxID()
	{
		return MaxID;
	}

}


