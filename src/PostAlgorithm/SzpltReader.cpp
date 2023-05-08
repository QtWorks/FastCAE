#include "SzpltReader.h"
#include <vtkInformation.h>
#include <vtkInformationVector.h>
#include <vtkDemandDrivenPipeline.h>
#include <vtkStreamingDemandDrivenPipeline.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkPoints.h>
#include <vtkPointData.h>
#include <vtkCellData.h>
#include <vtkUnstructuredGrid.h>
#include <vtkStructuredGrid.h>
#include <vtkUnsignedCharArray.h>
#include <vtkSmartPointer.h>
#include <vtkDoubleArray.h>
#include <vtkMath.h>
#include "TECIO.h"
#include <QFileInfo>
#include <QFile>
#include <QString>
#include <QDebug>



SzpltReader* SzpltReader::New()
{
    auto reader = new SzpltReader;
    reader->InitializeObjectBase();
    return reader;
}

void SzpltReader::PrintSelf(ostream& os, vtkIndent indent)
{
    Q_UNUSED(os)
    Q_UNUSED(indent)
}

SzpltReader::SzpltReader()
{
    this->SetNumberOfInputPorts(0);
    this->SetNumberOfOutputPorts(1);
    this->FileName = nullptr;
    TopologyDim = 1;
}

SzpltReader::~SzpltReader()
{
}

