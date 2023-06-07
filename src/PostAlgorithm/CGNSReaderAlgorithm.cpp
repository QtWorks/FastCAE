#include "CGNSReaderAlgorithm.h"
// #include <vtkCGNSReader.h>
#include <vtkAppendFilter.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkSmartPointer.h>
// #include <vtkDataSetMapper.h>
#include <vtkCellData.h>
#include <vtkDataArray.h>
#include <vtkDataSet.h>
#include <vtkDemandDrivenPipeline.h>
#include <vtkDoubleArray.h>
#include <vtkFieldData.h>
#include <vtkInformation.h>
#include <vtkPointData.h>
#include <vtkStreamingDemandDrivenPipeline.h>
#include <vtkUnstructuredGrid.h>
// #include <vtkCGNSFileSeriesReader.h>
#include "FCGNSReader.h"

#include <cgns_io.h>
#include <cgnslib.h>
#include <QDebug>
#include <vtkInformation.h>
#include <vtkInformationStringKey.h>

#define MAXBLOCKNUM 2000

CGNSReaderAlgorithm::CGNSReaderAlgorithm()
{
	this->FileName = NULL;
	// 设置输入端口的数量
	this->SetNumberOfInputPorts(0);
	// 设置输出端口的数量
	this->SetNumberOfOutputPorts(MAXBLOCKNUM + 1);

	for(int i = 0; i < MAXBLOCKNUM; ++i)
		_visibleStates.append(true);
}

CGNSReaderAlgorithm::~CGNSReaderAlgorithm()
{
	this->FileName = NULL;
}

/**
 * 许多过滤器可以在不直接提供ProcessRequest()方法的情况下实现。
 * 标准过滤器超类提供了ProcessRequest()的默认实现，该实现通过将最常见的请求转换为对特定于请求的方法的调用来实现。
 */
int CGNSReaderAlgorithm::ProcessRequest(vtkInformation* request, vtkInformationVector** inputVector,
										vtkInformationVector* outputVector)
{
	// vtkDemandDrivenPipeline::REQUEST_INFORMATION()定义请求以确保输出信息是最新的
	if(request->Has(vtkDemandDrivenPipeline::REQUEST_INFORMATION())) {
		return this->RequestInformation(request, inputVector, outputVector);
	}
	// vtkDemandDrivenPipeline::REQUEST_DATA()定义了向上游传播更新范围的请求。
	if(request->Has(vtkStreamingDemandDrivenPipeline::REQUEST_UPDATE_EXTENT())) {
		return this->RequestUpdateExtent(request, inputVector, outputVector);
	}
	// vtkDemandDrivenPipeline::REQUEST_DATA()定义请求以确保输出数据是最新的
	if(request->Has(vtkDemandDrivenPipeline::REQUEST_DATA())) {
		return this->RequestData(request, inputVector, outputVector);
	}
	return this->Superclass::ProcessRequest(request, inputVector, outputVector);
}

/**
 * @brief
 * @param[in]
 * @param[in] vtkInformationVector**包含输入管道信息。数组的每个元素代表一个输入端口。
 * 是一个vtkInformationVector，对应输入端口上连接的输入管道信息对象。
 * @param[in]
 * outputVector是一个vtkInformationVector，包含滤器的每个输出端口提供一个输出管道信息对象。
 * @note
 * 用于输入和输出的每个管道信息对象都包含一个vtkDataObject，其存储键为vtkDataObobject::DATA_OBJECT()。
 * @since 2.5.0
 */
