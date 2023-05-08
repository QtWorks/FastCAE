#include "NastranH5ReaderAlgorithm.h"
#include <vtkUnstructuredGrid.h>
#include <vtkInformation.h>
#include <vtkDemandDrivenPipeline.h>
#include <vtkStreamingDemandDrivenPipeline.h>
#include "NastranH5Reader.h"
#include <map>
#include <vtkDoubleArray.h>
#include <vtkPointData.h>
#include <vtkCellData.h>

NastranH5ReaderAlgorithm *NastranH5ReaderAlgorithm::New()
{
	auto reader = new NastranH5ReaderAlgorithm;
	reader->InitializeObjectBase();
	return reader;
}

void NastranH5ReaderAlgorithm::SetFileName(std::string name)
{
	m_FileName = name;
}

void NastranH5ReaderAlgorithm::PrintSelf(std::ostream &os, vtkIndent indent)
{
	this->Superclass::PrintSelf(os, indent);
	os << indent << "FileName:" << (this->m_FileName.empty() ? "(none)" : this->m_FileName) << "\n";
}
int NastranH5ReaderAlgorithm::FillOutputPortInformation(int port, vtkInformation *info)
{
	Q_UNUSED(port)
		info->Set(vtkUnstructuredGrid::DATA_TYPE_NAME(), "vtkUnstructuredGrid");
	return 1;
}

NastranH5ReaderAlgorithm::NastranH5ReaderAlgorithm()
{
	this->SetNumberOfInputPorts(0);
	this->SetNumberOfOutputPorts(1);
}

NastranH5ReaderAlgorithm::~NastranH5ReaderAlgorithm()
{
}

int NastranH5ReaderAlgorithm::ProcessRequest(vtkInformation *request, vtkInformationVector **inputVector, vtkInformationVector *outputVector)
{
	if (request->Has(vtkDemandDrivenPipeline::REQUEST_INFORMATION()))
	{
		return this->RequestInformation(request, inputVector, outputVector);
	}
	if (request->Has(vtkStreamingDemandDrivenPipeline::REQUEST_UPDATE_EXTENT()))
	{
		return this->RequestUpdateExtent(request, inputVector, outputVector);
	}
	if (request->Has(vtkDemandDrivenPipeline::REQUEST_DATA()))
	{
		return this->RequestData(request, inputVector, outputVector);
	}
	return this->Superclass::ProcessRequest(request, inputVector, outputVector);
}

