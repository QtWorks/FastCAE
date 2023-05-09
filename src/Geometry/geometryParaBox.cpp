/**
 * @file geometryParaBox.cpp
 * @brief 创建立方体（长方体）操作类源文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-28 17:03
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
#include "geometryParaBox.h"
#include <QDomElement>
#include <QDomDocument>
#include <QDomAttr>

namespace Geometry
{
	GeometryParaBox::GeometryParaBox()
	{
		_type = GeometryParaCreateBox;
	}

	void GeometryParaBox::setName(QString name)
	{
		_name = name;
	}

	QString GeometryParaBox::getName()
	{
		return _name;
	}

	void GeometryParaBox::setLocation(double *loc)
	{
		for (int i = 0; i < 3; ++i)
			_location[i] = loc[i];
	}

	void GeometryParaBox::getLocation(double *loc)
	{
		for (int i = 0; i < 3; ++i)
			loc[i] = _location[i];
	}

	void GeometryParaBox::setGeoPara(double *para)
	{
		for (int i = 0; i < 3; ++i)
			_geoPara[i] = para[i];
	}

	void GeometryParaBox::getGeoPara(double *para)
	{
		for (int i = 0; i < 3; ++i)
			para[i] = _geoPara[i];
	}

	QDomElement &GeometryParaBox::writeToProjectFile(QDomDocument *doc, QDomElement *parent)
	{
        QDomElement element = doc->createElement("Parameter"); //创建子节点
		QDomAttr typeattr = doc->createAttribute("Type");
		typeattr.setValue(this->typeToString());
		element.setAttributeNode(typeattr);

		QDomAttr nameattr = doc->createAttribute("Name");
		nameattr.setValue(_name);
		element.setAttributeNode(nameattr);

		QDomElement locationEle = doc->createElement("Location");
		QString locstr = QString("%1,%2,%3").arg(_location[0]).arg(_location[1]).arg(_location[2]);
		QDomText locText = doc->createTextNode(locstr);
		locationEle.appendChild(locText);
		element.appendChild(locationEle);

		QDomElement geoParaEle = doc->createElement("GeoPara");
		QString geoParaStr = QString("%1,%2,%3").arg(_geoPara[0]).arg(_geoPara[1]).arg(_geoPara[2]);
		QDomText paraText = doc->createTextNode(geoParaStr);
		geoParaEle.appendChild(paraText);
		element.appendChild(geoParaEle);

		parent->appendChild(element);
		return element;
	}

	void GeometryParaBox::readDataFromProjectFile(QDomElement *e)
	{
		_name = e->attribute("Name");
		QDomNodeList locList = e->elementsByTagName("Location");
		if (locList.size() != 1)
			return;
		QDomElement locele = locList.at(0).toElement();
		QString locstr = locele.text();
		QStringList locsl = locstr.split(",");
		if (locsl.size() != 3)
			return;
		for (int i = 0; i < 3; ++i)
		{
			_location[i] = locsl.at(i).toDouble();
		}

		QDomNodeList paraList = e->elementsByTagName("GeoPara");
		if (paraList.size() != 1)
			return;
		QDomElement paraele = paraList.at(0).toElement();
		QString parastr = paraele.text();
		QStringList parasl = parastr.split(",");
		if (parasl.size() != 3)
			return;
		for (int i = 0; i < 3; ++i)
		{
			_geoPara[i] = parasl.at(i).toDouble();
		}
	}

}
