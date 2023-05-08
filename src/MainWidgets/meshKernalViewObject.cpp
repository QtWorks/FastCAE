#include "meshKernalViewObject.h"
#include "MeshData/meshSingleton.h"
#include "MeshData/meshKernal.h"
#include "MeshData/meshSet.h"
#include "Settings/BusAPI.h"
#include "Settings/GraphOption.h"
#include <vtkUnstructuredGrid.h>
#include <vtkActor.h>
#include <vtkUnsignedCharArray.h>
#include <vtkUnsignedIntArray.h>
#include <vtkCellData.h>
#include <vtkPointData.h>
#include <vtkAppendFilter.h>
#include <vtkDataSetMapper.h>
#include <vtkProperty.h>
#include <vtkSelectionNode.h>
#include <vtkSelection.h>
#include <vtkExtractSelection.h>
#include <vtkDoubleArray.h>
#include <QThread>
#ifdef FASTCAE_HAS_OPENMP
#include <omp.h>
#endif
#include <QDebug>

namespace MainWidget
{
	MeshKernalViewObj::MeshKernalViewObj(MeshData::MeshKernal *k)
		: _kernal(k), _displayData(vtkUnstructuredGrid::New()),
		  _meshData(MeshData::MeshData::getInstance())
	{
		_actor[0] = vtkActor::New();
		_actor[1] = vtkActor::New();
		_actor[2] = vtkActor::New();
		this->generateIDProp();
		this->init();
	}

	MeshKernalViewObj::~MeshKernalViewObj()
	{
		//		if (_actor != nullptr) _actor->Delete();
		if (_displayData != nullptr)
			_displayData->Delete();
	}

	vtkDataSet *MeshKernalViewObj::getDisplayData()
	{
		return _displayData;
	}

	vtkActor **MeshKernalViewObj::getActor()
	{
		return _actor;
	}

	void MeshKernalViewObj::setPointColor(const QColor &c, bool disOnly)
	{
		vtkDataArray *dpointColor = _displayData->GetPointData()->GetScalars();
		double col[3]{c.red(), c.green(), c.blue()};
		if (nullptr == dpointColor)
		{
			dpointColor = vtkUnsignedCharArray::New();
			dpointColor->SetNumberOfComponents(3);
			_displayData->GetPointData()->SetScalars(dpointColor);
		}
		dpointColor->SetNumberOfTuples(_displayData->GetNumberOfPoints());
		dpointColor->FillComponent(0, col[0]);
		dpointColor->FillComponent(1, col[1]);
		dpointColor->FillComponent(2, col[2]);
		_displayData->Modified();

		if (disOnly)
			return;
		auto dataset = _kernal->getMeshData();
		vtkDataArray *pointColor = dataset->GetPointData()->GetScalars();
		if (nullptr == pointColor)
		{
			pointColor = vtkUnsignedCharArray::New();
			pointColor->SetNumberOfComponents(3);
			pointColor->SetNumberOfTuples(dataset->GetNumberOfPoints());
			dataset->GetPointData()->SetScalars(pointColor);
		}
		pointColor->FillComponent(0, col[0]);
		pointColor->FillComponent(1, col[1]);
		pointColor->FillComponent(2, col[2]);
	}

	void MeshKernalViewObj::setPointDisplayColor(QList<int> &indexs, const QColor &color)
	{
		vtkDataArray *colorArray = _displayData->GetPointData()->GetScalars();
		vtkDataArray *indexArray = _displayData->GetPointData()->GetArray("IDS");
		if (nullptr == colorArray || nullptr == indexArray)
			return;
		double col[3]{color.red(), color.green(), color.blue()};
		const int nPoint = indexArray->GetNumberOfTuples();
		for (int i = 0; i < nPoint; ++i)
		{
			if (indexs.isEmpty())
				break;
			int pointindex = indexArray->GetComponent(i, 1);
			if (indexs.contains(pointindex))
			{
				colorArray->SetComponent(i, 0, col[0]);
				colorArray->SetComponent(i, 1, col[1]);
				colorArray->SetComponent(i, 2, col[2]);
				indexs.removeOne(pointindex);
			}
		}
		_displayData->Modified();
	}

