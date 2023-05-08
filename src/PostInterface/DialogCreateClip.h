#ifndef DIALOGCREATECLIP_H
#define DIALOGCREATECLIP_H

#include "PostInterfaceAPI.h"
#include "PostFunctionDialogBase.h"

class vtkDataSet;

namespace Ui {
class CreateClipDialog;
}

namespace Post {
	class ShearPlaneWidget;

	class POSTINTERFACEAPI CreateClipDialog : public PostFunctionDialogBase
	{
		Q_OBJECT

	public:
		CreateClipDialog(PostTreeWidget* tree,bool isClip = true,QWidget *parent = nullptr);
		CreateClipDialog(PostTreeWidget* tree,RenderDataObject* obj, bool isClip = true,QWidget *parent = nullptr);
		~CreateClipDialog();

	private:
		void init();
		void initEidtInterface();
		void accept() override;
		void reject() override;
		void updateDisplayInterface() override;
		void showShearPlane();
		void getSelectedObjectsBound(double* bound);
		void blockDoubleSpinBoxSignals(bool b);

	private slots:
		void updatePlaneWidget(double* normal, double* origin);

		void on_xDoubleSpinBox_valueChanged(double x);
		void on_yDoubleSpinBox_valueChanged(double y);
		void on_zDoubleSpinBox_valueChanged(double z);

	private:
		bool _isClip{ true };
		bool _isEdit;

	private:
		Ui::CreateClipDialog *_ui;
		ShearPlaneWidget* _shearPlane{ nullptr };
		QList<vtkDataSet*> _seletedObjects{};		
	};
}
#endif // DIALOGCREATECLIP_H
