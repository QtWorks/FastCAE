#include "FCGNSReader.h"

#include "Common/DebugLogger.h"
#include "FCGNSStructureZoneReader.h"
#include "FCGNSUnStructureZoneReader.h"

#include <cgns_io.h>
#include <cgnslib.h>
#include <QFile>
#include <vtkDemandDrivenPipeline.h>
#include <vtkInformation.h>
#include <vtkInformationVector.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkSetGet.h>
#include <vtkStreamingDemandDrivenPipeline.h>

FCGNSReader* FCGNSReader::New()
{
	auto reader = new FCGNSReader;
	reader->InitializeObjectBase();
	return reader;
}

void FCGNSReader::PrintSelf(ostream& os, vtkIndent indent)
{
	Q_UNUSED(os)
	Q_UNUSED(indent)
}

FCGNSReader::FCGNSReader()
{
	this->SetNumberOfInputPorts(0);
	this->SetNumberOfOutputPorts(1);
	this->FileName = nullptr;
}

FCGNSReader::~FCGNSReader() {}

void FCGNSReader::readZone(int fileIndex, int baseIndex, int zoneIndex,
						   vtkMultiBlockDataSet* output)
{
	// 读取zonetype：Structured 或 Unstructured
	CGNS_ENUMT(ZoneType_t) zonetype;
	if(CG_OK != cg_zone_type(fileIndex, baseIndex, zoneIndex, &zonetype)){
		DebugError("Failed to read zone(index = %d) type\n", zoneIndex);
		return;
	}
		
	if(zonetype == CGNS_ENUMV(Structured)) {
		FCGNSStructeGridReader r(output);
		r.setInfo(fileIndex, baseIndex, zoneIndex);
		r.setReadBC(_readBC);
		r.read();
	} else if(zonetype == CGNS_ENUMV(Unstructured)) {
		FCGNSUnStructeGridReader r(output);
		r.setInfo(fileIndex, baseIndex, zoneIndex);
		r.read();
	}
}

int FCGNSReader::ProcessRequest(vtkInformation* request, vtkInformationVector** inputVector,
								vtkInformationVector* outputVector)
{
	if(request->Has(vtkDemandDrivenPipeline::REQUEST_INFORMATION())) {
		return this->RequestInformation(request, inputVector, outputVector);
	}
	if(request->Has(vtkStreamingDemandDrivenPipeline::REQUEST_UPDATE_EXTENT())) {
		return this->RequestUpdateExtent(request, inputVector, outputVector);
	}
	if(request->Has(vtkDemandDrivenPipeline::REQUEST_DATA())) {
		return this->RequestData(request, inputVector, outputVector);
	}
	return this->Superclass::ProcessRequest(request, inputVector, outputVector);
}

int FCGNSReader::RequestData(vtkInformation*, vtkInformationVector**,
							 vtkInformationVector* outputVector)
{
	auto output = vtkMultiBlockDataSet::GetData(outputVector);

	bool ok		= canReadFile();
	if(!ok) {
		return 0;
	}

	// 打开文件
	int currentFileIndex = 0;
	if(CG_OK != cg_open(FileName, CG_MODE_READ, &currentFileIndex)) {
		DebugError("Failed to open file %s\n", FileName);
		return 0;
	} else {
		DebugInfo("Success to open file %s\n", FileName);
	}

	// 获取CGNS数据库的单库（CGNSBase_t）的数量，一般为1
	int nBase = 0;
	if(CG_OK != cg_nbases(currentFileIndex, &nBase)) {
		DebugError("Failed to get number of base\n");
		return 0;
	}

	// 遍历读取zone（base和zone节点的索引都是从1开始的）
	for(int ibase = 1; ibase <= nBase; ++ibase) {
		int zone_node_number = 0;
		if(CG_OK != cg_nzones(currentFileIndex, ibase, &zone_node_number)) {
			return false;
		}
		for(int izone = 1; izone <= zone_node_number; ++izone) {
			readZone(currentFileIndex, ibase, izone, output);
		}
	}
	// 关闭文件
	cg_close(currentFileIndex);
	return 1;
}