int CGNSReaderAlgorithm::RequestData(vtkInformation*, vtkInformationVector**,
									 vtkInformationVector* outputVector)
{
	if(!this->FileName) {
		vtkErrorMacro("A FileName must be specified.");
		return 0;
	}

	_blockList.clear();
	_blockNames.clear();

	vtkMultiBlockDataSet*		 mBlock = nullptr;
	// bool useVTK = useVTKCGNSReader();

	vtkSmartPointer<FCGNSReader> reader = vtkSmartPointer<FCGNSReader>::New();
	reader->SetFileName(FileName);
	reader->Update();
	mBlock									   = reader->GetOutput();
	//     vtkSmartPointer<vtkCGNSReader> vtkReader = vtkSmartPointer<vtkCGNSReader>::New();
	//     if (useVTK)
	//     {
	//         vtkReader->SetFileName(FileName);
	//         vtkReader->Update();
	//         mBlock = vtkReader->GetOutput();
	//     }
	//     else
	//     {
	//         reader->SetFileName(FileName);
	//         reader->Update();
	//         mBlock = reader->GetOutput();
	//     }
	vtkSmartPointer<vtkAppendFilter> appFilter = vtkSmartPointer<vtkAppendFilter>::New();
	appFilter->MergePointsOn();

	if(mBlock == nullptr)
		return 0;
	getBlocks(mBlock);

	for(int i = 0; i < _blockList.size(); ++i) {
		if(!_visibleStates[i])
			continue;
		auto dataset = _blockList.at(i);

		fillPointArray(dataset);
		fillCellArray(dataset);
		appFilter->AddInputData(dataset);
	}

	appFilter->Update();

	vtkUnstructuredGrid* output = vtkUnstructuredGrid::GetData(outputVector);
	output->CopyStructure(appFilter->GetOutput());
	output->GetPointData()->PassData(appFilter->GetOutput()->GetPointData());
	output->GetCellData()->PassData(appFilter->GetOutput()->GetCellData());

	for(int i = 1; i <= _blockList.size(); i++) {
		if(i > MAXBLOCKNUM)
			break;
		auto							 data	   = _blockList.at(i - 1);
		vtkUnstructuredGrid*			 outData   = vtkUnstructuredGrid::GetData(outputVector, i);
		vtkSmartPointer<vtkAppendFilter> appFilter = vtkSmartPointer<vtkAppendFilter>::New();
		appFilter->AddInputData(data);
		appFilter->Update();
		outData->CopyStructure(appFilter->GetOutput());
		outData->GetPointData()->PassData(appFilter->GetOutput()->GetPointData());
		outData->GetCellData()->PassData(appFilter->GetOutput()->GetCellData());
		;
	}
	return 1;
}

bool CGNSReaderAlgorithm::useVTKCGNSReader()
{
	int currentFileIndex = 0;
	int OK				 = cg_open(FileName, CG_MODE_READ, &currentFileIndex);
	if(CG_OK != OK)
		return false;
	bool useVTK = false;
	int	 nBase	= 0;
	OK			= cg_nbases(currentFileIndex, &nBase);

	for(int ibase = 1; ibase <= nBase; ++ibase) {
		int zone_node_number = 0;
		cg_nzones(currentFileIndex, ibase, &zone_node_number);

		for(int izone = 1; izone <= zone_node_number; ++izone) {
			CGNS_ENUMT(ZoneType_t) zonetype;
			cg_zone_type(currentFileIndex, ibase, izone, &zonetype);
			if(zonetype == CGNS_ENUMV(Unstructured)) {
				int nSection{ 0 };
				cg_nsections(currentFileIndex, ibase, izone, &nSection);
				for(int iSec = 1; iSec <= nSection; ++iSec) {
					char	 sectionName[33] = { 0 };
					cgsize_t istart = 0, iend = 0;
					int		 nbndry = 0, iparent_flag = 0;
					CGNS_ENUMT(ElementType_t) itype;
					OK = cg_section_read(currentFileIndex, ibase, izone, iSec, sectionName, &itype,
										 &istart, &iend, &nbndry, &iparent_flag);
					if(itype >= 20) {
						cg_close(currentFileIndex);
						return true;
					}
				}
			}
		}
	}
	cg_close(currentFileIndex);
	return useVTK;
}

CGNSReaderAlgorithm* CGNSReaderAlgorithm::New()
{
	auto reader = new CGNSReaderAlgorithm;
	reader->InitializeObjectBase();
	return reader;
}

void CGNSReaderAlgorithm::PrintSelf(ostream& os, vtkIndent indent)
{
	this->Superclass::PrintSelf(os, indent);
	os << indent << "FileName:" << (this->FileName ? this->FileName : "(none)") << "\n";
}

void CGNSReaderAlgorithm::setVisible(int blockIndex, bool vis)
{
	if(blockIndex >= MAXBLOCKNUM)
		return;
	_visibleStates[blockIndex] = vis;
	//   this->Modified();
}

int CGNSReaderAlgorithm::getNumberOfBlocks()
{
	return _blockList.size();
}

QStringList CGNSReaderAlgorithm::getBlockNames()
{
	return _blockNames;
}

QStringList CGNSReaderAlgorithm::getBlockBCTypes()
{
	return _bcTypes;
}

int CGNSReaderAlgorithm::FillInputPortInformation(int, vtkInformation*)
{
	// 该算法没有输入端口
	// info->Set(vtkAlgorithm::INPUT_IS_REPEATABLE(), 1);
	// info->Set(vtkAlgorithm::INPUT_IS_OPTIONAL(), 1);
	// info->Set(vtkAlgorithm::INPUT_REQUIRED_DATA_TYPE(), "vtkDataSet");
	return 1;
}

int CGNSReaderAlgorithm::FillOutputPortInformation(int, vtkInformation* info)
{
	info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkUnstructuredGrid");
	return 1;
}

