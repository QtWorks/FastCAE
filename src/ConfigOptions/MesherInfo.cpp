/**
 * @file MesherInfo.cpp
 * @brief 网格剖分器信息类源文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-08 16:45
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
#include "MesherInfo.h"
#include <QDomElement>
#include <QDomAttr>
#include <QDebug>

namespace ConfigOption
{
	MesherInfo::MesherInfo()
	{
		this->setModuleType(DataProperty::Module_Mesher);
	}

	QString MesherInfo::getMesherName()
	{
		return _mesherName;
	}

	void MesherInfo::readParameters(QDomElement *ele)
	{
		_mesherName = ele->attribute("Name");
		this->appendProperty("Mesher", _mesherName);
		_template = ele->attribute("Template");
		_output = ele->attribute("Output");
		DataBase::readParameters(ele);
	}

	QString MesherInfo::getTemplate()
	{
		return _template;
	}

	QString MesherInfo::getOutput()
	{
		return _output;
	}

	void MesherInfo::writeParameters(QDomDocument *doc, QDomElement *parent)
	{
		QDomElement mesherEle = doc->createElement("Mesher");
		mesherEle.setAttribute("Name", _mesherName);
		mesherEle.setAttribute("Template", _template);
		mesherEle.setAttribute("Output", _output);

		DataBase::writeParameters(doc, &mesherEle);
		parent->appendChild(mesherEle);
	}

}
