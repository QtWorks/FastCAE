#include "GraphWidget.h"
#include "ui_GraphWidget.h"
#include "DialogSetBackgroundColor.h"
#include "DialogLightSetting.h"
#include "DialogRenderTitle.h"
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkAxesActor.h>
#include <QMenu>
#include <QAction>
#include <vtkLight.h>
#include "PostRenderData/RenderDataObject.h"
#include "PostRenderData/RenderProperty.h"
#include <vtkLightCollection.h>
#include <vtkLight.h>
#include <vtkCamera.h>
#include <vtkWindowToImageFilter.h>
#include <vtkPNGWriter.h>
#include <vtkBMPWriter.h>
#include <vtkJPEGWriter.h>
#include <vtkTextActor.h>
#include <vtkTextWidget.h>
#include <vtkTextRepresentation.h>
#include <vtkTextProperty.h>

namespace Post 
{
GraphWidget::GraphWidget(int id, int type,QWidget* parent /*= nullptr*/) :
    QWidget(parent),
    _PostType(type),
    _ID(id)
{
    _ui = new Ui::GraphWidget;
    _ui->setupUi(this);
    //this->setWindowTitle(QString("Render_%1").arg(_ID));

    _renderWindow = _ui->gWidget->renderWindow();
    _renderer = vtkRenderer::New();
    _renderWindow->AddRenderer(_renderer);
    _renderer->SetGradientBackground(true);
    _renderer->SetBackground(0.82, 0.84, 1.0);
    _renderer->SetBackground2(1.0, 1.0, 1.0);

    _textWidget = vtkTextWidget::New();
    vtkSmartPointer<vtkTextActor> textActor = vtkSmartPointer<vtkTextActor>::New();
    textActor->SetInput("VTK Render Title");
    textActor->GetTextProperty()->SetColor(1.0, 0.0, 0.0);
    textActor->GetTextProperty()->SetFontSize(1);
    textActor->SetDragable(false);

    vtkSmartPointer<vtkTextRepresentation> textRepresentation = vtkSmartPointer<vtkTextRepresentation>::New();
    textRepresentation->GetPositionCoordinate()->SetValue(0, 0.92);
    textRepresentation->GetPosition2Coordinate()->SetValue(0.2, 0.1);
    textRepresentation->SetShowBorderToOff();

    _textWidget->SetRepresentation(textRepresentation);
    _textWidget->SetInteractor(_renderWindow->GetInteractor());
    _textWidget->SetTextActor(textActor);
    _textWidget->SelectableOff();
    _textWidget->ResizableOff();
    _textWidget->Off();

    vtkSmartPointer<vtkAxesActor> axesActor = vtkSmartPointer<vtkAxesActor>::New();
    _axesWidget = vtkOrientationMarkerWidget::New();
    _axesWidget->SetOutlineColor(0.9300, 0.5700, 0.1300);
    _axesWidget->SetOrientationMarker(axesActor);
    _axesWidget->SetInteractor(_renderWindow->GetInteractor());
    _axesWidget->SetViewport(0.0, 0.0, 0.2, 0.2);
    _axesWidget->SetEnabled(1);
    _axesWidget->InteractiveOff();

}

GraphWidget::~GraphWidget()
{
    if (_ui != nullptr) delete _ui;
    //emit widgetClosed(this);
}

void GraphWidget::reRender()
{
    _renderWindow->Render();
}

bool GraphWidget::renderObject(RenderDataObject* obj)
{
    if (obj == nullptr) return false;
    auto act = obj->getAssembly();

    if (act == nullptr) return false;
    _renderer->AddActor(act);
    //	obj->()->updateScalarBar(_renderWindow->GetInteractor());
    obj->updateScalarBar(_renderWindow->GetInteractor());
    obj->setDisplayMode(_PostDisplayMode);
    _ObjectList.append(obj);

    this->fitView();
    return true;
}

void GraphWidget::removeObject(RenderDataObject* obj)
{
    if (obj == nullptr) return;
    auto act = obj->getAssembly();
    _renderer->RemoveActor(act);
    _ObjectList.removeOne(obj);
    //	obj->getViewProperty()->updateScalarBar(nullptr);
    obj->updateScalarBar(nullptr);
    this->reRender();
}

void GraphWidget::setView(double lookX, double lookY, double lookZ,
                          double upX, double upY, double upZ,
                          double posX, double posY, double posZ)
{
    vtkCamera *camera = _renderer->GetActiveCamera();

    if (camera == nullptr)  return;
    camera->SetPosition(posX, posY, posZ);          //相机位置
    camera->SetFocalPoint(lookX, lookY, lookZ);     //焦点位置
    camera->SetViewUp(upX, upY, upZ);               //朝上方向
    this->fitView();
}


void GraphWidget::fitView()
{
    _renderer->ResetCamera();
    _renderWindow->Render();
}

bool GraphWidget::saveImage(QString file)
{
    DecCreVTKSmartPtr(vtkWindowToImageFilter, winImageFilter)

            DeclarVTKSmartPtr(vtkImageWriter, writer)
            if (file.toLower().endsWith("png"))
            CreateVTKSmartPtr(vtkPNGWriter, writer)
            else if (file.toLower().endsWith("bmp"))
            CreateVTKSmartPtr(vtkBMPWriter, writer)
            else if (file.toLower().endsWith("jpg"))
            CreateVTKSmartPtr(vtkJPEGWriter, writer)

            if (writer == nullptr) return false;
    QString2Char(file, cF)
            winImageFilter->SetInput(_renderWindow);
    writer->SetFileName(cF);
    writer->SetInputConnection(winImageFilter->GetOutputPort());
    writer->Write();
    return true;
}

void GraphWidget::enabelAxis(bool enable)
{
    if (_axesWidget == nullptr) return;
    _axesWidget->SetEnabled(enable);
    this->reRender();
}

void GraphWidget::setBackground(double* top, double* bottom)
{
    _renderer->SetBackground(bottom);
    _renderer->SetBackground2(top);
    this->reRender();
}

void GraphWidget::addLight(double* color, double* position, double* focalPoint)
{
    vtkSmartPointer<vtkLight> light = vtkSmartPointer<vtkLight>::New();
    light->PositionalOff();
    light->SetPosition(position[0], position[1], position[2]);
    light->SetFocalPoint(focalPoint[0], focalPoint[1], focalPoint[2]);
    light->SetColor(color[0], color[1], color[2]);
    _renderer->AddLight(light);

    this->reRender();
}

void GraphWidget::deleteLight(int index)
{
    vtkLightCollection* lightColl = _renderer->GetLights();
    lightColl->InitTraversal();
    const int nLight = lightColl->GetNumberOfItems();

    for (int i = 0; i < nLight; i++)
    {
        vtkLight* light = lightColl->GetNextItem();
        if (i == index)
        {
            _renderer->RemoveLight(light);
        }
    }

    this->reRender();
}

void GraphWidget::refreshLight(int index, double* color, double* position, double* focalPoint)
{
    vtkLightCollection* lightColl = _renderer->GetLights();
    lightColl->InitTraversal();
    const int nLight = lightColl->GetNumberOfItems();

    for (int i = 0; i < nLight; i++)
    {
        vtkLight* light = lightColl->GetNextItem();
        if (i == index)
        {
            light->SetPosition(position[0], position[1], position[2]);
            light->SetFocalPoint(focalPoint[0], focalPoint[1], focalPoint[2]);
            light->SetColor(color[0], color[1], color[2]);
        }
    }

    this->reRender();
}

const int GraphWidget::getNumberOfLights()
{
    int nLight = 0;
    vtkLightCollection* lightColl = _renderer->GetLights();
    lightColl->InitTraversal();
    nLight = lightColl->GetNumberOfItems();

    return nLight;
}

vtkRenderWindowInteractor* GraphWidget::getInteractor()
{
    return _renderWindow->GetInteractor();
}

void GraphWidget::contextMenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(event)
    QMenu popMenu;
    QAction* act{ nullptr };
    act = popMenu.addAction(QStringLiteral("Axis"));
    act->setCheckable(true);
    act->setChecked(_axesWidget->GetEnabled());
    connect(act, &QAction::triggered, [=]() {
        const int e = _axesWidget->GetEnabled();  _axesWidget->SetEnabled(!e); this->reRender(); });

