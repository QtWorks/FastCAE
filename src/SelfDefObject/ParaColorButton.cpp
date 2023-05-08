#include "ParaColorButton.h"
#include "DataProperty/ParameterColor.h"
#include "MainWindow/MainWindow.h"
#include <QColorDialog>
#include <QDebug>

namespace SelfDefObj
{
	ParaColorBuutton::ParaColorBuutton(GUI::MainWindow *mw, DataProperty::ParameterBase *data)
		: SelfDefParaWidgetBase(data), _mainWindow(mw)
	{
		connect(this, SIGNAL(clicked()), this, SLOT(on_button_Clicked()));
		connect(data, SIGNAL(dataChanged()), this, SLOT(on_dataChanged()));
		_data = dynamic_cast<DataProperty::ParameterColor *>(data);
		QColor c = _data->getColor();
		this->setButtonColor(c);

		_inited = true;
	}

	void ParaColorBuutton::on_button_Clicked()
	{

		QColor col = _data->getColor();
		QColorDialog dlg(_mainWindow);
		dlg.setWindowTitle(tr("Select a color"));
		dlg.setCurrentColor(col);
		if (dlg.exec() != QDialog::Accepted)
			return;
		_color = dlg.selectedColor();
		//		_color = QColorDialog::getColor(, _mainWindow,tr("Select a color"), QColorDialog::ShowAlphaChannel);
		if (col == _color)
			return;

		submitCode();
	}

	void ParaColorBuutton::on_dataChanged()
	{
		QColor c = _data->getColor();
		this->setButtonColor(c);
	}

	void ParaColorBuutton::setButtonColor(QColor c)
	{
		QString text;
		QString color;
		if (!c.isValid())
		{
			color = QString("QPushButton{background-color: rgb(255, 255, 255);}");
			text = "Not Valid";
		}
		else
			color = QString("QPushButton{background-color: rgb(%1, %2, %3);}").arg(c.red()).arg(c.green()).arg(c.blue());

		this->setText(text);
		this->setStyleSheet(color);
		// 		QPalette pal = this->palette();
		// 		pal.setColor(QPalette::Button, c);
		// 		this->setPalette(pal);
		// 		this->setAutoFillBackground(true);
		// 		this->setFlat(true);
	}

	QString ParaColorBuutton::generateCode()
	{
		QString va = QString("%1,%2,%3").arg(_color.red()).arg(_color.green()).arg(_color.blue());
		QString code = SelfDefParaWidgetBase::generateCode();
		code.replace("%Value%", va);
		return code;
	}

}
