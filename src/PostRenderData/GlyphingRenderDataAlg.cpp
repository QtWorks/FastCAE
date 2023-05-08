#include "GlyphingRenderDataAlg.h"
#include "RenderDataManager.h"
#include "PostAlgorithm/GlyphingAlgorithm.h"
#include <vtkGlyph3D.h>
#include <vtkPointData.h>
#include <vtkDataSet.h>
#include <vtkAppendFilter.h>

namespace Post {
	GlyphingRenderDataAlg::GlyphingRenderDataAlg(RenderDataObject* parent)
		:RenderDataAlgorithm(parent)
	{
		this->setAlgoType(Vector);
		CreateVTKSmartPtr(GlyphingAlgorithm, _vtkAlg);
	}

	GlyphingRenderDataAlg::~GlyphingRenderDataAlg()
	{

	}

	void GlyphingRenderDataAlg::updateParam()
	{
		auto parent = this->getParentObj();
		if (parent == nullptr) return;

		if (_selectedObjects.size() < 1) return;

		auto glyph = GlyphingAlgorithm::SafeDownCast(_vtkAlg);
		if (glyph == nullptr) return;

		combineSelectedObjects();
		
		if (_isCombination)
		{
			if (_append == nullptr)return;
			glyph->SetInputConnection(_append->GetOutputPort());
		}
		else
		{
			auto id = _selectedObjects.uniqueKeys().at(0);
			auto obj = RenderDataManager::getInstance()->getObjectByID(id);
			if (obj == nullptr) return;
			auto v = _selectedObjects.values(id).at(0);
			glyph->SetInputConnection(obj->getOutputPort(v + 1));
// 			if (v == -1)
// 				glyph->SetInputConnection(obj->getOutputPort());
// 				/*glyph->SetInputData(obj->getOutputData());*/
// 			else
// 				glyph->SetInputConnection(obj->getOutputPort(v + 1));
// 				/*glyph->SetInputData(obj->getOutputData(v + 1));*/
		}

		glyph->setMaxNumber(_MaxNumber);
		glyph->setVectorName(_Vector);
		glyph->setPointDataUsed(_UsePointData);
		glyph->setScaleFactor(_ScaleFactor);
		glyph->setTipResolution(_TipResolution);
		glyph->setTipRadius(_TipRadius);
		glyph->setTipLength(_TipLength);
		glyph->setShaftResolution(_ShaftResolution);
		glyph->setShaftRadius(_ShaftRadius);
		glyph->setScaleMode(_ScaleMode);

		_mapper->SetInputConnection(glyph->GetOutputPort());
	}

// 	void GlyphingRenderDataAlg::combineSelectedObjects()
// 	{
// 		CreateVTKSmartPtr(vtkAppendFilter, _append);
// 
// 		_isCombination = false;
// 
// 		auto appendToFilter = [&](RenderDataObject*obj ,QList<int> list) {
// 			for (auto v : list)
// 			{
// 				_append->AddInputData(obj->getOutputData(v + 1));
// 			}
// 		};
// 
// 		if (_selectedObjects.size() == 1)
// 		{
// 			auto id = _selectedObjects.uniqueKeys().at(0);
// 			auto obj = RenderDataManager::getInstance()->getObjectByID(id);
// 			if (obj == nullptr) return;
// 
// 			auto vList = _selectedObjects.values(id);
// 			if ((vList.size() > 1) && (vList.size() != obj->getNumberOfBlocks()))
// 			{
// 				_isCombination = true;
// 				appendToFilter(obj, vList);
// // 				for (auto v : vList)
// // 				{
// // 					_append->AddInputData(obj->getOutputData(v + 1));
// // 				}
// 			}
// 		}
// 		else
// 		{
// 			if (_selectedObjects.size() > 0) _isCombination = true;
// 
// 			for (auto id : _selectedObjects.uniqueKeys())
// 			{
// 				auto obj = RenderDataManager::getInstance()->getObjectByID(id);
// 				if (obj == nullptr) continue;
// 
// 				auto vList = _selectedObjects.values(id);
// // 				if (vList.size() == 1)
// // 				{
// // 					if (vList.at(0) == -1)
// // 						_append->AddInputData(obj->getOutputData());
// // 					else
// // 						_append->AddInputData(obj->getOutputData(vList.at(0) + 1));
// // 				}
// // 				else 
// 				if (vList.size() == obj->getNumberOfBlocks())
// 				{
// 					_append->AddInputData(obj->getOutputData());			
// 				}
// 				else
// 				{
// // 					for (auto v : vList)
// // 					{
// // 						_append->AddInputData(obj->getOutputData(v + 1));
// // 					}
// 					appendToFilter(obj, vList);
// 				}
// 			}
// 		}
// 	}

}
