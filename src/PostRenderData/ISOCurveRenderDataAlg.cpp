#include "ISOCurveRenderDataAlg.h"
#include "RenderDataManager.h"
#include <vtkContourFilter.h>
#include <vtkDataSet.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPointData.h>
#include <QDebug>

namespace Post {
	ISOCurveRenderDataAlg::ISOCurveRenderDataAlg(RenderDataObject* parent)
		:ISORenderDataAlg(parent)
	{
		this->setAlgoType(ISOCurve);
		CreateVTKSmartPtr(vtkDataSetSurfaceFilter, _surfaceFilter)
		CreateVTKSmartPtr(vtkContourFilter, _vtkAlg);

// 		CreateVTKSmartPtr(vtkDataSetSurfaceFilter, _surfaceFilter)
// 			_vtkAlg->SetInputConnection(_surfaceFilter->GetOutputPort());
// 		_surfaceFilter->SetInputConnection(parent->getOutputPort());
	}

	void ISOCurveRenderDataAlg::updateParam()
	{
		auto parent = this->getParentObj();
		if (parent == nullptr) return;

		if (_selectedObjects.size() < 1) return;
		if (_surfaceFilter == nullptr) return;

		auto ISOAlg = vtkContourFilter::SafeDownCast(_vtkAlg);
		if (ISOAlg == nullptr) return;

		QString2Char(this->getVariable(), var)

		combineSelectedObjects();

		if (_isCombination)
		{
			if (_append == nullptr) return;
			_surfaceFilter->SetInputConnection(_append->GetOutputPort());
		}
		else
		{
			auto id = _selectedObjects.uniqueKeys().at(0);
			auto obj = RenderDataManager::getInstance()->getObjectByID(id);
			if (obj == nullptr) return;
			auto v = _selectedObjects.values(id).at(0);
			_surfaceFilter->SetInputConnection(obj->getOutputPort(v + 1));
		}

		_surfaceFilter->Update();
		_surfaceFilter->GetOutput()->GetPointData()->SetActiveScalars(var);
		ISOAlg->SetInputConnection(_surfaceFilter->GetOutputPort());
	
		const int count = _valueList.size();
		ISOAlg->SetNumberOfContours(count);
		for (int i = 0; i < count; i++)
		{
			ISOAlg->SetValue(i, _valueList.at(i));
		}
		ISOAlg->SetComputeScalars(true);
		ISOAlg->SetComputeNormals(true);
		ISOAlg->SetComputeGradients(true);

		_mapper->SetInputConnection(ISOAlg->GetOutputPort());
	}
}

