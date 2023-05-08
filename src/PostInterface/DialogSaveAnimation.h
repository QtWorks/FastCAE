#ifndef DIALOGSAVEANIMATION_H
#define DIALOGSAVEANIMATION_H

#include "PostInterfaceAPI.h"
#include <QDialog>

namespace Ui {
class SaveAnimationDialog;
}

namespace Post {
	class AnimationToolBar;

	class POSTINTERFACEAPI SaveAnimationDialog : public QDialog
	{
		Q_OBJECT

	public:
		explicit SaveAnimationDialog(AnimationToolBar* toolBar, QWidget *parent = nullptr);
		~SaveAnimationDialog();

		void getAnimationInfo(int& id, QString& file, int& fps);

	private:
		void init();
		void accept() override;
		void reject() override;

	private slots:
		void on_selectPushButton_clicked();

	private:
		QString _file;
		int _fps;
		int _id;

	private:
		Ui::SaveAnimationDialog *_ui;
		AnimationToolBar* _animation{ nullptr };
	};
}
#endif // DIALOGSAVEANIMATION_H
