#include "NastranH5Reader.h"
#include <fstream>
#include <H5Exception.h>

Hdf5IOBase::Hdf5IOBase(std::string fileName) : m_FileName(fileName)
{

}


bool Hdf5IOBase::exists() const
{
	if (m_FileName.empty()) {
		return false;
	}
	std::ifstream f(m_FileName.c_str());
	return f.good();
}

bool Hdf5IOBase::isHdf5File() const
{
	if (m_FileName.empty()) {
		return false;
	}
	return H5::H5File::isHdf5(m_FileName);
}

int Hdf5IOBase::getFreeSpace() const
{
	if (nullptr != m_Hdf5File) {
		return m_Hdf5File->getFreeSpace();
	}
	else {
		return -1;
	}
}

int Hdf5IOBase::getFileSize() const
{
	if (nullptr != m_Hdf5File) {
		return m_Hdf5File->getFileSize();
	}
	else {
		return -1;
	}
}

int Hdf5IOBase::getNumObjs() const
{
	if (nullptr != m_Hdf5File) {
		return m_Hdf5File->getNumObjs();
	}
	return 0;
}

std::string Hdf5IOBase::getobjnameByIdx(int id) const
{
	if (nullptr != m_Hdf5File) {
		return m_Hdf5File->getObjnameByIdx(id);
	}
	return "";
}

bool Hdf5IOBase::closeFile()
{
	if (nullptr != m_Hdf5File) {
		m_Hdf5File->close();
		delete m_Hdf5File;
		m_Hdf5File = nullptr;
	}
	return true;
}


Hdf5Reader::Hdf5Reader(std::string fileName) : Hdf5IOBase(fileName)
{
}

std::list<MemberInfo*> Hdf5Reader::getGroupMemberInfo(std::string groupPath)
{
	std::list<MemberInfo*> infos = {};
	bool flag = false;
	if (exists() && isHdf5File())
	{
		//m_Hdf5File = new H5::H5File(m_FileName, H5F_ACC_RDONLY);
		flag = openFile();
	}
	if (!flag)
		return infos;
	H5::Group group = m_Hdf5File->openGroup(groupPath);
	hsize_t objes = group.getNumObjs();
	hsize_t i = 0;
	while (i < objes)
	{
		std::string name = group.getObjnameByIdx(i);
		std::string type = "";
		if (group.getObjTypeByIdx(i) == H5O_TYPE_DATASET)
			type = "Dataset";
		else if (group.getObjTypeByIdx(i) == H5O_TYPE_NAMED_DATATYPE)
			type = "Named_Datatype";
		else if (group.getObjTypeByIdx(i) == H5O_TYPE_NTYPES)
			type = "Ntypes";
		else if (group.getObjTypeByIdx(i) == H5O_TYPE_UNKNOWN)
			type = "Unknown";
		else if (group.getObjTypeByIdx(i) == H5O_TYPE_GROUP)
			type = "Group";
		else
			type = "Map";
		infos.push_back(new MemberInfo(name, type));
		i++;
	}
	group.close();
	closeFile();
	//m_Hdf5File = nullptr;
	return infos;
}

