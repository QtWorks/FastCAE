#ifndef _RENDERDATAMANAGER_H_
#define _RENDERDATAMANAGER_H_

#include "PostRenderDataAPI.h"
#include "Macros.hxx"
#include <QList>


namespace Post {
	ForwardDeclar(RenderDataObject)

	class POSTRENDERDATAAPI  RenderDataManager
	{
		Singleton(RenderDataManager)

		//数据链表，只包含最外层根数据节点
		AddPtrListProperty(RenderDataObject, RenderObjectList)

	public:
		/**
		 * @brief 根据ID获取对象
		 * @param  id    对象ID
		 * @return ViewDataObject*
		 */
		RenderDataObject*  getObjectByID(const int id);
		/**
		 * @brief 移除对象
		 * @param  obj    被移除的对象
		 */
		void removeObject(RenderDataObject* obj);

		void clearData();

	private:
		void initialize();
	};

}

#endif