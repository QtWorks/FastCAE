#ifndef DIALOG_CREATEISO_H
#define DIALOG_CREATEISO_H

#include "PostFunctionDialogBase.h"
#include "PostInterfaceAPI.h"

namespace Ui {
class CreateISODialog;
}

namespace Post {
	class POSTINTERFACEAPI CreateISODialog : public PostFunctionDialogBase
	{
		Q_OBJECT

	public:
		explicit CreateISODialog(PostTreeWidget* tree, bool isoSurface, QWidget *parent = nullptr);
		~CreateISODialog();

	private:
		void init();
		void accept() override;
		void reject() override;
		void updateDisplayInterface() override;
		void updateVariableComboBox();

	private slots:
		void on_addPushButton_clicked();
		void on_removePushButton_clicked();
		void on_removeAllPushButton_clicked();
		void on_variableComboBox_currentIndexChanged(int index);

	private:
		double _range[2]{ 0 };
		bool _isSurface{ true };

	private:
		Ui::CreateISODialog *_ui;
	};
}
#endif // DIALOGCREATEISOSURFACE_H
