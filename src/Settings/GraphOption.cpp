/**
 * @file GraphOption.cpp
 * @brief 绘图信息配置类源(.cpp)文件
 * @author FastCAE研发小组(fastcae@diso.cn)
 * @version 2.5.0
 * @date 2022-02-13 17:34
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
#include "GraphOption.h"
#include <QSettings>
#include <QDebug>

namespace Setting
{
	void GraphOption::writeINI(QSettings *setting)
	{
		setting->remove("GraphOption");
		setting->setValue("/GraphOption/BackgroundTop/", _bgTop);
		setting->setValue("/GraphOption/BackgroundBottom/", _bgBottom);
		setting->setValue("/GraphOption/HighLight/", _highLightColor);
		setting->setValue("/GraphOption/PreHighLight/", _preHighLightColor);
		setting->setValue("/GraphOption/GeometrySurfaceColor/", _geoSurfaceColor);
		setting->setValue("/GraphOption/GeometryCurveColor/", _geoCurveColor);
		setting->setValue("/GraphOption/GeometryPointColor/", _geoPointColor);
		setting->setValue("/GraphOption/MeshFaceColor/", _meshFaceColor);
		setting->setValue("/GraphOption/MeshEdgeColor/", _meshEdgeColor);
		setting->setValue("/GraphOption/MeshNodeColor/", _meshNodeColor);
		setting->setValue("/GraphOption/MeshNodeSize/", _meshNodeSize);
		setting->setValue("/GraphOption/MeshEdgeWidth/", _meshEdgeWidth);
		setting->setValue("/GraphOption/GeometryCurveWidth/", _geoCurveWidth);
		setting->setValue("/GraphOption/GeometryPointSize/", _geoPointSize);
		setting->setValue("/GraphOption/Transparency/", _transparency);
		setting->setValue("/GeometryDisplay/ShowPoint", _showGeoPoint);
		setting->setValue("/GeometryDisplay/ShowEdge", _showGeoEdge);
		setting->setValue("/GeometryDisplay/ShowSurface", _showGeoSurface);
		setting->setValue("/MeshDisplay/ShowNode", _showMeshNode);
		setting->setValue("/MeshDisplay/ShowEdge", _showMeshEdge);
		setting->setValue("/MeshDisplay/ShowFace", _showMeshFace);
	}
	void GraphOption::readINI(QSettings *settings)
	{
		_bgTop = settings->value("/GraphOption/BackgroundTop/").value<QColor>();
		_bgBottom = settings->value("/GraphOption/BackgroundBottom/").value<QColor>();
		_highLightColor = settings->value("/GraphOption/HighLight/").value<QColor>();
		_preHighLightColor = settings->value("/GraphOption/PreHighLight/").value<QColor>();
		_geoSurfaceColor = settings->value("/GraphOption/GeometrySurfaceColor/").value<QColor>();
		_geoCurveColor = settings->value("/GraphOption/GeometryCurveColor/").value<QColor>();
		_geoPointColor = settings->value("/GraphOption/GeometryPointColor/").value<QColor>();
		_meshFaceColor = settings->value("/GraphOption/MeshFaceColor/").value<QColor>();
		_meshEdgeColor = settings->value("/GraphOption/MeshEdgeColor/").value<QColor>();
		_meshNodeColor = settings->value("/GraphOption/MeshNodeColor/").value<QColor>();
		_meshNodeSize = settings->value("/GraphOption/MeshNodeSize/").toFloat();
		_meshEdgeWidth = settings->value("/GraphOption/MeshEdgeWidth/").toFloat();
		_geoCurveWidth = settings->value("/GraphOption/GeometryCurveWidth/").toFloat();
		_geoPointSize = settings->value("/GraphOption/GeometryPointSize/").toFloat();
		_transparency = settings->value("/GraphOption/Transparency/").toInt();
		_showGeoPoint = settings->value("/GeometryDisplay/ShowPoint").toBool();
		_showGeoEdge = settings->value("/GeometryDisplay/ShowEdge").toBool();
		_showGeoSurface = settings->value("/GeometryDisplay/ShowSurface").toBool();
		_showMeshNode = settings->value("/MeshDisplay/ShowNode").toBool();
		_showMeshEdge = settings->value("/MeshDisplay/ShowEdge").toBool();
		_showMeshFace = settings->value("/MeshDisplay/ShowFace").toBool();
	}
	void GraphOption::setBackgroundTopColor(QColor c)
	{
		_bgTop = c;
	}
	void GraphOption::setBackgroundBottomColor(QColor c)
	{
		_bgBottom = c;
	}
	QColor GraphOption::getBackgroundTopColor()
	{
		return _bgTop;
	}
	QColor GraphOption::getBackgroundBottomColor()
	{
		return _bgBottom;
	}
	void GraphOption::setHighLightColor(QColor c)
	{
		_highLightColor = c;
	}
	QColor GraphOption::getHighLightColor()
	{
		return _highLightColor;
	}
	void GraphOption::setGeometrySurfaceColor(QColor c)
	{
		_geoSurfaceColor = c;
	}
	QColor GraphOption::getGeometrySurfaceColor()
	{
		return _geoSurfaceColor;
	}
	void GraphOption::setMeshFaceColor(QColor c)
	{
		_meshFaceColor = c;
	}
	QColor GraphOption::getMeshFaceColor()
	{
		return _meshFaceColor;
	}
	void GraphOption::setMeshEdgeColor(QColor c)
	{
		_meshEdgeColor = c;
	}
	QColor GraphOption::getMeshEdgeColor()
	{
		return _meshEdgeColor;
	}
	void GraphOption::setMeshNodeColor(QColor c)
	{
		_meshNodeColor = c;
	}
	QColor GraphOption::getMeshNodeColor()
	{
		return _meshNodeColor;
	}
	void GraphOption::setMeshNodeSize(float s)
	{
		_meshNodeSize = s;
	}
	float GraphOption::getMeshNodeSize()
	{
		return _meshNodeSize;
	}
	void GraphOption::setMeshEdgeWidth(float s)
	{
		_meshEdgeWidth = s;
	}
	float GraphOption::getMeshEdgeWidth()
	{
		return _meshEdgeWidth;
	}

	void GraphOption::setGeometryCurveColor(QColor c)
	{
		_geoCurveColor = c;
	}
	QColor GraphOption::getGeometryCurveColor()
	{
		return _geoCurveColor;
	}

	void GraphOption::setGeometryPointColor(QColor c)
	{
		_geoPointColor = c;
	}

	QColor GraphOption::getGeometryPointColor()
	{
		return _geoPointColor;
	}

	void GraphOption::setGeoPointSize(float s)
	{
		_geoPointSize = s;
	}
	float GraphOption::getGeoPointSize()
	{
		return _geoPointSize;
	}

	void GraphOption::setGeoCurveWidth(float s)
	{
		_geoCurveWidth = s;
	}
	float GraphOption::getGeoCurveWidth()
	{
		return _geoCurveWidth;
	}

	void GraphOption::sePretHighLightColor(QColor c)
	{
		_preHighLightColor = c;
	}

	QColor GraphOption::getPreHighLightColor()
	{
		return _preHighLightColor;
	}

	void GraphOption::setTransparency(int t)
	{
		_transparency = t;
	}

	int GraphOption::getTransparency()
	{
		return _transparency;
	}

	void GraphOption::isShowGeoPoint(bool show)
	{
		_showGeoPoint = show;
	}

	bool GraphOption::isShowGeoPoint()
	{
		return _showGeoPoint;
	}

	void GraphOption::isShowGeoEdge(bool show)
	{
		_showGeoEdge = show;
	}

	bool GraphOption::isShowGeoEdge()
	{
		return _showGeoEdge;
	}

	void GraphOption::isShowGeoSurface(bool show)
	{
		_showGeoSurface = show;
	}

	bool GraphOption::isShowGeoSurface()
	{
		return _showGeoSurface;
	}

	void GraphOption::isShowMeshNode(bool s)
	{
		_showMeshNode = s;
	}

	bool GraphOption::isShowMeshNode()
	{
		return _showMeshNode;
	}

	void GraphOption::isShowMeshEdge(bool s)
	{
		_showMeshEdge = s;
	}

	bool GraphOption::isShowMeshEdge()
	{
		return _showMeshEdge;
	}

	void GraphOption::isShowMeshFace(bool s)
	{
		_showMeshFace = s;
	}

	bool GraphOption::isShowMeshFace()
	{
		return _showMeshFace;
	}

}