#include "RenderDataImportSteady.h"
#include "PostAlgorithm/CGNSReaderAlgorithm.h"
#include "PostAlgorithm/Plot3DReaderAlgorithm.h"
#include "PostAlgorithm/TecSzpltReaderAlgorithm.h"
//#include "PostAlgorithm/NastranH5ReaderAlgorithm.h"
#include "RenderProperty.h"
#include <vtkDataSet.h>
#include <vtkDataSetReader.h>
#include <QDebug>
#include <vtkMultiBlockPLOT3DReader.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkAppendFilter.h>
#include <vtkUnstructuredGrid.h>
#include <vtkDataObject.h>
#include <vtkPointData.h>
#include <vtkCellData.h>
#include <vtkDataArray.h>
#include <vtkDataSetWriter.h>
#include <QFile>
#include <QString>
#include <vtkXMLUnstructuredGridReader.h>
#include <vtkXMLPUnstructuredGridReader.h>

namespace Post
{
	RenderDataImportSteady::RenderDataImportSteady(const QString &fileName)
		: RenderDataObject(nullptr), _FileName(fileName)
	{
		this->setDataType(Imp);

		QString f(fileName);
		f = f.replace(QString("\\"), QString("/"));

		const int index = fileName.lastIndexOf(".");
		const int nsize = fileName.size();
		_Suffix = fileName.right(nsize - index - 1).toLower();

		const int lIndex = f.lastIndexOf("/");
		_name = fileName.right(nsize - lIndex - 1);

		QFile file(f);
		if (!file.exists())
			return;

		if (_Suffix == "vtk")
		{
			CreateVTKSmartPtr(vtkDataSetReader, _vtkAlg) auto r = vtkDataSetReader::SafeDownCast(_vtkAlg);
			QString2Char(_FileName, c)
				r->SetFileName(c);
			r->ReadAllScalarsOn();
			r->ReadAllVectorsOn();
			r->ReadAllTensorsOn();
			r->ReadAllFieldsOn();
			r->ReadAllColorScalarsOn();
			r->ReadAllNormalsOn();
			r->ReadAllTCoordsOn();
			_blockNumber = 1;
			auto mapper = createMapper(true);
			mapper->SetInputConnection(_vtkAlg->GetOutputPort(0));
			//       mapper->Update();
		}
		else if (_Suffix == "xyz" || _Suffix == "x") // plot3d文件的后缀名为 .xyz/.x
		{
			CreateVTKSmartPtr(Plot3DReaderAlgorithm, _vtkAlg) auto r = Plot3DReaderAlgorithm::SafeDownCast(_vtkAlg);
			QString2Char(_FileName, c);
			r->SetFileName(c);
		}
		else if (_Suffix == "cgns") // cgns文件读取
		{
			CreateVTKSmartPtr(CGNSReaderAlgorithm, _vtkAlg) auto r = CGNSReaderAlgorithm::SafeDownCast(_vtkAlg);
			QString2Char(_FileName, c);
			r->SetFileName(c);
			r->Update();
			_blockNames = r->getBlockNames();
			_blockNumber = r->getNumberOfBlocks();
			qDebug() << r->getBlockNames();
			qDebug() << _blockNumber;

			for (int i = 0; i < _blockNumber; ++i)
			{
				auto mapper = createMapper(true);
				mapper->SetInputConnection(_vtkAlg->GetOutputPort(i + 1));
			}
		}
		else if (_Suffix == "szplt") // tecplot的szplt二进制文件读取
		{
			CreateVTKSmartPtr(TecSzpltReaderAlgorithm, _vtkAlg) auto r = TecSzpltReaderAlgorithm::SafeDownCast(_vtkAlg);
			QString2Char(_FileName, c);
			r->SetFileName(c);
			r->Update();
			_blockNames = r->getBlockNames();
			_blockNumber = r->getNumberOfBlocks();
			qDebug() << r->getBlockNames();
			qDebug() << _blockNumber;

			for (int i = 0; i < _blockNumber; ++i)
			{
				auto mapper = createMapper(true);
				mapper->SetInputConnection(_vtkAlg->GetOutputPort(i + 1));
			}
		}
        else if (_Suffix == "vtu")
        {
            CreateVTKSmartPtr(vtkXMLUnstructuredGridReader, _vtkAlg) auto r = vtkXMLUnstructuredGridReader::SafeDownCast(_vtkAlg);
            QString2Char(_FileName, c);
            r->SetFileName(c);
            r->Update();
            _blockNumber = 1;
            auto mapper = createMapper(true);
            mapper->SetInputConnection(_vtkAlg->GetOutputPort(0));
        }
        else if (_Suffix == "pvtu")
        {
            CreateVTKSmartPtr(vtkXMLPUnstructuredGridReader, _vtkAlg) auto r = vtkXMLPUnstructuredGridReader::SafeDownCast(_vtkAlg);
            QString2Char(_FileName, c);
            r->SetFileName(c);
            r->Update();
            _blockNumber = 1;
            auto mapper = createMapper(true);
            mapper->SetInputConnection(_vtkAlg->GetOutputPort(0));
        }
	}

	RenderDataImportSteady *RenderDataImportSteady::SafeDownCast(RenderDataObject *obj)
	{
		return dynamic_cast<RenderDataImportSteady *>(obj);
	}

	int RenderDataImportSteady::getBlockCount()
	{
		return _ActorList.size();
	}

	QStringList RenderDataImportSteady::getBlockNames()
	{
		QStringList names;
		if (_Suffix == "cgns")
		{

			auto r = CGNSReaderAlgorithm::SafeDownCast(_vtkAlg);
			names = r->getBlockNames();
		}
		else if (_Suffix == "szplt")
		{
			auto r = TecSzpltReaderAlgorithm::SafeDownCast(_vtkAlg);
			names = r->getBlockNames();
		}
		return names;
	}

	void RenderDataImportSteady::setBlockVisible(int index, bool vis)
	{
		if (_Suffix == "cgns")
		{
			auto r = CGNSReaderAlgorithm::SafeDownCast(_vtkAlg);
			r->setVisible(index, vis);
		}
		else if (_Suffix == "szplt")
		{
			auto r = TecSzpltReaderAlgorithm::SafeDownCast(_vtkAlg);
			r->setVisible(index, vis);
		}

		auto ac = this->getActorListAt(index);
		if (ac != nullptr)
			ac->SetVisibility(vis);
	}

}
