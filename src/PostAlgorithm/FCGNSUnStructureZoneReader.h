#ifndef _FCGNSUNSTRUCTEGRIDREADER_H__
#define _FCGNSUNSTRUCTEGRIDREADER_H__

#include "FCGNSGridReaderBase.h"
#include <QList>
#include <QString>
#include <cgnstypes.h>
#include <cgnslib.h>
#include <vtkUnstructuredGrid.h>

struct FSection
{
    FSection(QString name, int b, int e) :_name(name),_begin(b), _end(e){}
    QString _name{};
    int _begin{0};
    int _end{0};
};

class FCGNSUnStructeGridReader :public FCGNSGridReaderBase
{
public:
    FCGNSUnStructeGridReader(vtkMultiBlockDataSet* root);
    ~FCGNSUnStructeGridReader() = default;
 
    void read() override;

private:
    void addCells(vtkUnstructuredGrid* grid, int ncell, CGNS_ENUMT(ElementType_t) type, cgsize_t* eles);

    void spllitSection(vtkUnstructuredGrid* gird);

    QList<int> sectionOrder(int nsec);

private:
    QList<FSection> _sections;

};

#endif
