#ifndef DIALOGCREATECALCULATE_H
#define DIALOGCREATECALCULATE_H

#include "PostFunctionDialogBase.h"
#include "PostInterfaceAPI.h"

class QMenu;

namespace Ui {
class CreateCalculateDialog;
}

namespace Post {
	class POSTINTERFACEAPI CreateCalculateDialog : public PostFunctionDialogBase
	{
		Q_OBJECT

	public:
		explicit CreateCalculateDialog(PostTreeWidget* tree, QWidget *parent = nullptr);
		~CreateCalculateDialog();

	private:
		void init();
		void accept() override;
		void reject() override;
		void updateDisplayInterface() override;
		void setExpression(QString exp);

	private slots:
		void on_addPushButton_clicked();
		void on_minusPushButton_clicked();
		void on_multiplyPushButton_clicked();
		void on_dividedPushButton_clicked();
		void on_openParenPushButton_clicked();
		void on_closeParenPushButton_clicked();
		void on_iHatPushButton_clicked();
		void on_jHatPushButton_clicked();
		void on_kHatPushButton_clicked();
		void on_sinPushButton_clicked();
		void on_cosPushButton_clicked();
		void on_tanPushButton_clicked();
		void on_asinPushButton_clicked();
		void on_acosPushButton_clicked();
		void on_atanPushButton_clicked();
		void on_sinhPushButton_clicked();
		void on_coshPushButton_clicked();
		void on_tanhPushButton_clicked();
		void on_absPushButton_clicked();
		void on_sqrtPushButton_clicked();
		void on_signPushButton_clicked();
		void on_lnPushButton_clicked();
		void on_logPushButton_clicked();
		void on_ceilPushButton_clicked();
		void on_floorPushButton_clicked();
		void on_minPushButton_clicked();
		void on_maxPushButton_clicked();
		void on_superscriptPushButton_clicked();
		void on_expPushButton_clicked();
		void on_dotPushButton_clicked();
		void on_pointPushButton_clicked();
		void on_crossPushButton_clicked();
		void on_magPushButton_clicked();
		void on_normPushButton_clicked();
		void on_backPushButton_clicked();
		void on_clearPushButton_clicked();
		void on_expressionLineEdit_textChanged(QString text);
		void on_typeComboBox_currentIndexChanged(int index);

	private:
		QList<QString> _operationList{};
		QMenu* _vectorMenu{ nullptr };
		QMenu* _scalarMenu{ nullptr };
		bool _isPoint{ true };
		QList<QString> _scalarList{};
		QList<QString> _vectorList{};

	private:
		Ui::CreateCalculateDialog *_ui;
	};
}
#endif // DIALOGCREATECALCULATE_H
