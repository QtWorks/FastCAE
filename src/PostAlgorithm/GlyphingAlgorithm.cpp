#include "GlyphingAlgorithm.h"
#include <vtkInformation.h>
#include <vtkDataSet.h>
#include <vtkPolyData.h>
#include <vtkDemandDrivenPipeline.h>
#include <vtkStreamingDemandDrivenPipeline.h>
#include <vtkSmartPointer.h>
#include <vtkPointData.h>
#include <vtkCellData.h>
#include <vtkDataArray.h>
#include <vtkArrowSource.h>
#include <vtkMaskPoints.h>
#include <vtkGlyph3D.h>
#include <vtkCellCenters.h>
#include <QDebug>

GlyphingAlgorithm* GlyphingAlgorithm::New()
{
    auto glyphing = new GlyphingAlgorithm;
    glyphing->InitializeObjectBase();
    return glyphing;
}

void GlyphingAlgorithm::PrintSelf(ostream& os, vtkIndent indent)
{
    this->Superclass::PrintSelf(os, indent);
}

GlyphingAlgorithm::GlyphingAlgorithm()
{
    this->_pointsNumber = 0;
    //	this->_points = vtkPoints::New();
    // 	this->_polyData = vtkPolyData::New();
    // 	this->_maskPoints = vtkMaskPoints::New();
    // 	this->_glyph = vtkGlyph3D::New();
    // 	this->_arrowSource = vtkArrowSource::New();
    // 	this->_points = nullptr;
    this->_polyData = nullptr;
    this->_maskPoints = nullptr;
    this->_glyph = nullptr;
    this->_arrowSource = nullptr;
}

GlyphingAlgorithm::~GlyphingAlgorithm()
{
    this->_pointsNumber = -1;
    // 	this->_points = nullptr;
    this->_polyData = nullptr;
    this->_maskPoints = nullptr;
    this->_glyph = nullptr;
    this->_arrowSource = nullptr;
    //	this->_points->Delete();
    // 	this->_polyData->Delete();
    // 	this->_maskPoints->Delete();
    // 	this->_glyph->Delete();
    // 	this->_arrowSource->Delete();
}

int GlyphingAlgorithm::FillInputPortInformation(int port, vtkInformation* info)
{
    Q_UNUSED(port)
    info->Set(vtkAlgorithm::INPUT_REQUIRED_DATA_TYPE(), "vtkDataSet");
    return 1;
}

int GlyphingAlgorithm::FillOutputPortInformation(int port, vtkInformation* info)
{
    Q_UNUSED(port)
    info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkPolyData");
    return 1;
}

int GlyphingAlgorithm::ProcessRequest(vtkInformation* request, vtkInformationVector** inputVector, vtkInformationVector* outputVector)
{
    if (request->Has(vtkDemandDrivenPipeline::REQUEST_INFORMATION()))
    {
        return this->RequestInformation(request, inputVector,
                                        outputVector);
    }
    if (request->Has(
                vtkStreamingDemandDrivenPipeline::REQUEST_UPDATE_EXTENT()))
    {
        return this->RequestUpdateExtent(request, inputVector,
                                         outputVector);
    }
    if (request->Has(vtkDemandDrivenPipeline::REQUEST_DATA()))
    {
        return this->RequestData(request, inputVector, outputVector);
    }
    return this->Superclass::ProcessRequest(request, inputVector,
                                            outputVector);
}

