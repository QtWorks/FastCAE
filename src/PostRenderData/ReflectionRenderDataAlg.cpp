#include "ReflectionRenderDataAlg.h"
#include "RenderDataManager.h"
#include <vtkReflectionFilter.h>


namespace Post {

	ReflectionRenderDataAlg::ReflectionRenderDataAlg(RenderDataObject* obj):
		RenderDataAlgorithm(obj)
	{
		this->setAlgoType(AlgorithmType::Reflection);
		CreateVTKSmartPtr(vtkReflectionFilter, _vtkAlg);
	}

	ReflectionRenderDataAlg::~ReflectionRenderDataAlg()
	{

	}

	void ReflectionRenderDataAlg::updateParam()
	{
		auto parent = this->getParentObj();
		if (parent == nullptr) return;

		if (_selectedObjects.size() < 1) return;

		auto reflection = vtkReflectionFilter::SafeDownCast(_vtkAlg);
		if (reflection == nullptr) return;

		combineSelectedObjects();

		if (_isCombination)
		{
			if (_append == nullptr)return;
			reflection->SetInputConnection(_append->GetOutputPort());
		}
		else
		{
			auto id = _selectedObjects.uniqueKeys().at(0);
			auto obj = RenderDataManager::getInstance()->getObjectByID(id);
			if (obj == nullptr) return;
			auto v = _selectedObjects.values(id).at(0);	
			reflection->SetInputConnection(obj->getOutputPort(v + 1));
		}

		reflection->SetPlane(_Plane);
		reflection->SetCopyInput(_CopyInput);
		reflection->SetCenter(_Center);

		_mapper->SetInputConnection(_vtkAlg->GetOutputPort());
	}

}
