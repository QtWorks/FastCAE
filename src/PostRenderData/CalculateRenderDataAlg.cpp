#include "CalculateRenderDataAlg.h"
#include "RenderDataManager.h"
#include <vtkArrayCalculator.h>

namespace Post {
	CalculateRenderDataAlg::CalculateRenderDataAlg(RenderDataObject* parent)
		:RenderDataAlgorithm(parent)
	{
		this->setAlgoType(Calculator);
		CreateVTKSmartPtr(vtkArrayCalculator, _vtkAlg);
//		CreateVTKSmartPtr(vtkArrayCalculator, _vtkAlg)
//
// 			auto cal = vtkArrayCalculator::SafeDownCast(_vtkAlg);
// 		cal->SetAttributeTypeToPointData();
// 		cal->RemoveAllVariables();
// 
// 		_mapper->SetInputConnection(_vtkAlg->GetOutputPort());
// 		if (parent != nullptr)
// 			_vtkAlg->SetInputConnection(parent->getOutputPort());
	}

	void CalculateRenderDataAlg::updateParam()
	{
		auto parent = this->getParentObj();
		if (parent == nullptr) return;

		if (_selectedObjects.size() < 1) return;

		auto cal = vtkArrayCalculator::SafeDownCast(_vtkAlg);
		if (cal == nullptr) return;

		combineSelectedObjects();

		if (_isCombination)
		{
			if (_append == nullptr)return;
			cal->SetInputConnection(_append->GetOutputPort());
		}
		else
		{
			auto id = _selectedObjects.uniqueKeys().at(0);
			auto obj = RenderDataManager::getInstance()->getObjectByID(id);
			if (obj == nullptr) return;
			auto v = _selectedObjects.values(id).at(0);
			cal->SetInputConnection(obj->getOutputPort(v + 1));
		}
		

		cal->RemoveAllVariables();
		if (_UsePointData)
			cal->SetAttributeTypeToPointData();
		else
			cal->SetAttributeTypeToCellData();

		for (QString va : _InputScalars)
		{
			QString2Char(va, v)
				cal->AddScalarArrayName(v);
		}

		for (QString va : _InputVectors)
		{
			QString2Char(va, v)
				cal->AddVectorArrayName(v);
		}

		QString2Char(_Function, function)
			cal->SetFunction(function);

		{QString2Char(_ResultArrayName, res)
			cal->SetResultArrayName(res); }

		_mapper->SetInputConnection(_vtkAlg->GetOutputPort());
	}

}