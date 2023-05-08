/**
 * @file ComponentBase.cpp
 * @brief 组件基类源文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-28 14:57
 * @copyright Copyright (c) Since 2020 青岛数智船海科技有限公司  All rights reserved.
 *
 * ============================================================================
 * Program:   FastCAE
 *
 * Copyright (c) Since 2020 青岛数智船海科技有限公司  All rights reserved.
 * See License or http://www.fastcae.com/ for details.
 *
 * BSD 3-Clause License
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.
 * ==================================================================================
 */
#include "ComponentBase.h"
#include <qhash.h>

namespace DataProperty
{
	int ComponentBase::currMaxID = 0;
	QHash<int, ComponentType> ComponentBase::IDType;

	ComponentBase::ComponentBase(ComponentType type) : _type(type)
	{
		DataBase::setID(++currMaxID);
		IDType.insert(currMaxID, type);
	}

	ComponentBase::~ComponentBase()
	{
	}

	ComponentType ComponentBase::getComponentType()
	{
		return _type;
	}

	void ComponentBase::setID(int newID)
	{
		int oldID = getID();
		auto type = IDType.value(oldID);
		IDType.remove(oldID);
		IDType.insert(newID, type);
		DataBase::setID(newID);
		if (newID > currMaxID)
			currMaxID = newID;
	}

	int ComponentBase::getMaxID()
	{
		return currMaxID;
	}

	void ComponentBase::resetMaxID()
	{
		currMaxID = 0;
	}

	ComponentType ComponentBase::getComponentTypeByID(int ID)
	{
		return IDType.value(ID);
	}

	QString ComponentBase::componentTypeToString(ComponentType cpType)
	{
		QString sType{};
		switch (cpType)
		{
		case DataProperty::MESH:
			sType = "Mesh";
			break;
		case DataProperty::GEOMETRY:
			sType = "Geometry";
			break;
		default:
			break;
		}
		return sType;
	}

	DataProperty::ComponentType ComponentBase::stringToComponentType(QString sType)
	{
		ComponentType cpType;
		if (sType == "Mesh")
			cpType = MESH;
		else if (sType == "Geometry")
			cpType = GEOMETRY;
		return cpType;
	}
}