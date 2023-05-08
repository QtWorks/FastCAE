#include "Plot3DReaderAlgorithm.h"
#include <vtkMultiBlockPLOT3DReader.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkAlgorithmOutput.h>
#include <vtkAppendFilter.h>
#include <vtkInformation.h>
#include <vtkIndent.h>
#include <vtkDataSet.h>
#include <vtkUnstructuredGrid.h>
#include <vtkDataObject.h>
#include <vtkPointData.h>
#include <vtkCellData.h>
#include <vtkInformationVector.h>
#include <vtkStreamingDemandDrivenPipeline.h>
#include <vtkDemandDrivenPipeline.h>
#include <vtkIdTypeArray.h>
#include <vtkDoubleArray.h>
#include <QDebug>


#define  MAXBLOCKNUM  2000

Plot3DReaderAlgorithm::Plot3DReaderAlgorithm()
{	
    this->FileName = NULL;
    this->SetNumberOfInputPorts(0);
    this->SetNumberOfOutputPorts(MAXBLOCKNUM +1);

    for (int i = 0; i < MAXBLOCKNUM; ++i)
        _visibleStates.append(true);
}

Plot3DReaderAlgorithm::~Plot3DReaderAlgorithm()
{
    this->FileName = NULL;
}

Plot3DReaderAlgorithm* Plot3DReaderAlgorithm::New()
{
    return new Plot3DReaderAlgorithm;
}

void Plot3DReaderAlgorithm::PrintSelf(ostream& os, vtkIndent indent)
{	
    this->Superclass::PrintSelf(os, indent);
    os << indent << "FileName: "
       << (this->FileName ? this->FileName : "(none)") << "\n";

}

int Plot3DReaderAlgorithm::RequestData(vtkInformation*, vtkInformationVector**, vtkInformationVector* outputVector)
{	
    // Make sure we have a file to read.
    if (this->FileName == "")
    {
        vtkErrorMacro("A FileName must be specified.");
        return 0;
    }

    _blockList.clear();
    //    _blockNames.clear();

    vtkSmartPointer<vtkMultiBlockPLOT3DReader> reader = vtkSmartPointer<vtkMultiBlockPLOT3DReader>::New();
    //reader->SetFileName(FileName);
    QString qName(FileName);
    int indexDot = qName.lastIndexOf(".");
    qName = qName.left(indexDot);
    qName += ".q";
    reader->SetXYZFileName(FileName);
    reader->SetQFileName(qName.toLatin1().data());
    reader->AutoDetectFormatOn();
    reader->Update();

    //拿到文件中所有的数据块
    auto multidataset = reader->GetOutput();
    getBlocks(multidataset);
    vtkSmartPointer<vtkAppendFilter> appendFilter = vtkSmartPointer<vtkAppendFilter>::New();
    for (int i = 0; i < _blockList.size(); i++)
    {
        if (!_visibleStates[i]) continue;
        auto dataset = _blockList.at(i);

        appendFilter->AddInputData(dataset);
    }
    appendFilter->Update();

    //拷贝数据
    vtkUnstructuredGrid* output = vtkUnstructuredGrid::GetData(outputVector);
    output->CopyStructure(appendFilter->GetOutput());
    output->GetPointData()->PassData(appendFilter->GetOutput()->GetPointData());
    output->GetCellData()->PassData(appendFilter->GetOutput()->GetCellData());

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


int Plot3DReaderAlgorithm::ProcessRequest(vtkInformation* request,
                                          vtkInformationVector** inputVector,
                                          vtkInformationVector* outputVector)
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

void Plot3DReaderAlgorithm::getBlocks(vtkDataObject* blockData)
{
    auto block = vtkMultiBlockDataSet::SafeDownCast(blockData);

    if (block == nullptr)
    {
        auto dataset = vtkDataSet::SafeDownCast(blockData);
        if (dataset == nullptr) return;
        dataset->Modified();
        _blockList.append(dataset);
        return;
    }

    block->Modified();
    const int nBlock = block->GetNumberOfBlocks();

    for (int i = 0; i < nBlock; i++)
    {
        vtkDataObject* obj = block->GetBlock(i);
        getBlocks(obj);
    }
}

int Plot3DReaderAlgorithm::getNumberOfBlocks()
{
    return _blockList.size();
}

void Plot3DReaderAlgorithm::setVisible(int blockIndex, bool vis)
{
    if (blockIndex >= MAXBLOCKNUM) return;
    _visibleStates[blockIndex] = vis;
}

QStringList Plot3DReaderAlgorithm::getBlockNames()
{
    QStringList names{};
    const int n = getNumberOfBlocks();
    for (int i =0;i<n; ++i)
    {
        names.append(QString("Zone_%1").arg(i + 1));
    }
    return names;
}

QStringList Plot3DReaderAlgorithm::getBlockBCTypes()
{
    QStringList names{};
    const int n = getNumberOfBlocks();
    for (int i = 0; i < n; ++i)
    {
        names.append("None");
    }
    return names;
}

int Plot3DReaderAlgorithm::FillOutputPortInformation(int nPort, vtkInformation* info)
{
    Q_UNUSED(nPort)
    info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkUnstructuredGrid");
    return 1;
}


