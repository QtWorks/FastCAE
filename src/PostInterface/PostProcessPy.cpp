#include "PostProcessPy.h"
#include "RenderDirector.h"
#include "PostTreeWidget.h"
#include "GraphWidget.h"
#include "RenderWindowManager.h"
#include "DialogFileDirectory.h"
#include "PostRenderData/RenderDataManager.h"
#include "PostRenderData/RenderDataObject.h"
#include "PostRenderData/RenderProperty.h"
#include "PostRenderData/RenderDataImportSteady.h"
#include "PostRenderData/RenderDataImportUnSteady.h"
#include "PostRenderData/ClipRenderDataAlg.h"
#include "PostRenderData/SliceRenderDataAlg.h"
#include "PostRenderData/ISOCurveRenderDataAlg.h"
#include "PostRenderData/ISORenderDataAlg.h"
#include "PostRenderData/GlyphingRenderDataAlg.h"
#include "PostRenderData/StreamLineRenderDataAlg.h"
#include "PostRenderData/CalculateRenderDataAlg.h"
#include "PostRenderData/ReflectionRenderDataAlg.h"

namespace Post
{
	GUI::MainWindow *PostProcessPy::_mainWindow = nullptr;
	PostTreeWidget *PostProcessPy::_tree = nullptr;
	RenderDirector *PostProcessPy::_director = nullptr;

	void PostProcessPy::getBlockData(QMultiHash<int, int> &blockHash, char *blocks)
	{
		QString sblock = QString(blocks);
		QStringList blockList = sblock.split(";");
		for (auto objInfo : blockList)
		{
			QStringList info = objInfo.split(":");
			auto objID = info.at(0).toInt();
			QStringList bList = info.at(1).split(",");
			for (auto block : bList)
			{
				auto index = block.toInt();
				blockHash.insert(objID, index);
			}
		}
	}

	void PostProcessPy::init(GUI::MainWindow *mw, PostTreeWidget *tree)
	{
		_mainWindow = mw;
		_tree = tree;
	}

	void PostProcessPy::setDirector(RenderDirector *dire)
	{
		_director = dire;
	}

	void PostProcessPy::openPostFile(int wID, QString file)
	{
		RenderDataObject *dataObj = nullptr;
		if (FileDirectoryDialog::isGourpFiles(file))
        {
            dataObj = new RenderDataImportUnSteady(file);
        }
		else
        {
            dataObj = new RenderDataImportSteady(file);
        }
		dataObj->update();

		auto dataset = dataObj->getOutputData();

		RenderDataManager::getInstance()->appendRenderObjectList(dataObj);
        // RenderDirector::getInstance()->renderDataObjectToWindow(dataObj, wID);
		emit _director->signal_renderDataObject(dataObj, wID);
		_tree->updatePostTree();
		// emit _mainWindow->updatePostTreeSig();
	}

	void PostProcessPy::setDisplayMode(int wID, int type)
	{
		// 		auto rw = RenderWindowManager::getInstance()->getRenderWindowByID(wID);
		// 		if (rw == nullptr) return;
		// 		rw->setPostDisplayMode(type);
		emit _director->signal_setDisplayMode(wID, type);
	}

	void PostProcessPy::savePostImage(int wID, QString file)
	{
		auto rw = RenderWindowManager::getInstance()->getRenderWindowByID(wID);
		if (rw == nullptr)
			return;
		rw->saveImage(file);
	}

	void PostProcessPy::savePostAnimation(int pID, QString file, int fps)
	{
		auto obj = RenderDataManager::getInstance()->getObjectByID(pID);
		auto uObj = RenderDataImportUnSteady::SafeDownCast(obj);
		if (uObj == nullptr)
			return;
		emit _director->signal_saveAnimation(uObj, file, fps);
	}

