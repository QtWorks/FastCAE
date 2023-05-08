#ifndef _RENDERDATAIMPORTUNSTEADY_H__
#define _RENDERDATAIMPORTUNSTEADY_H__

#include "RenderDataImportSteady.h"
#include <QStringList>

namespace Post {
	class POSTRENDERDATAAPI RenderDataImportUnSteady : public RenderDataImportSteady
	{
		AddPropertyReadOnly(QStringList, FileList)
			AddProperty(int, CurrentIndex, 0)

	public:
		RenderDataImportUnSteady(const QString files);
		~RenderDataImportUnSteady();

		int getTotalCount();

		void setAnimationIndex(int index);
	private:
		void ReadFile();

	private:
	};

}
#endif