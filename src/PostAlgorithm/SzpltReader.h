#ifndef _SZPLT_READER_H
#define  _SZPLT_READER_H
#include <vtkMultiBlockDataSetAlgorithm.h>
#include <vector>
#include <QStringList>
enum  TecVarValueLocation
{
	CELLCENTERED = 0,
	NODAL,
};
enum TecZoneType
{
	ORDERED,
	FE_LINE_SEG,
	FE_TRIANGLE,
	FE_QUAD,
	FE_TET,
	FE_BRICK,
	FE_POLYGON,//szplt not support polygon
	FE_POLYHDFRON,//szplt not support polyhedron
};


class vtkPointData;
class vtkPoints;
class vtkCellData;
class vtkUnstructuredGrid;

class SzpltReader : public vtkMultiBlockDataSetAlgorithm
{
public:
	static SzpltReader* New();
	vtkTypeMacro(SzpltReader, vtkMultiBlockDataSetAlgorithm);
	void PrintSelf(ostream& os, vtkIndent indent) override;

	vtkSetStringMacro(FileName);
	vtkGetStringMacro(FileName);

	int ProcessRequest(vtkInformation* request, vtkInformationVector** inputVector, vtkInformationVector* outputVector);
	int RequestData(vtkInformation*, vtkInformationVector**, vtkInformationVector*);	

	//The following functions are originated from vtkTecplotReader
	//Binary files can only be written in block format
	void GetArraysFromBlockPackingZone(int zoneIndex,
		int numNodes, int numCells, vtkPoints* theNodes, vtkPointData* nodeData, vtkCellData* cellData, vtkMultiBlockDataSet* multZone);


	/**
	 * This function creates a vtkStructuredGrid object made up of a set of
	 * points and the associated attributes (node-based and / or cell-based)
	 * extracted from a block-packing (i.e., component-based) zone. This
	 * vtkStructuredGrid is then inserted, with a specified zone name, to a
	 * vtkMultiBlockDataSet object.
	 */
	void GetStructuredGridFromBlockPackingZone(int iDimSize, int jDimSize, int kDimSize, int zoneIndx,
		const char* zoneName, vtkMultiBlockDataSet* multZone);

	/**
	 * This function creates a vtkUnstructuredGrid object made up of a set of
	 * points and the associated attributes (node-based and / or cell-based)
	 * extracted from a block-packing (i.e., component-based) zone. This
	 * vtkUnstructuredGrid is then inserted, with a specified zone name, to a
	 * vtkMultiBlockDataSet object.
	 */
	void GetUnstructuredGridFromBlockPackingZone(int numNodes, int numCells, int cellType,
		int zoneIndx, const char* zoneName, vtkMultiBlockDataSet* multZone);


	/**
   * This function fills an allocated vtkUnstructuredGrid object with numberCells
   * cells of type cellTypeStr to define the grid topology.
   */
	void GetUnstructuredGridCells(int zoneIndex,
		int numberCells, int cellTypeStr, vtkUnstructuredGrid* unstrctGrid, vtkMultiBlockDataSet* multZone);


private:
	SzpltReader();
	~SzpltReader();	

private:
	int NumberOfVariables;

	std::string DataTitle;
	std::vector<int> CellBased;
	std::vector<std::string> ZoneNames;
	std::vector<std::string> Variables;

	char* FileName=nullptr;
	//vtkMultiBlockDataSet* mudataset{};
	int TopologyDim;
	int GeometryDim;
	char* dataSetTitle = nullptr;
	int32_t numVars;
	QStringList varNames;
	int32_t fileType;
	int32_t numZones;
	void* inputFileHandle=nullptr;//
	std::vector <int32_t>	 shareConnectivity;
	std::vector<std::vector<std::vector<double>>> varAllZones;//store all the variables of all zones

};
#endif