std::list<MemberInfo*> Hdf5Reader::getDataSetMemberInfo(std::string groupPath, std::string dataSetName)
{
	std::list<MemberInfo*> infos = {};
	std::string name = "";
	std::string type = "";
	int size = 0;
	bool flag = false;
	if (exists() && isHdf5File())
	{
		//m_Hdf5File = new H5::H5File(m_FileName, H5F_ACC_RDONLY);
		flag = openFile();
	}
	if (!flag)
		return infos;
	H5::Group group = m_Hdf5File->openGroup(groupPath);
	H5::DataSet dataset = group.openDataSet(dataSetName);
	H5::EnumType enumtype = dataset.getEnumType();
	H5::CompType comptype = dataset.getCompType();

	int num = enumtype.getNmembers();
	hsize_t i = 0;
	if (num)
	{
		for (int i = 0; i < num; i++)
		{
			name = comptype.getMemberName(i);
			H5::DataType m_datatype = comptype.getMemberDataType(i);
			H5::CompType m_comptype = comptype.getMemberCompType(i);
			H5::ArrayType m_arraytype = comptype.getMemberArrayType(i);
			size = m_comptype.getSize() / 8;

			if (m_datatype.getClass() == H5T_INTEGER)
				type = "64-bit integer";
			else if (m_datatype.getClass() == H5T_FLOAT)
				type = "64-bit floating-point";
			else if (m_datatype.getClass() == H5T_ARRAY)
			{
				type = "Array [";
				type += std::to_string(size);
				if (m_arraytype.detectClass(H5T_FLOAT))
					type = "] 64-bit floating-point";
				if (m_arraytype.detectClass(H5T_INTEGER))
					type += "] 64-bit integer";
			}
			else
			{
				type = "String, length=";
				type += std::to_string(size);
			}
			infos.push_back(new MemberInfo(name, type, size));
			m_datatype.close();
			m_comptype.close();
		}
	}
	enumtype.close();
	comptype.close();
	dataset.close();
	group.close();
	m_Hdf5File = nullptr;
	return infos;
}

std::string Hdf5Reader::getError()
{
	return m_ErrorMessage;
}

bool Hdf5Reader::openFile()
{
	if (exists() && isHdf5File())
	{
        m_Hdf5File = new H5::H5File(m_FileName, H5F_ACC_RDONLY);
        return true;
	}
	else
	{
		return false;
	}
}

bool Hdf5Reader::getType(std::string groupPath, const std::string datasetName, H5::DataType &datatype)
{
	if (groupPath.empty() || datasetName.empty()) {
		m_ErrorMessage = "组路径和数据集名称不能为空！";
		return false;
	}
	if (!openFile()) {
		m_ErrorMessage = "打开文件失败！";
		return false;
	}
	H5::Group group = m_Hdf5File->openGroup(groupPath);
	H5::DataSet dataSet = group.openDataSet(datasetName);
	datatype = dataSet.getDataType();
	dataSet.close();
	group.close();
	closeFile();
	return true;
}

MemberInfo::MemberInfo(std::string name, std::string type, int arraySize)
	: m_Name(name), m_Type(type), m_ArraySize(arraySize)
{

}

void MemberInfo::setName(std::string name)
{
	m_Name = name;
}

std::string MemberInfo::getName()
{
	return m_Name;
}

void MemberInfo::setType(std::string type)
{
	m_Type = type;
}

std::string MemberInfo::getType()
{
	return m_Type;
}

void MemberInfo::setArraySize(int size)
{
	m_ArraySize = size;
}

int MemberInfo::getArraySize()
{
	return m_ArraySize;
}

NastranH5Reader::NastranH5Reader(std::string fileName) : Hdf5Reader(fileName) {

}

std::vector<InputNodeGrid> NastranH5Reader::getNodes()
{
	std::vector<InputNodeGrid> dataVector = {};
	dataVector.clear();
	std::string groupPath = m_NodeGroupPath;
	std::string dataSetName = "GRID";
	getData(groupPath, dataSetName, dataVector);
	return dataVector;
}

std::list<std::string> NastranH5Reader::getElementType()
{
	std::list<std::string> types = {};
	auto groupInfo = getGroupMemberInfo(m_ElementsGroupPath);
	for (auto info : groupInfo)
	{
		types.push_back(info->getName());
	}
	return types;
}

std::vector<InputElementCbar> NastranH5Reader::getElementCbar()
{
	std::vector<InputElementCbar> data = {};
	if (getElements("CBAR", data))
	{
		return data;
	}
	else
	{
		return data;
	}
}

std::vector<InputElementCrod> NastranH5Reader::getElementCrod()
{
	std::vector<InputElementCrod> data = {};
	if (getElements("CROD", data))
	{
		return data;
	}
	else
	{
		return data;
	}
}

std::vector<InputElementCquad4> NastranH5Reader::getElementCquad4()
{
	std::vector<InputElementCquad4> data = {};
	if (getElements("CQUAD4", data))
	{
		return data;
	}
	else
	{
		return data;
	}
}

