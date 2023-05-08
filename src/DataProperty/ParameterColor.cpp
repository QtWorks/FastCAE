/**
 * @file ParameterColor.cpp
 * @brief 颜色类型参数类的源文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-08 18:04
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
#include "ParameterColor.h"
#include <QDomElement>
#include <QStringList>

namespace DataProperty
{
	ParameterColor::ParameterColor(): ParameterBase(Para_Color)
	{}
	ParameterColor::ParameterColor(QColor c) : ParameterBase(Para_Color),_color(c)
	{}


	void ParameterColor::copy(ParameterBase* ori, bool valueOnly /* = false */)
	{
		ParameterBase::copy(ori, valueOnly);
		ParameterColor*  pc = dynamic_cast<ParameterColor*>(ori);
		if (pc == nullptr) return;
		_color = pc->getColor();
	}

	void ParameterColor::setColor(QColor c)
	{
		if (c == _color) return;
		_color = c;
		emit dataChanged();
	}

	void ParameterColor::setColor(int* c)
	{
		QColor color(c[0],c[1],c[2]);
		this->setColor(color);
	}

	QColor ParameterColor::getColor()
	{
		return _color;
	}


	void ParameterColor::getColorF(double* c)
	{
		double r =0, g =0, b =0;
		_color.getRgbF(&r, &g, &b);
		c[0] = r; c[1] = g; c[2] = b;
	}

	bool ParameterColor::isSameValueWith(ParameterBase* p)
	{
		ParameterColor*  pc = dynamic_cast<ParameterColor*>(p);
		if (pc == nullptr) return false;
		QColor c = pc->getColor();
		return c == _color;
	}

	QString ParameterColor::valueToString()
	{
		int r = 0, g = 0, b = 0;
		_color.getRgb(&r, &g, &b);
		QString  sva = QString("%1,%2,%3").arg(r).arg(g).arg(b);
		return sva;
	}

	void ParameterColor::writeParameter(QDomDocument* doc, QDomElement* parent)
	{
		ParameterBase::writeParameter(doc, parent);
		parent->setAttribute("Value", valueToString());
	}

	void ParameterColor::readParameter(QDomElement* e)
	{
		ParameterBase::readParameter(e);
		QString sv = e->attribute("Value");
		this->setValueFromString(sv);
	}

	void ParameterColor::setValueFromString(QString v)
	{
		QStringList values = v.split(",");
		if (values.size() != 3) return;
		int c[3] = { values[0].toInt(),values[1].toInt() ,values[2].toInt() };
		this->setColor(c);
	}

}
