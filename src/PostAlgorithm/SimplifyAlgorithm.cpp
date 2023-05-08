#include "SimplifyAlgorithm.h"
#include <vtkInformation.h>
#include <vtkDataSet.h>
#include <vtkPolyData.h>
#include <vtkDemandDrivenPipeline.h>
#include <vtkStreamingDemandDrivenPipeline.h>
#include <vtkDataSetSurfaceFilter.h>
#include <vtkTriangleFilter.h>
#include <vtkDecimatePro.h>
#include <vtkSmartPointer.h>
#include <vtkKdTreePointLocator.h>
#include <vtkPointData.h>
#include <vtkDataArray.h>
#include <vtkDoubleArray.h>
#include <vtkCellData.h>
#include <vtkCellDataToPointData.h>
#include <QDebug>

SimplifyAlgorithm* SimplifyAlgorithm::New()
{
    auto simplify = new SimplifyAlgorithm;
    simplify->InitializeObjectBase();
    return simplify;
}

void SimplifyAlgorithm::PrintSelf(ostream& os, vtkIndent indent)
{
    this->Superclass::PrintSelf(os, indent);
}

SimplifyAlgorithm::SimplifyAlgorithm()
{
    this->_SurfaceReduce = 0.2;
    this->_surface = nullptr;
    this->_decimate = nullptr;
    this->_triangle = nullptr;
    this->_cellToPoint = nullptr;

    this->SetNumberOfInputPorts(1);
    this->SetNumberOfOutputPorts(1);
}

SimplifyAlgorithm::~SimplifyAlgorithm()
{
    this->_SurfaceReduce = 0;
    this->_surface = nullptr;
    this->_decimate = nullptr;
    this->_triangle = nullptr;
    this->_cellToPoint = nullptr;
}

int SimplifyAlgorithm::FillInputPortInformation(int port, vtkInformation* info)
{
    Q_UNUSED(port)
    info->Set(vtkAlgorithm::INPUT_REQUIRED_DATA_TYPE(), "vtkDataSet");
    return 1;
}

int SimplifyAlgorithm::FillOutputPortInformation(int port, vtkInformation* info)
{
    Q_UNUSED(port)
    info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkPolyData");
    return 1;
}

int SimplifyAlgorithm::ProcessRequest(vtkInformation* request, vtkInformationVector** inputVector, vtkInformationVector* outputVector)
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

int SimplifyAlgorithm::RequestData(vtkInformation* request, vtkInformationVector** inputVector, vtkInformationVector* outputVector)
{
    Q_UNUSED(request)
    CreateVTKSmartPtr(vtkDataSetSurfaceFilter, _surface);
    CreateVTKSmartPtr(vtkTriangleFilter, _triangle);
    CreateVTKSmartPtr(vtkDecimatePro, _decimate);
    CreateVTKSmartPtr(vtkCellDataToPointData, _cellToPoint);

    vtkDataSet* inputData = vtkDataSet::GetData(inputVector[0]);
    vtkPolyData* outputData = vtkPolyData::GetData(outputVector);
    if (inputData == nullptr)
    {
        vtkErrorMacro("InputData is error.");
        return 0;
    }

    renameCellArray(inputData->GetCellData());

    _cellToPoint->SetInputData(inputData);

    _surface->SetInputConnection(_cellToPoint->GetOutputPort());
    _triangle->SetInputConnection(_surface->GetOutputPort());  //表面三角化
    _decimate->SetInputConnection(_triangle->GetOutputPort());  //简化
    _decimate->SetPreserveTopology(false);
    _decimate->SplittingOn();
    _decimate->BoundaryVertexDeletionOn();
    _decimate->SetMaximumError(VTK_DOUBLE_MAX);
    _decimate->SetTargetReduction(_SurfaceReduce);
    _decimate->Update();

    vtkPolyData* data = _decimate->GetOutput();
    if (data == nullptr)
    {
        vtkErrorMacro("Simplify fiald.");
        return 0;
    }

    outputData->CopyStructure(data);
    outputData->GetPointData()->PassData(data->GetPointData());

    return 1;
}

void SimplifyAlgorithm::renameCellArray(vtkCellData* cellData)
{
    if (cellData == nullptr) return;

    const int nArray = cellData->GetNumberOfArrays();
    for (int i = 0; i < nArray; i++)
    {
        const char* name = cellData->GetArray(i)->GetName();
        Char2QString(name, sname);
        sname += "_cell";
        QString2Char(sname, tname);
        cellData->GetArray(i)->SetName(tname);
    }
}
