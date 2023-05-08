#include "TecSzpltReaderAlgorithm.h"
#include "SzpltReader.h"
#include <vtkDataSet.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkCellData.h>
#include <vtkPointData.h>
#include <vtkUnstructuredGrid.h>
#include <vtkCompositeDataSet.h>
#include <vtkInformation.h>
#include <vtkInformationVector.h>
#include <vtkDemandDrivenPipeline.h>
#include <vtkStreamingDemandDrivenPipeline.h>
#include <vtkAppendFilter.h>
#include <QDebug>

#define  MAXBLOCKNUM  2000

int TecSzpltReaderAlgorithm::ProcessRequest(vtkInformation* request, vtkInformationVector** inputVector, vtkInformationVector* outputVector)
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

int TecSzpltReaderAlgorithm::RequestData(vtkInformation*, vtkInformationVector**, vtkInformationVector* outputVector)
{
    qDebug() << "TecSzpltReaderAlgorithm::RequestData";
    if (!this->FileName)
    {
        vtkErrorMacro("A FileName must be specified.");
        return 0;
    }


    _blockList.clear();
    _blockNames.clear();

    vtkMultiBlockDataSet* mBlock = nullptr;

    vtkSmartPointer<SzpltReader> reader = vtkSmartPointer<SzpltReader>::New();

    reader->SetFileName(FileName);

    reader->Update();

    mBlock = reader->GetOutput();

    vtkSmartPointer<vtkAppendFilter> appFilter = vtkSmartPointer<vtkAppendFilter>::New();
    appFilter->MergePointsOn();

    if (mBlock == nullptr) return 0;
    getBlocks(mBlock);


    for (int i = 0; i < _blockList.size(); ++i)
    {
        if (!_visibleStates[i]) continue;
        auto dataset = _blockList.at(i);
        appFilter->AddInputData(dataset);
    }


    appFilter->Update();

    vtkUnstructuredGrid* output = vtkUnstructuredGrid::GetData(outputVector);
    output->CopyStructure(appFilter->GetOutput());
    output->GetPointData()->PassData(appFilter->GetOutput()->GetPointData());
    output->GetCellData()->PassData(appFilter->GetOutput()->GetCellData());

    for (int i = 1; i <= _blockList.size(); i++)
    {
        if (i > MAXBLOCKNUM) break;
        auto data = _blockList.at(i - 1);
        vtkUnstructuredGrid* outData = vtkUnstructuredGrid::GetData(outputVector, i);
        vtkSmartPointer<vtkAppendFilter> appFilter = vtkSmartPointer<vtkAppendFilter>::New();
        appFilter->AddInputData(data);
        appFilter->Update();
        outData->CopyStructure(appFilter->GetOutput());
        outData->GetPointData()->PassData(appFilter->GetOutput()->GetPointData());
        outData->GetCellData()->PassData(appFilter->GetOutput()->GetCellData());;
    }
    return 1;
}

TecSzpltReaderAlgorithm* TecSzpltReaderAlgorithm::New()
{
    auto reader = new TecSzpltReaderAlgorithm;
    reader->InitializeObjectBase();
    return reader;
}

TecSzpltReaderAlgorithm::TecSzpltReaderAlgorithm()
{
    this->FileName = NULL;
    this->SetNumberOfInputPorts(0);
    this->SetNumberOfOutputPorts(MAXBLOCKNUM + 1);
    for (int i = 0; i < MAXBLOCKNUM; ++i)
        _visibleStates.append(true);

}
TecSzpltReaderAlgorithm::~TecSzpltReaderAlgorithm()
{
    this->FileName = NULL;
}
void TecSzpltReaderAlgorithm::PrintSelf(ostream& os, vtkIndent indent)
{
    this->Superclass::PrintSelf(os, indent);
    os << indent << "FileName:" << (this->FileName ? this->FileName : "(none)") << "\n";
}

void TecSzpltReaderAlgorithm::getBlocks(vtkDataObject* blockData, const char* Name)
{
    auto block = vtkMultiBlockDataSet::SafeDownCast(blockData);

    if (block == nullptr)
    {
        auto dataset = vtkDataSet::SafeDownCast(blockData);
        if (dataset == nullptr) return;
        dataset->Modified();
        QString totalName = QString::fromLocal8Bit(Name);
        //QStringList NameBC = totalName.split("!|||!");


        _blockNames.append(totalName);


        _blockList.append(dataset);
        getPointArray(dataset);
        getCellArray(dataset);
        return;
    }

    block->Modified();
    const int nBlock = block->GetNumberOfBlocks();

    for (int i = 0; i < nBlock; i++)
    {
        vtkDataObject* obj = block->GetBlock(i);
        const char* currentName = block->GetMetaData(i)->Get(vtkCompositeDataSet::NAME());
        getBlocks(obj, currentName);
    }
}

int TecSzpltReaderAlgorithm::getNumberOfBlocks()
{
    return _blockList.size();
}
void TecSzpltReaderAlgorithm::setVisible(int blockIndex, bool vis)
{	
    _visibleStates[blockIndex] = vis;
}
QStringList TecSzpltReaderAlgorithm::getBlockNames()
{
    return _blockNames;
}


void TecSzpltReaderAlgorithm::getPointArray(vtkDataSet* dataset)
{
    if (dataset == nullptr) return;

    auto pointData = dataset->GetPointData();
    if (pointData == nullptr) return;

    const int nPointArray = pointData->GetNumberOfArrays();
    for (int i = 0; i < nPointArray; i++)
    {
        const char* aName = pointData->GetArrayName(i);
        auto dataArray = pointData->GetArray(aName);
        if (dataArray == nullptr) return; //continue;
        int aNum[2]{ 0 };
        aNum[0] = dataArray->GetNumberOfComponents();
        aNum[1] = dataArray->GetNumberOfTuples();

        if (_pointDataArray.contains(aName)) continue;
        _pointDataArray.insert(aName, aNum);
    }
}

void TecSzpltReaderAlgorithm::getCellArray(vtkDataSet* dataset)
{
    if (dataset == nullptr) return;

    auto cellData = dataset->GetCellData();
    if (cellData == nullptr) return;

    const int nCellArray = cellData->GetNumberOfArrays();
    for (int i = 0; i < nCellArray; i++)
    {
        const char* aName = cellData->GetArrayName(i);
        auto dataArray = cellData->GetArray(aName);
        if (dataArray == nullptr) return; //continue;
        int aNum[2]{ 0 };
        aNum[0] = dataArray->GetNumberOfComponents();
        aNum[1] = dataArray->GetNumberOfTuples();

        if (_cellDataArray.contains(aName)) continue;
        _cellDataArray.insert(aName, aNum);
    }
}

int TecSzpltReaderAlgorithm::FillOutputPortInformation(int port, vtkInformation* info)
{
    Q_UNUSED(port)
    info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkUnstructuredGrid");
    return 1;
}
