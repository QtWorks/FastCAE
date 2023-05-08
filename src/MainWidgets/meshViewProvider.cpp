#include "meshViewProvider.h"
#include "meshKernalViewObject.h"
#include "MainWindow/MainWindow.h"
#include "MainWidgets/preWindow.h"
#include "MeshData/meshSingleton.h"
#include "MeshData/meshSet.h"
#include "MeshData/meshKernal.h"
#include "Settings/BusAPI.h"
#include "Settings/GraphOption.h"
#include <vtkActor.h>
#include <vtkDataSetMapper.h>
#include <vtkDataSet.h>
#include <vtkProperty.h>
#include <vtkPointData.h>
#include <vtkDataArray.h>
#include <QDebug>
#include <assert.h>

namespace MainWidget
{
	MeshViewProvider::MeshViewProvider(GUI::MainWindow *mainwindow, PreWindow *renderWin) : _mainWindow(mainwindow), _preWindow(renderWin)
	{
		_meshData = MeshData::MeshData::getInstance();
		connect(_preWindow, SIGNAL(updateMeshActorSig()), this, SLOT(updateMeshActorSlot()));

		//connect(_preWindow, SIGNAL(removeSetDataSig(int)), this, SLOT(removeSetData(int)));
		//		connect(_preWindow, SIGNAL(highLightActorDispalyPoint(bool)), this, SLOT(highLightActorDispalyPoint(bool)));
		connect(_preWindow, SIGNAL(clearMeshSetHighLight()), this, SLOT(clearHighLight()));
		connect(_preWindow, SIGNAL(clearAllHighLight()), this, SLOT(clearHighLight()));
		connect(_preWindow, SIGNAL(highLighMeshSet(MeshData::MeshSet *)), this, SLOT(highLighMeshSet(MeshData::MeshSet *)));
		connect(_preWindow, SIGNAL(highLighKernel(MeshData::MeshKernal *)), this, SLOT(highLighKernel(MeshData::MeshKernal *)));
		//		connect(_preWindow, SIGNAL(highLighDataSet(vtkDataSet*)), this, SLOT(highLighDataSet(vtkDataSet*)));
		connect(_mainWindow, SIGNAL(updateMeshSetVisibleSig(MeshData::MeshSet *)), this, SLOT(updateMeshSetVisibily(MeshData::MeshSet *)));
		connect(_mainWindow, SIGNAL(updateMeshSetColorSig(int)), this, SLOT(updateMeshSetColor(int)));
	}

	MeshViewProvider::~MeshViewProvider()
	{
		QList<MeshKernalViewObj *> viewObjs = _viewObjects.values();
		for (auto obj : viewObjs)
			delete obj;
	}

	void MeshViewProvider::updateMeshActorSlot()
	{
		const int nk = _meshData->getKernalCount();
		for (int i = 0; i < nk; ++i)
		{
			auto Kernal = _meshData->getKernalAt(i);
			if (!_viewObjects.contains(Kernal))
			{
				auto vobj = new MeshKernalViewObj(Kernal);
				_viewObjects.insert(Kernal, vobj);
				updateDisplayModel(Kernal);
				updateGraphOption(Kernal);
				vtkActor **ac = vobj->getActor();
				_preWindow->AppendActor(ac[0]);
				_preWindow->AppendActor(ac[1]);
				_preWindow->AppendActor(ac[2]);
			}
		}
		QList<MeshData::MeshKernal *> disPlayed = _viewObjects.keys();
		for (auto ker : disPlayed)
		{
			if (_meshData->isContainsKernal(ker))
				continue;
			this->removeDisplay(ker);
		}
	}

	void MeshViewProvider::highLighKernel(MeshData::MeshKernal *k)
	{
		auto vobj = _viewObjects.value(k);
		vobj->highLight();
		_preWindow->reRender();
	}

	void MeshViewProvider::highLighMeshSet(MeshData::MeshSet *set)
	{
		if (set == nullptr)
			return;
		if (!set->isVisible())
			return;
		QList<int> kids = set->getKernals();
		MeshData::SetType type = set->getSetType();
		QColor c = Setting::BusAPI::instance()->getGraphOption()->getHighLightColor();
		for (int kid : kids)
		{
			auto k = MeshData::MeshData::getInstance()->getKernalByID(kid);
			if (k == nullptr)
				continue;
			QList<int> mids = set->getKernalMembers(kid);
			if (mids.isEmpty())
				continue;
			auto vobj = _viewObjects.value(k);
			if (vobj == nullptr)
				continue;
			if (type == MeshData::Node)
				vobj->setPointDisplayColor(mids, c);
			else if (type == MeshData::Element)
				vobj->setCellDisplayColor(mids, c);
		}
		_highLightSet = set;
		_preWindow->reRender();
	}

