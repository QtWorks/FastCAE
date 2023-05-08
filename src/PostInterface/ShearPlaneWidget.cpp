#include "ShearPlaneWidget.h"
#include "FuncCallback.h"
#include "GraphWidget.h"
#include "PostRenderData/RenderDataObject.h"
#include <vtkImplicitPlaneWidget2.h>
#include <vtkImplicitPlaneRepresentation.h>
#include <vtkPlane.h>

namespace Post {

	ShearPlaneWidget::ShearPlaneWidget(GraphWidget* window, RenderDataObject* obj):
		_window(window),
		_renderData(obj)
	{
		_callback = FuncCallback::New();
		_plane = vtkPlane::New();
		_planeWidget = vtkImplicitPlaneWidget2::New();
		_planeRep = vtkImplicitPlaneRepresentation::New();

		_callback->setPlane(_plane);
		
		_planeRep->SetPlaceFactor(1.0);
		_planeRep->SetNormal(_plane->GetNormal());
		_planeRep->SetOrigin(_plane->GetOrigin());
		_planeRep->PlaceWidget(obj->getBoundary());

		_planeWidget->SetInteractor(_window->getInteractor());
		_planeWidget->SetRepresentation(_planeRep);
		_planeWidget->AddObserver(vtkCommand::InteractionEvent, _callback);
		_planeWidget->On();
	}

	ShearPlaneWidget::~ShearPlaneWidget()
	{
		if (_plane != nullptr) _plane->Delete();
		if (_planeWidget != nullptr) _planeWidget->Delete();
		if (_planeRep != nullptr) _planeRep->Delete();
		if (_callback != nullptr) _callback->Delete();
		_window->reRender();
	}

	FuncCallback* ShearPlaneWidget::getCallback()
	{
		return _callback;
	}

	void ShearPlaneWidget::planeShow(bool show)
	{
		if (show) _planeWidget->On();
		else _planeWidget->Off();
	}

	void ShearPlaneWidget::setPlaceWidget(double* bound)
	{
		_planeRep->PlaceWidget(bound);
		//_planeRep->Modified();
		_planeRep->UpdatePlacement();
	}

	void ShearPlaneWidget::setPlaneNormal(double* normal)
	{
		_planeRep->SetNormal(normal);
		_plane->SetNormal(normal);

		_planeRep->UpdatePlacement();
	}

	void ShearPlaneWidget::setPlaneOrigin(double* origin)
	{
		_planeRep->SetOrigin(origin);
		_plane->SetOrigin(origin);

		_planeRep->UpdatePlacement();
	}

	void ShearPlaneWidget::getPlaneNormal(double* normal)
	{
		_plane->GetNormal(normal);
	}

	void ShearPlaneWidget::getPlaneOrigin(double* origin)
	{
		_plane->GetOrigin(origin);
	}

}