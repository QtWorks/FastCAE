﻿/**
 * @file ParameterDouble.cpp
 * @brief 双精度浮点类型参数类源文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-09 09:06
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
#include "ParameterDouble.h"
#include <QDomElement>
#include <QDomAttr>
#include <QDomDocument>
#include <QDomText>
#include <QDomNodeList>
#include <QStringList>
#include <math.h>

namespace DataProperty
{
	ParameterDouble::ParameterDouble() 
		: ParameterBase(Para_Double)
	{
		_range[0] = -1e66;
		_range[1] = 1e66;
	}
	void ParameterDouble::setValue(double v)
	{
		if (fabs(v - _value) > 0.00000001)
		{
			_value = v;
			emit dataChanged();
		}
		
	}
	double ParameterDouble::getValue()
	{
		return _value;
	}
	void ParameterDouble::setAccuracy(int a)
	{
		_accuracy = a;
	}
	int ParameterDouble::getAccuracy()
	{
		return _accuracy;
	}
	void ParameterDouble::setRange(double* range)
	{
		_range[0] = range[0];
		_range[1] = range[1];
	}
	void ParameterDouble::getRange(double* range)
	{
		range[0] = _range[0];
		range[1] = _range[1];
	}
	void ParameterDouble::setUnit(QString u)
	{
		_unit = u;
	}
	QString ParameterDouble::getUnit()
	{
		return _unit;
	}
	void ParameterDouble::writeParameter(QDomDocument* doc, QDomElement* parent)
	{
		ParameterBase::writeParameter(doc, parent);
		QDomAttr attr = doc->createAttribute("Value");
		attr.setValue(valueToString());
		parent->setAttributeNode(attr);

		QDomAttr uattr = doc->createAttribute("Unit");
		uattr.setValue(_unit);
		parent->setAttributeNode(uattr);

		QDomElement rangeele = doc->createElement("Range");
		QString sr = QString("%1,%2").arg(_range[0]).arg(_range[1]);
		QDomText rtext = doc->createTextNode(sr);
		rangeele.appendChild(rtext);
		parent->appendChild(rangeele);

		QDomElement accele = doc->createElement("Accuracy");
		QDomText acctext = doc->createTextNode(QString::number(_accuracy));
		accele.appendChild(acctext);
		parent->appendChild(accele);
	}

	void ParameterDouble::readParameter(QDomElement* e)
	{
		ParameterBase::readParameter(e);
		QString sv = e->attribute("Value");
		this->setValue(sv.toDouble());

		QString un = e->attribute("Unit");
		this->setUnit(un);

		QDomNodeList ralist = e->elementsByTagName("Range");
		if (ralist.size() != 1) return;
		QString sr = ralist.at(0).toElement().text();
		QStringList slrange = sr.split(",");
		if (slrange.size() != 2) return;
		_range[0] = slrange[0].toDouble();
		_range[1] = slrange[1].toDouble();

		QDomNodeList acclist = e->elementsByTagName("Accuracy");
		if (acclist.size() != 1) return;
		QString sacc = acclist.at(0).toElement().text();
		_accuracy = sacc.toInt();
	}

	void ParameterDouble::copy(ParameterBase* ori, bool valueOnly)
	{
		ParameterBase::copy(ori,valueOnly);
		ParameterDouble* p = dynamic_cast<ParameterDouble*> (ori);
		if (p != nullptr)
		{
			double v = p->getValue();
			this->setValue(v);
		    if (valueOnly) return;
			_accuracy = p->getAccuracy();
			_unit = p->getUnit();
			p->getRange(_range);
		}
		
	}

	bool ParameterDouble::isSameValueWith(ParameterBase* p)
	{
		bool same = false;
		ParameterDouble* pd = dynamic_cast<ParameterDouble*>(p);
		if (pd != nullptr)
		{
			double v = pd->getValue();
			if (fabs(v- _value) <0.00000001)
				same = true;
		}
		return same;
	}

	QString ParameterDouble::valueToString()
	{
		QString format = QString("%.%1f").arg(_accuracy);
		QByteArray ba = format.toLatin1();

		QString v = QString::asprintf(ba.data(), _value);
		return v;
	}

	void ParameterDouble::setValueFromString(QString v)
	{
		double value = v.toDouble();
		this->setValue(value);
	}

}
