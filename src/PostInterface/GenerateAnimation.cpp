#include "GenerateAnimation.h"
#include <QTextCodec>
#ifdef Q_OS_WIN
#include <vtkAVIWriter.h>
#endif
#include <vtkSmartPointer.h>
#include <vtkWindowToImageFilter.h>
#include <vtkImageResize.h>
#include <vtkRenderWindow.h>


GenerateAnimation::GenerateAnimation(AviSetting* setting)
{
#ifdef Q_OS_WIN
    _aviSetting = setting;
#else
    Q_UNUSED(setting)
#endif
}

void GenerateAnimation::setRenderWindow(vtkRenderWindow* renderWindow)
{
#ifdef Q_OS_WIN
    _renderWindow = renderWindow;
#else
    Q_UNUSED(renderWindow)
#endif
}


GenerateAnimation::~GenerateAnimation()
{
#ifdef Q_OS_WIN
    if (_aviWriter != nullptr)
    {
        _aviWriter->End();
        _aviWriter->Delete();
        _aviWriter = nullptr;
    }
#endif
}

void GenerateAnimation::on_generate()
{
#ifdef Q_OS_WIN

    //保存动画
    //	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));

    if (_aviSetting->saveFlag)
    {
        if (!_startGenerate)
        {
            QString aviName;
            aviName = _aviSetting->aviFilePath;
            if (_aviWriter == nullptr)
                _aviWriter = vtkAVIWriter::New();
            //			QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
            QByteArray ba = aviName.toLatin1();
            _aviWriter->SetFileName(ba.data());
            _aviWriter->SetRate(_aviSetting->frameRate);
            vtkSmartPointer<vtkWindowToImageFilter> windowToImageFilter = vtkSmartPointer<vtkWindowToImageFilter>::New();
            windowToImageFilter->SetInput(_renderWindow);
            windowToImageFilter->Modified();
            vtkSmartPointer<vtkImageResize> resize = vtkSmartPointer<vtkImageResize>::New();
            resize->SetInputConnection(windowToImageFilter->GetOutputPort());
            resize->Update();
            _aviWriter->SetInputConnection(resize->GetOutputPort());
            _aviWriter->Start();
            _aviWriter->Write();
            _startGenerate = true;
        }
        else
        {
            vtkSmartPointer<vtkWindowToImageFilter> windowToImageFilter = vtkSmartPointer<vtkWindowToImageFilter>::New();
            windowToImageFilter->SetInput(_renderWindow);
            windowToImageFilter->Modified();
            vtkSmartPointer<vtkImageResize> resize = vtkSmartPointer<vtkImageResize>::New();
            resize->SetInputConnection(windowToImageFilter->GetOutputPort());
            resize->Update();
            _aviWriter->SetInputConnection(resize->GetOutputPort());
            _aviWriter->Write();
        }
    }
#endif
}

void GenerateAnimation::on_finishSaveAvi()
{
#ifdef Q_OS_WIN
    if (_startGenerate)
    {
        if (_aviWriter != nullptr)
        {
            _aviWriter->End();
            _aviWriter->Delete();
            _aviWriter = nullptr;
        }
        _startGenerate = false;
        _aviSetting->saveFlag = false;
    }
#endif

}
