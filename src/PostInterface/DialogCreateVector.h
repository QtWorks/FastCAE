#ifndef CREATEVECTORDIALOG_H
#define CREATEVECTORDIALOG_H

#include "PostInterfaceAPI.h"
#include "PostFunctionDialogBase.h"

class vtkDataSet;

namespace Ui {
class CreateVectorDialog;
}

namespace Post {
// 	class PostTreeWidget;
// 	class RenderDataManager;
// 	class RenderWindowManager;
// 	class RenderDataObject;

	class POSTINTERFACEAPI CreateVectorDialog : public PostFunctionDialogBase
	{
		Q_OBJECT

	public:
		explicit CreateVectorDialog(PostTreeWidget* tree, QWidget *parent = nullptr);
		~CreateVectorDialog();

	private:
		void init();
		void accept() override;
		void reject() override;
		void updateDisplayInterface() override;
		void updateVectorComboBox();
		//void setSelectedObjectList();

// 	private slots:
// 		void setParentObject();

	private:
		Ui::CreateVectorDialog *_ui;
// 		PostTreeWidget* _tree{ nullptr };
// 		RenderDataManager* _dataManager{ nullptr };
// 		RenderWindowManager* _windowManager{ nullptr };
// 		RenderDataObject* _parentObject{ nullptr };
		QList<vtkDataSet*> _selectedObjects{};
	};
}
#endif // CREATEVECTORDIALOG_H
