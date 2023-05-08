#include "DialogGeoMeshRotate.h"
#include <ui_DialogGeoMeshRotate.h>
#include "GeometryWidgets/geoPointWidget.h"
#include "MeshData/meshSingleton.h"
#include "MeshData/meshKernal.h"
#include <gp_Ax1.hxx>
#include <TopoDS_Shape.hxx>
#include "Geometry/geometrySet.h"
#include <BRep_Builder.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <TopExp_Explorer.hxx>
#include "MeshData/meshSingleton.h"
#include "MeshData/meshKernal.h"
#include <vtkDataSet.h>
#include <vtkPoints.h>
#include <vtkAppendFilter.h>
#include <vtkSmartPointer.h>
#include <vtkUnstructuredGrid.h>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <BRepExtrema_DistShapeShape.hxx>

bool IsPointOnFace(TopoDS_Shape *s, double *pt, double aTolerance)
{
	gp_Pnt apt(pt[0], pt[1], pt[2]);
	TopoDS_Vertex aVertex = BRepBuilderAPI_MakeVertex(apt);
	BRepExtrema_DistShapeShape anExtrema(*s, aVertex);
	double dis = anExtrema.Value();
	if ((anExtrema.IsDone() == Standard_True))
	{
		if (dis < aTolerance)
			return true;
		return false;
	}
	return false;
};

namespace MainWidget
{
	GeoMeshRotateDialog::GeoMeshRotateDialog(GUI::MainWindow *m, MainWidget::PreWindow *p)
		: GeoDialogBase(m, p)
	{
		_ui = new Ui::GeoMeshRotateDialog;
		_ui->setupUi(this);

		_baseWidget = new GeometryWidget::GeoPointWidget(_mainWindow, _preWindow);
		_ui->basicPointlLayout->addWidget(_baseWidget);
		connect(_baseWidget, SIGNAL(buttonCkicked(GeoPointWidget *)), this, SLOT(pointWidgetClicked(GeoPointWidget *)));

		auto meshData = MeshData::MeshData::getInstance();
		meshData->getKernalCount();
	}

	GeoMeshRotateDialog::~GeoMeshRotateDialog()
	{
		for (auto f : _selectFaces)
			delete f;
		_selectFaces.clear();

		if (_ui != nullptr)
			delete _ui;
	}

	void GeoMeshRotateDialog::on_geoSelectSurface_clicked()
	{
		emit setSelectMode((int)ModuleBase::GeometrySurface);
		_baseWidget->handleProcess(false);
		_selectFace = true;
		_selectPoint = false;
	}

