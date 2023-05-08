/**
 * @file ParameterBool.cpp
 * @brief 布尔类型参数类的源文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-08 17:56
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
#include "ParameterBool.h"
#include <QDomDocument>
#include <QDomElement>
#include <QDomAttr>
#include <QString>

namespace DataProperty
{
	ParameterBool::ParameterBool() : ParameterBase(Para_Bool)
	{

	}
	
	void ParameterBool::setValue(bool ok)
	{
		bool unchange = (ok == _value);
		_value = ok;
		if (!unchange)
			emit dataChanged();
	}

	bool ParameterBool::getValue()
	{
		return _value;
	}

	void ParameterBool::writeParameter(QDomDocument* doc, QDomElement* parent)
	{
		ParameterBase::writeParameter(doc, parent);
		QString s = "false";
		if (_value) s = "true";
		QDomAttr attr = doc->createAttribute("Value");
		attr.setValue(s);
		parent->setAttributeNode(attr);
	}

	void ParameterBool::readParameter(QDomElement* e)
	{
		ParameterBase::readParameter(e);
		QString sv = e->attribute("Value");
		bool v = true;
		if (sv.toLower() == "false")
			v = false;
		this->setValue(v);
	}

	void ParameterBool::copy(ParameterBase* ori, bool valueOnly)
	{
		ParameterBase::copy(ori,valueOnly);
		ParameterBool* p = dynamic_cast<ParameterBool*>(ori);
		if (p != nullptr)
			this->setValue(p->getValue());
	}

	bool ParameterBool::isSameValueWith(ParameterBase* p)
	{
		bool is = false;
		ParameterBool* pb = dynamic_cast<ParameterBool*>(p);
		if (pb != nullptr)
		{
			bool s = pb->getValue();
			if (s == _value)
				is = true;
		}
		return is;
	}

	QString ParameterBool::valueToString()
	{
		QString t = "false";
		if (_value)
			t = "true";
		return t;
	}

	void ParameterBool::setValueFromString(QString v)
	{
		bool val = false;
		QString va = v.toLower();
		if (va == "true")
			val = true;
		else if (va == "false")
			val = false;
		this->setValue(val);
	}

}