std::vector<InputElementCquad8> NastranH5Reader::getElementCquad8()
{
	std::vector<InputElementCquad8> data = {};
	if (getElements("CQUAD8", data))
	{
		return data;
	}
	else
	{
		return data;
	}
}

std::vector<InputElementCtetra> NastranH5Reader::getElementCtetra()
{
	std::vector<InputElementCtetra> data = {};
	if (getElements("CTETRA", data))
	{
		return data;
	}
	else
	{
		return data;
	}
}
std::vector<InputElementChexa> NastranH5Reader::getElementChexa()
{
	std::vector<InputElementChexa> data = {};
	if (getElements("CHEXA", data))
	{
		return data;
	}
	else
	{
		return data;
	}
}

std::vector<ResultElementalStressBars> NastranH5Reader::getElementalResultBars()
{
	std::vector<ResultElementalStressBars> data = {};
	if (getElementalResult("BARS", data))
	{
		return data;
	}
	else
	{
		return data;
	}
}

std::vector<ResultElementalStressRod> NastranH5Reader::getElementalResultRod()
{
	std::vector<ResultElementalStressRod> data = {};
	if (getElementalResult("ROD", data))
	{
		return data;
	}
	else
	{
		return data;
	}
}

std::vector<ResultElementalStressQuad> NastranH5Reader::getElementalResultQuad4()
{
	std::vector<ResultElementalStressQuad> data = {};
	if (getElementalResult("QUAD_CN", data))
	{
		return data;
	}
	else
	{
		return data;
	}
}

std::vector<ResultElementalStressQuad> NastranH5Reader::getElementalResultQuad8()
{
	std::vector<ResultElementalStressQuad> data = {};
	if (getElementalResult("QUAD8", data))
	{
		return data;
	}
	else
	{
		return data;
	}
}

std::vector<ResultElementalStressTetra> NastranH5Reader::getElementalResultTetra()
{
	std::vector<ResultElementalStressTetra> data = {};
	if (getElementalResult("TETRA", data))
	{
		return data;
	}
	else
	{
		return data;
	}
}

std::vector<ResultElementalStressHexa> NastranH5Reader::getElementalResultHexa()
{
	std::vector<ResultElementalStressHexa> data = {};
	if (getElementalResult("HEXA", data))
	{
		return data;
	}
	else
	{
		return data;
	}
}

std::vector<ResultNodalDisplacement> NastranH5Reader::getNodalResult(std::string name)
{
	std::vector<ResultNodalDisplacement> dataVector = {};
	dataVector.clear();
	std::string dataSetName = name;
	std::list<MemberInfo*> infos = getGroupMemberInfo(m_NodalResultGroupPath);
	for (auto info : infos)
	{
		if (info->getName() == name)
		{
			getData(m_NodalResultGroupPath, dataSetName, dataVector);
			return dataVector;
		}

	}
	m_ErrorMessage = "数据集名不正确或者组内不存在该数据集！";
	return dataVector;
}

H5::DataType NastranH5Reader::getNodesType()
{
	H5::DataType datatype = H5::DataType();
	std::string datasetName = "GRID";
	bool flag = false;
	flag = getType(m_NodeGroupPath, datasetName, datatype);
	if (flag)
		return datatype;
	else
		return datatype;
}

H5::DataType NastranH5Reader::getElementCtetraType()
{
	H5::DataType datatype = H5::DataType();
	std::string datasetName = "CTETRA";
	bool flag = false;
	flag = getType(m_ElementsGroupPath, datasetName, datatype);
	if (flag)
		return datatype;
	else
		return datatype;
}

H5::DataType NastranH5Reader::getElementalResultTetraType()
{
	H5::DataType datatype = H5::DataType();
	std::string datasetName = "TETRA";
	bool flag = false;
	flag = getType(m_ElementalResultGroupPath, datasetName, datatype);
	if (flag)
		return datatype;
	else
		return datatype;
}

H5::DataType NastranH5Reader::getNodalResultType()
{
	H5::DataType datatype = H5::DataType();
	std::string datasetName = "DISPLACEMENT";
	bool flag = false;
	flag = getType(m_NodalResultGroupPath, datasetName, datatype);
	if (flag)
		return datatype;
	else
		return datatype;
}
