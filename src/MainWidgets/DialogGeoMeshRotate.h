#ifndef _DIALOGGEOMESHROTATE_H__
#define _DIALOGGEOMESHROTATE_H__


#include "mainWidgetsAPI.h"
#include "GeometryWidgets/geoDialogBase.h"
#include <QList>


class TopoDS_Shape;
class gp_Trsf;
class vtkDataSet;

namespace  Ui
{
	class GeoMeshRotateDialog;
}
namespace GeometryWidget
{
	class GeoPointWidget;
}

namespace MainWidget
{
	class MAINWIDGETSAPI GeoMeshRotateDialog :public GeometryWidget::GeoDialogBase
	{
		Q_OBJECT
	public:
		GeoMeshRotateDialog(GUI::MainWindow* m, MainWidget::PreWindow* p);
		~GeoMeshRotateDialog();

	private slots:
		void on_geoSelectSurface_clicked();

	private:
		bool getVector(double* vec);
		void shapeSlected(Geometry::GeometrySet* set, int index) override;
		void accept() override;
		void reject() override;
		void splitGeometry(Geometry::GeometrySet* set ,TopoDS_Shape& faces, TopoDS_Shape & others);
		void transformGeo(gp_Trsf* trsf);
		void transformMesh(gp_Trsf* trsf);
		void transformPoints(vtkDataSet* pts, TopoDS_Shape* faces, double mat[4][4]);
		void preMat(double* res, double mat[4][4], double* ori);

	private:
		Ui::GeoMeshRotateDialog* _ui{};
		GeometryWidget::GeoPointWidget* _baseWidget{};

		bool _selectFace{ false };
		bool _selectPoint{ false };

		QMultiHash<Geometry::GeometrySet*, int> _facesHash{};

		QList<TopoDS_Shape*> _selectFaces{};
	};


}

#endif