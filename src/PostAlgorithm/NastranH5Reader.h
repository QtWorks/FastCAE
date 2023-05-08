/**
 * @file NastranH5Reader.h
 * @brief NastranH5Reader
 * @author 闫智慧(chanyuantiandao@126.com)
 * @version 1.0.0
 * @date 2022-07-18 11:38:28
 */
#ifndef NastranH5Reader_H
#define NastranH5Reader_H

#include "H5Cpp.h"
#include <vector>
#include <list>

/**
 * @brief 类型定义，对应64-bit integer
 * @since 1.0.0
 */
typedef long long int Type64BitInt;
/**
* @brief 类型定义，对应64-bit floating-point
* @since 1.0.0
*/
typedef double Type64BitFloatPoint;
/**
* @brief 类型定义，对应String
* @since 1.0.0
*/
typedef char TypeString;

/**
* @brief 单元数据基类
* @since 1.0.0
*/
class InputElementBase {
public:
   Type64BitInt EID;
   Type64BitInt PID;
};
/**
* @brief CROD数据单元类
* @since 1.0.0
*/
class InputElementCrod : public InputElementBase {
public:
   Type64BitInt G[2];
   Type64BitInt DOMAIN_ID;
};
/**
* @brief CBAR单元数据类
* @since 1.0.0
*/
class InputElementCbar : public InputElementBase {
public:
   Type64BitInt GA;
   Type64BitInt GB;
   Type64BitInt FLAG;
   Type64BitFloatPoint X1;
   Type64BitFloatPoint X2;
   Type64BitFloatPoint X3;
   Type64BitInt GO;
   Type64BitInt PA;
   Type64BitInt PB;
   Type64BitFloatPoint W1A;
   Type64BitFloatPoint W2A;
   Type64BitFloatPoint W3A;
   Type64BitFloatPoint W1B;
   Type64BitFloatPoint W2B;
   Type64BitFloatPoint W3B;
   Type64BitInt DOMAIN_ID;
};

/**
* @brief CQUAD4单元数据类
* @since 1.0.0
*/
class InputElementCquad4 :public InputElementBase {
public:
   Type64BitInt G[4];
   Type64BitFloatPoint THETA;
   Type64BitFloatPoint ZOFFS;
   Type64BitInt TFLAG;
   Type64BitFloatPoint T[4];
   Type64BitInt MCID;
   Type64BitInt DOMAIN_ID;
};
/**
* @brief CQUAD8单元数据类
* @since 1.0.0
*/
class InputElementCquad8 :public InputElementBase {
public:
   Type64BitInt G[8];
   Type64BitFloatPoint T[4];
   Type64BitFloatPoint THETA;
   Type64BitFloatPoint ZOFFS;
   Type64BitInt TFLAG;
   Type64BitInt MCID;
   Type64BitInt DOMAIN_ID;
};

/**
* @brief CTRTRA单元数据类
* @since 1.0.0
*/
class InputElementCtetra : public InputElementBase {
public:
   Type64BitInt G[10];
   Type64BitInt DOMAIN_ID;
};
/**
* @brief CHEXA单元数据类
* @since 1.0.0
*/
class InputElementChexa : public InputElementBase {
public:
   Type64BitInt G[20];
   Type64BitInt DOMAIN_ID;
};

/**
* @brief GRID节点数据类
* @since 1.0.0
*/
class InputNodeGrid {
public:
   Type64BitInt ID;
   Type64BitInt CP;
   Type64BitFloatPoint X[3];
   Type64BitInt CD;
   Type64BitInt PS;
   Type64BitInt SEID;
   Type64BitInt DOMAIN_ID;
};

/**
* @brief 应力数据基类【静力分析】
* @since 1.0.0
*/
class ResultElementalStressBase {
public:
   Type64BitInt EID;
};