int SzpltReader::ProcessRequest(vtkInformation* request, vtkInformationVector** inputVector, vtkInformationVector* outputVector)
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
int SzpltReader::RequestData(vtkInformation*, vtkInformationVector**, vtkInformationVector* outputVector)
{

    auto output = vtkMultiBlockDataSet::GetData(outputVector);


    //fileName = tep_filename;
    QFileInfo info(FileName);
    if (!info.exists()) return false;
    QString name = info.fileName();
    QString path = info.filePath();

    // Open a .szplt file for reading with TECIO

    int i = tecFileReaderOpen((char const*)(FileName), &inputFileHandle);
    // Read the characteristics of the data set

    i = tecDataSetGetTitle(inputFileHandle, &dataSetTitle);

    i = tecDataSetGetNumVars(inputFileHandle, &numVars);

    for (int32_t var = 1; var <= numVars; ++var)
    {
        char* name = NULL;
        i = tecVarGetName(inputFileHandle, var, &name);
        varNames.append(QString(name));
        tecStringFree(&name);
    }

    i = tecFileGetType(inputFileHandle, &fileType);

    i = tecDataSetGetNumZones(inputFileHandle, &numZones);

    int32_t isDouble = 0;
    int32_t const FieldDataType_Double = 2; // ...TecUtil types are not available to TecIO so redefine
    if (numZones > 0)
    {
        int32_t type;
        i = tecZoneVarGetType(inputFileHandle, 1, 1, &type);
        if (type == FieldDataType_Double)
            isDouble = 1;
    }

    for (int32_t inputZone = 1; inputZone <= numZones; ++inputZone)
    {
        // Retrieve zone characteristics
        int32_t zoneType;
        i = tecZoneGetType(inputFileHandle, inputZone, &zoneType);
        if (zoneType == FE_POLYGON || zoneType == FE_POLYHDFRON)
            throw std::runtime_error("Unsupported zone type.");
        char* zoneTitle = NULL;
        i = tecZoneGetTitle(inputFileHandle, inputZone, &zoneTitle);



        int64_t iMax, jMax, kMax;
        i = tecZoneGetIJK(inputFileHandle, inputZone, &iMax, &jMax, &kMax);

        if (zoneType == ORDERED) {

            this->GetStructuredGridFromBlockPackingZone(
                        iMax, jMax, kMax, inputZone, zoneTitle, output);
        }
        else
        {
            this->GetUnstructuredGridFromBlockPackingZone(
                        iMax, jMax, zoneType, inputZone, zoneTitle, output);
        }
    }

    return 1;

}
void SzpltReader::GetArraysFromBlockPackingZone(int zoneIndex, int numNodes, int numCells, vtkPoints * theNodes,
                                                vtkPointData * nodeData, vtkCellData * cellData, vtkMultiBlockDataSet* multZone)
{
    Q_UNUSED(numCells)
    Q_UNUSED(multZone)
    if (!theNodes || !nodeData || !cellData)
    {
        qDebug() << "File not open, errors with reading, or nullptr vtkPoints /"
                 << "vtkPointData / vtkCellData.";
        return;
    }
    int i=0;

    std::vector<int32_t> varTypes(numVars);
    std::vector<int32_t> passiveVarList(numVars);
    std::vector<int32_t> valueLocation(numVars);
    std::vector<int32_t> shareVarFromZone(numVars);
    for (int32_t var = 1; var <= numVars; ++var)
    {
        i = tecZoneVarGetType(inputFileHandle, zoneIndex, var, &varTypes[var - 1]);
        i = tecZoneVarGetSharedZone(inputFileHandle, zoneIndex, var, &shareVarFromZone[var - 1]);
        i = tecZoneVarGetValueLocation(inputFileHandle, zoneIndex, var, &valueLocation[var - 1]);
        i = tecZoneVarIsPassive(inputFileHandle, zoneIndex, var, &passiveVarList[var - 1]);
    }

    std::vector<std::vector<double>> varVecs;
    for (int32_t var = 1; var <= numVars; ++var)
    {
        if (shareVarFromZone[var - 1] == 0)
        {

            int64_t numValues;
            i = tecZoneVarGetNumValues(inputFileHandle, zoneIndex, var, &numValues);
            // For large zones, could "chunk" this input/output--read/write the var in pieces instead of all at once
            switch ((FieldDataType_e)varTypes[var - 1])
            {
            case FieldDataType_Float:
            {
                std::vector<float> values(numValues);
                i = tecZoneVarGetFloatValues(inputFileHandle, zoneIndex, var, 1, numValues, &values[0]);
                varVecs.emplace_back(std::vector<double>(values.begin(), values.end()));
            }
                break;
            case FieldDataType_Double:
            {
                std::vector<double> values(numValues);
                i = tecZoneVarGetDoubleValues(inputFileHandle, zoneIndex, var, 1, numValues, &values[0]);
                varVecs.emplace_back(std::vector<double>(values.begin(), values.end()));
            }
                break;
            case FieldDataType_Int32:
            {
                std::vector<int32_t> values(numValues);
                i = tecZoneVarGetInt32Values(inputFileHandle, zoneIndex, var, 1, numValues, &values[0]);
                varVecs.emplace_back(std::vector<double>(values.begin(), values.end()));
            }
                break;
            case FieldDataType_Int16:
            {
                std::vector<int16_t> values(numValues);
                i = tecZoneVarGetInt16Values(inputFileHandle, zoneIndex, var, 1, numValues, &values[0]);
                varVecs.emplace_back(std::vector<double>(values.begin(), values.end()));
            }
                break;
            case FieldDataType_Byte:
            {
                std::vector<uint8_t> values(numValues);
                i = tecZoneVarGetUInt8Values(inputFileHandle, zoneIndex, var, 1, numValues, &values[0]);
                varVecs.emplace_back(std::vector<double>(values.begin(), values.end()));
            }
                break;
            default:
                i = -1;
                break;
            }
        }
        else
        {
            varVecs.emplace_back(varAllZones[shareVarFromZone[var - 1] - 1][var - 1]);
        }
    }
    varAllZones.emplace_back(varVecs);

    for (auto var = 1; var <= numNodes; ++var)
    {
        double coor[3] = { 0 };
        for (int j = 0; j < TopologyDim; ++j)
        {
            coor[j] = varVecs[j][var - 1];
        }
        theNodes->InsertNextPoint(coor);

    }


    //add variables to vtk grid
    for (int32_t var = TopologyDim + 1; var <= numVars; ++var)
    {
        vtkSmartPointer<vtkDoubleArray> array = vtkSmartPointer<vtkDoubleArray>::New();
        array->SetName(varNames.at(var - 1).toStdString().c_str());
        array->SetNumberOfValues(varVecs[var - 1].size());
        for (auto j = 0; j < varVecs[var - 1].size(); ++j)
        {
            array->SetValue(j, varVecs[var - 1][j]);
        }
        if (valueLocation[var - 1] == NODAL)
        {
            nodeData->AddArray(array);
        }
        if (valueLocation[var - 1] == CELLCENTERED)
        {
            cellData->AddArray(array);
        }
    }

}

