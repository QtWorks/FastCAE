#ifndef _FCGNSGRIDREADER_H__
#define _FCGNSGRIDREADER_H__

#include <QVector>
#include <cgnstypes.h>
#include <cgnslib.h>
#include <QHash>

class vtkMultiBlockDataSet;
class vtkDataSet;
class vtkDataArray;

struct VPoint
{
    double x{0};
    double y{0};
    double z{0};
};

class FCGNSGridReaderBase
{
public:
    FCGNSGridReaderBase(vtkMultiBlockDataSet* root);
    virtual ~FCGNSGridReaderBase() = default;

    void setInfo(int fileIndex, int baseIndex, int zoneIndex);

    virtual void read()=0;

protected:
    void readCoordinate(int dim,int count, cgsize_t range_from[3], cgsize_t range_to[3]);

    void readFlowSolution(vtkDataSet* grid);

    void readFieldData(int solIndex, CGNS_ENUMT(GridLocation_t) loc,QList<QString> &varNames,
                       QList<int> &valueType, QList<void*> &values);

    void addValueToGrid(CGNS_ENUMT(GridLocation_t) loc, QList<QString> varNames, 
                       QList<int> valueType, QList<void*> values);

    bool isVectorComponent(QString name, QString& vecName, QString& comp);

    vtkDataArray* generateScalarArray(QString varName, int num, int type,void* va);

    vtkDataArray* generateVectorArray(QString varName, int num, 
                   int xtype, void * x,int ytype, void* y, int ztype, void* z);

protected:
    vtkMultiBlockDataSet* _root{};
    int _fileIndex{ -1 }, _baseIndex{ -1 }, _zoneIndex{ -1 };
    bool _isStructedGrid{ false };
    int _dim{ 2 };
    vtkDataSet* _dataSet{};
    QString _zoneName;

    QVector<VPoint> _vertexList{};
};

#endif
