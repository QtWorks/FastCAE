#ifndef _FCGNSUNSTRUCTEDREADER_H_
#define _FCGNSUNSTRUCTEDREADER_H_

#include "FCGNSGridReaderBase.h"

QString GetBCType(QString name, int bcType);

class vtkStructuredGrid;

struct BCInfo 
{
    BCInfo(char* cname, cgsize_t* size, int bcType)
    {
        name = QString(cname);
        BCType = GetBCType(name, bcType);
        iMin = size[0] - 1;
        jMin = size[1] - 1;
        kMin = size[2] - 1;
        iMax = size[3] - 1;
        jMax = size[4] - 1;
        kMax = size[5] - 1;
    }

    QString name;
    int iMin{ 0 }, iMax{ 0 }, jMin{ 0 }, jMax{ 0 }, kMin{ 0 }, kMax{ 0 };
    QString BCType{ "None" };
};

class FCGNSStructeGridReader : public FCGNSGridReaderBase
{
public:
    FCGNSStructeGridReader(vtkMultiBlockDataSet* root);
    ~FCGNSStructeGridReader() = default;

    void read() override;

    void setReadBC(bool r);

    bool isReadBC();

private:
    void readBC();
    
    void spllitSection(vtkStructuredGrid* gird);

    void extractBCs(vtkStructuredGrid *grid);

    void extractBCGrid(vtkStructuredGrid* grid,  BCInfo* info ,QList<int> & indexs);
private:
    QList<BCInfo> _bcList{};

    bool _readBC{ false };
};

#endif