void SzpltReader::GetStructuredGridFromBlockPackingZone(int iDimSize, int jDimSize, int kDimSize, int zoneIndx, const char * zoneName, vtkMultiBlockDataSet * multZone)
{
    if (!zoneName || !multZone)
    {
        qDebug() << ("Zone name un-specified or nullptr vtkMultiBlockDataSet.");
        return;
    }

    // determine the topological dimension
    if (jDimSize == 1 && kDimSize == 1)
    {
        TopologyDim = vtkMath::Max(TopologyDim, 1);
    }
    else if (kDimSize == 1)
    {
        TopologyDim = vtkMath::Max(TopologyDim, 2);
    }
    else
    {
        TopologyDim = vtkMath::Max(TopologyDim, 3);
    }

    // number of points, number of cells, and dimensionality
    int numNodes = iDimSize * jDimSize * kDimSize;
    int numCells = ((iDimSize <= 1) ? 1 : (iDimSize - 1)) * ((jDimSize <= 1) ? 1 : (jDimSize - 1)) *
            ((kDimSize <= 1) ? 1 : (kDimSize - 1));
    int gridDims[3] = { iDimSize, jDimSize, kDimSize };

    // Create vtkPoints and vtkStructuredGrid and associate them
    vtkPoints* pntCords = vtkPoints::New();
    vtkStructuredGrid* strcGrid = vtkStructuredGrid::New();
    this->GetArraysFromBlockPackingZone(zoneIndx,
                                        numNodes, numCells, pntCords, strcGrid->GetPointData(), strcGrid->GetCellData(), multZone);
    strcGrid->SetDimensions(gridDims);
    strcGrid->SetPoints(pntCords);
    pntCords->Delete();
    pntCords = nullptr;

    if ((TopologyDim == 2 || TopologyDim == 3) ||
            (TopologyDim == 0 && GeometryDim > 1))
    {
        multZone->SetBlock(zoneIndx - 1, strcGrid);
        multZone->GetMetaData(zoneIndx - 1)->Set(vtkCompositeDataSet::NAME(), zoneName);
    }
    strcGrid->Delete();
    strcGrid = nullptr;
}

void SzpltReader::GetUnstructuredGridFromBlockPackingZone(int numNodes, int numCells, int cellType, int zoneIndx, const char * zoneName, vtkMultiBlockDataSet * multZone)
{
    vtkPoints* gridPnts = vtkPoints::New();
    vtkUnstructuredGrid* unstruct = vtkUnstructuredGrid::New();
    this->GetUnstructuredGridCells(zoneIndx, numCells, cellType, unstruct, multZone);

    this->GetArraysFromBlockPackingZone(zoneIndx,
                                        numNodes, numCells, gridPnts, unstruct->GetPointData(), unstruct->GetCellData(), multZone);

    unstruct->SetPoints(gridPnts);
    gridPnts->Delete();
    gridPnts = nullptr;

    if ((TopologyDim == 2 || TopologyDim == 3) ||
            (TopologyDim == 0 && GeometryDim > 1))
    {
        multZone->SetBlock(zoneIndx - 1, unstruct);
        multZone->GetMetaData(zoneIndx - 1)->Set(vtkCompositeDataSet::NAME(), zoneName);
    }
    unstruct->Delete();
    unstruct = nullptr;
}