	void PostProcessPy::setBlockColor(QMultiHash<int, int> blocks, QString name, int type, int component,
									  double red, double green, double blue, bool isVariable)
	{
		QList<RenderProperty *> proList{};
		GraphWidget *gw = nullptr;

		auto datalist = blocks.uniqueKeys();
		for (auto id : datalist)
		{
			auto obj = RenderDataManager::getInstance()->getObjectByID(id);
			if (obj == nullptr)
				continue;
			if (gw == nullptr)
				gw = RenderWindowManager::getInstance()->getRenderWindowByID(obj->getRenderWinID());

			for (auto bIndex : blocks.values(id))
			{
				if (bIndex == -1)
				{
					auto cPro = obj->getPropertyListAt(0);
					if (cPro == nullptr)
						continue;
					proList.append(cPro);
				}
				else
				{
					auto bPro = obj->getPropertyListAt(bIndex);
					if (bPro == nullptr)
						continue;
					proList.append(bPro);
				}
			}
		}

		if (isVariable)
		{
			for (auto pro : proList)
				pro->setCurrentVariable(type, name, component);
		}
		else
		{
			for (auto pro : proList)
				pro->setPropertyColor(red, green, blue);
		}

		emit _director->signal_renderWindow(gw->getID());
		// 		if (gw != nullptr) gw->reRender();
		_tree->updatePostTree();
	}

	void PostProcessPy::createClip(int parentID, QMultiHash<int, int> blocks, QString name,
								   double *ori, double *nor, bool out)
	{
		auto parent = RenderDataManager::getInstance()->getObjectByID(parentID);
		if (parent == nullptr)
			return;

		auto clip = new ClipRenderDataAlg(parent);
		clip->setName(name);
		clip->setSelectedObjectHash(blocks);
		clip->setPlaneOri(ori);
		clip->setPlaneNormal(nor);
		clip->setInsideOut(!out);

		clip->updateParam();
		clip->updateAlg();
		clip->update();

		parent->appendSubObjects(clip);
		// RenderDirector::getInstance()->renderDataObjectToWindow(clip, parent->getRenderWinID());
		emit _director->signal_renderDataObject(clip, parent->getRenderWinID());
		_tree->updatePostTree();
	}

	void PostProcessPy::editClip(int id, QMultiHash<int, int> blocks, QString name, double *ori, double *nor, bool out)
	{
		auto obj = RenderDataManager::getInstance()->getObjectByID(id);
		auto clip = dynamic_cast<ClipRenderDataAlg *>(obj);
		if (clip == nullptr)
			return;
		clip->setName(name);
		clip->setSelectedObjectHash(blocks);
		clip->setPlaneOri(ori);
		clip->setPlaneNormal(nor);
		clip->setInsideOut(!out);

		clip->updateParam();
		clip->updateAlg();
		clip->update();

		emit _director->signal_renderWindow(clip->getRenderWinID());
		_tree->updatePostTree();
	}

	void PostProcessPy::createSlice(int parentID, QMultiHash<int, int> blocks, QString name, double *ori, double *nor)
	{
		auto parent = RenderDataManager::getInstance()->getObjectByID(parentID);
		if (parent == nullptr)
			return;

		auto slice = new SliceRenderDataAlg(parent);
		slice->setName(name);
		slice->setSelectedObjectHash(blocks);
		slice->setPlaneOri(ori);
		slice->setPlaneNormal(nor);

		slice->updateParam();
		slice->updateAlg();
		slice->update();

		parent->appendSubObjects(slice);
		// RenderDirector::getInstance()->renderDataObjectToWindow(slice, parent->getRenderWinID());
		emit _director->signal_renderDataObject(slice, parent->getRenderWinID());
		_tree->updatePostTree();
	}

	void PostProcessPy::createISOSurface(int pID, QMultiHash<int, int> blocks, QString name,
										 QString variable, QStringList values)
	{
		auto parent = RenderDataManager::getInstance()->getObjectByID(pID);
		if (parent == nullptr)
			return;

		auto surface = new ISORenderDataAlg(parent);
		surface->setSelectedObjectHash(blocks);
		surface->setName(name);
		surface->setVariable(variable);

		for (auto value : values)
		{
			auto val = value.toDouble();
			surface->appendToValueList(val);
		}

		surface->updateParam();
		surface->updateAlg();
		surface->update();

		parent->appendSubObjects(surface);
		emit _director->signal_renderDataObject(surface, parent->getRenderWinID());
		_tree->updatePostTree();
		// RenderDirector::getInstance()->renderDataObjectToWindow(surface, parent->getRenderWinID());
	}

