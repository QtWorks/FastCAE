#include "FLineCallback.h"
#include <vtkLineWidget2.h>
#include <vtkLineRepresentation.h>

FLineCallback* FLineCallback::New()
{
    return new FLineCallback;
}

void FLineCallback::Execute(vtkObject* caller, unsigned long eventId, void* callData)
{
    Q_UNUSED(eventId)
    Q_UNUSED(callData)
    vtkLineWidget2* lineWidget = reinterpret_cast<vtkLineWidget2*>(caller);
    vtkLineRepresentation* rep = reinterpret_cast<vtkLineRepresentation*>
            (lineWidget->GetRepresentation());

    rep->GetPoint1WorldPosition(_startPoint);
    rep->GetPoint2WorldPosition(_endPoint);

    emit updateLineWidgetSig(_startPoint, _endPoint);
}

void FLineCallback::getLine(double* sPoint, double* ePoint)
{
    for (int i = 0; i < 3; i++)
    {
        sPoint[i] = _startPoint[i];
        ePoint[i] = _endPoint[i];
    }
}

void FLineCallback::setLine(double* sPoint, double* ePoint)
{
    for (int i = 0; i < 3; i++)
    {
        _startPoint[i] = sPoint[i];
        _endPoint[i] = ePoint[i];
    }
}

FLineCallback::FLineCallback()
{

}

FLineCallback::~FLineCallback()
{

}

