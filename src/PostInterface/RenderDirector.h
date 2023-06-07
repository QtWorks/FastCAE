#ifndef _RENDER_DIRECTOR_H_
#define _RENDER_DIRECTOR_H_

#include "PostInterfaceAPI.h"
#include "PostRenderData/Macros.hxx"
#include <QObject>

namespace Post {
	class RenderDataObject;
	class RenderWindowManager;
	class RenderDataManager;
	class AnimationToolBar;

	class POSTINTERFACEAPI RenderDirector:public QObject
	{
		Q_OBJECT

        Singleton(RenderDirector)

	signals:
		void signal_renderDataObject(RenderDataObject* obj,int wID);
		void signal_runAnimation(RenderDataObject* obj, int index);
		void signal_stopAnimation(RenderDataObject* obj, int index);
		void signal_firstFrame(RenderDataObject* obj);
		void signal_lastFrame(RenderDataObject* obj);
		void signal_proviousFrame(RenderDataObject* obj);
		void signal_nextFrame(RenderDataObject* obj);
		void signal_saveAnimation(RenderDataObject* obj, QString file, int fps);
		void signal_renderWindow(int wID);
		//void signal_saveImage(int wID);
		void signal_setDisplayMode(int wID, int type);

	public slots:
		void setAnimationToolBar(AnimationToolBar* toolBar);

		bool renderDataObjectToWindow(RenderDataObject* obj, int winID = -1);

		void updateDataObjectShowStatus(int objID, bool show, int index = -1);

		void renderWindow(int wID);
		void setDisplayMode(int wID, int type);
		//void saveImage(int wID);

	private:
		void initialize();
		void connectSignal();

	private:
		RenderDataManager* _dataManager;
		RenderWindowManager* _windowManager;
		AnimationToolBar* _animation;

	};
}



#endif