void CGNSReaderAlgorithm::getBlocks(vtkDataObject* blockData, const char* Name)
{
	auto block = vtkMultiBlockDataSet::SafeDownCast(blockData);

	if(block == nullptr) {
		auto dataset = vtkDataSet::SafeDownCast(blockData);
		if(dataset == nullptr)
			return;
		dataset->Modified();
		QString		totalName = QString::fromLocal8Bit(Name);
		QStringList NameBC	  = totalName.split("!|||!");

		if(NameBC.size() == 2) {
			_blockNames.append(NameBC.at(0));
			_bcTypes.append(NameBC.at(1));
		} else {
			_blockNames.append(totalName);
			_bcTypes.append("None");
		}

		_blockList.append(dataset);
		getPointArray(dataset);
		getCellArray(dataset);
		return;
	}

	block->Modified();
	const int nBlock = block->GetNumberOfBlocks();

	for(int i = 0; i < nBlock; i++) {
		vtkDataObject* obj		   = block->GetBlock(i);
		const char*	   currentName = block->GetMetaData(i)->Get(vtkCompositeDataSet::NAME());
		getBlocks(obj, currentName);
	}
}

void CGNSReaderAlgorithm::getPointArray(vtkDataSet* dataset)
{
	if(dataset == nullptr)
		return;

	auto pointData = dataset->GetPointData();
	if(pointData == nullptr)
		return;

	const int nPointArray = pointData->GetNumberOfArrays();
	for(int i = 0; i < nPointArray; i++) {
		const char* aName	  = pointData->GetArrayName(i);
		auto		dataArray = pointData->GetArray(aName);
		if(dataArray == nullptr)
			return; // continue;
		int aNum[2]{ 0 };
		aNum[0] = dataArray->GetNumberOfComponents();
		aNum[1] = dataArray->GetNumberOfTuples();

		if(_pointDataArray.contains(aName))
			continue;
		_pointDataArray.insert(aName, aNum);
	}
}

void CGNSReaderAlgorithm::getCellArray(vtkDataSet* dataset)
{
	if(dataset == nullptr)
		return;

	auto cellData = dataset->GetCellData();
	if(cellData == nullptr)
		return;

	const int nCellArray = cellData->GetNumberOfArrays();
	for(int i = 0; i < nCellArray; i++) {
		const char* aName	  = cellData->GetArrayName(i);
		auto		dataArray = cellData->GetArray(aName);
		if(dataArray == nullptr)
			return; // continue;
		int aNum[2]{ 0 };
		aNum[0] = dataArray->GetNumberOfComponents();
		aNum[1] = dataArray->GetNumberOfTuples();

		if(_cellDataArray.contains(aName))
			continue;
		_cellDataArray.insert(aName, aNum);
	}
}

void CGNSReaderAlgorithm::fillPointArray(vtkDataSet* dataset)
{
	Q_UNUSED(dataset)
	// 	if (dataset == nullptr) return; //continue;
	//
	// 	vtkPointData* pointData = dataset->GetPointData();
	// 	if (pointData == nullptr) return;
	//
	// 	QList<QString> pArrayNames = _pointDataArray.uniqueKeys();
	// 	for (auto name : pArrayNames)
	// 	{
	// 		QString2Char(name, cName)
	// 		vtkDataArray* array = pointData->GetArray(cName);
	// 		if (array != nullptr)continue;
	//
	// 		int* aNum = _pointDataArray.value(name);
	// 		vtkSmartPointer<vtkDoubleArray> dataArray = vtkSmartPointer<vtkDoubleArray>::New();
	// 		dataArray->SetName(cName);
	// 		dataArray->SetNumberOfComponents(aNum[0]);
	// 		dataArray->SetNumberOfTuples(aNum[1]);
	// 		dataArray->Fill(0);
	//
	// 		pointData->AddArray(dataArray);
	//	}
}

void CGNSReaderAlgorithm::fillCellArray(vtkDataSet* dataset)
{
	Q_UNUSED(dataset)
	// 	if (dataset == nullptr) return; //continue;
	//
	// 	vtkCellData* cellData = dataset->GetCellData();
	// 	if (cellData == nullptr) return;
	//
	// 	QList<QString> cArrayNames = _cellDataArray.uniqueKeys();
	// 	for (auto name : cArrayNames)
	// 	{
	// 		QString2Char(name, cName)
	// 		vtkDataArray* array = cellData->GetArray(cName);
	// 		if (array != nullptr)continue;
	//
	// 		int* aNum = _pointDataArray.value(name);
	// 		vtkSmartPointer<vtkDoubleArray> dataArray = vtkSmartPointer<vtkDoubleArray>::New();
	// 		dataArray->SetName(cName);
	// 		dataArray->SetNumberOfComponents(aNum[0]);
	// 		dataArray->SetNumberOfTuples(aNum[1]);
	// 		dataArray->Fill(0);
	//
	// 		cellData->AddArray(dataArray);
	// 	}
}
