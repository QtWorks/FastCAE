#include "RenderDataObject.h"
#include "RenderProperty.h"
#include "RenderDataAlgorithm.h"
#include <vtkDataSet.h>
#include <vtkAlgorithmOutput.h>
#include <vtkPointData.h>
#include <vtkCellData.h>
#include <vtkDataArray.h>
#include <vtkTextProperty.h>
#include <vtkScalarBarActor.h>
#include <vtkBorderRepresentation.h>
#include <vtkProp3DCollection.h>
#include <vtkProperty.h>
#include <vtkDataSetWriter.h>

namespace Post {
int RenderDataObject::MaxID = 0;

RenderDataObject::RenderDataObject(RenderDataObject* parent /*= nullptr*/)
    :_ParentObj(parent)
{
    _id = ++MaxID;

    CreateVTKSmartPtr(vtkAssembly, _actors)
            CreateVTKSmartPtr(vtkAssembly, _assistActors)
            CreateVTKSmartPtr(vtkAssembly, _assembly)
            _assembly->AddPart(_actors);
    _assembly->AddPart(_assistActors);

    //_ViewProperty = new RenderProperty(this);
    //		this->initScalarBar();
}

RenderDataObject::~RenderDataObject()
{
    for (auto pro : _PropertyList)
        delete pro;
    _PropertyList.clear();

    for (auto subObj : _SubObjects)
        delete subObj;
    _SubObjects.clear();
    //DeleteItem(_ViewProperty)
    //     if (_vtkAlg != nullptr)
    //         _vtkAlg->Delete();
}

vtkDataSet* RenderDataObject::getOutputData()
{
    if (_vtkAlg == nullptr) return nullptr;
    auto dObj = _vtkAlg->GetOutputDataObject(0);
    return vtkDataSet::SafeDownCast(dObj);
}

vtkDataSet* RenderDataObject::getOutputData(const int port)
{
    if (_vtkAlg == nullptr) return nullptr;
    auto dObj = _vtkAlg->GetOutputDataObject(port);
    return vtkDataSet::SafeDownCast(dObj);
}

QString RenderDataObject::getName()
{
    return _name;
}

vtkAssembly* RenderDataObject::getAssembly()
{
    return _assembly;
}

vtkAlgorithmOutput* RenderDataObject::getOutputPort()
{
    return _vtkAlg->GetOutputPort();
}

vtkAlgorithmOutput* RenderDataObject::getOutputPort(const int port)
{
    return _vtkAlg->GetOutputPort(port);
}

void RenderDataObject::setInputConnection(vtkAlgorithmOutput* alg)
{
    _vtkAlg->SetInputConnection(alg);
}

void RenderDataObject::update()
{
    //     if (_mapper == nullptr) return;
    //     _mapper->Update();
    if (_SubObjects.size() == 0)
    {
        for (auto mapper : _Mappers)
        {
            mapper->Update();
        }
    }
    else
    {
        for (auto obj : _SubObjects)
            obj->update();
    }
}

void RenderDataObject::updateAlg()
{

    if (_vtkAlg == nullptr) return;
    _vtkAlg->Update();

    for (auto obj : _SubObjects)
        obj->updateAlg();


    // 		if (_SubObjects.size() == 0)
    // 		{
    // 			if (_vtkAlg == nullptr) return;
    // 			_vtkAlg->Update();
    // 		}
    // 		else
    // 		{
    // 			for (auto obj : _SubObjects)
    // 				obj->updateAlg();
    // 		}

    // 		QString file = QString("E:/220331_%1.vtk").arg(this->getName());
    // 		QString2Char(file,cfile)
    // 		vtkSmartPointer<vtkDataSetWriter> w = vtkSmartPointer<vtkDataSetWriter>::New();
    // 		w->SetInputData(this->getOutputData());
    // 		w->SetFileName(cfile);
    // 		w->Update();
}

QStringList RenderDataObject::getPointDataArray()
{
    auto dataSet = this->getOutputData();
    if (dataSet == nullptr) return QStringList();
    auto pointData = dataSet->GetPointData();
    if (pointData == nullptr) return QStringList();
    const int nArray = pointData->GetNumberOfArrays();
    QStringList nameList;
    for (int i = 0; i < nArray; ++i)
    {
        const char* cName = pointData->GetArrayName(i);
        QString name = QString(cName);
        nameList.append(name);
    }
    return nameList;
}

QStringList RenderDataObject::getBlockPointDataArray(int index)
{
    auto dataSet = this->getOutputData(index);
    if (dataSet == nullptr) return QStringList();
    auto pointData = dataSet->GetPointData();
    if (pointData == nullptr) return QStringList();
    const int nArray = pointData->GetNumberOfArrays();
    QStringList nameList;
    for (int i = 0; i < nArray; ++i)
    {
        const char* cName = pointData->GetArrayName(i);
        QString name = QString(cName);
        nameList.append(name);
    }
    return nameList;
}

QStringList RenderDataObject::getCellDataArray()
{
    auto dataSet = this->getOutputData();
    if (dataSet == nullptr) return QStringList();

    auto cellData = dataSet->GetCellData();
    if (cellData == nullptr) return QStringList();
    const int nArray = cellData->GetNumberOfArrays();
    QStringList nameList;
    for (int i = 0; i < nArray; ++i)
    {
        const char* cName = cellData->GetArrayName(i);
        QString name = QString(cName);
        nameList.append(name);
    }
    return nameList;
}

QStringList RenderDataObject::getBlockCellDataArray(int index)
{
    auto dataSet = this->getOutputData(index);
    if (dataSet == nullptr) return QStringList();

    auto cellData = dataSet->GetCellData();
    if (cellData == nullptr) return QStringList();
    const int nArray = cellData->GetNumberOfArrays();
    QStringList nameList;
    for (int i = 0; i < nArray; ++i)
    {
        const char* cName = cellData->GetArrayName(i);
        QString name = QString(cName);
        nameList.append(name);
    }
    return nameList;
}

QString RenderDataObject::variableType(int vaLocation, QString vaName)
{
    QString type = "Unknown";
    vtkDataSet* data = getOutputData();
    if (data == nullptr) return 0;
    QString2Char(vaName, cName)
            vtkDataArray* dataArray = nullptr;
    if (vaLocation == 1)
        dataArray = data->GetPointData()->GetArray(cName);
    else if (vaLocation == 2)
        dataArray = data->GetCellData()->GetArray(cName);
    if (dataArray == nullptr) return 0;
    const int cNum = dataArray->GetNumberOfComponents();
    if (cNum == 1)
        type = "scalar";
    else if (cNum == 3)
        type = "vector";
    else if (cNum == 9)
        type = "tensor";
    return type;
}

int RenderDataObject::variableComponentCount(int vaLocation, QString vaName)
{
    vtkDataSet* data = getOutputData();
    if (data == nullptr) return 0;
    QString2Char(vaName, cName)
            vtkDataArray* dataArray = nullptr;
    if (vaLocation == 1)
        dataArray = data->GetPointData()->GetArray(cName);
    else if (vaLocation == 2)
        dataArray = data->GetCellData()->GetArray(cName);
    if (dataArray == nullptr) return 0;

    return dataArray->GetNumberOfComponents();
}

// 	vtkScalarBarWidget* RenderDataObject::getScalarBarWidget()
// 	{
// 		return _ScalarBar;
// 	}
// 
// 	vtkLookupTable* RenderDataObject::getLookupTable()
// 	{
// 		return _LookupTable;
// 	}

RenderDataObject * RenderDataObject::getRootViewObject()
{
    RenderDataObject* obj = this;
    while (obj->getParentObj() != nullptr)
    {
        obj = obj->getParentObj();
    }
    return obj;
}

void RenderDataObject::removeObject(RenderDataObject* obj)
{
    if (!_SubObjects.contains(obj)) return;
    _SubObjects.removeOne(obj);
    delete obj;
}

RenderDataObject* RenderDataObject::getObjectByID(int id)
{
    if (id == _id) return this;
    const int ncount = this->getSubObjectsCount();
    for (int i = 0; i < ncount; ++i)
    {
        auto subObj = getSubObjectsAt(i);
        auto viewObj = subObj->getObjectByID(id);
        if (viewObj != nullptr) return viewObj;
    }
    return nullptr;
}

void RenderDataObject::getSubObjects(QList<RenderDataObject*> &objs)
{
    for (auto v : _SubObjects)
    {
        objs.append(v);
        v->getSubObjects(objs);
    }
}

double* RenderDataObject::getBoundary()
{
    auto data = this->getOutputData();
    if (data == nullptr) return nullptr;
    return data->GetBounds();
}

vtkDataArray* RenderDataObject::getArray(int location, QString name)
{
    auto data = this->getOutputData();
    if (data == nullptr) return nullptr;
    vtkDataArray* dataArray = nullptr;
    if (location == 1)
    {
        auto pointData = data->GetPointData();
        if (pointData == nullptr) return nullptr;
        QString2Char(name, cname)
                dataArray = pointData->GetArray(cname);
    }
    else if (location == 2)
    {
        auto cellData = data->GetCellData();
        if (cellData == nullptr) return nullptr;
        QString2Char(name, cname)
                dataArray = cellData->GetArray(cname);
    }
    return dataArray;
}

// 	void RenderDataObject::initScalarBar()
// 	{
// 		DecCreVTKSmartPtr(vtkTextProperty, propLable)
// 		propLable->SetBold(0);
// 		propLable->SetItalic(0);
// 		propLable->SetShadow(0);
// 		propLable->SetJustification(VTK_TEXT_LEFT);
// 		propLable->SetColor(0, 0, 0);
// 		propLable->SetFontSize(14);
// 
// 		CreateVTKSmartPtr(vtkScalarBarWidget, _ScalarBar)
// 		_ScalarBar->GetScalarBarActor()->SetVerticalTitleSeparation(1);
// 		_ScalarBar->GetScalarBarActor()->SetBarRatio(0.2);
// 		_ScalarBar->GetBorderRepresentation()->SetPosition(0.90, 0.05);
// 		_ScalarBar->GetBorderRepresentation()->SetPosition2(0.08, 0.45);
// 		_ScalarBar->GetBorderRepresentation()->SetShowBorderToOff();
// 		_ScalarBar->GetScalarBarActor()->SetTitleTextProperty(propLable);
// 		_ScalarBar->GetScalarBarActor()->SetLabelTextProperty(propLable);
// 		_ScalarBar->GetScalarBarActor()->SetUnconstrainedFontSize(true);
// 
// 		CreateVTKSmartPtr(vtkLookupTable, _LookupTable)
// 			_LookupTable->SetHueRange(0.66667, 0.0);
// 		_LookupTable->SetNumberOfColors(255);
// 		_LookupTable->Build();
// 		_ScalarBar->GetScalarBarActor()->SetLookupTable(_LookupTable);
// 		//    _mapper->SetLookupTable(_LookupTable); 
// 	}

void RenderDataObject::setShowStatus(bool V)
{

    for (auto pro : _PropertyList)
    {
        if (pro == nullptr) continue;;
        pro->setShowStatus(V);
    }

    _ShowStatus = V;
    _assembly->SetVisibility(V);
    // 		if (!V) _ScalarBar->Off();
    // 		else
    // 		{
    // 			bool show = false;
    // 			if (show) _ScalarBar->On();
    // 			else _ScalarBar->Off();
    // 		}
}

int RenderDataObject::getPointDataNum()
{
    auto data = this->getOutputData();
    if (data == nullptr) return 0;
    return data->GetNumberOfPoints();
}

int RenderDataObject::getNumberOfBlockPoints(int index)
{
    auto data = this->getOutputData(index);
    if (data == nullptr) return 0;
    return data->GetNumberOfPoints();
}

int RenderDataObject::getCellDataNum()
{
    auto data = this->getOutputData();
    if (data == nullptr) return 0;
    return data->GetNumberOfCells();
}


int RenderDataObject::getNumberOfBlockCells(int index)
{
    auto data = this->getOutputData(index);
    if (data == nullptr) return 0;
    return data->GetNumberOfCells();
}

QVector<AttributeInfo> RenderDataObject::getPointDataArrayInfo()
{
    auto dataSet = this->getOutputData();
    if (dataSet == nullptr) return QVector<AttributeInfo>();

    QVector<AttributeInfo> info;
    //point
    auto pointData = dataSet->GetPointData();
    if (pointData != nullptr)
    {
        const int nArray = pointData->GetNumberOfArrays();
        for (int i = 0; i < nArray; ++i)
        {
            const char* cName = pointData->GetArrayName(i);
            QString namePoint = QString(cName);
            const int pNum = pointData->GetArray(i)->GetNumberOfComponents();
            QString typeNamePoint = getTypeName(pNum);
            double rangePoint[2] = { 0 };
            pointData->GetArray(i)->GetRange(rangePoint);
            QString pointRange = "[" + QString::number(rangePoint[0]) + "," + QString::number(rangePoint[1]) + "]";

            AttributeInfo p;
            p.kind = QString::fromLocal8Bit("点属性");
            p.name = namePoint;
            p.type = typeNamePoint;
            p.range = pointRange;

            info.push_back(p);
        }
    }

    // cell
    auto cellData = dataSet->GetCellData();
    if (cellData != nullptr)
    {
        const int nCArray = cellData->GetNumberOfArrays();

        for (int i = 0; i < nCArray; ++i)
        {
            const char* cName = cellData->GetArrayName(i);
            QString nameCell = QString(cName);
            const int cNum = cellData->GetArray(i)->GetNumberOfComponents();
            QString typeNameCell = getTypeName(cNum);
            double rangeCell[2] = { 0 };
            cellData->GetArray(i)->GetRange(rangeCell);
            QString cellRange = "[" + QString::number(rangeCell[0]) + "," + QString::number(rangeCell[1]) + "]";

            AttributeInfo c;
            c.kind = QString::fromLocal8Bit("单元属性");
            c.name = nameCell;
            c.type = typeNameCell;
            c.range = cellRange;

            info.push_back(c);
        }
    }

    return info;
}

void RenderDataObject::getRange(double* range, int type, QString vaName, int componentIndex)
{
    vtkDataSet* data = this->getOutputData();
    if (data == nullptr) return;
    QString2Char(vaName, cName)
            vtkDataArray* dataArray = nullptr;
    if (type == 1)
        dataArray = data->GetPointData()->GetArray(cName);
    else if (type == 2)
        dataArray = data->GetCellData()->GetArray(cName);
    if (dataArray == nullptr) return;

    dataArray->GetRange(range, componentIndex);
}

QStringList RenderDataObject::getBlockNames()
{
    return _blockNames;
}

bool RenderDataObject::getBlockShowStatus(const int index)
{
    if (index < 0 || index >= _PropertyList.size()) return false;

    auto pro = _PropertyList.at(index);
    if (pro == nullptr) return false;

    return pro->getShowStatus();
}

void RenderDataObject::setBlockShowStatus(const int index, bool show)
{
    if (index < 0 || index >= _PropertyList.size()) return;

    auto pro = _PropertyList.at(index);
    if (pro == nullptr) return;

    pro->setShowStatus(show);
}

QString RenderDataObject::getBlockName(const int index)
{
    QString name;

    if (index < 0 || index >= _blockNumber || index >= _blockNames.size()) return name;

    return _blockNames.at(index);
}

int RenderDataObject::getNumberOfBlocks()
{
    return _blockNumber;
}

int RenderDataObject::getNumberOfAlgorithmByType(int type)
{
    int num = 0;
    for (auto obj : _SubObjects)
    {
        auto alg = RenderDataAlgorithm::SafeDownCast(obj);
        if(alg == nullptr) continue;

        if (alg->getAlgoType() == (AlgorithmType)type) ++num;
    }

    return num;
}

void RenderDataObject::updateScalarBar(vtkRenderWindowInteractor* interactor)
{
    for (auto pro : _PropertyList)
    {
        if(pro == nullptr) continue;

        pro->updateScalarBar(interactor);
    }
}

QString RenderDataObject::getTypeName(int dim)
{
    QString typeName = "";
    if (dim == 1)
        typeName = QString::fromLocal8Bit("标量");
    else if (dim == 3)
        typeName = QString::fromLocal8Bit("矢量");
    else if (dim >= 4)
        typeName = QString::fromLocal8Bit("张量");;
    return typeName;
}



vtkDataSetMapper* RenderDataObject::createMapper(bool assist)
{
    Q_UNUSED(assist)
    DecCreVTKSmartPtr(vtkDataSetMapper, mapper)
            DecCreVTKSmartPtr(vtkActor, actor)

            actor->SetMapper(mapper);
    _actors->AddPart(actor);
    _ActorList.append(actor);
    _Mappers.append(mapper);

    mapper->SetScalarVisibility(false);
    //		mapper->SetLookupTable(_LookupTable);
    mapper->SetInterpolateScalarsBeforeMapping(true);  //抗锯齿

    //RenderProperty* rProperty = new RenderProperty(this, _Mappers.size() - 1);
    auto pro = actor->GetProperty();
    if (pro != nullptr)
    {
        auto color = colorList.at(_ActorList.size() % colorList.size());
        pro->SetColor(color.redF(), color.greenF(), color.blueF());
    }

    RenderProperty* rProperty = new RenderProperty(this, mapper, actor);

    _PropertyList.append(rProperty);

    return mapper;
}

void RenderDataObject::setDisplayMode(int mode)
{
    _DisplayMode = mode;

    if (_actors == nullptr) return;
    auto collect = _actors->GetParts();
    if (collect == nullptr) return;
    collect->InitTraversal();
    const int nColl = collect->GetNumberOfItems();
    for (int i = 0; i < nColl; i++)
    {
        auto prop = collect->GetNextProp3D();
        auto act = vtkActor::SafeDownCast(prop);
        auto property = act->GetProperty();

        switch (mode)
        {
        case 0: property->SetRepresentationToPoints(); break;
        case 1: property->SetRepresentationToWireframe(); break;
        case 2: property->SetRepresentationToSurface(); property->SetEdgeVisibility(false); break;
        case 3: property->SetRepresentationToSurface(); property->SetEdgeVisibility(true); break;
        default: break;
        }
    }
}
}
