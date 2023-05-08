#include "StreamLineRenderDataAlg.h"
#include "RenderDataManager.h"
#include "PostAlgorithm/GlyphingAlgorithm.h"
#include <vtkStreamTracer.h>
#include <vtkActor.h>
#include <vtkPolyData.h>
#include <vtkDataSet.h>
#include <vtkPointData.h>
#include <vtkMaskPoints.h>
#include <vtkArrowSource.h>
#include <vtkProperty.h>

namespace Post {
	StreamLineRenderDataAlg::StreamLineRenderDataAlg(RenderDataObject* parent)
		:RenderDataAlgorithm(parent)
	{
		CreateVTKSmartPtr(vtkLineSource, _line)
			CreateVTKSmartPtr(vtkStreamTracer, _vtkAlg)

// 			auto trace = vtkStreamTracer::SafeDownCast(_vtkAlg);
// 		trace->SetSourceConnection(_line->GetOutputPort());
// 		_mapper->SetInputConnection(_vtkAlg->GetOutputPort());
// 
// 		if (parent != nullptr)
// 			this->setInputConnection(parent->getOutputPort());

		CreateVTKSmartPtr(GlyphingAlgorithm, _glyph3D)
//CreateVTKSmartPtr(vtkGlyph3D, _glyph3D)
			CreateVTKSmartPtr(vtkDataSetMapper, _vecMapper)
			DecCreVTKSmartPtr(vtkActor, actor)
			actor->SetMapper(_vecMapper);
		_vecMapper->SetScalarVisibility(false);
		//_vecMapper->SetInputConnection(_glyph3D->GetOutputPort());
		actor->GetProperty()->SetColor(0, 0, 0);
		_assistActors->AddPart(actor);
		_AssistActors.append(actor);
	}

	StreamLineRenderDataAlg::~StreamLineRenderDataAlg()
	{
		//   _line->Delete();
	}

	void StreamLineRenderDataAlg::setLineSource(double* start, double* end)
	{
		if (_line == nullptr) return;
		_line->SetPoint1(start);
		_line->SetPoint2(end);
	}

	void StreamLineRenderDataAlg::updateParam()
	{
		auto parent = this->getParentObj();
		if (parent == nullptr) return;

		if (_selectedObjects.size() < 1) return;

		auto trace = vtkStreamTracer::SafeDownCast(_vtkAlg);
		if (trace == nullptr) return;

		_line->SetResolution(_SeedCount);
		trace->SetSourceConnection(_line->GetOutputPort());

		combineSelectedObjects();

		if (_isCombination)
		{
			if (_append == nullptr) return;
			trace->SetInputConnection(_append->GetOutputPort());
		}
		else
		{
			auto id = _selectedObjects.uniqueKeys().at(0);
			auto obj = RenderDataManager::getInstance()->getObjectByID(id);
			if (obj == nullptr) return;
			auto v = _selectedObjects.values(id).at(0);
			trace->SetInputConnection(obj->getOutputPort(v + 1));
		}

		QString2Char(_Vector, v)
			if (_UsePointData)
				trace->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, v);
			else
				trace->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_CELLS, v);

		trace->SetIntegratorTypeToRungeKutta45();
		trace->SetMaximumPropagation(_MaxLength);//设置流线长度
		trace->SetIntegrationStepUnit(2);//设置流线积分步长单位
		trace->SetInitialIntegrationStep(_InitStep);//设置流线积分初始步长
		trace->SetMinimumIntegrationStep(_MinStep);//设置流线积分最小步长
		trace->SetMaximumIntegrationStep(_MaxStep);//设置流线积分最大步长
		trace->SetMaximumNumberOfSteps(_StepNumber);//设置流线积分最大步数
		trace->SetTerminalSpeed(1e-12);//设置流线积分终止速度
		trace->SetMaximumError(1e-6);
		trace->SetComputeVorticity(true);

		switch (_Direction)
		{
		case 1:trace->SetIntegrationDirectionToForward(); break;
		case 2:trace->SetIntegrationDirectionToBackward(); break;
		default:trace->SetIntegrationDirectionToBoth(); break;//设置流线积分方向
		}

		_mapper->SetInputConnection(trace->GetOutputPort());
		//trace->Update();

		//addActorGlyph(trace->GetOutput());

		_glyph3D->SetInputConnection(trace->GetOutputPort());
		_glyph3D->setMaxNumber(_ArrowCount);
		_glyph3D->setScaleFactor(_ArrowFactor);
		_glyph3D->setPointDataUsed(_UsePointData);
		_glyph3D->setVectorName(_Vector);

		//_glyph3D->Update();

		_vecMapper->SetInputConnection(_glyph3D->GetOutputPort());
		//_vecMapper->Update();
	}


	void StreamLineRenderDataAlg::setArrowColor(double* rgb)
	{
		if (rgb == nullptr) return;
		auto actor = _AssistActors.at(0);
		actor->GetProperty()->SetColor(rgb);

	}

	void StreamLineRenderDataAlg::updateAlg()
	{
		//RenderDataObject::updateAlg();
		_glyph3D->Update();
	}

	void StreamLineRenderDataAlg::update()
	{
		//RenderDataObject::update();
		_vecMapper->Update();
	}

	void StreamLineRenderDataAlg::addActorGlyph(vtkDataSet* dataset)
	{
		QString2Char(_Vector, v)
			auto array = dataset->GetPointData()->GetArray(v);

		vtkNew<vtkPoints> points;
		const int nPoints = dataset->GetNumberOfPoints();
		for (vtkIdType i = 0; i < nPoints; i++)
		{
			double* p;
			p = dataset->GetPoint(i);
			points->InsertNextPoint(p);
		}
		vtkNew<vtkPolyData> polyData;
		polyData->SetPoints(points);
		polyData->GetPointData()->SetNormals(array);

		vtkNew<vtkMaskPoints> maskPoints;
		maskPoints->SetInputData(polyData);
		maskPoints->SetMaximumNumberOfPoints(_ArrowCount);
		maskPoints->SetOnRatio(_Ratio);
		maskPoints->SetRandomModeType(2);
		maskPoints->Update();

		vtkSmartPointer<vtkArrowSource> Glyph2d = vtkSmartPointer<vtkArrowSource>::New();
		Glyph2d->SetTipResolution(_TipResolution);
		Glyph2d->SetTipRadius(_TipRadius);
		Glyph2d->SetTipLength(_TipLength);
		Glyph2d->SetShaftResolution(_ShaftResolution);
		Glyph2d->SetShaftRadius(_ShaftRadius);
		Glyph2d->Update();

// 		_glyph3D->SetSourceConnection(Glyph2d->GetOutputPort());//设置之前设置好的矢量箭头为矢量符号
// 		_glyph3D->SetInputConnection(maskPoints->GetOutputPort());//设置通过maskpoints过滤的点数据为输入数据	
// 		_glyph3D->SetOrient(1);
// 		_glyph3D->SetVectorModeToUseNormal();
// 		_glyph3D->SetScaleMode(1);//开启箭头比例缩放模式
// 		_glyph3D->SetScaleModeToDataScalingOff();//关闭箭头随速度或者标量大小而变化
// 		_glyph3D->SetScaleFactor(_ArrowFactor);//控制箭头比例，大小
// 		_glyph3D->Update();
// 
// 		_assistActors->SetVisibility(_ShowArrow);
// 		_vecMapper->SetInputConnection(_glyph3D->GetOutputPort());
	}

	void StreamLineRenderDataAlg::setShowArrow(bool v)
	{
		_ShowArrow = v;
		_assistActors->SetVisibility(v);
	}
}