#ifndef _RENDERWINDOW_MANAGER_H_
#define _RENDERWINDOW_MANAGER_H_

#include "PostInterfaceAPI.h"
#include "PostRenderData/Macros.hxx"
#include <QList>

namespace Post {
	ForwardDeclar(GraphWidget)
	
	class POSTINTERFACEAPI RenderWindowManager
	{
		Singleton(RenderWindowManager)

		AddPtrListProperty(GraphWidget,RenderWindowList)

	public:
		GraphWidget* getRenderWindowByID(const int id);

		void removeRenderWindow(GraphWidget* widget);

	private:
		void initialize();
	};
}


#endif