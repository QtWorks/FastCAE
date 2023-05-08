#include "RenderWindowManager.h"
#include "GraphWidget.h"

namespace Post {
	RenderWindowManager* RenderWindowManager::_instance = nullptr;

	GraphWidget* RenderWindowManager::getRenderWindowByID(const int id)
	{
		for (auto render : _RenderWindowList)
		{
			if (render == nullptr) continue;
			if (render->getID() == id) return render;
		}

		return nullptr;
	}

	void RenderWindowManager::removeRenderWindow(GraphWidget* widget)
	{
		_RenderWindowList.removeOne(widget);
	}

	void RenderWindowManager::initialize()
	{

	}

}

