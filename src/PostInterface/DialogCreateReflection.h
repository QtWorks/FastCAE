#ifndef DIALOGCREATEREFLECTION_H
#define DIALOGCREATEREFLECTION_H

#include "PostInterfaceAPI.h"
#include "PostFunctionDialogBase.h"

class QButtonGroup;

namespace Ui {
class CreateReflectionDialog;
}

namespace Post {
	enum ReflectionPlaneType {
		USE_XMIN = 0,
		USE_YMIN,
		USE_ZMIN,
		USE_XMAX,
		USE_YMAX,
		USE_ZMAX,
		USE_X,
		USE_Y,
		USE_Z
	};


	class POSTINTERFACEAPI CreateReflectionDialog : public PostFunctionDialogBase
	{
		Q_OBJECT

	public:
		explicit CreateReflectionDialog(PostTreeWidget* tree, QWidget *parent = nullptr);
		~CreateReflectionDialog();

	private:
		void init();
		void accept() override;
		void reject() override;
		void updateDisplayInterface() override;
		void getSelectedDataBound();

	private slots:
		void setReflectionPlane(int id,bool c);

	private:
		ReflectionPlaneType _type{ USE_XMIN };
		double _xRange[2]{ 0 };
		double _yRange[2]{ 0 };
		double _zRange[2]{ 0 };

	private:
		Ui::CreateReflectionDialog *_ui;
		QButtonGroup* _buttonGroup{ nullptr };
	};
}
#endif // DIALOGCREATEREFLECTION_H