	void MeshKernalViewObj::setCellColor(const QColor &c, bool disOnly)
	{
		double col[3]{c.red(), c.green(), c.blue()};
		vtkDataArray *dcellcolor = _displayData->GetCellData()->GetScalars();
		if (dcellcolor == nullptr)
		{
			dcellcolor = vtkUnsignedCharArray::New();
			dcellcolor->SetNumberOfComponents(3);
			_displayData->GetCellData()->SetScalars(dcellcolor);
		}

		dcellcolor->SetNumberOfTuples(_displayData->GetNumberOfCells());
		dcellcolor->FillComponent(0, col[0]);
		dcellcolor->FillComponent(1, col[1]);
		dcellcolor->FillComponent(2, col[2]);
		_displayData->Modified();

		if (disOnly)
			return;
		auto dataset = _kernal->getMeshData();
		vtkDataArray *cellcolor = dataset->GetCellData()->GetScalars();
		if (nullptr == cellcolor)
		{
			cellcolor = vtkUnsignedCharArray::New();
			cellcolor->SetNumberOfComponents(3);
			dataset->GetCellData()->SetScalars(cellcolor);
			cellcolor->SetNumberOfTuples(dataset->GetNumberOfCells());
		}
		cellcolor->FillComponent(0, col[0]);
		cellcolor->FillComponent(1, col[1]);
		cellcolor->FillComponent(2, col[2]);
	}

	void MeshKernalViewObj::setCellDisplayColor(QList<int> &indexs, const QColor &color)
	{
		vtkDataArray *colorArray = _displayData->GetCellData()->GetScalars();
		vtkDataArray *indexArray = _displayData->GetCellData()->GetArray("IDS");
		double col[3]{color.red(), color.green(), color.blue()};
		if (nullptr == colorArray || nullptr == indexArray)
			return;
		const int nCell = indexArray->GetNumberOfTuples();

		int nprocess = 1;
#ifdef FASTCAE_HAS_OPENMP
		int ncore = QThread::idealThreadCount();
		nprocess = ncore - 1 > 0 ? ncore - 1 : ncore;
		omp_set_num_threads(nprocess);
#endif

		QList<int> spliters{0};
		const int countPart = nCell / nprocess;
		while (spliters.last() < nCell - 1)
		{
			int cu = spliters.last() + countPart;
			if (abs(cu - nCell) < 0.2 * countPart)
				cu = nCell - 1;
			spliters.append(cu);
		}

		auto serial = [=](int beg, int end)
		{
			for (int i = beg; i <= end; ++i)
			{
				int cellid = indexArray->GetComponent(i, 1);
				if (indexs.contains(cellid))
				{
					colorArray->SetComponent(i, 0, col[0]);
					colorArray->SetComponent(i, 1, col[1]);
					colorArray->SetComponent(i, 2, col[2]);
				}
			}
		};
#ifdef FASTCAE_HAS_OPENMP
#pragma omp parallel for shared(colorArray, spliters)
#endif
		for (int i = 0; i < nprocess; ++i)
		{
			int beg = spliters[i];
			int end = spliters[i + 1];
			serial(beg, end);
		}

		_displayData->Modified();
	}

	void MeshKernalViewObj::setPointDisplayColorByDisplayIndex(QList<int> &indexs, const QColor &color)
	{
		vtkDataArray *colorArray = _displayData->GetPointData()->GetScalars();
		vtkDataArray *indexArray = _displayData->GetPointData()->GetArray("IDS");
		if (nullptr == colorArray || nullptr == indexArray)
			return;
		double col[3]{color.red(), color.green(), color.blue()};
		for (int index : indexs)
		{
			colorArray->SetComponent(index, 0, col[0]);
			colorArray->SetComponent(index, 1, col[1]);
			colorArray->SetComponent(index, 2, col[2]);
		}
		_displayData->Modified();
	}

