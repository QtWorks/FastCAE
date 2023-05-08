#ifndef _PARACOLORBUTTON_H_
#define _PARACOLORBUTTON_H_

#include "SelfDefObjectAPI.h"
#include "SelfDefParaWidgetBase.h"
#include <QPushButton>
#include <QColor>

namespace GUI
{
	class MainWindow;
}

namespace DataProperty
{
	class ParameterBase;
	class ParameterColor;
}


namespace  SelfDefObj
{
	class SELFDEFINEOBJAPI ParaColorBuutton : public QPushButton, public SelfDefParaWidgetBase
	{
		Q_OBJECT

	public:
		ParaColorBuutton(GUI::MainWindow* mw, DataProperty::ParameterBase* data);
		~ParaColorBuutton() = default;


	private slots:
		void on_button_Clicked();
		void on_dataChanged();
		
	private:
		void  setButtonColor(QColor);
		QString generateCode()  override;

	private:
		DataProperty::ParameterColor*  _data{};


		QColor _color{};
		GUI::MainWindow* _mainWindow{};

	};
}

#endif