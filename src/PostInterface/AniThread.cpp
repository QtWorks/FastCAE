#include "AniThread.h"
#include "PostRenderData/RenderDataImportUnSteady.h"
#include "PostRenderData/RenderDataObject.h"

#include <QDebug>

namespace Post {
	AniThread::AniThread()
	{

	}

	AniThread::~AniThread()
	{

	}

	void AniThread::initThread(int frame_xh, int max_frames, RenderDataImportUnSteady* unSteady)
	{
		_currFrameNum = frame_xh;
		_maxFrameNum = max_frames;
		_unSteadyObj = unSteady;
	}

	void AniThread::stop(bool flag)
	{
		stopped = flag;
	}

	void AniThread::run()
	{
		for (int i = _currFrameNum; i < _maxFrameNum; i++)
		{
			if (stopped)
			{
				return;
			}

			while (true)
			{
				if (g_qUnSteady.size() == 0)
				{
					g_mutex.lock();
					auto rootObj = _unSteadyObj->getRootViewObject();
					auto rootObject = dynamic_cast<RenderDataImportUnSteady*>(rootObj);
					if (rootObject == nullptr) 
					{ 
						g_mutex.unlock(); 
						return; 
					}
					rootObject->setAnimationIndex(i + 1);
					_unSteadyObj->update();
					g_qUnSteady.enqueue(_unSteadyObj);
					g_mutex.unlock();

					break;
				}

				if (stopped)
				{
					return;
				}
			}
		}
	}
}