#include "RenderDataManager.h"
#include "PostRenderData/RenderDataObject.h"

namespace Post {
	RenderDataManager* RenderDataManager::_instance = nullptr;

	RenderDataObject* RenderDataManager::getObjectByID(const int id)
	{
		for (auto v : _RenderObjectList)
		{
			auto obj = v->getObjectByID(id);
			if (obj != nullptr) return obj;
		}
		return nullptr;
	}

	void RenderDataManager::removeObject(RenderDataObject* obj)
	{
		auto parent = obj->getParentObj();
		if (parent == nullptr)
		{
			_RenderObjectList.removeOne(obj);
			delete obj;
		}
		else
			parent->removeObject(obj);
	}

	void RenderDataManager::clearData()
	{
		for (auto d : _RenderObjectList)
			delete  d;
		_RenderObjectList.clear();
	}

	void RenderDataManager::initialize()
	{

	}

}