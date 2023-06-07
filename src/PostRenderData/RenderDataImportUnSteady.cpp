#include "RenderDataImportUnSteady.h"
#include <QDir>
#include <QDebug>
#include <vtkDataSetReader.h>
#include "PostAlgorithm/CGNSReaderAlgorithm.h"
#include "PostAlgorithm/Plot3DReaderAlgorithm.h"
#include "Macros.hxx"
#include <vtkXMLUnstructuredGridReader.h>
#include <vtkXMLPUnstructuredGridReader.h>

namespace Post {
	QStringList getSelectGroupFiles(const QString path)
	{
		QStringList groupFiles;

		//截取目录路径
		int indexSlash = path.lastIndexOf("/");
		QString directory = path.left(indexSlash);

		QDir dir(directory);
		if (!dir.exists())
		{
			//path error
			return QStringList();
		}

		if (dir.cd(directory))
		{
			dir.setFilter(QDir::Files);
			dir.setSorting(QDir::Name);

			//后缀名过滤
			int indexDot = path.lastIndexOf(".");
			QString ext = path.mid(indexDot, path.length() - indexDot);
			QStringList fiter{};
			fiter.append("*" + ext);
			dir.setNameFilters(fiter);

			//截取组名
			QString regGroupName = path.mid(indexSlash + 1, path.length() - indexSlash);
			int indexFirstDot = regGroupName.indexOf(".");
			QString prefix = regGroupName.left(indexFirstDot);

			QFileInfoList list = dir.entryInfoList();
			if (list.count() > 0)
			{
				for (int i = 0; i < list.count(); i++)
				{
					QFileInfo fileInfo = list.at(i);
					QString fileName = fileInfo.fileName();
					if (fileName.mid(0, prefix.length()) == prefix)
					{
						groupFiles.append(fileInfo.absoluteFilePath());
					}
				}
			}
		}

		return groupFiles;
	}

	RenderDataImportUnSteady::RenderDataImportUnSteady(const QString files)
		:RenderDataImportSteady(files)
	{
		this->setSteady(false);
		_FileList = getSelectGroupFiles(files);

		QString fileName = _FileList.at(_CurrentIndex);
		QString f(fileName);
		f = f.replace(QString("\\"), QString("/"));

		QString Suffix = this->getSuffix();

		const int index = fileName.lastIndexOf(".");
		const int nsize = fileName.size();
		Suffix = fileName.right(nsize - index - 1).toLower();

		const int lIndex = f.lastIndexOf("/");
		_name = fileName.right(nsize - lIndex - 1);

		QFile file(f);
		if (!file.exists()) return;

		// 	DeclarVTKSmartPtr(vtkMultiBlockPLOT3DReader, _vtkPlot3D);
		// 	vtkNew<vtkAppendFilter> appendFilter;

		if (Suffix == "vtk")
		{
			CreateVTKSmartPtr(vtkDataSetReader, _vtkAlg)
				auto r = vtkDataSetReader::SafeDownCast(_vtkAlg);
			QString2Char(fileName, c)
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
		else if (Suffix == "xyz" || Suffix == "x") // plot3d文件的后缀名为 .xyz/.x
		{
			CreateVTKSmartPtr(Plot3DReaderAlgorithm, _vtkAlg)
				auto r = Plot3DReaderAlgorithm::SafeDownCast(_vtkAlg);
			QString2Char(fileName, c);
			r->SetFileName(c);

		}
		else if (Suffix == "cgns") // cgns文件读取
		{
			CreateVTKSmartPtr(CGNSReaderAlgorithm, _vtkAlg)
				auto r = CGNSReaderAlgorithm::SafeDownCast(_vtkAlg);
			QString2Char(fileName, c);
			r->SetFileName(c);
			r->Update();
			
			_blockNumber = r->getNumberOfBlocks();
			_blockNames = r->getBlockNames();

			for (int i = 0; i < _blockNumber; ++i)
			{
				auto mapper = createMapper(true);
				mapper->SetInputConnection(_vtkAlg->GetOutputPort(i + 1));
			}
        }
        else if (Suffix == "vtu")
        {
            CreateVTKSmartPtr(vtkXMLUnstructuredGridReader, _vtkAlg)
                auto r = vtkXMLUnstructuredGridReader::SafeDownCast(_vtkAlg);
            QString2Char(fileName, c)
                r->SetFileName(c);
            _blockNumber = 1;
            auto mapper = createMapper(true);
            mapper->SetInputConnection(_vtkAlg->GetOutputPort(0));
        }
        else if (Suffix == "pvtu")
        {
            CreateVTKSmartPtr(vtkXMLPUnstructuredGridReader, _vtkAlg)
                auto r = vtkXMLPUnstructuredGridReader::SafeDownCast(_vtkAlg);
            QString2Char(fileName, c)
                r->SetFileName(c);
            _blockNumber = 1;
            auto mapper = createMapper(true);
            mapper->SetInputConnection(_vtkAlg->GetOutputPort(0));
        }
	}

	void RenderDataImportUnSteady::ReadFile()
	{
		QString f = _FileList.at(_CurrentIndex);
		if (this->getSuffix() == "vtk")
		{
			auto reader = vtkDataSetReader::SafeDownCast(_vtkAlg);
			QString2Char(f, c);
			reader->SetFileName(c);
		}
		else if (this->getSuffix() == "cgns")
		{
			auto r = CGNSReaderAlgorithm::SafeDownCast(_vtkAlg);
			QString2Char(f, c);
			r->SetFileName(c);
		}
		else if (this->getSuffix() == "x" || this->getSuffix() == "xyz")
		{
			auto r = Plot3DReaderAlgorithm::SafeDownCast(_vtkAlg);
			QString2Char(f, c);
			r->SetFileName(c);
        }
        else if (this->getSuffix() == "vtu")
        {
            auto r = vtkXMLUnstructuredGridReader::SafeDownCast(_vtkAlg);
            QString2Char(f, c);
            r->SetFileName(c);
        }
        else if (this->getSuffix() == "pvtu")
        {
            auto r = vtkXMLPUnstructuredGridReader::SafeDownCast(_vtkAlg);
            QString2Char(f, c);
            r->SetFileName(c);
        }
	}

	RenderDataImportUnSteady::~RenderDataImportUnSteady()
	{

	}

	int RenderDataImportUnSteady::getTotalCount()
	{
		return  _FileList.size();
	}

	void RenderDataImportUnSteady::setAnimationIndex(int index)
	{
		_CurrentIndex = index;
		this->ReadFile();
	}
}
