#include "LineWidget.h"
#include "FLineCallback.h"
#include "GraphWidget.h"
#include <vtkLineWidget2.h>
#include <vtkLineRepresentation.h>

namespace Post {
LineWidget::LineWidget(GraphWidget* gw, RenderDataObject* obj):
    _window(gw)
{
    Q_UNUSED(obj)
    _lineWidget = vtkLineWidget2::New();
    _callback = FLineCallback::New();
    _lineRep = vtkLineRepresentation::New();
    _lineRep->SetDirectionalLine(true);

    _lineWidget->SetInteractor(gw->getInteractor());
    _lineWidget->SetRepresentation(_lineRep);
    _lineWidget->AddObserver(vtkCommand::InteractionEvent, _callback);
    _lineWidget->On();
}

LineWidget::~LineWidget()
{
    _lineWidget->Delete();
    _lineRep->Delete();
    _callback->Delete();
    _window->reRender();
}

FLineCallback* LineWidget::getCallback()
{
    return _callback;
}

void LineWidget::setLine(double* sPoint, double* ePoint)
{
    _lineRep->SetPoint1WorldPosition(sPoint);
    _lineRep->SetPoint2WorldPosition(ePoint);

    _callback->setLine(sPoint, ePoint);
}

void LineWidget::getLine(double* sPoint, double* ePoint)
{
    _callback->getLine(sPoint, ePoint);
}

}