	void PostProcessPy::createISOCurve(int pID, QMultiHash<int, int> blocks, QString name,
									   QString variable, QStringList values)
	{
		auto parent = RenderDataManager::getInstance()->getObjectByID(pID);
		if (parent == nullptr)
			return;

		auto curve = new ISOCurveRenderDataAlg(parent);
		curve->setSelectedObjectHash(blocks);
		curve->setName(name);
		curve->setVariable(variable);

		for (auto value : values)
		{
			auto val = value.toDouble();
			curve->appendToValueList(val);
		}

		curve->updateParam();
		curve->updateAlg();
		curve->update();

		parent->appendSubObjects(curve);
		emit _director->signal_renderDataObject(curve, parent->getRenderWinID());
		_tree->updatePostTree();
		// RenderDirector::getInstance()->renderDataObjectToWindow(surface, parent->getRenderWinID());
	}

	void PostProcessPy::createVector(int pID, QMultiHash<int, int> blocks, QString name, QString vector,
									 int maxNumber, int scaleMode, double scaleFactor, bool isPointData)
	{
		auto parent = RenderDataManager::getInstance()->getObjectByID(pID);
		if (parent == nullptr)
			return;

		auto glyph = new GlyphingRenderDataAlg(parent);
		glyph->setSelectedObjectHash(blocks);
		glyph->setName(name);
		glyph->setVector(vector);
		glyph->setMaxNumber(maxNumber);
		glyph->setUsePointData(isPointData);
		glyph->setScaleMode(scaleMode);
		glyph->setScaleFactor(scaleFactor);

		glyph->updateParam();
		glyph->updateAlg();
		glyph->update();

		parent->appendSubObjects(glyph);
		emit _director->signal_renderDataObject(glyph, parent->getRenderWinID());
		_tree->updatePostTree();
		// RenderDirector::getInstance()->renderDataObjectToWindow(glyph, parent->getRenderWinID());
	}

	void PostProcessPy::createStreamLine(int pID, QMultiHash<int, int> blocks, QString name, QString vector,
										 double *start, double *end, int seeds, double maxLength, double initStep, double minStep,
										 double maxStep, int stepNumber, int direction, bool isPointData)
	{
		auto parent = RenderDataManager::getInstance()->getObjectByID(pID);
		if (parent == nullptr)
			return;

		auto sline = new StreamLineRenderDataAlg(parent);
		sline->setSelectedObjectHash(blocks);
		sline->setVector(vector);
		sline->setName(name);
		sline->setUsePointData(isPointData);
		sline->setLineSource(start, end);
		sline->setSeedCount(seeds);
		sline->setMaxLength(maxLength);
		sline->setInitStep(initStep);
		sline->setMinStep(minStep);
		sline->setMaxStep(maxStep);
		sline->setStepNumber(stepNumber);
		sline->setDirection(direction);

		sline->updateParam();
		sline->updateAlg();
		sline->update();

		parent->appendSubObjects(sline);
		emit _director->signal_renderDataObject(sline, parent->getRenderWinID());
		_tree->updatePostTree();
		// RenderDirector::getInstance()->renderDataObjectToWindow(sline, parent->getRenderWinID());
	}