	void MeshKernalViewObj::setCellDisplayColorByDisplayIndex(QList<int> &indexs, const QColor &color)
	{
		vtkDataArray *colorArray = _displayData->GetCellData()->GetScalars();
		vtkDataArray *indexArray = _displayData->GetCellData()->GetArray("IDS");
		if (nullptr == colorArray || nullptr == indexArray)
			return;
		double col[3]{color.red(), color.green(), color.blue()};
		for (int index : indexs)
		{
			colorArray->SetComponent(index, 0, col[0]);
			colorArray->SetComponent(index, 1, col[1]);
			colorArray->SetComponent(index, 2, col[2]);
		}
		_displayData->Modified();
	}

	void MeshKernalViewObj::showCells(const QList<int> &indexs, bool show)
	{
		auto dataSet = _kernal->getMeshData();
		vtkDataArray *showArray = dataSet->GetCellData()->GetArray("SHOW");
		if (showArray == nullptr)
			return;
		int value = 0;
		if (show)
			value = 1;
		for (int index : indexs)
			showArray->SetComponent(index, 0, value);

		this->updateDisplayMember();
	}

	void MeshKernalViewObj::highLight()
	{
		auto gp = Setting::BusAPI::instance()->getGraphOption();
		QColor color = gp->getHighLightColor();
		_actor[POINTACTOR]->GetMapper()->SetScalarVisibility(false);
		_actor[EDGEACTOR]->GetMapper()->SetScalarVisibility(false);
		_actor[FACEACTOR]->GetMapper()->SetScalarVisibility(false);

		_actor[POINTACTOR]->GetProperty()->SetColor(color.red(), color.green(), color.blue());
		_actor[EDGEACTOR]->GetProperty()->SetColor(color.red(), color.green(), color.blue());
		_actor[FACEACTOR]->GetProperty()->SetColor(color.red(), color.green(), color.blue());

		_isKernalHighLight = true;
	}

	void MeshKernalViewObj::clearHighLight()
	{
		auto gp = Setting::BusAPI::instance()->getGraphOption();
		QColor color = gp->getMeshEdgeColor();
		_actor[POINTACTOR]->GetMapper()->SetScalarVisibility(true);
		_actor[EDGEACTOR]->GetMapper()->SetScalarVisibility(true);
		_actor[FACEACTOR]->GetMapper()->SetScalarVisibility(true);
		if (gp->isShowMeshEdge() && gp->isShowMeshFace())
		{
			_actor[EDGEACTOR]->GetMapper()->SetScalarVisibility(false);
			_actor[EDGEACTOR]->GetProperty()->SetColor(color.red(), color.green(), color.blue());
		}

		_isKernalHighLight = false;
	}

	bool MeshKernalViewObj::isKernalHighLight()
	{
		return _isKernalHighLight;
	}

	void MeshKernalViewObj::generateIDProp()
	{
		auto dataset = _kernal->getMeshData();
		const int id = _kernal->getID();
		// cell ID与显示隐藏状态
		vtkSmartPointer<vtkUnsignedIntArray> kcellid_index = vtkSmartPointer<vtkUnsignedIntArray>::New();
		kcellid_index->SetNumberOfComponents(2);
		kcellid_index->SetName("IDS");
		const int ncell = dataset->GetNumberOfCells();
		for (int i = 0; i < ncell; ++i)
			kcellid_index->InsertNextTuple2(id, i);
		dataset->GetCellData()->AddArray(kcellid_index);

		vtkSmartPointer<vtkUnsignedIntArray> cstatesArray = vtkSmartPointer<vtkUnsignedIntArray>::New();
		cstatesArray->SetName("SHOW");
		cstatesArray->SetNumberOfValues(ncell);
		cstatesArray->Fill(1);
		dataset->GetCellData()->AddArray(cstatesArray);

		// point ID与显示隐藏状态
		vtkSmartPointer<vtkUnsignedIntArray> kpointid_index = vtkSmartPointer<vtkUnsignedIntArray>::New();
		kpointid_index->SetNumberOfComponents(2);
		kpointid_index->SetName("IDS");
		const int npoint = dataset->GetNumberOfPoints();
		for (int i = 0; i < npoint; ++i)
			kpointid_index->InsertNextTuple2(id, i);
		dataset->GetPointData()->AddArray(kpointid_index);

		vtkSmartPointer<vtkUnsignedIntArray> pstatesArray = vtkSmartPointer<vtkUnsignedIntArray>::New();
		pstatesArray->SetName("SHOW");
		pstatesArray->SetNumberOfValues(npoint);
		pstatesArray->Fill(1);
		dataset->GetPointData()->AddArray(pstatesArray);
	}