	void MeshViewProvider::clearHighLight()
	{
		QList<MeshKernalViewObj *> vobjs = _viewObjects.values();
		for (auto v : vobjs)
			if (v->isKernalHighLight())
				v->clearHighLight();

		if (_highLightSet != nullptr)
		{
			auto gp = Setting::BusAPI::instance()->getGraphOption();
			MeshData::SetType type = _highLightSet->getSetType();
			QList<int> kids = _highLightSet->getKernals();
			for (int kid : kids)
			{
				auto k = MeshData::MeshData::getInstance()->getKernalByID(kid);
				auto vobj = _viewObjects.value(k);
				if (vobj == nullptr)
					continue;
				if (type == MeshData::Node)
					vobj->setPointColor(gp->getMeshNodeColor(), true);
				else if (type == MeshData::Element)
					vobj->setCellColor(gp->getMeshFaceColor(), true);
			}
			_highLightSet = nullptr;
		}

		QList<int> datasetList = _highLightSelectItems.uniqueKeys();
		for (auto dataset : datasetList)
		{
			auto k = _meshData->getKernalByID(dataset);
			auto vObjs = _viewObjects.value(k);
			QList<int> members = _highLightSelectItems.values();
			if (vObjs == nullptr)
				continue;
			if (_selectModel == ModuleBase::BoxMeshNode || _selectModel == ModuleBase::MeshNode)
			{
				QColor c = Setting::BusAPI::instance()->getGraphOption()->getMeshNodeColor();
				vObjs->setPointDisplayColor(members, c);
			}

			else if (_selectModel == ModuleBase::BoxMeshCell || _selectModel == ModuleBase::MeshCell)
			{
				QColor c = Setting::BusAPI::instance()->getGraphOption()->getMeshFaceColor();
				vObjs->setCellDisplayColor(members, c);
			}

			_highLightSelectItems.clear();
		}

		_preWindow->reRender();
	}

	void MeshViewProvider::updateMeshSetVisibily(MeshData::MeshSet *set)
	{
		if (set == nullptr)
			return;
		MeshData::SetType type = set->getSetType();
		QList<int> kids = set->getKernals();
		for (int kid : kids)
		{
			auto k = MeshData::MeshData::getInstance()->getKernalByID(kid);
			if (k == nullptr)
				continue;
			QList<int> mids = set->getKernalMembers(kid);
			if (mids.isEmpty())
				continue;
			auto vobj = _viewObjects.value(k);
			if (vobj == nullptr)
				continue;
			if (type == MeshData::Element)
				vobj->showCells(mids, set->isVisible());
		}
		_preWindow->reRender();
	}

	void MeshViewProvider::updateMeshSetColor(int setid)
	{
		auto meshData = MeshData::MeshData::getInstance();
		auto meshSet = meshData->getMeshSetByID(setid);
		if (meshSet == nullptr)
			return;
		QColor c = meshSet->getColor();

		QList<int> ks = meshSet->getKernals();
		for (int k : ks)
		{
			auto kernal = meshData->getKernalByID(k);
			if (kernal == nullptr)
				continue;
			auto viewObj = _viewObjects.value(kernal);
			if (viewObj == nullptr)
				continue;

			QList<int> mem = meshSet->getKernalMembers(k);
			if (meshSet->getSetType() == MeshData::Element)
			{
				viewObj->setCellDisplayColor(mem, c);
			}
			else if (meshSet->getSetType() == MeshData::Node)
			{
				viewObj->setPointDisplayColor(mem, c);
			}
		}
	}

	void MeshViewProvider::removeDisplay(MeshData::MeshKernal *kernal)
	{
		auto viewObj = _viewObjects.value(kernal);
		if (viewObj == nullptr)
			return;
		vtkActor **ac = viewObj->getActor();
		_preWindow->RemoveActor(ac[POINTACTOR]);
		_preWindow->RemoveActor(ac[EDGEACTOR]);
		_preWindow->RemoveActor(ac[FACEACTOR]);
		_viewObjects.remove(kernal);
		delete viewObj;
		_preWindow->reRender();
	}

	MainWidget::MeshKernalViewObj *MeshViewProvider::getViewObjByDisplayDataSet(vtkDataSet *data)
	{
		QList<MeshKernalViewObj *> kobjs = _viewObjects.values();
		for (auto obj : kobjs)
		{
			auto d = obj->getDisplayData();
			if (d == data)
				return obj;
		}
		return nullptr;
	}

	void MeshViewProvider::updateDisplayModel(MeshData::MeshKernal *k)
	{
		QList<MeshKernalViewObj *> vobjs;
		if (nullptr == k)
			vobjs = _viewObjects.values();
		else
			vobjs.append(_viewObjects.value(k));

		auto gp = Setting::BusAPI::instance()->getGraphOption();
		bool showNode = gp->isShowMeshNode();
		bool showEdge = gp->isShowMeshEdge();
		bool showFace = gp->isShowMeshFace();
		for (auto kobj : vobjs)
		{
			if (nullptr == kobj)
				continue;
			vtkActor **acs = kobj->getActor();
			acs[POINTACTOR]->SetVisibility(showNode);
			acs[EDGEACTOR]->SetVisibility(showEdge);
			acs[FACEACTOR]->SetVisibility(showFace);
			if (showEdge && showFace)
			{
				acs[EDGEACTOR]->GetMapper()->SetScalarVisibility(false);
				QColor edgeColor = gp->getMeshEdgeColor();
				acs[EDGEACTOR]->GetProperty()->SetColor(edgeColor.redF(), edgeColor.greenF(), edgeColor.blueF());
			}
			else
				acs[EDGEACTOR]->GetMapper()->SetScalarVisibility(true);
		}

		if (k != nullptr)
			showKernal(k, k->isVisible());
		else
		{
			auto ks = _viewObjects.keys();
			for (auto ck : ks)
				showKernal(ck, ck->isVisible());
		}
	}