	void PostProcessPy::createCalaulate(int pID, QMultiHash<int, int> blocks, QString name, QString func,
										QStringList scalars, QStringList vectors, bool isPointData)
	{
		auto parent = RenderDataManager::getInstance()->getObjectByID(pID);
		if (parent == nullptr)
			return;

		auto calculate = new CalculateRenderDataAlg(parent);

		calculate->setName(name);
		calculate->setSelectedObjectHash(blocks);
		calculate->clearInputScalars();
		calculate->clearInputVectors();
		calculate->setUsePointData(isPointData);
		calculate->setFunction(func);
		calculate->setResultArrayName(name);

		for (auto v : scalars)
			calculate->appendInputScalars(v);
		for (auto v : vectors)
			calculate->appendInputVectors(v);

		calculate->updateParam();
		calculate->updateAlg();
		calculate->update();

		parent->appendSubObjects(calculate);
		emit _director->signal_renderDataObject(calculate, parent->getRenderWinID());
		_tree->updatePostTree();
		// RenderDirector::getInstance()->renderDataObjectToWindow(calculate, parent->getRenderWinID());
	}

	void PostProcessPy::createReflection(int pID, QMultiHash<int, int> blocks, QString name, int plane, double center)
	{
		auto parent = RenderDataManager::getInstance()->getObjectByID(pID);
		if (parent == nullptr)
			return;

		auto reflection = new ReflectionRenderDataAlg(parent);
		reflection->setSelectedObjectHash(blocks);
		reflection->setPlane(plane);
		reflection->setCenter(center);

		reflection->updateParam();
		reflection->updateAlg();
		reflection->update();

		parent->appendSubObjects(reflection);
		emit _director->signal_renderDataObject(reflection, parent->getRenderWinID());
		_tree->updatePostTree();
		// RenderDirector::getInstance()->renderDataObjectToWindow(reflection, parent->getRenderWinID());
	}

	void PostProcessPy::runAnimation(int pID, int index)
	{
		auto obj = RenderDataManager::getInstance()->getObjectByID(pID);
		auto uObj = RenderDataImportUnSteady::SafeDownCast(obj);
		if (uObj == nullptr)
			return;
		emit _director->signal_runAnimation(uObj, index);
	}

	void PostProcessPy::stopAnimation(int pID, int index)
	{
		auto obj = RenderDataManager::getInstance()->getObjectByID(pID);
		auto uObj = RenderDataImportUnSteady::SafeDownCast(obj);
		if (uObj == nullptr)
			return;
		emit _director->signal_stopAnimation(uObj, index);
	}

	void PostProcessPy::firstFrame(int pID)
	{
		auto obj = RenderDataManager::getInstance()->getObjectByID(pID);
		auto uObj = RenderDataImportUnSteady::SafeDownCast(obj);
		if (uObj == nullptr)
			return;
		emit _director->signal_firstFrame(uObj);
	}

	void PostProcessPy::proviousFrame(int pID)
	{
		auto obj = RenderDataManager::getInstance()->getObjectByID(pID);
		auto uObj = RenderDataImportUnSteady::SafeDownCast(obj);
		if (uObj == nullptr)
			return;
		emit _director->signal_proviousFrame(uObj);
	}

	void PostProcessPy::nextFrame(int pID)
	{
		auto obj = RenderDataManager::getInstance()->getObjectByID(pID);
		auto uObj = RenderDataImportUnSteady::SafeDownCast(obj);
		if (uObj == nullptr)
			return;
		emit _director->signal_nextFrame(uObj);
	}

	void PostProcessPy::lastFrame(int pID)
	{
		auto obj = RenderDataManager::getInstance()->getObjectByID(pID);
		auto uObj = RenderDataImportUnSteady::SafeDownCast(obj);
		if (uObj == nullptr)
			return;
		emit _director->signal_lastFrame(uObj);
	}

}

void POSTINTERFACEAPI openPostFile(int id, char *type, char *file)
{
	Q_UNUSED(type)
	QString sfile = QString(file);
	Post::PostProcessPy::openPostFile(id, sfile);
}