void SzpltReader::GetUnstructuredGridCells(int zoneIndex, int numberCells, int cellType, vtkUnstructuredGrid * unstrctGrid, vtkMultiBlockDataSet* multZone)
{
    if (!unstrctGrid)
    {
        //vtkErrorMacro(<< "vtkUnstructuredGrid object.");
        return;
    }

    // determine the number of points per cell and the cell type
    int numCellPnts = -1;
    int theCellType = -1;

    if (cellType == FE_BRICK)
    {
        numCellPnts = 8;
        theCellType = VTK_HEXAHEDRON;
        TopologyDim = vtkMath::Max(TopologyDim, 3);
    }
    else if (cellType == FE_TRIANGLE)
    {
        numCellPnts = 3;
        theCellType = VTK_TRIANGLE;
        TopologyDim = vtkMath::Max(TopologyDim, 2);
    }
    else if (cellType == FE_QUAD)
    {
        numCellPnts = 4;
        theCellType = VTK_QUAD;
        TopologyDim = vtkMath::Max(TopologyDim, 2);
    }
    else if (cellType == FE_TET)
    {
        numCellPnts = 4;
        theCellType = VTK_TETRA;
        TopologyDim = vtkMath::Max(TopologyDim, 3);
    }
    // 	else if (strcmp(cellTypeStr, "POINT") == 0 || strcmp(cellTypeStr, "") == 0)
    // 	{
    // 		numCellPnts = 1;
    // 		theCellType = VTK_VERTEX;
    // 		TopologyDim = vtkMath::Max(TopologyDim, 0);
    // 	}
    else
    {
        qDebug() << "Unknown cell type for a zone.";
        return;
    }

    // the storage of each cell begins with the number of points per cell,
    // followed by a list of point ids representing the cell
    vtkIdTypeArray* cellInfoList = vtkIdTypeArray::New();
    cellInfoList->SetNumberOfValues((numCellPnts + 1) * numberCells);
    vtkIdType* cellInforPtr = cellInfoList->GetPointer(0);

    // type of each cell
    vtkUnsignedCharArray* cellTypeList = vtkUnsignedCharArray::New();
    cellTypeList->SetNumberOfValues(numberCells);
    unsigned char* cellTypesPtr = cellTypeList->GetPointer(0);

    // Retrieve zone node map, if any, and send to the output file
    //std::vector<std::vector<int32_t>> nodeVecs;// all the nodes map
    int32_t shareConnectivityFromZone;
    shareConnectivity.emplace_back(shareConnectivityFromZone);

    int i = tecZoneConnectivityGetSharedZone(inputFileHandle, zoneIndex, &shareConnectivityFromZone);
    if (cellType != 0 && shareConnectivityFromZone == 0)
    {
        int64_t numValues;
        i = tecZoneNodeMapGetNumValues(inputFileHandle, zoneIndex, numberCells, &numValues);
        int32_t is64Bit;
        i = tecZoneNodeMapIs64Bit(inputFileHandle, zoneIndex, &is64Bit);
        if (is64Bit)
        {
            std::vector<int64_t> nodeMap(numValues);
            i = tecZoneNodeMapGet64(inputFileHandle, zoneIndex, 1, numberCells, &nodeMap[0]);

            for (int j = 0; j < numberCells; j++)
            {
                *cellTypesPtr++ = theCellType;
                *cellInforPtr++ = numCellPnts;
                for (int nc = 0; nc < numCellPnts; nc++)
                {
                    *cellInforPtr++ =
                            nodeMap[numCellPnts * j + nc] - 1;
                }
            }
        }
        else
        {
            std::vector<int32_t> nodeMap(numValues);
            i = tecZoneNodeMapGet(inputFileHandle, zoneIndex, 1, numberCells, &nodeMap[0]);

            for (int j = 0; j < numberCells; j++)
            {
                *cellTypesPtr++ = theCellType;
                *cellInforPtr++ = numCellPnts;
                for (int nc = 0; nc < numCellPnts; nc++)
                {
                    *cellInforPtr++ =
                            nodeMap[numCellPnts * j + nc] - 1;
                }
            }
        }
        cellInforPtr = nullptr;
        cellTypesPtr = nullptr;



        // create a cell array object to accept the cell info
        vtkCellArray* theCellArray = vtkCellArray::New();
        theCellArray->ImportLegacyFormat(cellInfoList);
        cellInfoList->Delete();
        cellInfoList = nullptr;

        // create a vtkUnstructuredGrid object and attach the 3 arrays (types, locations,
        // and cells) to it for export.
        unstrctGrid->SetCells(cellTypeList, theCellArray);
        theCellArray->Delete();
        cellTypeList->Delete();
        theCellArray = nullptr;
        cellTypeList = nullptr;

    }
    else if (shareConnectivityFromZone != 0)
    {
        unstrctGrid->SetCells(static_cast<vtkUnstructuredGrid*>(multZone->GetBlock(shareConnectivityFromZone - 1))->GetCellTypesArray(),
                              static_cast<vtkUnstructuredGrid*>(multZone->GetBlock(shareConnectivityFromZone - 1))->GetCells());
    }
}