    act = popMenu.addAction(QStringLiteral("BackGround Color"));
    connect(act, &QAction::triggered, [=] {SetBackgroundColorDialog dlg(_renderer, _renderWindow);
        dlg.exec(); });

    // 		act = popMenu.addAction(QStringLiteral("Light"));
    // 		connect(act, &QAction::triggered, [=] {LightSettingDialog dlg(_renderer, _renderWindow);
    // 		dlg.exec(); });
    //
    // 		act = popMenu.addAction(QStringLiteral("Title"));
    // 		connect(act, &QAction::triggered, [=] {RenderTitleDialog dlg(_textWidget, _renderWindow);
    // 		dlg.exec(); });

    popMenu.exec(QCursor::pos());
}

vtkRenderWindow* GraphWidget::getRenderWindow()
{
    return _renderWindow;
}

bool GraphWidget::setRenderTitle(const char* text, double* color, double* pos, double* size, bool movable, bool visible)
{
    if (_textWidget == nullptr) return false;

    vtkTextActor* actor = _textWidget->GetTextActor();
    vtkTextRepresentation* rep = vtkTextRepresentation::SafeDownCast(_textWidget->GetRepresentation());
    if (actor == nullptr || rep == nullptr) return false;

    actor->SetInput(text);
    actor->GetTextProperty()->SetColor(color);
    rep->GetPositionCoordinate()->SetValue(pos);
    rep->GetPosition2Coordinate()->SetValue(size);
    _textWidget->SetSelectable(!movable);
    _textWidget->SetEnabled(visible);
    _renderWindow->Render();

    return true;
}