void POSTINTERFACEAPI createClip(int pID, char *blocks, char *name, double xOri, double yOri,
								 double zOri, double xNor, double yNor, double zNor, bool out)
{
	QString sname = QString(name);
	// 	QString sblock = QString(blocks);
	// 	QStringList blockList = sblock.split(";");
	// 	QMultiHash<int, int> dataHash;
	// 	for (auto objInfo : blockList)
	// 	{
	// 		QStringList info = objInfo.split(":");
	// 		auto objID = info.at(0).toInt();
	// 		QStringList bList = info.at(1).split(",");
	// 		for (auto block : bList)
	// 		{
	// 			auto index = block.toInt();
	// 			dataHash.insert(objID, index);
	// 		}
	// 	}

	QMultiHash<int, int> dataHash;

	double ori[3]{0};
	double nor[3]{0};
	ori[0] = xOri;
	ori[1] = yOri;
	ori[2] = zOri;
	nor[0] = xNor;
	nor[1] = yNor;
	nor[2] = zNor;

	Post::PostProcessPy::getBlockData(dataHash, blocks);
	Post::PostProcessPy::createClip(pID, dataHash, sname, ori, nor, out);
}

void POSTINTERFACEAPI createSlice(int pID, char *blocks, char *name, double xOri, double yOri,
								  double zOri, double xNor, double yNor, double zNor)
{
	QString sname = QString(name);
	// 	QString sblock = QString(blocks);
	// 	QStringList blockList = sblock.split(";");
	// 	QMultiHash<int, int> dataHash;
	// 	for (auto objInfo : blockList)
	// 	{
	// 		QStringList info = objInfo.split(":");
	// 		auto objID = info.at(0).toInt();
	// 		QStringList bList = info.at(1).split(",");
	// 		for (auto block : bList)
	// 		{
	// 			auto index = block.toInt();
	// 			dataHash.insert(objID, index);
	// 		}
	// 	}
	QMultiHash<int, int> dataHash;

	double ori[3]{0};
	double nor[3]{0};
	ori[0] = xOri;
	ori[1] = yOri;
	ori[2] = zOri;
	nor[0] = xNor;
	nor[1] = yNor;
	nor[2] = zNor;

	Post::PostProcessPy::getBlockData(dataHash, blocks);
	Post::PostProcessPy::createSlice(pID, dataHash, sname, ori, nor);
}

void POSTINTERFACEAPI createISOSurface(int pID, char *blocks, char *name, char *variable, char *values)
{
	QString sname = QString(name);
	QString svariable = QString(variable);
	QString svalue = QString(values);
	QStringList valueList = svalue.split(",");
	QMultiHash<int, int> dataHash;

	Post::PostProcessPy::getBlockData(dataHash, blocks);
	Post::PostProcessPy::createISOSurface(pID, dataHash, sname, svariable, valueList);
}

void POSTINTERFACEAPI createISOCurve(int pID, char *blocks, char *name, char *variable, char *values)
{
	QString sname = QString(name);
	QString svariable = QString(variable);
	QString svalue = QString(values);
	QStringList valueList = svalue.split(",");
	QMultiHash<int, int> dataHash;

	Post::PostProcessPy::getBlockData(dataHash, blocks);
	Post::PostProcessPy::createISOCurve(pID, dataHash, sname, svariable, valueList);
}

void POSTINTERFACEAPI createVector(int pID, char *blocks, char *name, char *vector, int maxNumber,
								   int scaleMode, double scaleFactor, bool isPointData)
{
	QString sname = QString(name);
	QString svector = QString(vector);
	QMultiHash<int, int> dataHash;

	Post::PostProcessPy::getBlockData(dataHash, blocks);
	Post::PostProcessPy::createVector(pID, dataHash, sname, svector, maxNumber, scaleMode, scaleFactor, isPointData);
}

