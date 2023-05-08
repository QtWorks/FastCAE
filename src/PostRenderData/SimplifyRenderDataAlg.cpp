#include "SimplifyRenderDataAlg.h"
#include "PostAlgorithm/SimplifyAlgorithm.h"

namespace Post {
	SimplifyRenderDataAlg::SimplifyRenderDataAlg(RenderDataObject* parent)
		:RenderDataAlgorithm(parent)
	{
		this->setAlgoType(Simplify);

		CreateVTKSmartPtr(SimplifyAlgorithm, _vtkAlg);

		if (parent == nullptr) return;

		auto simp = SimplifyAlgorithm::SafeDownCast(_vtkAlg);
		simp->SetInputData(parent->getOutputData());
		_mapper->SetInputConnection(_vtkAlg->GetOutputPort());

	}


	SimplifyRenderDataAlg::~SimplifyRenderDataAlg()
	{
		//     _tri->Delete();
		//     _surface->Delete();
	}

	void SimplifyRenderDataAlg::setSurfaceReduce(double V)
	{
		_SurfaceReduce = V;
		auto dec = SimplifyAlgorithm::SafeDownCast(_vtkAlg);
		if (dec == nullptr) return;
		dec->setSurfaceReduce(V);

	}

}