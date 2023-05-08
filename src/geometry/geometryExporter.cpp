/**
 * @file geometryExporter.cpp
 * @brief 几何导出类源文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-03-28 15:33
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
#include "geometryExporter.h"
#include "geometryData.h"
#include "geometrySet.h"
#include <QFileInfo>
#include <QDebug>
#include <TopoDS_Compound.hxx>
#include <BRep_Builder.hxx>
#include <BRepTools.hxx>
#include <IGESCAFControl_Writer.hxx>
#include <IGESControl_Controller.hxx>
#include <STEPControl_Writer.hxx>

namespace Geometry
{
	GeometryExporter::GeometryExporter(QString fileName)
	{
		_fileName = fileName;
		_geoData = GeometryData::getInstance();
	}

	bool GeometryExporter::write()
	{
		QFileInfo info(_fileName);

		const QString suffix = info.suffix().toLower();

		std::string str = _fileName.toStdString();
		const char *ch = str.c_str();

		qDebug() << suffix;
		bool ok = false;
		if (suffix == "brep")
		{
			ok = writeBrep(ch);
		}
		else if (suffix == "igs" || suffix == "iges")
		{
			ok = writeIgs(ch);
		}
		else if (suffix == "stp" || suffix == "step")
		{
			ok = writeStp(ch);
		}
		return ok;
	}

	bool GeometryExporter::writeBrep(const char *file)
	{
		TopoDS_Compound aRes;
		BRep_Builder aBuilder;
		aBuilder.MakeCompound(aRes);

		const int nset = _geoData->getGeometrySetCount();
		bool success = false;
		for (int i = 0; i < nset; ++i)
		{
			GeometrySet *set = _geoData->getGeometrySetAt(i);
			if (set == nullptr)
				continue;
			TopoDS_Shape *shape = set->getShape();

			if (shape == nullptr)
				continue;
			aBuilder.Add(aRes, *shape);
			success = true;
		}
		if (!success)
			return false;
		success = BRepTools::Write(aRes, file);
		return success;
	}

	bool GeometryExporter::writeIgs(const char *file)
	{
		IGESControl_Controller::Init();
		IGESControl_Writer igesWriter;

		const int nset = _geoData->getGeometrySetCount();
		bool success = false;
		for (int i = 0; i < nset; ++i)
		{
			GeometrySet *set = _geoData->getGeometrySetAt(i);
			if (set == nullptr)
				continue;
			TopoDS_Shape *shape = set->getShape();

			if (shape == nullptr)
				continue;
			igesWriter.AddShape(*shape);
			success = true;
		}
		if (!success)
			return false;

		igesWriter.ComputeModel();
		success = igesWriter.Write(file);
		return success;
	}

	bool GeometryExporter::writeStp(const char *file)
	{
		STEPControl_Writer stpWriter;

		const int nset = _geoData->getGeometrySetCount();
		bool success = false;
		for (int i = 0; i < nset; ++i)
		{
			GeometrySet *set = _geoData->getGeometrySetAt(i);
			if (set == nullptr)
				continue;
			TopoDS_Shape *shape = set->getShape();

			stpWriter.Transfer(*shape, STEPControl_AsIs);
			success = true;
		}
		if (!success)
			return false;

		success = stpWriter.Write(file);
		return success;
	}

}