int GlyphingAlgorithm::RequestData(vtkInformation* request, vtkInformationVector** inputVector, vtkInformationVector* outputVector)
{
    Q_UNUSED(request)
    vtkDataSet* inputData = vtkDataSet::GetData(inputVector[0]);
    vtkPolyData* outputData = vtkPolyData::GetData(outputVector);
    if (inputData == nullptr)
    {
        vtkErrorMacro("InputData is error.");
        return 0;
    }

    if (!extractPoints(inputData))
    {
        vtkErrorMacro("Glyphing faild.");
        return 0;
    }

    if (_maskPoints == nullptr) CreateVTKSmartPtr(vtkMaskPoints, _maskPoints);

    int mRatio = 1;
    if (_pointsNumber > 20000)
        mRatio = _pointsNumber / 20000;

    _maskPoints->SetInputData(_polyData);
    _maskPoints->SetOnRatio(mRatio);
    _maskPoints->RandomModeOn();
    _maskPoints->SetMaximumNumberOfPoints(_MaxNumber);

    if (_arrowSource == nullptr) CreateVTKSmartPtr(vtkArrowSource, _arrowSource);
    _arrowSource->SetTipResolution(_TipResolution);
    _arrowSource->SetTipRadius(_TipRadius);
    _arrowSource->SetTipLength(_TipLength);
    _arrowSource->SetShaftResolution(_ShaftResolution);
    _arrowSource->SetShaftRadius(_ShaftRadius);

    if (_glyph == nullptr) CreateVTKSmartPtr(vtkGlyph3D, _glyph);
    _glyph->SetSourceConnection(_arrowSource->GetOutputPort());
    _glyph->SetInputConnection(_maskPoints->GetOutputPort());
    _glyph->SetVectorModeToUseNormal();
    _glyph->SetScaleMode(_ScaleMode);
    _glyph->SetScaleFactor(_ScaleFactor);
    _glyph->ScalingOn();
    _glyph->OrientOn();
    _glyph->Update();

    outputData->CopyStructure(_glyph->GetOutput());
    outputData->GetPointData()->PassData(_glyph->GetOutput()->GetPointData());

    return 1;
}


bool GlyphingAlgorithm::extractPoints(vtkDataSet* inputData)
{
    if (_PointDataUsed)
    {
        auto pointData = inputData->GetPointData();
        if (pointData == nullptr) return false;

        extractPointDataArray(inputData);
        QString2Char(_VectorName, aName);
        auto array = pointData->GetArray(aName);

        //if (_points == nullptr) CreateVTKSmartPtr(vtkPoints, _points);
        vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
        _pointsNumber = inputData->GetNumberOfPoints();
        for (vtkIdType i = 0; i < _pointsNumber; i++)
        {
            double* p;
            p = inputData->GetPoint(i);
            //_points->InsertNextPoint(p);
            points->InsertNextPoint(p);
        }

        if (_polyData == nullptr) CreateVTKSmartPtr(vtkPolyData, _polyData);
        //_polyData->SetPoints(_points);
        _polyData->SetPoints(points);
        _polyData->GetPointData()->SetNormals(array);
    }
    else
    {
        auto cellData = inputData->GetCellData();
        if (cellData == nullptr) return false;

        QString2Char(_VectorName, aName);
        auto array = cellData->GetArray(aName);

        vtkSmartPointer<vtkCellCenters> cellCenters = vtkSmartPointer<vtkCellCenters>::New();
        cellCenters->SetInputData(inputData);
        cellCenters->VertexCellsOn();
        cellCenters->Update();

        extractPointDataArray(cellCenters->GetOutput());
        //if (_points == nullptr) CreateVTKSmartPtr(vtkPoints, _points);
        vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
        vtkPolyData* cPolyData = cellCenters->GetOutput();
        if (cPolyData == nullptr) return false;

        _pointsNumber = cPolyData->GetNumberOfCells();
        for (vtkIdType i = 0; i < _pointsNumber; i++)
        {
            double p[3];
            cPolyData->GetPoint(i,p);
            //_points->InsertNextPoint(p);
            points->InsertNextPoint(p);
        }

        if (_polyData == nullptr) CreateVTKSmartPtr(vtkPolyData, _polyData);
        //_polyData->SetPoints(_points);
        _polyData->SetPoints(points);
        _polyData->GetPointData()->SetNormals(array);
    }

    return true;
}

void GlyphingAlgorithm::extractPointDataArray(vtkDataSet* inputData)
{
    auto pointData = inputData->GetPointData();
    if (_polyData == nullptr) CreateVTKSmartPtr(vtkPolyData, _polyData);
    if (pointData == nullptr || _polyData == nullptr) return;

    const int nPointArray = pointData->GetNumberOfArrays();
    for (int i = 0; i < nPointArray; i++)
    {
        vtkDataArray* array = pointData->GetArray(i);
        _polyData->GetPointData()->AddArray(array);
    }
}

void GlyphingAlgorithm::extractCellDataArray(vtkDataSet* inputData)
{
    auto cellData = inputData->GetCellData();
    if (_polyData == nullptr) CreateVTKSmartPtr(vtkPolyData, _polyData);
    if (cellData == nullptr || _polyData == nullptr) return;

    const int nCellArray = cellData->GetNumberOfArrays();
    for (int i = 0; i < nCellArray; i++)
    {
        vtkDataArray* array = cellData->GetArray(i);
        _polyData->GetCellData()->AddArray(array);
    }
}
