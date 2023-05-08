#include "ClipRenderDataAlg.h"
#include "RenderDataManager.h"
#include <vtkTableBasedClipDataSet.h>
#include <vtkDataSet.h>
 
namespace Post {
	ClipRenderDataAlg::ClipRenderDataAlg(RenderDataObject* parent)
		:RenderDataAlgorithm(parent)
	{
		this->setAlgoType(Clip);
		CreateVTKSmartPtr(vtkTableBasedClipDataSet, _vtkAlg)
		CreateVTKSmartPtr(vtkPlane, _plane)
		
	}

	ClipRenderDataAlg::~ClipRenderDataAlg()
	{
		//   _plane->Delete();
	}

	void ClipRenderDataAlg::setPlaneOri(double* ori)
	{
		_origin[0] = ori[0];
		_origin[1] = ori[1];
		_origin[2] = ori[2];
	}

	void ClipRenderDataAlg::getPlaneOrigin(double* origin)
	{
		origin[0] = _origin[0];
		origin[1] = _origin[1];
		origin[2] = _origin[2];
	}

	void ClipRenderDataAlg::setPlaneNormal(double* normal)
	{
		_normal[0] = normal[0];
		_normal[1] = normal[1];
		_normal[2] = normal[2];
	}

	void ClipRenderDataAlg::getPlaneNormal(double* normal)
	{
		normal[0] = _normal[0];
		normal[1] = _normal[1];
		normal[2] = _normal[2];
	}

	void ClipRenderDataAlg::updateParam()
	{
		auto parent = this->getParentObj();
		if (parent == nullptr) return;

		if (_selectedObjects.size() < 1) return;

		auto clip = vtkTableBasedClipDataSet::SafeDownCast(_vtkAlg);
		if (clip == nullptr) return;

		combineSelectedObjects();

		if (_isCombination)
		{
			if (_append == nullptr) return;
			clip->SetInputConnection(_append->GetOutputPort());
		}
		else
		{
			auto id = _selectedObjects.uniqueKeys().at(0);
			auto obj = RenderDataManager::getInstance()->getObjectByID(id);
			if (obj == nullptr) return;
			auto v = _selectedObjects.values(id).at(0);
			clip->SetInputConnection(obj->getOutputPort(v + 1));	
		}

		_plane->SetNormal(_normal);
		_plane->SetOrigin(_origin);
		clip->SetClipFunction(_plane);
		clip->SetInsideOut(_InsideOut);

		_mapper->SetInputConnection(clip->GetOutputPort());
	}

}