#include "ISORenderDataAlg.h"
#include "RenderDataManager.h"
#include <vtkContourFilter.h>
#include <vtkDataSet.h>
#include <vtkPointData.h>
#include <vtkUnstructuredGrid.h>
#include <QDebug>

namespace Post {
	ISORenderDataAlg::ISORenderDataAlg(RenderDataObject* parent)
		:RenderDataAlgorithm(parent)
	{
		this->setAlgoType(ISO);
		CreateVTKSmartPtr(vtkContourFilter, _vtkAlg);
// 		CreateVTKSmartPtr(vtkContourFilter, _vtkAlg);
// 		_mapper->SetInputConnection(_vtkAlg->GetOutputPort());
// 		if (parent)
// 			this->setInputConnection(parent->getOutputPort());
		//    qDebug() << parent->getOutputData()->GetNumberOfCells();
	}

	void ISORenderDataAlg::updateParam()
	{
		auto parent = this->getParentObj();
		if (parent == nullptr) return;

		if (_selectedObjects.size() < 1) return;

		auto ISOAlg = vtkContourFilter::SafeDownCast(_vtkAlg);
		if (ISOAlg == nullptr) return;
		QString2Char(_Variable, var)

		combineSelectedObjects();

		if (_isCombination)
		{
			if (_append == nullptr) return;
			_append->Update();
			_append->GetOutput()->GetPointData()->SetActiveScalars(var);
			ISOAlg->SetInputConnection(_append->GetOutputPort());
		}
		else
		{
			auto id = _selectedObjects.uniqueKeys().at(0);
			auto obj = RenderDataManager::getInstance()->getObjectByID(id);
			if (obj == nullptr) return;
			auto v = _selectedObjects.values(id).at(0);
			obj->getOutputData(v + 1)->GetPointData()->SetActiveScalars(var);
			ISOAlg->SetInputConnection(obj->getOutputPort(v + 1));
		}

		

//			this->getParentObj()->getOutputData()->GetPointData()->SetActiveScalars(v);

// 		ISOAlg->SetNumberOfContours(1);
// 		ISOAlg->SetValue(0, _Value);
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

	void ISORenderDataAlg::appendToValueList(double val)
	{
		_valueList.append(val);
	}

	int ISORenderDataAlg::getValueCount()
	{
		return _valueList.size();
	}

	double ISORenderDataAlg::valueAt(int index)
	{
		if (index < 0 || index >= _valueList.size()) return 0;

		return _valueList.at(index);
	}

}