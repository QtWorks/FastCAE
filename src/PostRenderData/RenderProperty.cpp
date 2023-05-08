#include "RenderDataObject.h"
#include "RenderProperty.h"
#include <vtkDataSet.h>
#include <vtkPointData.h>
#include <vtkCellData.h>
#include <vtkDataArray.h>
#include <vtkScalarBarActor.h>
#include <vtkProperty.h>
#include <vtkAssembly.h>
#include <vtkProp3DCollection.h>
#include <vtkTextProperty.h>
#include <vtkBorderRepresentation.h>
#include <QDebug>

namespace Post {
	RenderProperty::RenderProperty(RenderDataObject* vobj, vtkMapper* mapper, vtkActor* actor) :
		_renderDataObj(vobj),
		_mapper(mapper),
		_actor(actor)
	{
		if (_actor != nullptr)
		{
			auto pro = _actor->GetProperty();
			if (pro != nullptr)
				pro->GetColor(_color);
		}

		this->initScalarBar();
	}

	void RenderProperty::setCurrentVariable(int type, QString vaName, int componentIndex /*= -1*/)
	{
		//auto mapper = _renderDataObj->_Mappers.at(_index);
		if (_mapper == nullptr) return;

		//_variableColor = true;

		if (type == 0)
			_mapper->SetScalarVisibility(false);
		else
			_mapper->SetScalarVisibility(true);

		switch (type)
		{
		case 1: _mapper->SetScalarModeToUsePointFieldData(); break;
		case 2: _mapper->SetScalarModeToUseCellFieldData(); break;
		default: break;
		}
		QString2Char(vaName, va)

		_mapper->SelectColorArray(va);
		_mapper->SetArrayComponent(componentIndex);
		double range[2] = { 0,0 };
//		this->getRange(range, type, vaName, componentIndex);
		_renderDataObj->getRange(range, type, vaName, componentIndex);
		if (fabs(range[0] - range[1]) < 1e-6)
		{
			if (fabs(range[0]) < 1e-6)
			{
				range[0] = -1e-5;
				range[1] = 1e-5;
			}
			else
			{
				range[0] -= range[0] * 0.0001;
				range[1] += range[1] * 0.0001;
			}

		}
		_mapper->SetScalarRange(range);
		_mapper->Update();


		//QString2Char(vaName, va)
		//auto sBar = _renderDataObj->getScalarBarWidget();
		if (_scalarBar != nullptr)
			_scalarBar->GetScalarBarActor()->SetTitle(va);

		_VariableType = type;
		_VariableName = vaName;
		_ComponentIndex = componentIndex;// 记录设置
		if (type == 0)
			_scalarBar->Off();
		else
		{
			if (_ShowColorMap) _scalarBar->On();
			else _scalarBar->Off();
		}


	}

	void RenderProperty::updateScalarBar(vtkRenderWindowInteractor* interactor)
	{
		if (_scalarBar == nullptr) return;
		if (interactor != nullptr)
			_scalarBar->SetInteractor(interactor);
		if (interactor == nullptr) _scalarBar->Off();
		if (_ShowColorMap) _scalarBar->On();
		else _scalarBar->Off();
	}

	void RenderProperty::setColorMapProperty(int level, double min, double max)
	{
		_scalarBar->GetScalarBarActor()->SetNumberOfLabels(level);
		_lookupTable->SetRange(min, max);
		_mapper->SetScalarRange(min, max);
		_mapper->Update();
		// 		for (auto mapper : _viewDataObj->_Mappers)
		// 		{
		// 			mapper->SetScalarRange(min, max);
		// 			mapper->Update();
		// 		}
	}

	void RenderProperty::setColorMapColor(int index, double r, double g, double b)
	{
		//qDebug() << _renderDataObj->_LookupTable->GetNumberOfColors();
		_lookupTable->SetTableValue(index, r, g, b);
		_mapper->Update();
// 		for (auto mapper : _viewDataObj->_Mappers)
// 			mapper->Update();
	}

// 	void RenderProperty::getRange(double* range, int type, QString vaName, int componentIndex)
// 	{
// 		vtkDataSet* data = _renderDataObj->getOutputData();
// 		if (data == nullptr) return;
// 		QString2Char(vaName, cName)
// 			vtkDataArray* dataArray = nullptr;
// 		if (type == 1)
// 			dataArray = data->GetPointData()->GetArray(cName);
// 		else if (type == 2)
// 			dataArray = data->GetCellData()->GetArray(cName);
// 		if (dataArray == nullptr) return;
// 
// 		dataArray->GetRange(range, componentIndex);
// 	}

	void RenderProperty::updateColorScaleNums(int num)
	{
		_lookupTable->SetNumberOfColors(num);
// 		for (auto mapper : _renderDataObj->_Mappers)
// 		{
// 			_mapper->Update();
// 		}
		_mapper->Update();
	}

	void RenderProperty::getPropertyColor(double* color)
	{
		auto pro = _actor->GetProperty();
		if (pro == nullptr) return;
		pro->GetColor(_color);
		color[0] = _color[0];
		color[1] = _color[1];
		color[2] = _color[2];
	}

