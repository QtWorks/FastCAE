#ifndef _ISOCURVE_RENDERDATAALG_H_
#define _ISOCURVE_RENDERDATAALG_H_

#include "ISORenderDataAlg.h"
#include <vtkDataSetSurfaceFilter.h>
#include <QString>

namespace Post {
	class POSTRENDERDATAAPI ISOCurveRenderDataAlg : public ISORenderDataAlg
	{


	public:
		ISOCurveRenderDataAlg(RenderDataObject* parent);
		~ISOCurveRenderDataAlg() = default;

		
		void updateParam() override;

	private:
		DeclarVTKSmartPtr(vtkDataSetSurfaceFilter, _surfaceFilter)


	};
}


#endif