bool GraphWidget::setRenderTitleText(const char* text)
{
    if (_textWidget == nullptr) return false;

    vtkTextActor* actor = _textWidget->GetTextActor();
    if (actor == nullptr) return false;

    actor->SetInput(text);
    _renderWindow->Render();

    return true;
}

bool GraphWidget::setRenderTitleColor(double* color)
{
    if (_textWidget == nullptr) return false;

    vtkTextActor* actor = _textWidget->GetTextActor();
    if (actor == nullptr) return false;

    actor->GetTextProperty()->SetColor(color);
    _renderWindow->Render();

    return true;
}

bool GraphWidget::setRendetTitlePosition(double xCoor, double yCoor)
{
    if (_textWidget == nullptr) return false;

    vtkTextRepresentation* rep = vtkTextRepresentation::SafeDownCast(_textWidget->GetRepresentation());
    if (rep == nullptr) return false;

    rep->GetPositionCoordinate()->SetValue(xCoor, yCoor);
    _renderWindow->Render();

    return true;
}

bool GraphWidget::setRendetTitleSize(double width, double height)
{
    if (_textWidget == nullptr) return false;

    vtkTextRepresentation* rep = vtkTextRepresentation::SafeDownCast(_textWidget->GetRepresentation());
    if (rep == nullptr) return false;

    rep->GetPosition2Coordinate()->SetValue(width, height);
    _renderWindow->Render();

    return true;
}

bool GraphWidget::setRenderTitleVisible(bool visible)
{
    if (_textWidget == nullptr) return false;

    _textWidget->SetEnabled(visible);
    _renderWindow->Render();

    return true;
}

bool GraphWidget::setRenderTitleMovale(bool move)
{
    if (_textWidget == nullptr) return false;

    _textWidget->SetSelectable(!move);
    _renderWindow->Render();

    return true;
}

void GraphWidget::setPostDisplayMode(int mode)
{
    _PostDisplayMode = mode;
    for (auto obj : _ObjectList)
    {
        if(obj == nullptr) continue;
        obj->setDisplayMode(mode);
    }

    this->reRender();
}

}
