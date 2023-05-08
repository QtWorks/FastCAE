#ifndef _SIMPLIFY_RENDERDATAALG_H_
#define _SIMPLIFY_RENDERDATAALG_H_

#include "RenderDataAlgorithm.h"
#include "Macros.hxx"
#include <vtkSmartPointer.h>
#include <vtkDecimatePro.h>
#include <vtkTriangleFilter.h>
#include <vtkDataSetSurfaceFilter.h>

namespace Post {
	class POSTRENDERDATAAPI SimplifyRenderDataAlg :public RenderDataAlgorithm
	{
		AddPropertySetOverride(double, SurfaceReduce, 0.2)

	public:
		SimplifyRenderDataAlg(RenderDataObject* parent);
		~SimplifyRenderDataAlg();

	private:
		DeclarVTKSmartPtr(vtkDataSetSurfaceFilter, _surface)
			DeclarVTKSmartPtr(vtkTriangleFilter, _tri)


	};
}

#endif