	void MeshKernalViewObj::init()
	{
		vtkSmartPointer<vtkAppendFilter> filter = vtkSmartPointer<vtkAppendFilter>::New();
		filter->AddInputData(_kernal->getMeshData());
		filter->Update();
		_displayData->DeepCopy(filter->GetOutput());

		auto gp = Setting::BusAPI::instance()->getGraphOption();

		setCellColor(gp->getMeshFaceColor());
		setPointColor(gp->getMeshNodeColor());

		vtkSmartPointer<vtkDataSetMapper> pointMapper = vtkSmartPointer<vtkDataSetMapper>::New();
		pointMapper->SetInputData(_displayData);
		pointMapper->SetScalarModeToUsePointData();
		_actor[POINTACTOR]->SetMapper(pointMapper);
		_actor[POINTACTOR]->GetProperty()->SetRepresentationToPoints();

		vtkSmartPointer<vtkDataSetMapper> edgeMapper = vtkSmartPointer<vtkDataSetMapper>::New();
		edgeMapper->SetInputData(_displayData);
		edgeMapper->SetScalarModeToUseCellData();
		_actor[EDGEACTOR]->SetMapper(edgeMapper);
		_actor[EDGEACTOR]->GetProperty()->SetRepresentationToWireframe();

		vtkSmartPointer<vtkDataSetMapper> faceMapper = vtkSmartPointer<vtkDataSetMapper>::New();
		faceMapper->SetInputData(_displayData);
		faceMapper->SetScalarModeToUseCellData();
		_actor[FACEACTOR]->SetMapper(faceMapper);
		_actor[FACEACTOR]->GetProperty()->SetRepresentationToSurface();
	}

	void MeshKernalViewObj::updateDisplayMember()
	{
		auto dataset = _kernal->getMeshData();
		vtkDataArray *array = dataset->GetCellData()->GetArray("SHOW");
		if (array == nullptr)
			return;

		vtkSmartPointer<vtkIdTypeArray> idArray = vtkSmartPointer<vtkIdTypeArray>::New();
		const int n = array->GetNumberOfTuples();
		for (int i = 0; i < n; ++i)
		{
			double v = fabs(array->GetComponent(i, 0));
			if (v > 0.5)
				idArray->InsertNextValue(i);
		}
		vtkSmartPointer<vtkSelectionNode> selectionNode = vtkSmartPointer<vtkSelectionNode>::New();
		selectionNode->SetFieldType(vtkSelectionNode::CELL);
		selectionNode->SetContentType(vtkSelectionNode::INDICES);
		selectionNode->SetSelectionList(idArray);
		vtkSmartPointer<vtkSelection> selection = vtkSmartPointer<vtkSelection>::New();
		selection->AddNode(selectionNode);

		vtkSmartPointer<vtkExtractSelection> extractionSelection = vtkSmartPointer<vtkExtractSelection>::New();
		extractionSelection->SetInputData(0, dataset);
		extractionSelection->SetInputData(1, selection);
		extractionSelection->Update();

		_displayData->DeepCopy(extractionSelection->GetOutput());
		_displayData->Modified();
	}

}
