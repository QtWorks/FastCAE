#include "RenderDirector.h"
#include "GraphWidget.h"
#include "AnimationToolBar.h"
#include "PostProcessPy.h"
#include "PostRenderData/RenderDataObject.h"
#include "PostRenderData/RenderDataManager.h"
#include "PostInterface/RenderWindowManager.h"

namespace Post {
	RenderDirector* RenderDirector::_instance = nullptr;

	void RenderDirector::setAnimationToolBar(AnimationToolBar* toolBar)
	{
		_animation = toolBar;
		connect(this, SIGNAL(signal_runAnimation(RenderDataObject*,int)), toolBar, SLOT(on_RunAnimation(RenderDataObject*,int)));
		connect(this, SIGNAL(signal_stopAnimation(RenderDataObject*,int)), toolBar, SLOT(on_stopAnimation(RenderDataObject*,int)));
		connect(this, SIGNAL(signal_firstFrame(RenderDataObject*)), toolBar, SLOT(on_FirstFrame(RenderDataObject*)));
		connect(this, SIGNAL(signal_lastFrame(RenderDataObject*)), toolBar, SLOT(on_LastFrame(RenderDataObject*)));
		connect(this, SIGNAL(signal_proviousFrame(RenderDataObject*)), toolBar, SLOT(on_PreviousFrame(RenderDataObject*)));
		connect(this, SIGNAL(signal_nextFrame(RenderDataObject*)), toolBar, SLOT(on_NextFrame(RenderDataObject*)));
		connect(this, SIGNAL(signal_saveAnimation(RenderDataObject*,QString,int)), toolBar, SLOT(slot_saveAnimation(RenderDataObject*,QString,int)));
	}

	bool RenderDirector::renderDataObjectToWindow(RenderDataObject* obj, int winID /*= -1*/)
	{
		if (obj == nullptr) return false;
		GraphWidget* gw = nullptr;

		int oldID = obj->getRenderWinID();
		gw = _windowManager->getRenderWindowByID(oldID);
		if (gw != nullptr) gw->removeObject(obj);
		obj->setRenderWinID(-1);

		/*if (winID == -1)*/
		gw = _windowManager->getRenderWindowByID(winID);
		if (gw == nullptr) return false;
		int id = gw->getID();
		obj->setRenderWinID(id);

		return gw->renderObject(obj);
	}

	void RenderDirector::updateDataObjectShowStatus(int objID, bool show, int index /*= -1*/)
	{
		auto obj = _dataManager->getObjectByID(objID);
		if (obj == nullptr) return;

		if (index == -1)
			obj->setShowStatus(show);
		else
			obj->setBlockShowStatus(index, show);

		int id = obj->getRenderWinID();
		auto rw = _windowManager->getRenderWindowByID(id);
		if (rw != nullptr) rw->reRender();

	}

	void RenderDirector::renderWindow(int wID)
	{
		auto window = _windowManager->getRenderWindowByID(wID);
		if (window == nullptr) return;
		window->reRender();
	}

	void RenderDirector::setDisplayMode(int wID, int type)
	{
		auto window = _windowManager->getRenderWindowByID(wID);
		if (window == nullptr) return;
		window->setPostDisplayMode(type);
	}

// 	void RenderDirector::saveImage(int wID,QString file)
// 	{
// 		auto window = _windowManager->getRenderWindowByID(wID);
// 		if (window == nullptr) return;
// 		window->saveImage(file);
// 	}

	void RenderDirector::initialize()
	{
		_dataManager = RenderDataManager::getInstance();
		_windowManager = RenderWindowManager::getInstance();
		_animation = nullptr;

		PostProcessPy::setDirector(this);

		connectSignal();
	}

	void RenderDirector::connectSignal()
	{
		connect(this, SIGNAL(signal_renderDataObject(RenderDataObject*, int)), this, SLOT(renderDataObjectToWindow(RenderDataObject*, int)));
		connect(this, SIGNAL(signal_renderWindow(int)), this, SLOT(renderWindow(int)));
		connect(this, SIGNAL(signal_setDisplayMode(int,int)), this, SLOT(setDisplayMode(int,int)));
	//	connect(this, SIGNAL(signal_saveImage(int)), this, SLOT(saveImage(int)));
	}

}