	bool GeoMeshRotateDialog::getVector(double *vec)
	{
		if (_ui->radioButtonX->isChecked())
			vec[0] = 1.0;
		else if (_ui->radioButtonY->isChecked())
			vec[1] = 1.0;
		else if (_ui->radioButtonZ->isChecked())
			vec[2] = 1.0;
		else
		{
			vec[0] = _ui->doubleSpinBoxX->value();
			vec[1] = _ui->doubleSpinBoxY->value();
			vec[2] = _ui->doubleSpinBoxZ->value();
		}

		double mod = vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2];
		if (mod > 0.000001)
			return true;
		return false;
	}

	void GeoMeshRotateDialog::shapeSlected(Geometry::GeometrySet *set, int index)
	{
		if (_selectFace)
		{
			bool exist = false;
			if (_facesHash.size() > 0)
			{
				QMultiHash<Geometry::GeometrySet *, int>::iterator it = _facesHash.begin();
				for (; it != _facesHash.end(); it++)
				{
					if (it.key() == set && it.value() == index)
					{
						it = _facesHash.erase(it);
						emit highLightGeometryFaceSig(set, index, false);
						exist = true;
						break;
					}
				}
			}
			if (!exist)
			{
				_facesHash.insert(set, index);
				emit highLightGeometryFaceSig(set, index, true);
			}

			QString text = QString("Selected Face(%1)").arg(_facesHash.size());
			_ui->edgelabel->setText(text);
		}
	}

	void GeoMeshRotateDialog::accept()
	{
		double basicPoint[3]{0};
		double vec[3]{0};
		double deg = 0;

		bool ok = _baseWidget->getCoordinate(basicPoint);
		ok = this->getVector(vec);
		deg = _ui->lineEditDegree->text().toDouble();

		gp_Ax1 axis(gp_Pnt(basicPoint[0], basicPoint[1], basicPoint[2]), gp_Dir(vec[0], vec[1], vec[2]));
		gp_Trsf atrsf;
		atrsf.SetRotation(axis, deg * 3.141592653 / 180.0);

		this->transformGeo(&atrsf);
		this->transformMesh(&atrsf);

		QDialog::accept();
		this->close();
	}

	void GeoMeshRotateDialog::reject()
	{
		QDialog::reject();
		this->close();
	}

	void GeoMeshRotateDialog::splitGeometry(Geometry::GeometrySet *set, TopoDS_Shape &faces, TopoDS_Shape &others)
	{
		TopoDS_Shape *setShape = set->getShape();
		QList<int> faceIndexs = _facesHash.values(set);
		TopoDS_Compound compFace;
		BRep_Builder facebuilder;
		facebuilder.MakeCompound(compFace);
		QList<Handle(TopoDS_TShape)> tshapelist;
		for (int index : faceIndexs)
		{
			TopExp_Explorer faceEx(*setShape, TopAbs_FACE);
			for (int i = 0; i < index && faceEx.More(); ++i, faceEx.Next())
				;
			const TopoDS_Shape &faceshape = faceEx.Current();
			tshapelist.append(faceshape.TShape());
			facebuilder.Add(compFace, faceshape);
			TopoDS_Shape *copy = new TopoDS_Shape(faceshape);
			_selectFaces.append(copy);
		}
		faces = compFace;

		TopoDS_Compound othersComp;
		BRep_Builder otherBuilder;
		otherBuilder.MakeCompound(othersComp);
		TopExp_Explorer ex;
		for (ex.Init(*setShape, TopAbs_SOLID); ex.More(); ex.Next())
		{
			otherBuilder.Add(othersComp, ex.Current());
		}
		for (ex.Init(*setShape, TopAbs_FACE, TopAbs_SOLID); ex.More(); ex.Next())
		{
			const TopoDS_Shape &cface = ex.Current();
			if (tshapelist.contains(cface.TShape()))
				continue;
			otherBuilder.Add(othersComp, ex.Current());
		}
		others = othersComp;
	}

	void GeoMeshRotateDialog::transformGeo(gp_Trsf *trsf)
	{
		QList<Geometry::GeometrySet *> geoSetList = _facesHash.uniqueKeys();
		for (auto set : geoSetList)
		{
			emit hideGeometry(set);
			TopoDS_Shape faces;
			TopoDS_Shape others;
			this->splitGeometry(set, faces, others);
			faces.Move(*trsf);
			TopoDS_Compound compAll;
			BRep_Builder builder;
			builder.MakeCompound(compAll);
			builder.Add(compAll, faces);
			builder.Add(compAll, others);
			TopoDS_Shape *shape = set->getShape();
			*shape = compAll;
			emit showGeometry(set);
		}
	}

	void GeoMeshRotateDialog::transformMesh(gp_Trsf *trsf)
	{
		auto meshdata = MeshData::MeshData::getInstance();
		const int nKernal = meshdata->getKernalCount();
		if (nKernal == 0)
			return;
		BRep_Builder builder;
		TopoDS_Compound commp;
		builder.MakeCompound(commp);
		for (auto s : _selectFaces)
			builder.Add(commp, *s);

		NCollection_Mat4<double> mat4;
		trsf->GetMat4(mat4);
		double mat[4][4];
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				mat[i][j] = mat4.GetValue(i, j);

		for (int i = 0; i < nKernal; ++i)
		{
			auto kernal = meshdata->getKernalAt(i);
			vtkDataSet *dataset = kernal->getMeshData();
			transformPoints(dataset, &commp, mat);
		}
	}

	void GeoMeshRotateDialog::transformPoints(vtkDataSet *mesh, TopoDS_Shape *faces, double mat[4][4])
	{
		vtkSmartPointer<vtkAppendFilter> appf = vtkSmartPointer<vtkAppendFilter>::New();
		appf->AddInputData(mesh);
		appf->Update();
		vtkUnstructuredGrid *ung = appf->GetOutput();
		vtkPoints *points = ung->GetPoints();
		double ptcoor[3] = {0};
		const int npt = points->GetNumberOfPoints();
		for (int i = 0; i < npt; ++i)
		{
			points->GetPoint(i, ptcoor);
			if (!IsPointOnFace(faces, ptcoor, 1e-5))
				continue;
			double res[3]{0};
			this->preMat(res, mat, ptcoor);
			points->SetPoint(i, res);
		}
		points->Modified();
		mesh->DeepCopy(ung);
		mesh->Modified();
	}

	void GeoMeshRotateDialog::preMat(double *res, double mat[4][4], double *ori)
	{
		for (int i = 0; i < 3; ++i)
		{
			res[i] = mat[i][0] * ori[0] + mat[i][1] * ori[1] + mat[i][2] * ori[2] + mat[i][3] * 1.0;
		}
	}

}
