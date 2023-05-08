#include "RenderDataAlgorithm.h"
#include "RenderProperty.h"
#include "RenderDataManager.h"
#include <vtkAppendFilter.h>
#include <vtkDataSet.h>
#include <vtkProperty.h>

namespace Post {
	RenderDataAlgorithm::RenderDataAlgorithm(RenderDataObject* parent): RenderDataObject(parent)
	{
		this->setDataType(Alg);
		this->setParentObj(parent);

		CreateVTKSmartPtr(vtkAppendFilter, _append);
		CreateVTKSmartPtr(vtkDataSetMapper, _mapper)
		CreateVTKSmartPtr(vtkActor, _actor)
		_algorithmProperty = new RenderProperty(this, _mapper, _actor);
		
		auto pro = _actor->GetProperty();
		if (pro != nullptr)
		{
			auto color = colorList.at(_ActorList.size() % colorList.size());
			pro->SetColor(color.redF(), color.greenF(), color.blueF());
		}

		_actor->SetMapper(_mapper);
		_actors->AddPart(_actor);
		_Mappers.append(_mapper);
		_ActorList.append(_actor);
		_PropertyList.append(_algorithmProperty);
	}

	RenderDataAlgorithm* RenderDataAlgorithm::SafeDownCast(RenderDataObject* obj)
	{
		return dynamic_cast<RenderDataAlgorithm*>(obj);
	}

	void RenderDataAlgorithm::setName(QString name)
	{
		_name = name;
	}

	void RenderDataAlgorithm::setSelectedObjectHash(QMultiHash<int, int> hash)
	{
		_selectedObjects = hash;
	}

	QMultiHash<int, int> RenderDataAlgorithm::getSelectedObjectHash()
	{
		return _selectedObjects;
	}

	void RenderDataAlgorithm::updateParam()
	{

	}

	void RenderDataAlgorithm::combineSelectedObjects()
	{
		_append->RemoveAllInputs();
		_isCombination = false;

		auto appendToFilter = [&](RenderDataObject*obj, QList<int> list) {
			for (auto v : list)
			{
				_append->AddInputData(obj->getOutputData(v + 1));
			}
		};

		if (_selectedObjects.size() == 1)
		{
			auto id = _selectedObjects.uniqueKeys().at(0);
			auto obj = RenderDataManager::getInstance()->getObjectByID(id);
			if (obj == nullptr) return;

			auto vList = _selectedObjects.values(id);
			if ((vList.size() > 1) && (vList.size() != obj->getNumberOfBlocks()))
			{
				_isCombination = true;
				appendToFilter(obj, vList);
			}
		}
		else
		{
			if (_selectedObjects.size() > 0) _isCombination = true;

			for (auto id : _selectedObjects.uniqueKeys())
			{
				auto obj = RenderDataManager::getInstance()->getObjectByID(id);
				if (obj == nullptr) continue;

				auto vList = _selectedObjects.values(id);
				if (vList.size() == obj->getNumberOfBlocks())
				{
					_append->AddInputData(obj->getOutputData());
				}
				else
				{
					appendToFilter(obj, vList);
				}
			}
		}
	}

}