int NastranH5ReaderAlgorithm::RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *outputVector)
{
	if (this->m_FileName.empty())
	{
		vtkErrorMacro("A FileName must be specified.");
		return 0;
	}

	//vtkUnstructuredGrid* grid = vtkUnstructuredGrid::GetData(outputVector);
	vtkNew<vtkUnstructuredGrid> grid;

	// std::map<旧ID, 新ID>
	std::map<int, int> nodeIndexmaps = {};
	std::map<int, int> eleIndexmaps = {};
	// 节点遍历转换
	auto fileReader = new NastranH5Reader(m_FileName);
	auto data = fileReader->getNodes();
	vtkNew<vtkPoints> points;
	for (InputNodeGrid node : data)
	{
		double ids[3] = { node.X[0] , node.X[1] , node.X[2] };
		nodeIndexmaps[node.ID] = points->InsertNextPoint(ids);
	}
	grid->SetPoints(points);

	// 节点平移形变
	auto displacementTranslational = vtkSmartPointer<vtkDoubleArray>::New();
	displacementTranslational->SetNumberOfComponents(3);
	displacementTranslational->SetName("Displacement Translational");
	displacementTranslational->SetComponentName(0, "X");
	displacementTranslational->SetComponentName(1, "Y");
	displacementTranslational->SetComponentName(2, "Z");

	// 节点旋转形变
	auto displacementRotational = vtkSmartPointer<vtkDoubleArray>::New();
	displacementRotational->SetNumberOfComponents(3);
	displacementRotational->SetName("Displacement Rotational");
	displacementRotational->SetComponentName(0, "RX");
	displacementRotational->SetComponentName(1, "RY");
	displacementRotational->SetComponentName(2, "RZ");

	auto displacements = fileReader->getNodalResult("DISPLACEMENT");
	for (auto dis : displacements)
	{
		displacementTranslational->InsertTuple3(nodeIndexmaps[dis.ID], dis.X, dis.Y, dis.Z);
		displacementRotational->InsertTuple3(nodeIndexmaps[dis.ID], dis.RX, dis.RY, dis.RZ);
	}

	grid->GetPointData()->AddArray(displacementRotational);
	grid->GetPointData()->AddArray(displacementTranslational);

	// 单元遍历转换
	auto eleTypes = fileReader->getElementType();
	eleIndexmaps.clear();
	for (auto type : eleTypes)
	{
		if (type == "CROD") {
			auto elements = fileReader->getElementCrod();
			vtkIdType ids[2] = { 0 };
			for (InputElementCrod ele : elements)
			{
				for (int i = 0; i < 2; i++)
				{
					ids[i] = nodeIndexmaps[ele.G[i]];
				}
				eleIndexmaps[ele.EID] = grid->InsertNextCell(VTK_LINE, 2, ids);
			}
			// 单元总应力
			auto totalStress = vtkSmartPointer<vtkDoubleArray>::New();
			totalStress->SetNumberOfComponents(1);
			totalStress->SetName("Total Stress");
			totalStress->SetComponentName(0, "T");
			auto axialStress = vtkSmartPointer<vtkDoubleArray>::New();
			axialStress->SetNumberOfComponents(1);
			axialStress->SetName("Axial Stress");
			axialStress->SetComponentName(0, "A");


			auto stresses = fileReader->getElementalResultRod();
			for (auto stress : stresses)
			{
				totalStress->InsertTuple1(eleIndexmaps[stress.EID], stress.T);
				axialStress->InsertTuple1(eleIndexmaps[stress.EID], stress.A);
			}

			grid->GetCellData()->AddArray(totalStress);
			grid->GetCellData()->AddArray(axialStress);
		}
		else if (type == "CBAR") {
			auto elements = fileReader->getElementCbar();
			for (InputElementCbar ele : elements)
			{
				Type64BitInt ids[2] = { nodeIndexmaps[ele.GA], nodeIndexmaps[ele.GB] };
				eleIndexmaps[ele.EID] = grid->InsertNextCell(VTK_LINE, 2, ids);
			}

			auto cStress = vtkSmartPointer<vtkDoubleArray>::New();
			cStress->SetNumberOfComponents(1);
			cStress->SetName("Stress At Point C");
			cStress->SetComponentName(0, "XC");

			auto dStress = vtkSmartPointer<vtkDoubleArray>::New();
			dStress->SetNumberOfComponents(1);
			dStress->SetName("Stress At Point D");
			dStress->SetComponentName(0, "XD");

			auto eStress = vtkSmartPointer<vtkDoubleArray>::New();
			eStress->SetNumberOfComponents(1);
			eStress->SetName("Stress At Point E");
			eStress->SetComponentName(0, "XE");

			auto fStress = vtkSmartPointer<vtkDoubleArray>::New();
			fStress->SetNumberOfComponents(1);
			fStress->SetName("Stress At Point F");
			fStress->SetComponentName(0, "XF");

			auto stresses = fileReader->getElementalResultBars();
			for (auto stress : stresses)
			{
				cStress->InsertTuple1(eleIndexmaps[stress.EID], stress.XC);
				dStress->InsertTuple1(eleIndexmaps[stress.EID], stress.XD);
				eStress->InsertTuple1(eleIndexmaps[stress.EID], stress.XE);
				fStress->InsertTuple1(eleIndexmaps[stress.EID], stress.XF);
			}

			grid->GetCellData()->AddArray(cStress);
			grid->GetCellData()->AddArray(dStress);
			grid->GetCellData()->AddArray(eStress);
			grid->GetCellData()->AddArray(fStress);
		}
		else if (type == "CQUAD4") {
			auto elements = fileReader->getElementCquad4();
			vtkIdType ids[4] = { 0 };
			for (InputElementCquad4 ele : elements)
			{
				for (int i = 0; i < 4; i++)
				{
					ids[i] = nodeIndexmaps[ele.G[i]];
				}
				eleIndexmaps[ele.EID] = grid->InsertNextCell(VTK_QUAD, 4, ids);
			}

			// 单元应力
			auto normalStress = vtkSmartPointer<vtkDoubleArray>::New();
			normalStress->SetNumberOfComponents(2);
			normalStress->SetName("Normal Stress");
			normalStress->SetComponentName(0, "X");
			normalStress->SetComponentName(1, "Y");

			// 单元切应力
			auto shearStress = vtkSmartPointer<vtkDoubleArray>::New();
			shearStress->SetNumberOfComponents(1);
			shearStress->SetName("Shear Stress");
			shearStress->SetComponentName(0, "TXY");

			auto stresses = fileReader->getElementalResultQuad4();
			for (auto stress : stresses)
			{
				normalStress->InsertTuple2(eleIndexmaps[stress.EID], stress.X1[0], stress.Y1[0]);
				shearStress->InsertTuple1(eleIndexmaps[stress.EID], stress.TXY1[0]);
			}

			grid->GetCellData()->AddArray(normalStress);
			grid->GetCellData()->AddArray(shearStress);
		}
		else if (type == "CQUAD8") {
			auto elements = fileReader->getElementCquad8();
			vtkIdType ids[8] = { 0 };
			for (InputElementCquad8 ele : elements)
			{
				for (int i = 0; i < 8; i++)
				{
					ids[i] = nodeIndexmaps[ele.G[i]];
				}
				eleIndexmaps[ele.EID] = grid->InsertNextCell(VTK_QUADRATIC_QUAD, 8, ids);
			}
			// 单元应力
			auto normalStress = vtkSmartPointer<vtkDoubleArray>::New();
			normalStress->SetNumberOfComponents(2);
			normalStress->SetName("Normal Stress");
			normalStress->SetComponentName(0, "X");
			normalStress->SetComponentName(1, "Y");

			// 单元切应力
			auto shearStress = vtkSmartPointer<vtkDoubleArray>::New();
			shearStress->SetNumberOfComponents(1);
			shearStress->SetName("Shear Stress");
			shearStress->SetComponentName(0, "TXY");

			auto stresses = fileReader->getElementalResultQuad8();
			for (auto stress : stresses)
			{
				normalStress->InsertTuple2(eleIndexmaps[stress.EID], stress.X1[0], stress.Y1[0]);
				shearStress->InsertTuple1(eleIndexmaps[stress.EID], stress.TXY1[0]);
			}

			grid->GetCellData()->AddArray(normalStress);
			grid->GetCellData()->AddArray(shearStress);
		}
		else if (type == "CHEXA") {
			auto elements = fileReader->getElementChexa();
			vtkIdType ids[8] = { 0 };
			for (InputElementChexa ele : elements)
			{
				for (int i = 0; i < 8; i++)
				{
					ids[i] = nodeIndexmaps[ele.G[i]];
				}
				eleIndexmaps[ele.EID] = grid->InsertNextCell(VTK_HEXAHEDRON, 8, ids);
			}
			// 单元应力
			auto normalStress = vtkSmartPointer<vtkDoubleArray>::New();
			normalStress->SetNumberOfComponents(3);
			normalStress->SetName("Normal Stress");
			normalStress->SetComponentName(0, "X");
			normalStress->SetComponentName(1, "Y");
			normalStress->SetComponentName(2, "Z");

			// 单元切应力
			auto shearStress = vtkSmartPointer<vtkDoubleArray>::New();
			shearStress->SetNumberOfComponents(3);
			shearStress->SetName("Shear Stress");
			shearStress->SetComponentName(0, "TXY");
			shearStress->SetComponentName(1, "TYZ");
			shearStress->SetComponentName(2, "TZX");

			auto stresses = fileReader->getElementalResultHexa();
			for (auto stress : stresses)
			{
				normalStress->InsertTuple3(eleIndexmaps[stress.EID], stress.X[0], stress.Y[0], stress.Z[0]);
				shearStress->InsertTuple3(eleIndexmaps[stress.EID], stress.TXY[0], stress.TYZ[0], stress.TZX[0]);
			}

			grid->GetCellData()->AddArray(normalStress);
			grid->GetCellData()->AddArray(shearStress);
		}
		else if (type == "CTETRA") {
			auto elements = fileReader->getElementCtetra();
			vtkIdType ids[10] = { 0 };
			for (InputElementCtetra ele : elements)
			{
				for (int i = 0; i < 10; i++)
				{
					ids[i] = nodeIndexmaps[ele.G[i]];
				}
				eleIndexmaps[ele.EID] = grid->InsertNextCell(VTK_QUADRATIC_TETRA, 10, ids);
			}
			// 单元应力
			auto normalStress = vtkSmartPointer<vtkDoubleArray>::New();
			normalStress->SetNumberOfComponents(3);
			normalStress->SetName("Normal Stress");
			normalStress->SetComponentName(0, "X");
			normalStress->SetComponentName(1, "Y");
			normalStress->SetComponentName(2, "Z");

			// 单元切应力
			auto shearStress = vtkSmartPointer<vtkDoubleArray>::New();
			shearStress->SetNumberOfComponents(3);
			shearStress->SetName("Shear Stress");
			shearStress->SetComponentName(0, "TXY");
			shearStress->SetComponentName(1, "TYZ");
			shearStress->SetComponentName(2, "TZX");

			auto stresses = fileReader->getElementalResultTetra();
			for (auto stress : stresses)
			{
				normalStress->InsertTuple3(eleIndexmaps[stress.EID], stress.X[0], stress.Y[0], stress.Z[0]);
				shearStress->InsertTuple3(eleIndexmaps[stress.EID], stress.TXY[0], stress.TYZ[0], stress.TZX[0]);
			}

			grid->GetCellData()->AddArray(normalStress);
			grid->GetCellData()->AddArray(shearStress);
		}
		else {
			vtkErrorMacro("Unknown Element Type: " + type);
			return 0;
		}
	}

	vtkUnstructuredGrid* uGrid = vtkUnstructuredGrid::GetData(outputVector);
	uGrid->CopyStructure(grid);
	uGrid->GetPointData()->PassData(grid->GetPointData());
	uGrid->GetCellData()->PassData(grid->GetCellData());

	return 1;
}

void NastranH5ReaderAlgorithm::operator=(const NastranH5ReaderAlgorithm &other)
{
	this->m_FileName = other.m_FileName;
}

