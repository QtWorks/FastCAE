#include "FuncCallback.h"
#include <vtkPlane.h>
#include <vtkImplicitPlaneWidget2.h>
#include <vtkImplicitPlaneRepresentation.h>

FuncCallback* FuncCallback::New()
{
    return new FuncCallback;
}

void FuncCallback::Execute(vtkObject* caller, unsigned long eventId, void* callData)
{
    Q_UNUSED(eventId)
    Q_UNUSED(callData)
    vtkImplicitPlaneWidget2* planeWidget =
            reinterpret_cast<vtkImplicitPlaneWidget2*>(caller);
    vtkImplicitPlaneRepresentation* rep =
            reinterpret_cast<vtkImplicitPlaneRepresentation*>(
                planeWidget->GetRepresentation());
    rep->GetPlane(this->_plane);

    emit updatePlaneWidgetSig(_plane->GetNormal(), _plane->GetOrigin());
}

vtkPlane* FuncCallback::getPlane()
{
    return	_plane;
}

void FuncCallback::setPlane(vtkPlane* plane)
{
    _plane = plane;
}

FuncCallback::FuncCallback()
{

}

FuncCallback::~FuncCallback()
{

}

