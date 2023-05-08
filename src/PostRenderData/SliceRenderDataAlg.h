#ifndef _SLICE_RENDERDATAALG_H_
#define _SLICE_RENDERDATAALG_H_

#include "RenderDataAlgorithm.h"
#include "Macros.hxx"
#include <vtkPlane.h>
#include <vtkSmartPointer.h>

namespace Post {
	class POSTRENDERDATAAPI SliceRenderDataAlg : public RenderDataAlgorithm
	{
	public:
		SliceRenderDataAlg(RenderDataObject* parent);
		~SliceRenderDataAlg();
		/**
		 * @brief 设置平面原点位置
		 * @param  ori
		 */
		void setPlaneOri(double* ori);

		void getPlaneOrigin(double* origin);
		/**
		 * @brief 设置平面向量
		 * @param  normal
		 */
		void setPlaneNormal(double* normal);

		void getPlaneNormal(double* normal);

		void updateParam() override;

	private:
		double _origin[3]{ 0 };
		double _normal[3]{ 0 };


	private:
		DeclarVTKSmartPtr(vtkPlane, _plane)
	};
}
#endif // !VIEWDATASLICE_H__