void POSTINTERFACEAPI createStreamLine(int pID, char *blocks, char *name, char *vector, double xStart,
									   double yStart, double zStart, double xEnd, double yEnd, double zEnd, int seeds, double maxLength,
									   double initStep, double minStep, double maxStep, int stepNumber, int direction, bool isPointData)
{
	QString sname = QString(name);
	QString svector = QString(vector);
	QMultiHash<int, int> dataHash;

	double start[3]{0};
	double end[3]{0};

	start[0] = xStart;
	start[1] = yStart;
	start[2] = zStart;
	end[0] = xEnd;
	end[1] = yEnd;
	end[2] = zEnd;

	Post::PostProcessPy::getBlockData(dataHash, blocks);
	Post::PostProcessPy::createStreamLine(pID, dataHash, sname, svector, start, end, seeds, maxLength,
										  initStep, minStep, maxStep, stepNumber, direction, isPointData);
}

void POSTINTERFACEAPI createCalaulate(int pID, char *blocks, char *name, char *func,
									  char *scalars, char *vectors, bool isPoint)
{
	QString sname = QString(name);
	QString sfunc = QString(func);
	QString scalar = QString(scalars);
	QString vector = QString(vectors);
	QStringList scalarList{};
	if (!scalar.isEmpty())
		scalarList = scalar.split(",");
	QStringList vectorList{};
	if (!vector.isEmpty())
		vectorList = vector.split(",");
	QMultiHash<int, int> dataHash;

	Post::PostProcessPy::getBlockData(dataHash, blocks);
	Post::PostProcessPy::createCalaulate(pID, dataHash, sname, sfunc, scalarList, vectorList, isPoint);
}

void POSTINTERFACEAPI createReflection(int pID, char *blocks, char *name, int plane, double center)
{
	QString sname = QString(name);
	QMultiHash<int, int> dataHash;

	Post::PostProcessPy::getBlockData(dataHash, blocks);
	Post::PostProcessPy::createReflection(pID, dataHash, sname, plane, center);
}

void POSTINTERFACEAPI savePostImage(int id, char *file)
{
	QString sfile = QString(file);
	Post::PostProcessPy::savePostImage(id, sfile);
}

void POSTINTERFACEAPI setDisplayMode(int id, int type)
{
	Post::PostProcessPy::setDisplayMode(id, type);
}

void POSTINTERFACEAPI setBlockColor(char *blocks, char *name, int type, int component, double red, double green, double blue, bool isVariable)
{
	QString vName = QString(name);
	QMultiHash<int, int> dataHash;
	Post::PostProcessPy::getBlockData(dataHash, blocks);
	Post::PostProcessPy::setBlockColor(dataHash, vName, type, component, red, green, blue, isVariable);
}

void POSTINTERFACEAPI runAnimation(int pID, int index)
{
	Post::PostProcessPy::runAnimation(pID, index);
}

void POSTINTERFACEAPI firstFrame(int pID)
{
	Post::PostProcessPy::firstFrame(pID);
}

void POSTINTERFACEAPI proviousFrame(int pID)
{
	Post::PostProcessPy::proviousFrame(pID);
}

void POSTINTERFACEAPI nextFrame(int pID)
{
	Post::PostProcessPy::nextFrame(pID);
}

void POSTINTERFACEAPI lastFrame(int pID)
{
	Post::PostProcessPy::lastFrame(pID);
}

void POSTINTERFACEAPI stopAnimation(int pID, int index)
{
	Post::PostProcessPy::stopAnimation(pID, index);
}

void POSTINTERFACEAPI savePostAnimation(int id, char *file, int fps)
{
	QString sfile = QString(file);
	Post::PostProcessPy::savePostAnimation(id, file, fps);
}

void POSTINTERFACEAPI editClip(int id, char *blocks, char *name, double xOri, double yOri,
							   double zOri, double xNor, double yNor, double zNor, bool out)
{
	QString sname = QString(name);
	QMultiHash<int, int> dataHash;

	double ori[3]{0};
	double nor[3]{0};
	ori[0] = xOri;
	ori[1] = yOri;
	ori[2] = zOri;
	nor[0] = xNor;
	nor[1] = yNor;
	nor[2] = zNor;

	Post::PostProcessPy::getBlockData(dataHash, blocks);
	Post::PostProcessPy::editClip(id, dataHash, sname, ori, nor, out);
}