/**
* @brief 应用数据类【静力分析】
* @since 1.0.0
*/
class ResultElementalStressBars : public ResultElementalStressBase {
public:
   Type64BitFloatPoint SD;
   Type64BitFloatPoint XC;
   Type64BitFloatPoint XD;
   Type64BitFloatPoint XE;
   Type64BitFloatPoint XF;
   Type64BitFloatPoint AX;
   Type64BitFloatPoint MAX;
   Type64BitFloatPoint MIN;
   Type64BitFloatPoint MS;
   Type64BitInt DOMAIN_ID;
};
/**
* @brief 应用数据类【静力分析】
* @since 1.0.0
*/
class ResultElementalStressRod : public ResultElementalStressBase {
public:
   Type64BitFloatPoint A;
   Type64BitFloatPoint MSA;
   Type64BitFloatPoint T;
   Type64BitFloatPoint MST;
   Type64BitInt DOMAIN_ID;
};
/**
* @brief 应用数据类【静力分析】
* @since 1.0.0
*/
class ResultElementalStressQuad : public ResultElementalStressBase {
public:
   TypeString TERM[4];
   Type64BitInt GRID[5];
   Type64BitFloatPoint FD1[5];
   Type64BitFloatPoint X1[5];
   Type64BitFloatPoint Y1[5];
   Type64BitFloatPoint TXY1[5];
   Type64BitFloatPoint FD2[5];
   Type64BitFloatPoint X2[5];
   Type64BitFloatPoint Y2[5];
   Type64BitFloatPoint TXY2[5];
   Type64BitInt DOMAIN_ID;
};
/**
* @brief 应力数据类【静力分析】
* @since 1.0.0
*/
class ResultElementalStressTetra : public ResultElementalStressBase {
public:
   Type64BitInt CID;
   TypeString CTYPE[4];
   Type64BitInt NODEF;
   Type64BitInt GRID[5];
   Type64BitFloatPoint X[5];
   Type64BitFloatPoint Y[5];
   Type64BitFloatPoint Z[5];
   Type64BitFloatPoint TXY[5];
   Type64BitFloatPoint TYZ[5];
   Type64BitFloatPoint TZX[5];
   Type64BitInt DOMAIN_ID;
};
/**
* @brief 应力数据类【静力分析】
* @since 1.0.0
*/
class ResultElementalStressHexa : public ResultElementalStressBase {
public:
   Type64BitInt CID;
   TypeString CTYPE[4];
   Type64BitInt NODEF;
   Type64BitInt GRID[9];
   Type64BitFloatPoint X[9];
   Type64BitFloatPoint Y[9];
   Type64BitFloatPoint Z[9];
   Type64BitFloatPoint TXY[9];
   Type64BitFloatPoint TYZ[9];
   Type64BitFloatPoint TZX[9];
   Type64BitInt DOMAIN_ID;
};


/**
* @brief 位移数据类【静力分析】
* @since 1.0.0
*/
class ResultNodalDisplacement {
public:
   Type64BitInt ID;
   Type64BitFloatPoint X;
   Type64BitFloatPoint Y;
   Type64BitFloatPoint Z;
   Type64BitFloatPoint RX;
   Type64BitFloatPoint RY;
   Type64BitFloatPoint RZ;
   Type64BitInt DOMAIN_ID;
};
/**
* @brief 节点约束类【静力分析】
* @since 1.0.0
*/
class ResultNodalSpc_force {
public:
   Type64BitInt ID;
   Type64BitFloatPoint X;
   Type64BitFloatPoint Y;
   Type64BitFloatPoint Z;
   Type64BitFloatPoint RX;
   Type64BitFloatPoint RY;
   Type64BitFloatPoint RZ;
   Type64BitInt DOMAIN_ID;
};
/**
* @brief 单元类型
* @since 1.0.0
*/
enum class ElementType : int
{
   UNDEFINED = 0,		///< 未定义的
   CROD,				///< CROD单元【1D】，连接两个节点，横截面的属性不变
   CTUBE,				///< CTUBE单元【1D】
   CBEND,
   CBAR,
   CBEAM,
   CVISC,
   CQUAD4,				///< 四边形壳单元【2D】
   CQUAD8,
   CTRIA3,
   CTRIA6,
   CSHEAR,
   CRAC2D,
   CTETRA,				///< 【3D】
   CPENTA,
   CHEXA,
   CTRIAX6,
   CTRIAX,
   CQUADX,
};

class Hdf5IOBase
{
public:
	/**
	 * @brief 构造函数
	 * @param fileName 文件的名称
	 * @since 1.0.0
	 */
	Hdf5IOBase(std::string fileName);
	/**
	 * @brief 析构造函数
	 * @since 1.0.0
	 */
    virtual ~Hdf5IOBase() = default;

	/**
	 * @brief 判断文件名称的合法性
	 * @return 合法返回true，不合法返回false
	 * @since 1.0.0
	 */
	bool exists() const;
	/**
	 * @brief 判断文件名是否为空
	 * @return 空返回false，非空返回true
	 * @since 1.0.0
	 */
	bool isHdf5File() const;
	/**
	 * @brief 判断剩余空间
	 * @return 返回剩余空间
	 * @since 1.0.0
	 */
	int getFreeSpace() const;
	/**
	 * @brief 读取文件的大小
	 * @return 返回文件的大小
	 * @since 1.0.0
	 */
	int getFileSize() const;
	/**
	 * @brief 获取当前目录下的对象数
	 * @return 返回对象数
	 * @since 1.0.0
	 */
	int getNumObjs() const;
	/**
	 * @brief 通过id获取对象的名字
	 * @param id 对象的相对位置
	 * @return 返回id相应对象的名字
	 * @since 1.0.0
	 */
	std::string getobjnameByIdx(int id) const;
	/**
	 * @brief 打开文件
	 * @return 打开成功返回true，打开失败返回false
	 * @since 1.0.0
	 */
	virtual bool openFile() = 0;
	/**
	 * @brief 关闭文件
	 * @return 关闭成功返回true，关闭失败返回false
	 * @since 1.0.0
	 */
	virtual bool closeFile();


protected:
	/**
	 * @brief 文件名称（含路径）
	 * @since 1.0.0
	 */
	std::string m_FileName = "";
	/**
	 * @brief 指向文件地址的指针
	 * @since 1.0.0
	 */
	H5::H5File* m_Hdf5File = nullptr;
};

