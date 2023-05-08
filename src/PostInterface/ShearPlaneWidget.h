#ifndef _SHEARPLANE_WIDGET_H_
#define _SHEARPLANE_WIDGET_H_

#include "PostInterfaceAPI.h"

class FuncCallback;
class vtkPlane;
class vtkImplicitPlaneRepresentation;
class vtkImplicitPlaneWidget2;

namespace Post {
	class GraphWidget;
	class RenderDataObject;

	class POSTINTERFACEAPI ShearPlaneWidget
	{
	public:
		ShearPlaneWidget(GraphWidget* window,RenderDataObject* obj);
		~ShearPlaneWidget();

		FuncCallback* getCallback();

		void planeShow(bool show);
		void setPlaceWidget(double* bound);

		void setPlaneNormal(double* normal);
		void setPlaneOrigin(double* origin);
		void getPlaneNormal(double* normal);
		void getPlaneOrigin(double* origin);

	private:
		FuncCallback* _callback{ nullptr };
		vtkPlane* _plane{ nullptr };
		vtkImplicitPlaneWidget2* _planeWidget{ nullptr };
		vtkImplicitPlaneRepresentation* _planeRep{ nullptr };
		GraphWidget* _window{ nullptr };
		RenderDataObject* _renderData{ nullptr };

	};
}

#endif