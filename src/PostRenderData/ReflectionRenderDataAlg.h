#ifndef _REFLECTION_RENDERDATAALG_H_
#define _REFLECTION_RENDERDATAALG_H_

#include "Macros.hxx"
#include "RenderDataAlgorithm.h"

class vtkReflectionFilter;

namespace Post {
	class POSTRENDERDATAAPI ReflectionRenderDataAlg :public RenderDataAlgorithm
	{
		AddProperty(int, Plane, 0)
		AddProperty(bool, CopyInput, false)
		AddProperty(double, Center, 0)

	public:
		ReflectionRenderDataAlg(RenderDataObject* obj);
		~ReflectionRenderDataAlg();


		void updateParam() override;

	private:
		//DeclarVTKSmartPtr(vtkReflectionFilter,_Reflection)
	};
}

#endif