/**
 * @brief MemberInfo类，获取组或者数据集中成员的名字、类型、大小信息
 * @since 1.0.0
 */
class MemberInfo
{
public:
    MemberInfo(std::string name, std::string type, int arraySize = 0);
    ~MemberInfo() = default;

    void setName(std::string name);
    std::string getName();
    void setType(std::string type);
    std::string getType();
    void setArraySize(int size);
    int getArraySize();
private:
    std::string m_Name = "";
    std::string m_Type = "";
    int m_ArraySize = 0;
};

/**
 * @brief Hdf5Reader类
 * @since 1.0.0
 */
class Hdf5Reader : public Hdf5IOBase
{
public:
    /**
     * @brief 构造函数
     * @param fileName
     * @since 1.0.0
     */
    Hdf5Reader(std::string fileName);
    /**
     * @brief 析构函数
     * @since 1.0.0
     */
    virtual ~Hdf5Reader() override = default;

    /**
     * @brief 读取表格数据
     * @param groupPath 组的路径
     * @param dataSetName 数据集（表）的名称
     * @param dataVector 存储返回的数据
     * @return 成功获取数据时返回true，否则返回false
     * @since 1.0.0
     */
    template <class T>
    bool getData(std::string groupPath, std::string dataSetName, std::vector<T>& dataVector) {
        if (groupPath.empty() || dataSetName.empty()) {
            m_ErrorMessage = "组路径和数据集名称不能为空！";
            return false;
        }
        if (!openFile()) {
            m_ErrorMessage = "打开文件失败！";
            return false;
        }
        H5::Group group = m_Hdf5File->openGroup(groupPath);
        H5::DataSet dataSet = group.openDataSet(dataSetName);
        H5::DataSpace dataSpace = dataSet.getSpace();

        hsize_t dims[1];
        int num = dataSpace.getSimpleExtentDims(dims);
        H5::DataType dataType = dataSet.getDataType();
        dataVector.clear();
        dataVector.resize(dims[0]);
        dataSet.read(dataVector.data(), dataType);
        dataSet.close();
        group.close();
        closeFile();
        return true;
    }
    /**
     * @brief 返回组下的成员信息
     * @param groupPath 组的路径
     * @return 含有组下成员信息的list地址
     * @since 1.0.0
     */
    std::list<MemberInfo*> getGroupMemberInfo(std::string groupPath);
    /**
     * @brief 返回数据集下的数据信息
     * @param groupPath 组的路径
     * @param dataSetName 数据集的名称
     * @return 返回数据集下数据信息的list地址
     * @since 1.0.0
     */
    std::list<MemberInfo*> getDataSetMemberInfo(std::string groupPath, std::string dataSetName);
    /**
     * @brief 当调用函数失败后返回错误信息
     * @return 返回错误信息提示
     * @since 1.0.0
     */
    std::string getError();
    /**
     * @brief 打开文件
     * @return 打开成功返回true，打开失败返回false
     * @since 1.0.0
     */
    bool openFile() override;

    /**
     * @brief 6.15练习把得到reader提取到的数据的datatype
     * @param groupPath 组的路径
     * @param datasetName 数据集的名字
     * @param datatype 返回的数据类型
     * @return
     * @since 1.0.0
     */
    bool getType(std::string groupPath,const std::string datasetName, H5::DataType &datatype);


private:
    /**
     * @brief 保存错误信息
     * @since 1.0.0
     */
    std::string m_ErrorMessage = "";
};

class NastranH5Reader : public Hdf5Reader
{
public:
    /**
     * @brief 构造函数
     * @param fileName
     * @since 1.0.0
     */
    NastranH5Reader(std::string fileName);
    /**
     * @brief 析构函数
     * @since 1.0.0
     */
    virtual ~NastranH5Reader() override = default;