bool FCGNSReader::canReadFile()
{
	int		 cgioFile;
	bool	 ierr = true;
	double	 rootNodeId;
	double	 childId;
	float	 FileVersion	= 0.0;
	int		 intFileVersion = 0;
	char	 dataType[CGIO_MAX_DATATYPE_LENGTH + 1];
	char	 errmsg[CGIO_MAX_ERROR_LENGTH + 1];
	int		 ndim = 0;
	cgsize_t dimVals[12];
	int		 fileType	 = CGIO_FILE_NONE;
	char*	 fileTypeStr = new char[20];

	// 检查文件文件名以确定它是否是有效的数据库
	auto	 result		 = cgio_check_file(FileName, &fileType);
	if(CGIO_ERR_NONE != result || CGIO_FILE_NONE == fileType) {
		DebugError("%s is a invalid database!\n", FileName);
		return false;
	} else {
		DebugInfo("Check database: %s?\tpass!\n", FileName);
	}

	// 确定当前库是否支持fileType给出的数据库类型
	// 始终支持CGIO_FILE_ADF;如果库是用HDF5构建的，则支持CGIO_FILE_HDF5;在32位模式下构建时支持CGIO_FILE_ADF2。
	result = cgio_is_supported(fileType);
	switch(fileType) {
		case CGIO_FILE_ADF:
			strcpy(fileTypeStr, "CGIO_FILE_ADF");
			break;
		case CGIO_FILE_HDF5:
			strcpy(fileTypeStr, "CGIO_FILE_HDF5");
			break;
		case CGIO_FILE_ADF2:
			strcpy(fileTypeStr, "CGIO_FILE_ADF2");
			break;
		case CGIO_FILE_NONE:
			strcpy(fileTypeStr, "CGIO_FILE_NONE");
			break;
		default:
			fileTypeStr = "Unknown";
			break;
	}
	if(CGIO_ERR_FILE_TYPE == result) {
		DebugError("FileType: %s is not support!\n", fileTypeStr);
		return false;
	} else {
		DebugInfo("FileType: support by library?\tyes!\n");
	}

	// 打开数据库，设置数据库标识cgioFile，用于后续操作
	if(cgio_open_file(FileName, CG_MODE_READ, fileType, &cgioFile) != CG_OK) {
		cgio_error_message(errmsg);
		DebugError("Failed to open file %s, error: %s\n", FileName, errmsg);
		return 0;
	} else {
		DebugInfo("Success to open file %s, identifier = %d\n", FileName, cgioFile);
	}

	// 获取数据库中根节点的标识
	if(CG_OK != cgio_get_root_id(cgioFile, &rootNodeId)) {
		DebugError("Failed to get root node identifier of database(%d)\n", cgioFile);
		goto CloseDataBase;
	} else {
		DebugInfo("Success to get root node identifier of database(%d), identifier = %d\n",
				  cgioFile, rootNodeId);
	}

	// 为什么还要获取一次fileType？
	// cgio_get_file_type(cgioFile, &fileType);

	// 获取生成文件的CGNS动态库版本
	if(CG_OK != cgio_get_node_id(cgioFile, rootNodeId, "CGNSLibraryVersion", &childId)) {
		cgio_error_message(errmsg);
		DebugError("Failed to get CGNSLibraryVersion node, error: %s\n", errmsg);
		ierr = false;
		goto CloseDataBase;
	} else {
		DebugInfo("Success to get CGNSLibraryVersion node, identifier = %f\n", childId);
	}

	// 获取CGNSLibraryVersion节点的数据类型（ "MT", "I4", "I8", "U4", "U8", "R4", "C1", "B1"）
	// "MT" 不包含数据的空节点
	// "I4" 32位整数(4字节)
	// "I8" 64位整数(8字节)
	// "U4" 32位无符号整数(4字节)
	// "U8" 64位无符号整数(8字节)
	// "R4" 32位实数(4字节)
	// "R8" 64位实数(8字节)
	// "C1" 字符
	// "B1" 无符号字节
	if(CG_OK != cgio_get_data_type(cgioFile, childId, dataType)) {
		cgio_error_message(errmsg);
		DebugError("Failed to get CGNSLibraryVersion value type, error: %s\n", errmsg);
		ierr = false;
		goto CloseDataBase;
	} else {
		DebugInfo("Success to get CGNSLibraryVersion value type: %s\n", dataType);
	}

	// 获取CGNSLibraryVersion节点的数据的维度
	if(CG_OK != cgio_get_dimensions(cgioFile, childId, &ndim, dimVals)) {
		cgio_error_message(errmsg);
		DebugError("Failed to get CGNSLibraryVersion value dimensions, error: %s\n", errmsg);
		ierr = false;
		goto CloseDataBase;
	} else {
		DebugInfo("Success to get CGNSLibraryVersion value dimensions, num of dimensions: %d\n",
				  ndim);
	}

	// 检查CGNSLibraryVersion节点的数据类型（float，参考cg_version函数：http://cgns.github.io/CGNS_docs_current/midlevel/fileops.html）
	if(strcmp(dataType, "R4") != 0) {
		DebugError("Unexpected data type for CGNS library version: %s\n", dataType);
		ierr = false;
		goto CloseDataBase;
	}

	// 检查CGNSLibraryVersion节点的数据的维度
	if((ndim != 1) || (dimVals[0] != 1)) {
		DebugError("Invalid data dimension for CGNS library version\n");
		ierr = false;
		goto CloseDataBase;
	}

	// 读取CGNSLibraryVersion节点的数据
	if(cgio_read_all_data_type(cgioFile, childId, "R4", &FileVersion)) {
		DebugError("An error occurred reading the CGNS library version\n");
		ierr = false;
		goto CloseDataBase;
	} else {
		DebugInfo("CGNS library version: %f\n", FileVersion);
	}

	// 检测生成CGNS文件的库版本号是否比当前版本FastCAE使用的CGNS库版本更新
	intFileVersion = static_cast<int>(FileVersion * 1000 + 0.5);

	if(intFileVersion > CGNS_VERSION) {
		// 主版本号一样的，可以读取
		if(floor(intFileVersion / 1000) > floor(CGNS_VERSION / 1000)) {
			DebugError("The file %s was written with a more newer version of the CGNS library\n",
					   FileName);
			ierr = false;
		}
		// warn only if different in second digit
		if((intFileVersion / 100) > (CGNS_VERSION / 100)) {
			vtkWarningMacro(<< "The file being read is more recent"
							   "than the CGNS library used");
		}
	}
	if((intFileVersion / 10) < 255) {
		vtkWarningMacro(<< "The file being read was written with an old version"
						   "of the CGNS library. Please update your file"
						   "to a more recent version.");
	}

CloseDataBase:
	cgio_close_file(cgioFile);
	return ierr;
}

void FCGNSReader::setReadBC(bool read)
{
	_readBC = read;
	this->Modified();
}

bool FCGNSReader::isReadBC()
{
	return _readBC;
}