	void MeshViewProvider::updateGraphOption(MeshData::MeshKernal *k /*= nullptr*/)
	{
		QList<MeshKernalViewObj *> vobjs;
		if (nullptr == k)
			vobjs = _viewObjects.values();
		else
			vobjs.append(_viewObjects.value(k));

		auto gp = Setting::BusAPI::instance()->getGraphOption();
		const bool showNode = gp->isShowMeshNode();
		const bool showEdge = gp->isShowMeshEdge();
		const bool showFace = gp->isShowMeshFace();
		const float pointSize = gp->getMeshNodeSize();
		const float lineWidth = gp->getMeshEdgeWidth();
		const QColor pointColor = gp->getMeshNodeColor();
		const QColor edgeColor = gp->getMeshEdgeColor();
		const QColor faceColor = gp->getMeshFaceColor();
		for (auto kobj : vobjs)
		{
			if (nullptr == kobj)
				continue;
			kobj->setPointColor(pointColor);
			kobj->setCellColor(faceColor);
			vtkActor **acs = kobj->getActor();
			acs[POINTACTOR]->GetProperty()->SetPointSize(pointSize);
			acs[EDGEACTOR]->GetProperty()->SetLineWidth(lineWidth);
			if (showEdge && showFace)
			{
				acs[EDGEACTOR]->GetMapper()->SetScalarVisibility(false);
				acs[EDGEACTOR]->GetProperty()->SetColor(edgeColor.redF(), edgeColor.greenF(), edgeColor.blueF());
			}
			else
				acs[EDGEACTOR]->GetMapper()->SetScalarVisibility(true);
		}
	}

	void MeshViewProvider::showKernal(MeshData::MeshKernal *k, bool show)
	{
		if (k == nullptr)
			return;
		auto vobj = _viewObjects.value(k);
		if (vobj == nullptr)
			return;
		vtkActor **acs = vobj->getActor();
		if (show)
		{
			auto gp = Setting::BusAPI::instance()->getGraphOption();
			const bool showNode = gp->isShowMeshNode();
			const bool showEdge = gp->isShowMeshEdge();
			const bool showFace = gp->isShowMeshFace();

			acs[POINTACTOR]->SetVisibility(showNode);
			acs[EDGEACTOR]->SetVisibility(showEdge);
			acs[FACEACTOR]->SetVisibility(showFace);
		}
		else
		{
			acs[POINTACTOR]->SetVisibility(false);
			acs[EDGEACTOR]->SetVisibility(false);
			acs[FACEACTOR]->SetVisibility(false);
		}
		_preWindow->reRender();
	}

	void MeshViewProvider::setMeshSelectMode(ModuleBase::SelectModel m)
	{
		clearHighLight();
		_selectModel = m;

		QList<MeshKernalViewObj *> objs = _viewObjects.values();
		for (auto vobj : objs)
		{
			vtkActor **acs = vobj->getActor();
			acs[POINTACTOR]->SetPickable(false);
			acs[EDGEACTOR]->SetPickable(false);
			acs[FACEACTOR]->SetPickable(false);

			if (m == ModuleBase::MeshNode || m == ModuleBase::BoxMeshNode)
				acs[POINTACTOR]->SetPickable(true);
			else if (m == ModuleBase::MeshCell || m == ModuleBase::BoxMeshCell)
				acs[FACEACTOR]->SetPickable(true);
		}
	}

	void MeshViewProvider::highLighSelectItem(QMultiHash<int, int> *items)
	{
		if (items->isEmpty())
			return;
		_highLightSelectItems = *items;
		QColor c = Setting::BusAPI::instance()->getGraphOption()->getHighLightColor();
		QList<int> datasetList = items->uniqueKeys();
		for (auto dataset : datasetList)
		{
			auto k = _meshData->getKernalByID(dataset);
			auto vObjs = _viewObjects.value(k);
			QList<int> members = items->values();
			if (vObjs == nullptr)
				continue;
			if (_selectModel == ModuleBase::BoxMeshNode || _selectModel == ModuleBase::MeshNode)
				vObjs->setPointDisplayColor(members, c);
			else if (_selectModel == ModuleBase::BoxMeshCell || _selectModel == ModuleBase::MeshCell)
				vObjs->setCellDisplayColor(members, c);
		}
		_preWindow->reRender();
	}

	QMultiHash<int, int> *MeshViewProvider::getSelectItem()
	{
		return &_highLightSelectItems;
	}

}