#ifndef DIALOGCREATESTREAMLINE_H
#define DIALOGCREATESTREAMLINE_H

#include "PostInterfaceAPI.h"
#include "PostFunctionDialogBase.h"

namespace Ui {
class CreateStreamLineDialog;
}

namespace Post {
	class LineWidget;

	class POSTINTERFACEAPI CreateStreamLineDialog : public PostFunctionDialogBase
	{
		Q_OBJECT

	public:
		explicit CreateStreamLineDialog(PostTreeWidget* tree, QWidget *parent = nullptr);
		~CreateStreamLineDialog();

	private:
		void init();
		void accept() override;
		void reject() override;
		void updateDisplayInterface() override;
		void showLineWidget();
		void getSelectedObjectsBound(double* start, double*  end);
		void updateVectorComboBox();

	private slots:
		void updateLineWidget(double* start, double* end);

		void on_lengthDoubleSpinBox_valueChanged(double v);
		void on_lengthHorizontalSlider_valueChanged(int v);

	private:
		double _length{ 0 };

	private:
		Ui::CreateStreamLineDialog *_ui;
		LineWidget* _lineWidget{ nullptr };

	};
}
#endif // DIALOGCREATESTREAMLINE_H
