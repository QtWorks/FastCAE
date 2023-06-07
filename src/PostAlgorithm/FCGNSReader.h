#ifndef _FCGNSREADER_H__
#define _FCGNSREADER_H__

#include <vtkMultiBlockDataSetAlgorithm.h>

class FCGNSReader : public vtkMultiBlockDataSetAlgorithm {
public:
	static FCGNSReader* New();
	vtkTypeMacro(FCGNSReader, vtkMultiBlockDataSetAlgorithm);
	void PrintSelf(ostream& os, vtkIndent indent) override;

	/**@name Getter和Setter宏
	 * 相当于setter/getter，同vtkSetMacro(FileName, char*)/vtkGetMacro(FileName, char*)
	 * @{
	 */
	vtkSetStringMacro(FileName);
	vtkGetStringMacro(FileName);
	//@}

	int	 ProcessRequest(vtkInformation* request, vtkInformationVector** inputVector,
						vtkInformationVector* outputVector) override;
	int	 RequestData(vtkInformation*, vtkInformationVector**, vtkInformationVector*) override;

	/**
	 * @brief 检测指定文件是否可以被正常读取（包括文件格式、CGNS库版本号）
	 */
	bool canReadFile();

	void setReadBC(bool read);

	bool isReadBC();

private:
	FCGNSReader();
	~FCGNSReader();
	/**
	 * @brief 读取CGNS文件的单个zone
	 * @param[in] fileIndex 文件的索引号
	 * @param[in] baseIndex base的索引号（从1开始）
	 * @param[in] zoneIndex zone的索引号（从1开始）
	 * @param[out] output
	 * @since 2.5.0
	 */
	void readZone(int fileIndex, int baseIndex, int zoneIndex, vtkMultiBlockDataSet* output);

protected:
	char* FileName;
	bool  _readBC{ true };
};

#endif