	void RenderProperty::setPropertyColor(double r, double g, double b)
	{
		_color[0] = r;
		_color[1] = g;
		_color[2] = b;

		if (_actor == nullptr)return;

		auto pro = _actor->GetProperty();
		if (pro == nullptr) return;

		//_variableColor = false;
		_VariableType = 0;
		pro->SetColor(_color);

		_mapper->SetScalarVisibility(false);
		_mapper->Update();
	}

// 	bool RenderProperty::isVariableColor()
// 	{
// 		return false;//_variableColor;
// 	}

	void RenderProperty::initScalarBar()
	{
		DecCreVTKSmartPtr(vtkTextProperty, propLable)
		propLable->SetBold(0);
		propLable->SetItalic(0);
		propLable->SetShadow(0);
		propLable->SetJustification(VTK_TEXT_LEFT);
		propLable->SetColor(0, 0, 0);
		propLable->SetFontSize(14);

		CreateVTKSmartPtr(vtkScalarBarWidget, _scalarBar)
		_scalarBar->GetScalarBarActor()->SetVerticalTitleSeparation(1);
		_scalarBar->GetScalarBarActor()->SetBarRatio(0.2);
		_scalarBar->GetBorderRepresentation()->SetPosition(0.90, 0.05);
		_scalarBar->GetBorderRepresentation()->SetPosition2(0.08, 0.45);
		_scalarBar->GetBorderRepresentation()->SetShowBorderToOff();
		_scalarBar->GetScalarBarActor()->SetTitleTextProperty(propLable);
		_scalarBar->GetScalarBarActor()->SetLabelTextProperty(propLable);
		_scalarBar->GetScalarBarActor()->SetUnconstrainedFontSize(true);

		CreateVTKSmartPtr(vtkLookupTable, _lookupTable)
		_lookupTable->SetHueRange(0.66667, 0.0);
		_lookupTable->SetNumberOfColors(255);
		_lookupTable->Build();
		_scalarBar->GetScalarBarActor()->SetLookupTable(_lookupTable);
		_mapper->SetLookupTable(_lookupTable);
	}

	void RenderProperty::setShowColorMap(bool V)
	{
		if (_scalarBar == nullptr) return;
		if (_VariableType == 0)
		{
			_scalarBar->Off();
			return;
		}
		_ShowColorMap = V;
		if (_ShowColorMap)
			_scalarBar->On();
		else
			_scalarBar->Off();

	}

	void RenderProperty::setTransparency(double V)
	{
		_Transparency = V;
// 		auto ass = _viewDataObj->getAssembly();
// 		if (ass == nullptr) return;
// 		auto collect = ass->GetParts();
// 		if (collect == nullptr) return;
// 		collect->InitTraversal();
// 		int nc = collect->GetNumberOfItems();
// 		for (int i = 0; i < nc; ++i)
// 		{
// 			auto prop3D = collect->GetNextProp3D();
// 			auto actor = vtkActor::SafeDownCast(prop3D);
// 			if (actor == nullptr) continue;
// 			auto prop = actor->GetProperty();
// 			if (prop == nullptr) continue;
// 			prop->SetOpacity(V);
// 		}
		if (_actor == nullptr) return;
		auto prop = _actor->GetProperty();
		prop->SetOpacity(V);
	}

	void RenderProperty::setDisplayMode(int V)
	{
		_DisplayMode = V;
		// 		auto actors = _renderDataObj->_actors;
		// 
		// 		if (actors == nullptr) return;
		// 		auto collect = actors->GetParts();
		// 		if (collect == nullptr) return;
		// 		collect->InitTraversal();
		// 		int nc = collect->GetNumberOfItems();
		// 		for (int i = 0; i < nc; ++i)
		// 		{
		// 			auto prop3D = collect->GetNextProp3D();
		// 			auto actor = vtkActor::SafeDownCast(prop3D);
		// 			auto property = actor->GetProperty();
		// 			switch (V)
		// 			{
		// 			case 0: property->SetRepresentationToPoints(); break;
		// 			case 1: property->SetRepresentationToWireframe(); break;
		// 			case 2: property->SetRepresentationToSurface(); property->SetEdgeVisibility(false); break;
		// 			case 3: property->SetRepresentationToSurface(); property->SetEdgeVisibility(true); break;
		// 			default: break;
		// 			}
		// 		}

		auto property = _actor->GetProperty();
		switch (V)
		{
		case 0: property->SetRepresentationToPoints(); break;
		case 1: property->SetRepresentationToWireframe(); break;
		case 2: property->SetRepresentationToSurface(); property->SetEdgeVisibility(false); break;
		case 3: property->SetRepresentationToSurface(); property->SetEdgeVisibility(true); break;
		default: break;
		}

	}


	void RenderProperty::setShowStatus(bool V)
	{
		_ShowStatus = V;
		_actor->SetVisibility(V);
		if (!V) _scalarBar->Off();
		else
		{
			bool show = false;
			if (show) _scalarBar->On();
			else _scalarBar->Off();
		}
	}
}