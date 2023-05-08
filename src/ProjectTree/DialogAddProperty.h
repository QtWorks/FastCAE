#ifndef __DIALOGADDPROPERTY_H__
#define __DIALOGADDPROPERTY_H__

#include <QDialog>

namespace Ui
{
	class CreateEleProp;
}
namespace GUI
{
	class MainWindow;
}
namespace ModelData
{
	class ModelDataBaseExtend;
}

namespace ProjectTree
{
	class AddPropDialog : public QDialog
	{
	public:
		AddPropDialog(GUI::MainWindow* mw, ModelData::ModelDataBaseExtend* model);
		~AddPropDialog();

	private:
		void init();
		void accept() override;

	private:
		Ui::CreateEleProp* _ui{};

		GUI::MainWindow* _mainWindow{};
		ModelData::ModelDataBaseExtend* _model{};


	};
}


#endif // !__DIALOGADDPROPERTY_H__