    /**
     * @brief 节点函数
     * @return vector<InputNodeGrid>
     * @since 1.0.0
     */
    std::vector<InputNodeGrid> getNodes();
    /**
     * @brief /INPUT/ELEMENTAL/下数据集的模板函数
     * @param name DatasetName
     * @param dataVector 存储容器
     * @return 读取成功返回true，读取失败返回false
     * @since 1.0.0
     */
    template <class T>
    bool getElements(std::string name, std::vector<T>& dataVector)
    {
        std::list<MemberInfo*> infos = getGroupMemberInfo(m_ElementsGroupPath);
        bool isValid = false;
        for (auto info : infos) {
            if (info->getName() == name) {
                isValid = true;
            }
        }
        if (!isValid) {
            m_ErrorMessage = "数据集名不正确或者组内不存在该数据集！";
            return false;
        }
        getData(m_ElementsGroupPath, name, dataVector);
        return true;
    }
    std::list<std::string> getElementType();
    /**
    * @brief 读取ELEMENT中一维单元CBAR函数
    * @return 返回数据集
    * @since 1.0.0
    */
    std::vector<InputElementCbar> getElementCbar();
    /**
     * @brief 读取ELEMENT中一维单元CROD函数
     * @return 返回数据集
     * @since 1.0.0
     */
    std::vector<InputElementCrod> getElementCrod();
    /**
     * @brief 读取ELEMENT中二维单元CQUAD4
     * @return 返回数据集
     * @since 1.0.0
     */
    std::vector<InputElementCquad4> getElementCquad4();
    /**
     * @brief 读取ELEMENT中二维单元CQUAD8
     * @return 返回数据集
     * @since 1.0.0
     */
    std::vector<InputElementCquad8> getElementCquad8();
    /**
     * @brief 读取ELEMENT中三维单元CTETRA
     * @return 返回数据集
     * @since 1.0.0
     */
    std::vector<InputElementCtetra> getElementCtetra();
    /**
     * @brief 读取ELEMENT中三维单元CHEXA
     * @return 返回数据集
     * @since 1.0.0
     */
    std::vector<InputElementChexa> getElementChexa();

    /**
     * @brief /RESULT/ELEMENTAL/STRESS下数据集的模板函数
     * @param name DatasetName
     * @param dataVector 存储容器
     * @return 读取成功返回true，读取失败返回false
     * @since 1.0.0
     */
    template <class T>
    bool getElementalResult(std::string name, std::vector<T>& dataVector)
    {
        std::list<MemberInfo*> infos = getGroupMemberInfo(m_ElementalResultGroupPath);
        bool isValid = false;
        for (auto info : infos) {
            if (info->getName() == name) {
                isValid = true;
            }
        }
        if (!isValid) {
            m_ErrorMessage = "数据集名不正确或者组内不存在该数据集！";
            return false;
        }
        getData(m_ElementalResultGroupPath, name, dataVector);
        return true;
    }
    /**
     * @brief 一维单元CBAR压力结果函数
     * @return 返回数据集
     * @since 1.0.0
     */
    std::vector<ResultElementalStressBars> getElementalResultBars();
    /**
    * @brief 一维单元CROD压力结果函数
     * @return 返回数据集
     * @since 1.0.0
     */
    std::vector<ResultElementalStressRod> getElementalResultRod();
    /**
    * @brief 二维单元CQUAD4压力结果函数
     * @return 返回数据集
     * @since 1.0.0
     */
    std::vector<ResultElementalStressQuad> getElementalResultQuad4();
    /**
    * @brief 二维单元CQUAD8压力结果函数
     * @return 返回数据集
     * @since 1.0.0
    */
    std::vector<ResultElementalStressQuad> getElementalResultQuad8();
    /**
    * @brief 三维单元CTETRA压力结果函数
     * @return 返回数据集
    * @since 1.0.0
    */
    std::vector<ResultElementalStressTetra> getElementalResultTetra();
    /**
    * @brief 三维单元CHEXA压力结果函数
     * @return 返回数据集
     * @since 1.0.0
    */
    std::vector<ResultElementalStressHexa> getElementalResultHexa();

    /**
     * @brief 位移结果函数
     * @param name DatasetName
     * @return 返回数据集
     * @since 1.0.0
     */
    std::vector<ResultNodalDisplacement> getNodalResult(std::string name = "");

    /**
     * @brief 节点类型函数
     * @return 返回节点数据集的数据类型
     * @since 1.0.0
     */
    H5::DataType getNodesType();
    H5::DataType getElementCtetraType();
    H5::DataType getElementalResultTetraType();
    H5::DataType getNodalResultType();

private:
    /**
     * @brief 保存错误信息
     * @since 1.0.0
     */
    std::string m_ErrorMessage = "";
    const std::string m_NodeGroupPath = "/NASTRAN/INPUT/NODE/";
    const std::string m_ElementsGroupPath = "/NASTRAN/INPUT/ELEMENT/";
    const std::string m_NodalResultGroupPath = "/NASTRAN/RESULT/NODAL/";
    const std::string m_ElementalResultGroupPath = "/NASTRAN/RESULT/ELEMENTAL/STRESS/";
};

#endif // NastranH5Reader_H
