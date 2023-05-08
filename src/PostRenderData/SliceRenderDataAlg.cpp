#include "SliceRenderDataAlg.h"
#include "RenderDataManager.h"
#include <vtkCutter.h>

namespace Post {
	SliceRenderDataAlg::SliceRenderDataAlg(RenderDataObject* parent)
		:RenderDataAlgorithm(parent)
	{
		this->setAlgoType(Slice);
		CreateVTKSmartPtr(vtkCutter, _vtkAlg)
		CreateVTKSmartPtr(vtkPlane, _plane)
	}

	SliceRenderDataAlg::~SliceRenderDataAlg()
	{
		//   _plane->Delete();
	}

	void SliceRenderDataAlg::setPlaneOri(double* ori)
	{
		_origin[0] = ori[0];
		_origin[1] = ori[1];
		_origin[2] = ori[2];
	}

	void SliceRenderDataAlg::getPlaneOrigin(double* origin)
	{
		origin[0] = _origin[0];
		origin[1] = _origin[1];
		origin[2] = _origin[2];
	}

	void SliceRenderDataAlg::setPlaneNormal(double* normal)
	{
		_normal[0] = normal[0];
		_normal[1] = normal[1];
		_normal[2] = normal[2];
	}

	void SliceRenderDataAlg::getPlaneNormal(double* normal)
	{
		normal[0] = _normal[0];
		normal[1] = _normal[1];
		normal[2] = _normal[2];
	}

	void SliceRenderDataAlg::updateParam()
	{
		auto parent = this->getParentObj();
		if (parent == nullptr) return;

		if (_selectedObjects.size() < 1) return;

		auto cut = vtkCutter::SafeDownCast(_vtkAlg);
		if (cut == nullptr) return;

		combineSelectedObjects();

		if (_isCombination)
		{
			if (_append == nullptr) return;
			cut->SetInputConnection(_append->GetOutputPort());
		}
		else
		{
			auto id = _selectedObjects.uniqueKeys().at(0);
			auto obj = RenderDataManager::getInstance()->getObjectByID(id);
			if (obj == nullptr) return;
			auto v = _selectedObjects.values(id).at(0);
			cut->SetInputConnection(obj->getOutputPort(v + 1));
		}

		_plane->SetNormal(_normal);
		_plane->SetOrigin(_origin);
		cut->SetCutFunction(_plane);

		_mapper->SetInputConnection(cut->GetOutputPort());
	}

}