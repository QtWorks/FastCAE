#include "DataSetIntegrationAlgorithm.h"
#include <vtkInformation.h>
#include <vtkUnstructuredGrid.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkDemandDrivenPipeline.h>
#include <vtkStreamingDemandDrivenPipeline.h>
#include <vtkSmartPointer.h>
#include <vtkPointData.h>
#include <vtkDataArray.h>
#include <vtkDoubleArray.h>
#include <vtkCellData.h>
#include <vtkAppendFilter.h>
#include <QDebug>

DataSetIntegrationAlgorithm *DataSetIntegrationAlgorithm::New()
{
	auto algo = new DataSetIntegrationAlgorithm;
	algo->InitializeObjectBase();
	return algo;
}

void DataSetIntegrationAlgorithm::PrintSelf(ostream &os, vtkIndent indent)
{
	this->Superclass::PrintSelf(os, indent);
}

DataSetIntegrationAlgorithm::DataSetIntegrationAlgorithm()
{
	this->SetNumberOfInputPorts(1);
	this->SetNumberOfOutputPorts(1);
}

DataSetIntegrationAlgorithm::~DataSetIntegrationAlgorithm()
{
}

int DataSetIntegrationAlgorithm::FillInputPortInformation(int port, vtkInformation *info)
{
	info->Set(vtkAlgorithm::INPUT_REQUIRED_DATA_TYPE(), "vtkMultiBlockDataSet");
	return 1;
}

int DataSetIntegrationAlgorithm::FillOutputPortInformation(int port, vtkInformation *info)
{
	info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkUnstructuredGrid");
	return 1;
}

int DataSetIntegrationAlgorithm::ProcessRequest(vtkInformation *request, vtkInformationVector **inputVector, vtkInformationVector *outputVector)
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

int DataSetIntegrationAlgorithm::RequestData(vtkInformation *request, vtkInformationVector **inputVector, vtkInformationVector *outputVector)
{
	vtkMultiBlockDataSet *inputData = vtkMultiBlockDataSet::GetData(inputVector[0]);
	vtkUnstructuredGrid *outputData = vtkUnstructuredGrid::GetData(outputVector);

	if (inputData == nullptr)
	{
		vtkErrorMacro("InputData is error.");
		return 0;
	}

	vtkSmartPointer<vtkAppendFilter> appFliter = vtkSmartPointer<vtkAppendFilter>::New();
	appFliter->MergePointsOn();
	getBlocks(inputData);

	for (auto dataset : _blockList)
	{
		fillPointArray(dataset);
		fillCellArray(dataset);
		appFliter->AddInputData(dataset);
	}

	appFliter->Update();

	outputData->CopyStructure(appFliter->GetOutput());
	outputData->GetPointData()->PassData(appFliter->GetOutput()->GetPointData());
	outputData->GetCellData()->PassData(appFliter->GetOutput()->GetCellData());

	return 1;
}

void DataSetIntegrationAlgorithm::getBlocks(vtkDataObject *blockData)
{
	auto block = vtkMultiBlockDataSet::SafeDownCast(blockData);

	if (block == nullptr)
	{
		auto dataset = vtkDataSet::SafeDownCast(blockData);
		if (dataset == nullptr)
			return;
		dataset->Modified();

		_blockList.append(dataset);

		getPointArray(dataset);
		getCellArray(dataset);

		return;
	}

	block->Modified();
	const int nBlock = block->GetNumberOfBlocks();

	for (int i = 0; i < nBlock; i++)
	{
		vtkDataObject *obj = block->GetBlock(i);
		getBlocks(obj);
	}
}

void DataSetIntegrationAlgorithm::getPointArray(vtkDataSet *dataset)
{
	if (dataset == nullptr)
		return;

	auto pointData = dataset->GetPointData();
	if (pointData == nullptr)
		return;

	const int nPointArray = pointData->GetNumberOfArrays();
	for (int i = 0; i < nPointArray; i++)
	{
		const char *aName = pointData->GetArrayName(i);
		auto dataArray = pointData->GetArray(aName);
		if (dataArray == nullptr)
			return; // continue;
		int aNum[2]{0};
		aNum[0] = dataArray->GetNumberOfComponents();
		aNum[1] = dataArray->GetNumberOfTuples();

		if (_pointDataArray.contains(aName))
			continue;
		_pointDataArray.insert(aName, aNum);
	}
}

void DataSetIntegrationAlgorithm::getCellArray(vtkDataSet *dataset)
{
	if (dataset == nullptr)
		return;

	auto cellData = dataset->GetCellData();
	if (cellData == nullptr)
		return;

	const int nCellArray = cellData->GetNumberOfArrays();
	for (int i = 0; i < nCellArray; i++)
	{
		const char *aName = cellData->GetArrayName(i);
		auto dataArray = cellData->GetArray(aName);
		if (dataArray == nullptr)
			return; // continue;
		int aNum[2]{0};
		aNum[0] = dataArray->GetNumberOfComponents();
		aNum[1] = dataArray->GetNumberOfTuples();

		if (_cellDataArray.contains(aName))
			continue;
		_cellDataArray.insert(aName, aNum);
	}
}

void DataSetIntegrationAlgorithm::fillPointArray(vtkDataSet *dataset)
{
	if (dataset == nullptr)
		return; // continue;

	vtkPointData *pointData = dataset->GetPointData();
	if (pointData == nullptr)
		return;

	QList<QString> pArrayNames = _pointDataArray.uniqueKeys();
	for (auto name : pArrayNames)
	{
		QByteArray ba = name.toLatin1();
		char *cName = ba.data();
		vtkDataArray *array = pointData->GetArray(cName);
		if (array != nullptr)
			continue;

		int *aNum = _pointDataArray.value(name);
		vtkSmartPointer<vtkDoubleArray> dataArray = vtkSmartPointer<vtkDoubleArray>::New();
		dataArray->SetName(cName);
		dataArray->SetNumberOfComponents(aNum[0]);
		dataArray->SetNumberOfTuples(aNum[1]);
		dataArray->Fill(0);

		pointData->AddArray(dataArray);
	}
}

void DataSetIntegrationAlgorithm::fillCellArray(vtkDataSet *dataset)
{
	if (dataset == nullptr)
		return; // continue;

	vtkCellData *cellData = dataset->GetCellData();
	if (cellData == nullptr)
		return;

	QList<QString> cArrayNames = _cellDataArray.uniqueKeys();
	for (auto name : cArrayNames)
	{
		QByteArray ba = name.toLatin1();
		char *cName = ba.data();
		vtkDataArray *array = cellData->GetArray(cName);
		if (array != nullptr)
			continue;

		int *aNum = _pointDataArray.value(name);
		vtkSmartPointer<vtkDoubleArray> dataArray = vtkSmartPointer<vtkDoubleArray>::New();
		dataArray->SetName(cName);
		dataArray->SetNumberOfComponents(aNum[0]);
		dataArray->SetNumberOfTuples(aNum[1]);
		dataArray->Fill(0);

		cellData->AddArray(dataArray);
	}
}
